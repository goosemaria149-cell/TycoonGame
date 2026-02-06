#pragma once
#include "Building.h"

/// Produces crystal and gold using energy and iron.
class CrystalMine : public Building
{
public:
    CrystalMine();

    void UpdateEfficiency(float deltaTime) override;
    [[nodiscard]] float CalculateProduction(float deltaTime) const override;
};
