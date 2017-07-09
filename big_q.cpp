/**
 * \file big_q.cpp
 * \date 28-Apr-2017
 *
 *
 */

#include <iostream>
#include <random>
#include <algorithm>
#include <val/montecarlo/Chronology.h>

using namespace std;

int main(int argc, char** argv)
{

    default_random_engine dre;
    uniform_real_distribution<double> urd;
    const double k = atof(argv[1]);
    const int N = atoi(argv[2]);

    dre.seed(4);

    const int nr_trials = 10'000'000;

    double cumulative_value = 0.0;

    StopWatch stopWatch;

    for (int ix = 0; ix<nr_trials; ++ix) {
        vector<double> values;
        for ( int jx = 0; jx < N; ++jx )
            values.push_back(urd(dre));

        auto pr = minmax_element(values.begin(), values.end());

        auto ratio = *pr.second / *pr.first;

        if ( ratio > k )
            cumulative_value += 1.0;
    }

    cout << "Probability > " << k << " is = " << cumulative_value/static_cast<double>(nr_trials)
         << " out of " << N << " random values\n";

    stopWatch.stop();

    return 0;
}
