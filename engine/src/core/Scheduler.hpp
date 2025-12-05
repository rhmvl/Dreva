#pragma once
#include <entt/entt.hpp>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace kine
{

/**
 * @class Scheduler
 * @brief Manages game systems and executes them in dependency-sorted order.
 *
 * The Scheduler allows registering named systems (functions) and defining
 * ordering dependencies between them (“A must run before B”).
 * A topological sort is performed when needed, and the sorted systems are
 * executed every frame.
 */
class Scheduler
{
   public:
    /**
     * @brief Signature of a game system function.
     * @param registry The ECS registry
     * @param dt Delta time of the frame or fixed time step
     */
    using SystemFunc = std::function<void(entt::registry&, float)>;

    /**
     * @brief Registers a new system.
     * @param name Unique system name
     * @param func System function to execute
     * @return True if added
     */
    bool addSystem(std::string name, SystemFunc func);

    /**
     * @brief Declares that system @p before must execute before system @p after.
     *
     * Adds a directed dependency edge: before → after.
     */
    bool addDependency(const std::string& before, const std::string& after);

    /**
     * @brief Rebuilds the execution order by performing a topological sort.
     * @return False if a cycle is detected
     */
    bool rebuildOrder();

    /**
     * @brief Executes all systems once using variable delta time.
     */
    void update(entt::registry& reg, float dt);

    /**
     * @brief Executes fixed-step systems while accumulator allows it.
     */
    void fixedUpdate(entt::registry& reg, float& accumulator, float fixedDt);

   private:
    /**
     * @brief DFS helper for topological sorting.
     * @return False if a dependency cycle is detected
     */
    bool visit(const std::string& name);

    std::unordered_map<std::string, SystemFunc> systems;              ///< Registered systems
    std::unordered_map<std::string, std::vector<std::string>> edges;  ///< Dependencies

    std::vector<std::string> sorted;  ///< Sorted execution list

    std::unordered_map<std::string, bool> perm;  ///< Permanently visited in DFS
    std::unordered_map<std::string, bool> temp;  ///< Temporarily visited in DFS

    bool dirty = true;      ///< If true, ordering must be rebuilt
    bool hasCycle = false;  ///< Tracks cycle existence
};

}  // namespace kine
