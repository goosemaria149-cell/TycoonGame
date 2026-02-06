#pragma once
#include "Building.h"

/// End-game producer that converts multiple inputs into diamonds.
class DiamondMine : public Building
{
public:
    DiamondMine();
    virtual ~DiamondMine() = default;

    virtual void UpdateEfficiency(float deltaTime) override;
    [[nodiscard]] virtual float CalculateProduction(float deltaTime) const override;
};
