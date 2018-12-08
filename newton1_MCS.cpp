/**
 * \file newton1_MCS.cpp
 * \date 26-Jun-2017
 *
 * \brief Dice Rolling Problem: Expected number of rolls till two consecutive sixes.
 */

#include <val/montecarlo/MonteCarloSim_beta.h>
#include <val/montecarlo/Chronology.h>

using INT_X_INT_P_DISTRIBUTION = Distribution<int, int, std::uniform_int_distribution>;

int main() {

    const int nr_events = 1;

    INT_X_INT_P_DISTRIBUTION distribution(1, 6, nr_events);

    auto condition_met ( [](INT_X_INT_P_DISTRIBUTION& pd,
            double& iv,
            DRE& dre) -> bool { ///> condition met?

        int prior_value = pd.events[0];

        pd.reload_random_values(dre);

        iv = 2.0;

        while ( !( pd.events[0] == 6 && prior_value == 6 ) ) {
            prior_value = pd.events[0];
            pd.reload_random_values(dre);
            ++iv;
        }

        return true;
    } );

    MonteCarloSimulation<int, double, int, std::uniform_int_distribution>
            monteCarloSimulation(
            10'000'000,
            1,
            condition_met,
            distribution
    );

    monteCarloSimulation.change_message("expected number of rolls is = ");

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();

}