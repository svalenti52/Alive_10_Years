/**
 * \file square_dist_interior.cpp
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
    
        // interior points are (x,y) and (a,b)

        double x = urd(dre);
        double y = urd(dre);
        double a = urd(dre);
        double b = urd(dre);

        auto diff_squared1 = (x-a) * (x-a);
        auto diff_squared2 = (y-b) * (y-b);

        auto interim_value = sqrt( diff_squared1 + diff_squared2 );

        cumulative_value += interim_value;
    }

    cout << "Probability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';

    stopWatch.stop();

    return 0;
}
