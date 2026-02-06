#include "Resource.h"
#include <algorithm>
#include <random>

namespace
{
constexpr float kGoldMinPrice = 100.0f;
constexpr float kGoldMaxPrice = 500.0f;
constexpr float kDiamondMinPrice = 400.0f;
constexpr float kDiamondMaxPrice = 1000.0f;

[[nodiscard]] float NextRandomChange(float minValue, float maxValue)
{
    static thread_local std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<float> dist(minValue, maxValue);
    return dist(rng);
}
} // namespace

Resource::Resource(ResourceType type, const std::string &name, float amount, float basePrice, bool isOwned)
    : m_type(type), m_name(name), m_amount(amount), m_basePrice(basePrice), m_isOwned(isOwned)
{
}

void Resource::UpdatePrice(float volatility)
{
    if (m_type == ResourceType::GOLD)
    {
        const float priceChange = NextRandomChange(-0.05f, 0.05f);
        float newPrice = m_basePrice * (1.0f + priceChange);
        m_basePrice = std::clamp(newPrice, kGoldMinPrice, kGoldMaxPrice);
    }
    else if (m_type == ResourceType::DIAMOND)
    {
        const float priceChange = NextRandomChange(-0.03f, 0.03f);
        float newPrice = m_basePrice * (1.0f + priceChange);
        m_basePrice = std::clamp(newPrice, kDiamondMinPrice, kDiamondMaxPrice);
    }
    else
    {
        const float priceChange = NextRandomChange(-volatility, volatility);
        float newPrice = m_basePrice * (1.0f + priceChange);

        switch (m_type)
        {
        case ResourceType::WOOD:
            m_basePrice = std::clamp(newPrice, 1.0f, 6.85f);
            break;
        case ResourceType::STONE:
            m_basePrice = std::clamp(newPrice, 4.0f, 12.0f);
            break;
        case ResourceType::IRON:
            m_basePrice = std::clamp(newPrice, 5.0f, 39.0f);
            break;
        case ResourceType::CRYSTAL:
            m_basePrice = std::clamp(newPrice, 50.0f, 200.0f);
            break;
        case ResourceType::ENERGY:
            m_basePrice = std::clamp(newPrice, 10.0f, 40.0f);
            break;
        default:
            m_basePrice = std::max(1.0f, newPrice);
            break;
        }
    }
}
