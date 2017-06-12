/** \file challenge5.cpp
 *
 */

//
// Created by svalenti on 5/29/2017.
//

#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{

    default_random_engine dre;
    uniform_real_distribution<double> urd;
    dre.seed(1);

    int nr_triangles = 0;
    int nr_trials = 10'000'000;

    for ( int ix =0; ix < nr_trials; ++ix ) {

        vector<double> breaks = { urd(dre), 0.0 };

        if ( breaks[0] >= 0.5 )
            breaks[1] = breaks[0] * urd(dre);
        else
            breaks[1] = (1.0 - breaks[0]) * urd(dre) + breaks[0];

        sort(breaks.begin(), breaks.end());

        vector<double> sides = { breaks[0], breaks[1] - breaks[0], 1.0 - breaks[1] };

        if ( all_of( sides.begin(), sides.end(), [](double side) -> bool { return side < 0.5; } )) {
            nr_triangles += 1;
         }
    }

    cout << "Probability of triangle with long piece broken = "
         << static_cast<double>(nr_triangles)/static_cast<double>(nr_trials) << '\n';

    return 0;
}
