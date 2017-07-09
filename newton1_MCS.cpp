/**
 * \file newton1_MCS.cpp
 * \date 26-Jun-2017
 *
 * \brief Dice Rolling Problem: Expected number of rolls till two consecutive sixes.
 */

#include <val/montecarlo/MonteCarloSim.h>
#include <val/montecarlo/Chronology.h>

using DIST = DistributionType;

int main() {

    auto condition_met = [](Distribution<int, DIST::UniformIntegral>& pd,
            Distribution<int, DIST::UniformIntegral>& sd,
            double& iv) -> bool { ///> condition met?

        int prior_value = pd.events[0];

        pd.reload_random_values();

        iv = 2.0;

        while ( !( pd.events[0] == 6 && pd.events[0] == prior_value ) ) {
            prior_value = pd.events[0];
            pd.reload_random_values();
            ++iv;
        }

        return true;
    };

    MonteCarloSimulation<int, int, DIST::UniformIntegral, DIST::UniformIntegral>
            monteCarloSimulation(
            10'000'000,
            condition_met,
            1, 6, 1, 1,
            1, 6, 1, 2
    );

    monteCarloSimulation.change_message("expected number of rolls is = ");

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();

}