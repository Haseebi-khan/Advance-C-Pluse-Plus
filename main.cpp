#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <random>
#include <algorithm>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>

double M_PI = 3.16;

// =============================================================================
// CORE DATA STRUCTURES
// =============================================================================

struct Point {
    double lat, lng;
    Point(double lat = 0, double lng = 0) : lat(lat), lng(lng) {}
    
    // Calculate Haversine distance in kilometers
    double distanceTo(const Point& other) const {
        const double R = 6371.0; // Earth's radius in km
        double dLat = (other.lat - lat) * M_PI / 180.0;
        double dLng = (other.lng - lng) * M_PI / 180.0;
        double a = sin(dLat/2) * sin(dLat/2) + 
                   cos(lat * M_PI / 180.0) * cos(other.lat * M_PI / 180.0) * 
                   sin(dLng/2) * sin(dLng/2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        return R * c;
    }
};

enum class DriverStatus { AVAILABLE, BUSY, OFFLINE };
enum class TripStatus { REQUESTED, DRIVER_ASSIGNED, DRIVER_ARRIVED, IN_PROGRESS, COMPLETED, CANCELLED };

struct Driver {
    int id;
    Point location;
    std::atomic<DriverStatus> status;
    std::string name;
    double rating;
    std::mutex driver_mutex;
    
    Driver(int id, Point loc, const std::string& name) 
        : id(id), location(loc), status(DriverStatus::AVAILABLE), name(name), rating(4.5) {}
    
    bool isAvailable() const {
        return status.load() == DriverStatus::AVAILABLE;
    }
    
    void setStatus(DriverStatus new_status) {
        status.store(new_status);
    }
};

struct TripRequest {
    int id;
    int passenger_id;
    Point pickup_location;
    Point destination;
    std::chrono::system_clock::time_point timestamp;
    TripStatus status;
    int assigned_driver_id;
    double estimated_fare;
    double surge_multiplier;
    
    TripRequest(int id, int passenger_id, Point pickup, Point dest)
        : id(id), passenger_id(passenger_id), pickup_location(pickup), 
          destination(dest), timestamp(std::chrono::system_clock::now()),
          status(TripStatus::REQUESTED), assigned_driver_id(-1), 
          estimated_fare(0.0), surge_multiplier(1.0) {}
};

// =============================================================================
// SPATIAL INDEX - QUADTREE IMPLEMENTATION
// =============================================================================

struct QuadTreeNode {
    Point center;
    double half_width, half_height;
    std::vector<std::shared_ptr<Driver>> drivers;
    std::unique_ptr<QuadTreeNode> nw, ne, sw, se;
    bool is_leaf;
    static const int MAX_CAPACITY = 10;
    
    QuadTreeNode(Point center, double hw, double hh) 
        : center(center), half_width(hw), half_height(hh), is_leaf(true) {}
    
    bool contains(const Point& point) const {
        return (point.lat >= center.lat - half_height && 
                point.lat <= center.lat + half_height &&
                point.lng >= center.lng - half_width && 
                point.lng <= center.lng + half_width);
    }
    
    void subdivide() {
        if (!is_leaf) return;
        
        double qw = half_width / 2.0;
        double qh = half_height / 2.0;
        
        nw = std::make_unique<QuadTreeNode>(Point(center.lat + qh, center.lng - qw), qw, qh);
        ne = std::make_unique<QuadTreeNode>(Point(center.lat + qh, center.lng + qw), qw, qh);
        sw = std::make_unique<QuadTreeNode>(Point(center.lat - qh, center.lng - qw), qw, qh);
        se = std::make_unique<QuadTreeNode>(Point(center.lat - qh, center.lng + qw), qw, qh);
        
        is_leaf = false;
    }
    
    bool insert(std::shared_ptr<Driver> driver) {
        if (!contains(driver->location)) return false;
        
        if (is_leaf) {
            if (drivers.size() < MAX_CAPACITY) {
                drivers.push_back(driver);
                return true;
            } else {
                subdivide();
                // Redistribute existing drivers
                auto temp_drivers = drivers;
                drivers.clear();
                for (auto& d : temp_drivers) {
                    if (!nw->insert(d) && !ne->insert(d) && !sw->insert(d) && !se->insert(d)) {
                        drivers.push_back(d); // Keep if can't fit in children
                    }
                }
                return insert(driver); // Try again
            }
        } else {
            return nw->insert(driver) || ne->insert(driver) || 
                   sw->insert(driver) || se->insert(driver);
        }
    }
    
    void queryRange(const Point& center, double radius, std::vector<std::shared_ptr<Driver>>& result) {
        // Simple bounding box check first
        if (center.lat - radius > this->center.lat + half_height ||
            center.lat + radius < this->center.lat - half_height ||
            center.lng - radius > this->center.lng + half_width ||
            center.lng + radius < this->center.lng - half_width) {
            return;
        }
        
        if (is_leaf) {
            for (auto& driver : drivers) {
                if (driver->isAvailable() && 
                    driver->location.distanceTo(center) <= radius) {
                    result.push_back(driver);
                }
            }
        } else {
            if (nw) nw->queryRange(center, radius, result);
            if (ne) ne->queryRange(center, radius, result);
            if (sw) sw->queryRange(center, radius, result);
            if (se) se->queryRange(center, radius, result);
        }
    }
};

class SpatialIndex {
private:
    std::unique_ptr<QuadTreeNode> root;
    std::mutex index_mutex;
    
public:
    SpatialIndex(Point center, double width, double height) {
        root = std::make_unique<QuadTreeNode>(center, width/2, height/2);
    }
    
    void addDriver(std::shared_ptr<Driver> driver) {
        std::lock_guard<std::mutex> lock(index_mutex);
        root->insert(driver);
    }
    
    std::vector<std::shared_ptr<Driver>> findNearbyDrivers(const Point& location, double radius_km) {
        std::lock_guard<std::mutex> lock(index_mutex);
        std::vector<std::shared_ptr<Driver>> result;
        root->queryRange(location, radius_km, result);
        
        // Sort by distance
        std::sort(result.begin(), result.end(), 
                 [&location](const auto& a, const auto& b) {
                     return a->location.distanceTo(location) < b->location.distanceTo(location);
                 });
        
        return result;
    }
    
    void rebuild(const std::vector<std::shared_ptr<Driver>>& all_drivers) {
        std::lock_guard<std::mutex> lock(index_mutex);
        // For production: implement incremental updates instead of full rebuild
        root = std::make_unique<QuadTreeNode>(Point(0, 0), 180, 90); // Global bounds
        for (auto& driver : all_drivers) {
            if (driver->isAvailable()) {
                root->insert(driver);
            }
        }
    }
};

// =============================================================================
// DISPATCH ENGINE - CORE MATCHING LOGIC
// =============================================================================

class DispatchEngine {
private:
    std::vector<std::shared_ptr<Driver>> drivers;
    std::unordered_map<int, std::shared_ptr<TripRequest>> active_requests;
    std::unique_ptr<SpatialIndex> spatial_index;
    std::mutex requests_mutex;
    std::atomic<int> next_request_id{1};
    
    // Pricing and surge logic
    std::unordered_map<std::string, int> area_demand; // Area -> demand count
    std::mutex pricing_mutex;
    
    double calculateBaseFare(const Point& pickup, const Point& destination) {
        double distance = pickup.distanceTo(destination);
        return 2.50 + (distance * 1.20); // Base fare + per km rate
    }
    
    double calculateSurgeMultiplier(const Point& location) {
        std::lock_guard<std::mutex> lock(pricing_mutex);
        // Simple grid-based surge calculation
        std::string area_key = std::to_string((int)(location.lat * 10)) + "," + 
                              std::to_string((int)(location.lng * 10));
        
        int demand = area_demand[area_key];
        if (demand > 20) return 2.5;
        if (demand > 10) return 1.8;
        if (demand > 5) return 1.4;
        return 1.0;
    }
    
    void updateAreaDemand(const Point& location, int delta) {
        std::lock_guard<std::mutex> lock(pricing_mutex);
        std::string area_key = std::to_string((int)(location.lat * 10)) + "," + 
                              std::to_string((int)(location.lng * 10));
        area_demand[area_key] += delta;
        if (area_demand[area_key] < 0) area_demand[area_key] = 0;
    }
    
public:
    DispatchEngine() {
        // Initialize spatial index with global bounds
        spatial_index = std::make_unique<SpatialIndex>(Point(0, 0), 360, 180);
    }
    
    void addDriver(std::shared_ptr<Driver> driver) {
        drivers.push_back(driver);
        spatial_index->addDriver(driver);
    }
    
    int requestRide(int passenger_id, Point pickup, Point destination) {
        auto request = std::make_shared<TripRequest>(
            next_request_id++, passenger_id, pickup, destination);
        
        // Calculate pricing
        request->estimated_fare = calculateBaseFare(pickup, destination);
        request->surge_multiplier = calculateSurgeMultiplier(pickup);
        request->estimated_fare *= request->surge_multiplier;
        
        updateAreaDemand(pickup, 1);
        
        {
            std::lock_guard<std::mutex> lock(requests_mutex);
            active_requests[request->id] = request;
        }
        
        // Try to dispatch immediately
        bool dispatched = dispatchRequest(request);
        
        if (!dispatched) {
            std::cout << "⏳ Request " << request->id << " queued for retry\n";
        }
        
        return request->id;
    }
    
    bool dispatchRequest(std::shared_ptr<TripRequest> request) {
        // Find nearby available drivers
        auto nearby_drivers = spatial_index->findNearbyDrivers(
            request->pickup_location, 5.0); // 5km radius
        
        for (auto& driver : nearby_drivers) {
            std::lock_guard<std::mutex> driver_lock(driver->driver_mutex);
            
            if (driver->isAvailable()) {
                // Assign driver
                driver->setStatus(DriverStatus::BUSY);
                request->assigned_driver_id = driver->id;
                request->status = TripStatus::DRIVER_ASSIGNED;
                
                double eta = driver->location.distanceTo(request->pickup_location) / 25.0 * 60; // 25km/h avg speed
                
                std::cout << "🚗 Driver " << driver->id << " (" << driver->name 
                         << ") assigned to request " << request->id 
                         << " | ETA: " << std::fixed << std::setprecision(1) << eta << " min"
                         << " | Fare: $" << std::setprecision(2) << request->estimated_fare;
                if (request->surge_multiplier > 1.0) {
                    std::cout << " (Surge " << request->surge_multiplier << "x)";
                }
                std::cout << "\n";
                
                return true;
            }
        }
        
        return false; // No available driver found
    }
    
    void completeTrip(int request_id) {
        std::lock_guard<std::mutex> lock(requests_mutex);
        
        if (active_requests.find(request_id) != active_requests.end()) {
            auto request = active_requests[request_id];
            request->status = TripStatus::COMPLETED;
            
            // Free up the driver
            for (auto& driver : drivers) {
                if (driver->id == request->assigned_driver_id) {
                    std::lock_guard<std::mutex> driver_lock(driver->driver_mutex);
                    driver->setStatus(DriverStatus::AVAILABLE);
                    // Simulate driver moving to destination
                    driver->location = request->destination;
                    break;
                }
            }
            
            updateAreaDemand(request->pickup_location, -1);
            active_requests.erase(request_id);
            
            std::cout << "✅ Trip " << request_id << " completed\n";
        }
    }
    
    void simulateDriverMovement() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-0.01, 0.01);
        
        for (auto& driver : drivers) {
            if (driver->isAvailable()) {
                driver->location.lat += dis(gen);
                driver->location.lng += dis(gen);
            }
        }
        
        // Rebuild spatial index periodically (in production, use incremental updates)
        spatial_index->rebuild(drivers);
    }
    
    void printSystemStats() {
        int available = 0, busy = 0, offline = 0;
        for (const auto& driver : drivers) {
            switch (driver->status.load()) {
                case DriverStatus::AVAILABLE: available++; break;
                case DriverStatus::BUSY: busy++; break;
                case DriverStatus::OFFLINE: offline++; break;
            }
        }
        
        std::lock_guard<std::mutex> lock(requests_mutex);
        std::cout << "📊 System Stats: Drivers [Available: " << available 
                  << ", Busy: " << busy << ", Offline: " << offline 
                  << "] | Active Requests: " << active_requests.size() << "\n";
    }
};

// =============================================================================
// SIMULATION AND PERFORMANCE TESTING
// =============================================================================

class SystemSimulator {
private:
    DispatchEngine dispatch_engine;
    std::vector<std::thread> worker_threads;
    std::atomic<bool> running{true};
    std::atomic<int> total_requests{0};
    std::atomic<int> successful_matches{0};
    std::chrono::high_resolution_clock::time_point start_time;
    
public:
    void initializeDrivers(int count) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> lat_dis(25.0, 25.5);  // Karachi bounds
        std::uniform_real_distribution<> lng_dis(67.0, 67.5);
        
        std::vector<std::string> driver_names = {
            "Ahmed", "Ali", "Hassan", "Omar", "Faisal", "Tariq", "Bilal", "Hamza",
            "Usman", "Imran", "Shahid", "Naveed", "Asif", "Kamran", "Wasim"
        };
        
        for (int i = 0; i < count; i++) {
            Point location(lat_dis(gen), lng_dis(gen));
            std::string name = driver_names[i % driver_names.size()] + std::to_string(i);
            auto driver = std::make_shared<Driver>(i, location, name);
            dispatch_engine.addDriver(driver);
        }
        
        std::cout << "🚗 Initialized " << count << " drivers\n";
    }
    
    void startRideRequestSimulation(int requests_per_second, int duration_seconds) {
        start_time = std::chrono::high_resolution_clock::now();
        
        worker_threads.emplace_back([this, requests_per_second, duration_seconds]() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> lat_dis(25.0, 25.5);
            std::uniform_real_distribution<> lng_dis(67.0, 67.5);
            std::uniform_int_distribution<> passenger_dis(1000, 9999);
            
            int interval_ms = 1000 / requests_per_second;
            auto end_time = std::chrono::steady_clock::now() + 
                           std::chrono::seconds(duration_seconds);
            
            while (std::chrono::steady_clock::now() < end_time && running) {
                Point pickup(lat_dis(gen), lng_dis(gen));
                Point destination(lat_dis(gen), lng_dis(gen));
                int passenger_id = passenger_dis(gen);
                
                dispatch_engine.requestRide(passenger_id, pickup, destination);
                total_requests++;
                
                std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
            }
        });
        
        // Trip completion simulator
        worker_threads.emplace_back([this, duration_seconds]() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> completion_delay(3, 15); // 3-15 seconds
            
            auto end_time = std::chrono::steady_clock::now() + 
                           std::chrono::seconds(duration_seconds + 10);
            
            int request_id = 1;
            while (std::chrono::steady_clock::now() < end_time && running) {
                std::this_thread::sleep_for(std::chrono::seconds(completion_delay(gen)));
                dispatch_engine.completeTrip(request_id++);
                successful_matches++;
            }
        });
        
        // Driver movement simulator
        worker_threads.emplace_back([this, duration_seconds]() {
            auto end_time = std::chrono::steady_clock::now() + 
                           std::chrono::seconds(duration_seconds);
            
            while (std::chrono::steady_clock::now() < end_time && running) {
                dispatch_engine.simulateDriverMovement();
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        });
        
        // Stats reporter
        worker_threads.emplace_back([this, duration_seconds]() {
            auto end_time = std::chrono::steady_clock::now() + 
                           std::chrono::seconds(duration_seconds);
            
            while (std::chrono::steady_clock::now() < end_time && running) {
                dispatch_engine.printSystemStats();
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        });
    }
    
    void stopSimulation() {
        running = false;
        for (auto& thread : worker_threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time).count();
        
        std::cout << "\n📈 SIMULATION RESULTS:\n";
        std::cout << "Duration: " << duration << " ms\n";
        std::cout << "Total Requests: " << total_requests.load() << "\n";
        std::cout << "Successful Matches: " << successful_matches.load() << "\n";
        std::cout << "Match Rate: " << std::fixed << std::setprecision(1) 
                  << (100.0 * successful_matches.load() / total_requests.load()) << "%\n";
        std::cout << "Average Latency: " << (duration / (double)total_requests.load()) 
                  << " ms per request\n";
    }
};

// =============================================================================
// MAIN APPLICATION
// =============================================================================

int main() {
    std::cout << "🚀 Ride-Hailing Dispatch System Starting...\n";
    std::cout << "=" << std::string(50, '=') << "\n\n";
    
    SystemSimulator simulator;
    
    // Initialize system with drivers
    simulator.initializeDrivers(1000);
    
    std::cout << "\n🎯 Starting high-load simulation...\n";
    std::cout << "Parameters: 50 requests/sec for 30 seconds\n\n";
    
    // Start simulation
    simulator.startRideRequestSimulation(50, 30);
    
    // Let simulation run
    std::this_thread::sleep_for(std::chrono::seconds(35));
    
    // Stop and show results
    simulator.stopSimulation();
    
    std::cout << "\n✅ Simulation completed successfully!\n";
    
    return 0;
}