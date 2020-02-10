#pragma once

#include <random>

namespace random
{

class Randomizer
{
public:
    explicit Randomizer(const std::uniform_int_distribution<int>& distribution);
    ~Randomizer() = default;

    void SetDistribution(const std::uniform_int_distribution<int>& distribution);
    std::uniform_int_distribution<int> GetDistribution() const;

    int GetRandomValue() const;

private:
    std::uniform_int_distribution<int> distribution_;
};

} // random