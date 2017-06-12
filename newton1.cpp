/** \file newton1.cpp
 *
 */

//
// Created by svalenti on 4/28/2017.
//

#include <iostream>
#include <random>

using namespace std;

int main(int argc, char** argv)
{

    default_random_engine dre;
    uniform_int_distribution<int> urd(1, 6);

    dre.seed(0);

    const int nr_trials = 1'000'000;

    double cumulative_value = 0.0;

    for (int ix = 0; ix<nr_trials; ++ix) {

        int prior_value = urd(dre);  // roll 1
        int current_value = urd(dre); // roll 2
        int jx;

        for ( jx = 2; jx < 10'000'000; ++jx ) {
            if ( current_value == 6 && current_value == prior_value ) break;
            else {
                prior_value = current_value;
                current_value = urd(dre);
            }
        }

        cumulative_value += static_cast<double>(jx);
    }

    cout << "Expected number of rolls is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';

    return 0;
}
