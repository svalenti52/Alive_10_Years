/** \file challenge6.cpp
 *
 */

// challenge6.cpp
// Created by svalenti on 4/28/2017.
//

#include <iostream>
#include <random>
#include <complex>

using namespace std;

int main(int argc, char** argv)
{

    default_random_engine dre;
    uniform_real_distribution<double> urd;
    uniform_real_distribution<double> ang(0.0, 2.0 * 3.1415926536);
    dre.seed(1);

    const int nr_trials = 10'000'000;

    double cumulative_value = 0.0;

    for (int ix = 0; ix<nr_trials; ++ix) {

        vector<complex<double>> darts = { polar(sqrt(urd(dre)), ang(dre)), polar(sqrt(urd(dre)), ang(dre))};

        double dist = sqrt(norm(darts[0] - darts[1]));

        if ( dist >= 1.0 )
            cumulative_value += 1.0;
    }

    cout << "Probability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';

    return 0;
}
