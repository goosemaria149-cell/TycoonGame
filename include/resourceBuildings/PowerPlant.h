#pragma once
#include "Building.h"

/// Produces energy from wood and stone.
class PowerPlant : public Building
{
public:
    PowerPlant();

    void UpdateEfficiency(float deltaTime) override;
    [[nodiscard]] float CalculateProduction(float deltaTime) const override;
};
