/**
 * \file twins.cpp
 * \date 28-April-2017
 *
 * \brief 20 students divided into 5 groups of 4; probability that twins
 * in the class will be in the same group.
 *
 *
 */

#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{

    default_random_engine dre;
    uniform_real_distribution<double> urd;

    dre.seed(4);

    const int nr_trials = 10'000'000;

    double cumulative_value = 0.0;

    vector<int> students = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    for ( int ix = 0; ix < nr_trials; ++ix ) {

        random_shuffle(students.begin(), students.end());

        for ( int jx = 0; jx < 20; jx += 4 )
            if ( any_of(students.begin()+jx, students.begin()+jx+4, [](int i) {return i == 1;}) &&
                 any_of(students.begin()+jx, students.begin()+jx+4, [](int i) {return i == 2;}) ) {
                cumulative_value += 1.0;
                break;
            }
    }

    cout << "\nProbability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';

    return 0;
}
