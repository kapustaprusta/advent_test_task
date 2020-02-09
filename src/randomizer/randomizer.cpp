#include <QRandomGenerator>

#include "randomizer.h"

namespace random
{

Randomizer::Randomizer(const std::uniform_int_distribution<int>& distribution)
{
    distribution_ = distribution;
}

void Randomizer::SetDistribution(const std::uniform_int_distribution<int>& distribution)
{
    distribution_ = distribution;
}

std::uniform_int_distribution<int> Randomizer::GetDistribution()
{
    return distribution_;
}

int Randomizer::GetRandomValue()
{
    return distribution_(*QRandomGenerator::global());
}

} // random