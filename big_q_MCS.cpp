/**
 * \file big_q_MCS.cpp
 * \date 26-Jun-2017
 *
 * \brief From Random Unit Interval set, choose numerator N to be max, denominator D to be min
 * so N/D is largest from set.
 *
 * \details Probability that N/D is larger than parametrized number (threshold).
 */

#include <val/montecarlo/Chronology.h>
#include <val/montecarlo/MonteCarloSim_beta.h>
#include <algorithm>

using REAL_DISTRIBUTION = Distribution<double, double, std::uniform_real_distribution>;

int main(int argc, char** argv) {


    const double k = strtod(argv[1], nullptr); ///> Threshold value (k is variable name taken from text)
    const int N = strtol(argv[2], nullptr, 10);    ///> Number of values in unit interval to generate

    REAL_DISTRIBUTION distribution(0.0, 1.0, N);

    auto condition_met ( [k](REAL_DISTRIBUTION& random_Qvals,
            double& interim_count,
            DRE& dre) -> bool { ///> condition met?

        ///> interim_count defaults to 1.0, correct for this problem

        /**
         * minmax_element creates a pair composed of the minimum (first) and maximum
         * (second) values.
         */

        auto [ptr_min, ptr_max] = std::minmax_element(random_Qvals.events.begin(), random_Qvals.events.end());

        return ( *ptr_max / *ptr_min ) > k; ///> maximum / minimum > threshold ?
    } );

    /**
     * MonteCarloSimulation_beta is the beta version of the MonteCarloSimulation class.
     * It now parametrizes the y-axis (2nd template parameter) and has one Distribution.
     */
    MonteCarloSimulation<double, double, double, std::uniform_real_distribution> monteCarloSimulation(
            10'000'000,
            1,
            condition_met,
            distribution);

    StopWatch stopWatch;

    monteCarloSimulation.run();

    monteCarloSimulation.print_result();

    stopWatch.stop();
}
