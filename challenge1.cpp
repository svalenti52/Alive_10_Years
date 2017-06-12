/** \file challenge1.cpp
 *
 */

// challenge1.cpp
// Created by svalenti on 4/28/2017.
//

#include <iostream>
#include <random>

using namespace std;

const double right_angle_radians = 3.1415926536 / 2.0;

int main(int argc, char** argv)
{

    default_random_engine dre;
    uniform_real_distribution<double> urd;
    dre.seed(1);

    const int nr_trials = 10'000'000;
    int nr_triangles = 0;

    double nr_obtuse_triangles = 0.0;

    while ( nr_triangles < nr_trials ) {

        double side_1 = urd(dre);
        double side_2 = urd(dre);

        if ( side_1 + side_2 > 1.0 ) {
            ++nr_triangles;
            if ( acos( (side_1*side_1 + side_2 * side_2 - 1.0) /
                    ( 2.0 * side_1 * side_2 ) ) > right_angle_radians )
                nr_obtuse_triangles += 1.0;
        }
    }

    cout << "Probability is = " << nr_obtuse_triangles/static_cast<double>(nr_trials) << '\n';

    return 0;
}
