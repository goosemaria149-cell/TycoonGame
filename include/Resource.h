#pragma once
#include <string>

/// Supported resource categories for the game economy.
enum class ResourceType
{
    MONEY,
    WOOD,
    STONE,
    IRON,
    GOLD,
    CRYSTAL,
    ENERGY,
    DIAMOND
};

/// Value object representing one resource type in player inventory.
class Resource
{
public:
    Resource() = default;
    Resource(ResourceType type, const std::string &name, float amount, float basePrice, bool isOwned);
    virtual ~Resource() = default;

    /// Returns the type of this resource.
    [[nodiscard]] ResourceType GetType() const { return m_type; }
    /// Returns the display name.
    [[nodiscard]] const std::string &GetName() const { return m_name; }
    /// Returns the stored amount.
    [[nodiscard]] float GetAmount() const { return m_amount; }
    /// Returns current market base price.
    [[nodiscard]] float GetBasePrice() const { return m_basePrice; }
    /// Returns whether this resource is currently owned.
    [[nodiscard]] bool IsOwned() const { return m_isOwned; }

    // Setters
    void SetAmount(float amount) { m_amount = amount; }
    void SetBasePrice(float price) { m_basePrice = price; }
    void SetOwned(bool owned) { m_isOwned = owned; }

    /// Updates the price based on volatility and resource-specific rules.
    virtual void UpdatePrice(float volatility);
    /// Production rate multiplier used by buildings/production recipes.
    [[nodiscard]] virtual float GetProductionRate() const { return 1.0f; }

protected:
    ResourceType m_type{ResourceType::MONEY};
    std::string m_name;
    float m_amount{0.0f};
    float m_basePrice{0.0f};
    bool m_isOwned{false};
};
