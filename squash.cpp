//
// Created by svalenti on 5/25/2017.
//

// squash.cpp

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

const int dimension = 10;

double ps_probability(Matrix<double, dimension, dimension>& ps,
        Matrix<double, dimension, dimension>& qs, int ix, int jx) {
    return 2.0/3.0 * ps(ix-1, jx) + 1.0/3.0 * qs(ix, jx-1);
}

double qs_probability(Matrix<double, dimension, dimension>& ps,
        Matrix<double, dimension, dimension>& qs, int ix, int jx) {
    return 1.0/2.0 * (ps(ix, jx) + qs(ix, jx-1));
}

int main(int argc, char** argv)
{
    using namespace std;

    Matrix<double, dimension, dimension> ps_matrix;
    Matrix<double, dimension, dimension> qs_matrix;

    for ( int ix=1; ix < dimension; ++ix ) {
        ps_matrix(ix, 0) = 0.0;
        ps_matrix(0, ix) = 1.0;
        qs_matrix(ix, 0) = 0.0;
        qs_matrix(0, ix) = 1.0;
        ps_matrix(0, 0) = 0.0;
        qs_matrix(0, 0) = 0.0;
    }

    for ( int jx = 1; jx < dimension; ++jx ) {
        ps_matrix(jx, 1) = pow(2.0/3.0, jx);
        qs_matrix(jx, 1) = ps_matrix(jx, 1) / 2.0;
        qs_matrix(1, jx) = 1.0 - ps_matrix(jx, 1);
        ps_matrix(1, jx) = 1.0 - qs_matrix(jx, 1);
    }

    for ( int ix = 2; ix < dimension; ++ix )
        for ( int jx = 2; jx < dimension; ++jx ) {
            ps_matrix(ix, jx) = ps_probability(ps_matrix, qs_matrix, ix, jx);
            qs_matrix(ix, jx) = qs_probability(ps_matrix, qs_matrix, ix, jx);
        }

    cout << ps_matrix << "\n\n";

    cout << qs_matrix << "\n\n";

    cout << "probability of server winning at beginning of game = " << ps_matrix(9,9) << '\n';

    cout << "probability of non-server winning at beginning of game = " << qs_matrix(9,9) << '\n';

    return 0;
}
