/** \file liars.cpp
 *
 */

// liars.cpp
// Created by svalenti on 4/28/2017.
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

    const int nr_trials = 10'000'000;

    const double liar_if_gt = 0.99;

    double msg_tx_correctly = 0.0;

    const int nr_people = 41;

    for (int ix = 0; ix<nr_trials; ++ix) {

        vector<double> people;

        for ( int jx = 0; jx < nr_people; ++jx )
            people.push_back(urd(dre));

        long nr_liars = count_if(people.begin(), people.end(),
                [liar_if_gt](double is_liar) -> bool { return is_liar > liar_if_gt; } );

        if ( nr_liars % 2 == 0 )
            msg_tx_correctly += 1.0;
    }

    cout << "Probability is = " << msg_tx_correctly/static_cast<double>(nr_trials) << '\n';

    return 0;
}
