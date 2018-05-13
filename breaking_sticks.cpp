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

    if (argc != 2)
    {
        cout << "Arguments Incorrect... Should be one argument\n";
        return 1;
    }
    const int nr_sticks = atoi(argv[1]);
    if (nr_sticks < 2)
    {
        cout << "Argument should be at least two...\n";
        return 2;
    }
    const int nr_breaks = nr_sticks - 1;

    const int nr_trials = 1'000'000;

    double cumulative_value = 0.0;

    for ( int ix = 0; ix < nr_trials; ++ix )
    {
        vector<double> invisible_marks = { urd(dre), urd(dre)};

        vector<double> breaks;
        for ( int jx = 0; jx < nr_breaks; ++jx )
            breaks.push_back(urd(dre));
        sort(breaks.begin(), breaks.end());

        bool MarksInSameStick = true;
        for ( auto a_break : breaks)
        {

            if ( none_of(invisible_marks.begin(), invisible_marks.end(),
                    [a_break](double im) -> bool { return im < a_break; } ))
                continue;

            else
            {
                MarksInSameStick = all_of(invisible_marks.begin(), invisible_marks.end(),
                    [a_break](double im) -> bool { return im < a_break; } );
                break;
            }
        }
        if ( MarksInSameStick )
            cumulative_value += 1.0;
    }

    cout << "Probability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';

    return 0;
}
