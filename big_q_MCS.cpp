/**
 * \file big_q_MCS.cpp
 * \date 26-Jun-2017
 *
 * \brief From Random Unit Interval set, choose numerator N to be max, denominator D to be min
 * so N/D is largest from set.
 *
 * \detail Probability that N/D is larger than parametrized number.
 */

#include <val/util.h>
#include <val/montecarlo/MonteCarloSim.h>
#include <algorithm>

using DIST = DistributionType;

int main(int argc, char** argv) {


    const double k = atof(argv[1]);
    const int N = atoi(argv[2]);

    auto condition_met = [k](Distribution<double, DIST::UniformReal>& random_Qvals,
            Distribution<double, DIST::UniformReal>& sd,
            double& iv) -> bool { ///> condition met?

        ///> iv defaults to 1.0

        auto pr = std::minmax_element(random_Qvals.events.begin(), random_Qvals.events.end());

        return ( *pr.second / *pr.first ) > k;
    };

    MonteCarloSimulation<double, double, DIST::UniformReal, DIST::UniformReal> monteCarloSimulation(
            10'000'000,
            condition_met,
            0.0, 1.0, N, 4,
            0.0, 1.0, 0, 2);

    StopWatch stopWatch;

    monteCarloSimulation.run();

    monteCarloSimulation.print_result();

    stopWatch.stop();
}
