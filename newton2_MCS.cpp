/**
 * \file newton2_MCS.cpp
 * \date 26-Jun-2017
 *
 * \brief Coin Flipping Problem: Probability at least four heads before seven tails.
 * 
 * \details Ten flips are run on each turn when we assured that one of two
 * mutually exclusive events will occur:
 *      1) at least four heads will have shown out of the ten flips
 *      2) at least seven tails will have shown out of the ten flips
 */

#include <val/montecarlo/MonteCarloSim.h>
#include <algorithm>
#include <val/util.h>

int main() {

    auto condition_met = [](Distribution<bool, DistributionType::BernoulliIntegral>& pd,
            Distribution<int, DistributionType::UniformIntegral>& sd,
            double& iv) {

        return std::count(pd.events.begin(), pd.events.end(), true) >= 4;
    };

    MonteCarloSimulation<bool, int, DistributionType::BernoulliIntegral, DistributionType::UniformIntegral>
            monteCarloSimulation(
            10'000'000,
            condition_met,
            1, 2, 10, 1, ///> for the Bernoulli Distribution use first two parameters as Q and D to form Q/D
            0, 1, 0, 2   ///> continued, this Q/D should give a probability that is used as an input for
                         ///> for the distribution
    );

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();
}
