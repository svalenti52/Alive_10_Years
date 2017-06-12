/** \file ping_pong.cpp
 *
 */

//
// Created by svalenti on 5/24/2017.
//

// ping_pong.cpp

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

double probability(Matrix<double, 12, 12>& m, int ix, int jx, double prob) {
    return prob * m(ix-1, jx) + (1.0 - prob) * m(ix, jx-1);
}

int main(int argc, char** argv)
{
    using namespace std;

    double prob = atof(argv[1]) / 100.0;

    cout << prob << '\n' << flush;

    Matrix<double, 12, 12> matrix;

    matrix(0,0) = 0.0;
    for ( int ix=1; ix < 12; ++ix ) {
        matrix(ix, 0) = 0.0;
        matrix(0, ix) = 1.0;
    }

    for ( int ix = 1; ix < 12; ++ix )
        for ( int jx = 1; jx < 12; ++jx )
            matrix(ix, jx) = probability(matrix, ix, jx, prob);

    cout << matrix << '\n';

    return 0;
}
