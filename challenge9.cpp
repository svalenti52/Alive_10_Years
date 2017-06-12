/** \file challenge9.cpp
 *
 */

// challenge9.cpp
// Created by svalenti on 4/28/2017.
//

#include <iostream>
#include <random>
#include <complex>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{

    default_random_engine dre;
    uniform_real_distribution<double> urd;
    dre.seed(4);

    const int nr_trials = 10'000'000;
    //const int nr_trials = 1;
    const complex<double> center(0.5, 0.5);

    double cumulative_value = 0.0;

    for (int ix = 0; ix<nr_trials; ++ix) {

        complex<double> position (urd(dre), urd(dre));

        vector<double> distances_from_edge = { position.real(), position.imag(),
                                               1.0 - position.real(), 1.0 - position.imag() };

        auto min_distance_from_edge = min_element(distances_from_edge.begin(), distances_from_edge.end());

        double dist_from_center = sqrt ( norm( position - center ) );

        if ( dist_from_center < *min_distance_from_edge )
            cumulative_value += 1.0;
    }

    cout << "Probability closer to center of green = " << cumulative_value/static_cast<double>(nr_trials) << '\n';

    return 0;
}
