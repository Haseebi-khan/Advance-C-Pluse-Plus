#include <iostream>
#include <string>
#include <map>

using namespace std;

class ResourcesManager {
public:
    // Provide a single global access point
    static ResourcesManager& getInstance() {
        static ResourcesManager instance; // created once, reused
        return instance;
    }

    // Delete copy constructor & assignment -> non-copyable
    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;

    // Example function: load a resource
    void loadResource(const string& name, const string& path) {
        resources[name] = path;  // fake loading
        cout << "Loaded: " << name << " from " << path << "\n";
    }

    string getResource(const string& name) {
        return resources[name];
    }

private:
    // Private constructor -> nobody can create instance outside
    ResourcesManager() {
        cout << "ResourcesManager created\n";
    }

    map<string, string> resources;
};

int main() {
    auto& rm = ResourcesManager::getInstance();

    rm.loadResource("texture1", "assets/texture1.png");
    rm.loadResource("sound1", "assets/sound1.wav");

    cout << "Texture1 path: " << rm.getResource("texture1") << "\n";

    return 0;
}


