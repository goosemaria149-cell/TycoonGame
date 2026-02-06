#pragma once

#include <algorithm>
#include <random>

namespace RandomUtil
{
inline bool RollChance(float chance)
{
    const float boundedChance = std::clamp(chance, 0.0f, 1.0f);
    static thread_local std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(rng) < boundedChance;
}
} // namespace RandomUtil
