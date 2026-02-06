#pragma once
#include "Building.h"

/// Reputation-support building with no direct output.
class ResearchLab : public Building
{
public:
    ResearchLab();

    void UpdateEfficiency(float deltaTime) override;
    [[nodiscard]] float CalculateProduction(float deltaTime) const override;
};
