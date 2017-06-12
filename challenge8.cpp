/** \file challenge8.cpp
 *
 */

// challenge8.cpp
// Created by svalenti on 4/28/2017.
//

#include <iostream>
#include <random>
#include <val/util.h>

using namespace std;

int main(int argc, char** argv)
{
    if ( argc != 2 ) { cout << "usage: ./a <nr of teams>\n"; return 1; }
    int max = atoi(argv[1]);

    default_random_engine dre;
    uniform_int_distribution<int> uid(1,max);
    dre.seed(1);

    const int nr_trials = 1'000'000;

    double cumulative_value = 0.0;

    integral_histogram histogram(3, 300);

    for (int ix = 0; ix<nr_trials; ++ix) {

        vector<int> seasons_till_3 { uid(dre), uid(dre), uid(dre) };

        while ( true ) {

            if (seasons_till_3[seasons_till_3.size()-3]==seasons_till_3[seasons_till_3.size()-2] &&
                    seasons_till_3[seasons_till_3.size()-2]==seasons_till_3[seasons_till_3.size()-1]) {
                cumulative_value += static_cast<double>(seasons_till_3.size());
                break;
            }

            seasons_till_3.push_back(uid(dre));
        }
        if ( seasons_till_3.size() > 300 ) histogram.increment_bucket(300);
        else histogram.increment_bucket(seasons_till_3.size());
    }

    cout << "Expected number of games till 3 in a row = "
         << cumulative_value/static_cast<double>(nr_trials) << '\n';

    cout << "Approximate location of 50% probability at "
         << histogram.get_midpoint() << " seasons\n";

    return 0;
}
