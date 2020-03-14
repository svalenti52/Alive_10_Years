/** \file challenge7.cpp
 *
 */

// challenge7.cpp
// Created by svalenti on 4/28/2017.
//

#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

const double pi = M_PI;

int main(int argc, char** argv)
{

    default_random_engine dre(1);
    uniform_real_distribution<double> urd(0.0, 2.0 * pi);

    const int nr_trials = 10'000'000;

    double cumulative_value = 0.0;

    for (int ix = 0; ix<nr_trials; ++ix) {

        vector<double> angles = { urd(dre), urd(dre) };

        sort(angles.begin(), angles.end());

        if (angles[0]<pi && angles[1]>pi)
        {

            if (angles[0]<angles[1]-pi) continue;

            cumulative_value += 1.0;
        }
    }

    cout << "Probability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';

    return 0;
}
