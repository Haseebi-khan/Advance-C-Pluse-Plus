#include <iostream>
#include <memory>
#include <map>
#include <string>

using namespace std;

class ResourcesManager {
public:
    ResourcesManager() {
        cout << "ResourcesManager created\n";
    }

    void loadResource(const string& name, const string& path) {
        resources[name] = path;
        cout << "Loaded: " << name << " from " << path << "\n";
    }

    string getResource(const string& name) {
        return resources[name];
    }

    // Still prevent copying
    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;

private:
    map<string, string> resources;
};

int main() {
    // Central ownership
    auto manager = make_unique<ResourcesManager>();

    manager->loadResource("texture1", "assets/texture1.png");
    manager->loadResource("sound1", "assets/sound1.wav");

    cout << "Texture1 path: " << manager->getResource("texture1") << "\n";
    return 0;
}
