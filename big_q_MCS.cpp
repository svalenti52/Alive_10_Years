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
#include <val/montecarlo/MonteCarloSim.h>
#include <algorithm>

using DIST = DistributionType;

int main(int argc, char** argv) {


    const double k = atof(argv[1]); ///> Threshold value (k is variable name taken from text)
    const int N = atoi(argv[2]);    ///> Number of values in unit interval to generate

    Distribution<double, DIST::UniformReal> distribution(0.0, 1.0, N);

    auto condition_met = [k](Distribution<double, DIST::UniformReal>& random_Qvals,
            double& interim_count) -> bool { ///> condition met?

        ///> interim_count defaults to 1.0, correct for this problem

        /**
         * minmax_element creates a pair composed of the minimum (first) and maximum
         * (second) values.
         */
        auto pr = std::minmax_element(random_Qvals.events.begin(), random_Qvals.events.end());

        return ( *pr.second / *pr.first ) > k; ///> maximum / minimum > threshold ?
    };

    /**
     * MonteCarloSimulation_alpha is the alpha version of the MonteCarloSimulation class.
     * It now parametrizes the y-axis (2nd template parameter) and has one Distribution.
     */
    MonteCarloSimulation_alpha<double, double, DIST::UniformReal> monteCarloSimulation(
            10'000'000,
            condition_met,
            distribution);

    StopWatch stopWatch;

    monteCarloSimulation.run();

    monteCarloSimulation.print_result();

    stopWatch.stop();
}
