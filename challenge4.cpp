/** \file challenge4.cpp
 *
 */

//
// Created by svalenti on 5/29/2017.
//

#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

const double right_angle_radians = M_PI_2;

int main(int argc, char** argv)
{

    default_random_engine dre;
    uniform_real_distribution<double> urd;
    dre.seed(4);

    int nr_triangles = 0;
    int nr_triangles_bound = 1'000'000;
    double nr_obtuse_triangles = 0.0;

    while ( nr_triangles < nr_triangles_bound ) {
        vector<double> breaks = { urd(dre), urd(dre)};
        sort(breaks.begin(), breaks.end());
        vector<double> sides = { breaks[0], breaks[1] - breaks[0], 1.0 - breaks[1] };
        if ( all_of( sides.begin(), sides.end(), [](double side) -> bool { return side < 0.5; } )) {
            nr_triangles += 1;
            sort(sides.begin(), sides.end());
            if ( acos( (sides[0]*sides[0] + sides[1] * sides[1] - sides[2] * sides[2]) /
                    ( 2.0 * sides[0] * sides[1] ) ) > right_angle_radians )
                nr_obtuse_triangles += 1.0;
        }
    }

    cout << "Probability is = " << nr_obtuse_triangles/static_cast<double>(nr_triangles) << '\n';

    return 0;
}
