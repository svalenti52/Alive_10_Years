/**
 * \file square_dist_opposite.cpp
 * \brief
 *
 */

#include <iostream>
#include <random>
#include <val/montecarlo/Chronology.h>

using namespace std;

int main(int argc, char** argv)
{

    default_random_engine dre;
    uniform_real_distribution<double> urd;
    dre.seed(1);

    const int nr_trials = 10'000'000;

    double cumulative_value = 0.0;

    StopWatch stopWatch;

    for (int ix = 0; ix<nr_trials; ++ix) {

        double x = urd(dre);
        double y = urd(dre);

        auto diff_squared = (x-y) * (x-y);

        double interim_value = sqrt( 1 + diff_squared );

        cumulative_value += interim_value;
    }

    cout << "Probability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';

    stopWatch.stop();

    return 0;
}
