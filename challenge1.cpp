/** \file challenge1.cpp
 * \brief Out of the legitimate triangles formed by the random breaking of
 * a rod in two places, how many are obtuse?
 * \date 28-May-2017.
 */

#include <iostream>
#include <random>

using namespace std;

const double right_angle_radians = M_PI_2;

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
