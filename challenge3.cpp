/** \file challenge3.cpp
 * \brief What is the probability of a rod, with two random breaks in it,
 * having all it sides less than half the original length?
 * \date 28-May-2017.
 */

#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{

    default_random_engine dre;
    uniform_real_distribution<double> urd;
    dre.seed(1);

    const int nr_trials = 10'000'000;

    double cumulative_value = 0.0;

    for (int ix = 0; ix<nr_trials; ++ix) {
        vector<double> breaks = { urd(dre), urd(dre)};
        sort(breaks.begin(), breaks.end());
        vector<double> sides = { breaks[0], breaks[1] - breaks[0], 1.0 - breaks[1] };
        if ( all_of( sides.begin(), sides.end(), [](double side) -> bool { return side < 0.5; } ))
            cumulative_value += 1.0;
    }

    cout << "Probability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';

    return 0;
}
