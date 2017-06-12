/** \file breaking_sticks.cpp
 *
 */

// breaking_sticks.cpp
// Created by svalenti on 4/28/2017.
//

#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {

    default_random_engine dre;
    uniform_real_distribution<double> urd;
    dre.seed(2);

    const int nr_sticks = atoi(argv[1]);
    const int nr_breaks = nr_sticks - 1;

    const int nr_trials = 1'000'000;

    double cumulative_value = 0.0;

    for ( int ix = 0; ix < nr_trials; ++ix ) {

        vector<double> invis_marks = { urd(dre), urd(dre)};

        vector<double> breaks;
        for ( int jx = 0; jx < nr_breaks; ++jx )
            breaks.push_back(urd(dre));
        breaks.push_back(0.0);
        breaks.push_back(1.0);
        sort(breaks.begin(), breaks.end());

        for ( int jx = 1; jx < breaks.size(); ++jx) {

            if ( all_of(invis_marks.begin(), invis_marks.end(),
                    [breaks, jx](double im) -> bool { return im < breaks[jx]; }
            )) {
                cumulative_value += 1.0;
                break;
            }

            else if ( none_of(invis_marks.begin(), invis_marks.end(),
                    [breaks, jx](double im) -> bool { return im < breaks[jx]; }
                ))
                continue;

            else break;
        }
    }

    cout << "Probability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';

    return 0;
}
