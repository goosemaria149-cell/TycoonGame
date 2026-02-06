#pragma once
#include "Building.h"
#include "Production.h"
#include <memory>
#include <vector>

/// Factory for constructing concrete building and production templates.
class BuildingFactory
{
public:
    /// Creates a building template for the given type.
    [[nodiscard]] static std::unique_ptr<Building> CreateBuilding(BuildingType type);
    /// Returns all supported building types.
    [[nodiscard]] static std::vector<BuildingType> GetAvailableBuildingTypes();

    /// Creates a production template for the given type.
    [[nodiscard]] static std::unique_ptr<Production> CreateProduction(ProductionType type);
    /// Returns all supported production types.
    [[nodiscard]] static std::vector<ProductionType> GetAvailableProductionTypes();
};
