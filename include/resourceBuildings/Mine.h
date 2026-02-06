#pragma once
#include "Building.h"

/// Converts energy into stone and iron.
class Mine : public Building
{
public:
    Mine();

    void UpdateEfficiency(float deltaTime) override;
    [[nodiscard]] float CalculateProduction(float deltaTime) const override;
};
