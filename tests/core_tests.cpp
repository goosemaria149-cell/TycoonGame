#include <catch2/catch_test_macros.hpp>

#include "Building.h"
#include "BuildingFactory.h"
#include "GameConstants.h"
#include "Production.h"
#include "Resource.h"
#include "ResourceManager.h"

namespace
{
void ResetResource(ResourceType type)
{
    auto &rm = ResourceManager::Instance();
    const float existing = rm.Get(type);
    if (existing > 0.0f)
    {
        const bool consumed = rm.Consume(type, existing);
        (void)consumed;
    }
}
} // namespace

TEST_CASE("Building factory creates all known building types")
{
    for (const auto type : BuildingFactory::GetAvailableBuildingTypes())
    {
        auto building = BuildingFactory::CreateBuilding(type);
        REQUIRE(building != nullptr);
        CHECK(building->GetType() == type);
    }
}

TEST_CASE("Production factory creates all known production types")
{
    for (const auto type : BuildingFactory::GetAvailableProductionTypes())
    {
        auto production = BuildingFactory::CreateProduction(type);
        REQUIRE(production != nullptr);
        CHECK(production->GetType() == type);
        CHECK_FALSE(production->IsInvested());
    }
}

TEST_CASE("Building upgrades respect max level")
{
    auto building = BuildingFactory::CreateBuilding(BuildingType::WOODCUTTER);
    REQUIRE(building != nullptr);

    for (int i = 1; i < Building::MAX_LEVEL; ++i)
    {
        CHECK(building->Upgrade());
    }
    CHECK(building->GetLevel() == Building::MAX_LEVEL);
    CHECK_FALSE(building->Upgrade());
}

TEST_CASE("Resource manager add and consume")
{
    auto &rm = ResourceManager::Instance();
    ResetResource(ResourceType::WOOD);

    rm.Add(ResourceType::WOOD, 10.0f);
    CHECK(rm.Get(ResourceType::WOOD) == 10.0f);
    CHECK(rm.Consume(ResourceType::WOOD, 3.5f));
    CHECK(rm.Get(ResourceType::WOOD) == 6.5f);
    CHECK_FALSE(rm.Consume(ResourceType::WOOD, 7.0f));
}

TEST_CASE("Resource price updates remain within configured bounds")
{
    Resource wood(ResourceType::WOOD, "Wood", 0.0f, GameConstants::WOOD_BASE_PRICE, false);
    for (int i = 0; i < 250; ++i)
    {
        wood.UpdatePrice(GameConstants::PRICE_VOLATILITY);
        CHECK(wood.GetBasePrice() >= 1.0f);
        CHECK(wood.GetBasePrice() <= 6.85f);
    }

    Resource gold(ResourceType::GOLD, "Gold", 0.0f, GameConstants::GOLD_BASE_PRICE, false);
    for (int i = 0; i < 250; ++i)
    {
        gold.UpdatePrice(GameConstants::PRICE_VOLATILITY);
        CHECK(gold.GetBasePrice() >= 100.0f);
        CHECK(gold.GetBasePrice() <= 500.0f);
    }

    Resource diamond(ResourceType::DIAMOND, "Diamond", 0.0f, GameConstants::DIAMOND_BASE_PRICE, false);
    for (int i = 0; i < 250; ++i)
    {
        diamond.UpdatePrice(GameConstants::PRICE_VOLATILITY);
        CHECK(diamond.GetBasePrice() >= 400.0f);
        CHECK(diamond.GetBasePrice() <= 1000.0f);
    }
}
