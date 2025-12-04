#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include <entt/entt.hpp>

namespace dreva::engine {

class Scheduler {
public:
    using SystemFunc = std::function<void(entt::registry&, float)>;

    bool addSystem(std::string name, SystemFunc func);
    bool addDependency(const std::string& before, const std::string& after);

    // Returns false when a cyclic dependency exists
    bool rebuildOrder();

    void update(entt::registry& reg, float dt);
    void fixedUpdate(entt::registry& reg, float& accumulator, float fixedDt);

private:
    bool visit(const std::string& name);

    std::unordered_map<std::string, SystemFunc> systems;
    std::unordered_map<std::string, std::vector<std::string>> edges;

    std::vector<std::string> sorted;

    std::unordered_map<std::string, bool> perm;
    std::unordered_map<std::string, bool> temp;

    bool dirty = true;
    bool hasCycle = false;
};

}
