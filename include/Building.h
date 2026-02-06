#pragma once
#include <string>
#include <vector>
#include "Resource.h"

/// Buildable structures available in the game.
enum class BuildingType
{
    WOODCUTTER,
    MINE,
    CRYSTAL_MINE,
    POWER_PLANT,
    RESEARCH_LAB,
    DIAMOND_MINE
};

class Building
{
public:
    Building(BuildingType type,
             const std::string &name,
             float cost,
             float baseProductionRate,
             const std::vector<Resource> &inputResources,
             const std::vector<Resource> &outputResources,
             float maintenanceCost,
             float upgradeCost,
             int requiredReputation = 0);

    virtual ~Building() = default;

    /// Returns building type.
    [[nodiscard]] BuildingType GetType() const { return m_type; }
    /// Returns display name.
    [[nodiscard]] const std::string &GetName() const { return m_name; }
    /// Returns purchase cost.
    [[nodiscard]] float GetCost() const { return m_cost; }
    /// Returns base units produced per second at 100% efficiency.
    [[nodiscard]] float GetBaseProductionRate() const { return m_baseProductionRate; }
    /// Returns resource inputs consumed for production.
    [[nodiscard]] const std::vector<Resource> &GetInputResources() const { return m_inputResources; }
    /// Returns resource outputs produced.
    [[nodiscard]] const std::vector<Resource> &GetOutputResources() const { return m_outputResources; }
    /// Returns operational state.
    [[nodiscard]] bool IsOperational() const { return m_isOperational; }
    /// Returns ownership state.
    [[nodiscard]] bool IsOwned() const { return m_isOwned; }
    /// Returns current production efficiency in [0, 1].
    [[nodiscard]] float GetEfficiency() const { return m_efficiency; }
    /// Returns current building level.
    [[nodiscard]] int GetLevel() const { return m_level; }
    /// Returns maintenance cost per tick.
    [[nodiscard]] float GetMaintenanceCost() const { return m_maintenanceCost; }
    /// Returns current upgrade cost.
    [[nodiscard]] float GetUpgradeCost() const { return m_upgradeCost; }
    /// Returns required reputation to purchase.
    [[nodiscard]] int GetRequiredReputation() const { return m_requiredReputation; }

    // Setters
    void SetOperational(bool operational) { m_isOperational = operational; }
    void SetOwned(bool owned) { m_isOwned = owned; }
    void SetEfficiency(float efficiency) { m_efficiency = efficiency; }
    void SetLevel(int level) { m_level = level; }
    void SetMaintenanceCost(float cost) { m_maintenanceCost = cost; }
    void SetUpgradeCost(float cost) { m_upgradeCost = cost; }
    void SetRequiredReputation(int reputation) { m_requiredReputation = reputation; }
    void SetBaseProductionRate(float rate) { m_baseProductionRate = rate; }

    /// Updates operational state and performs production/consumption.
    virtual void Update(float deltaTime);
    /// Upgrades this building when possible.
    [[nodiscard]] virtual bool Upgrade();
    /// Recomputes current efficiency.
    virtual void UpdateEfficiency(float deltaTime);
    /// Returns production amount for this update interval.
    [[nodiscard]] virtual float CalculateProduction(float deltaTime) const;

    // how fast we lose efficiency when fuel == 0 (per second)
    static constexpr float EFFICIENCY_DECAY_RATE = 0.03f; // 3% per second

    // globally throttle fuel consumption
    static constexpr float FUEL_CONSUMPTION_FACTOR = 0.1f; // use only .1 the resources

    // shared building progression cap
    static constexpr int MAX_LEVEL = 5;

protected:
    BuildingType m_type;
    std::string m_name;
    float m_cost;
    float m_baseProductionRate;
    std::vector<Resource> m_inputResources;
    std::vector<Resource> m_outputResources;
    bool m_isOperational;
    bool m_isOwned;
    float m_efficiency;
    int m_level;
    float m_maintenanceCost;
    float m_upgradeCost;
    int m_requiredReputation;
};
