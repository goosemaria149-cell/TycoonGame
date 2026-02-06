#pragma once
#include "Building.h"

/// Produces wood without fuel input.
class Woodcutter : public Building
{
public:
    Woodcutter();

    void UpdateEfficiency(float deltaTime) override;
    [[nodiscard]] float CalculateProduction(float deltaTime) const override;
};
