/** \file square_dist_adjacent.cpp
 * \brief
 *
 */

#include <iostream>
#include <random>
#include <val/util.h>

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

        double interim_value = sqrt( x*x + y*y );

        cumulative_value += interim_value;
    }

    cout << "Probability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';

    stopWatch.stop();

    return 0;
}
