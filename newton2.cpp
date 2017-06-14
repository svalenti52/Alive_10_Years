/** \file newton2.cpp
 * \brief What is probability of throwing 4 heads before 7 tails varying
 * the fairness of the coin?
 * \date 28-Apr-2017.
 */

#include <iostream>
#include <random>

using namespace std;

int main(int argc, char** argv)
{

    default_random_engine dre;
    uniform_real_distribution<double> urd;

    dre.seed(4);

    const int nr_trials = 10'000'000;

    double cumulative_value = 0.0;

    for (int ix = 0; ix<nr_trials; ++ix) {

        int nr_heads = 0;
        int nr_tails = 0;

        for ( int jx = 0; jx < 10; ++jx ) {
            ++(urd(dre) < 0.45 ? nr_heads : nr_tails); // 0.5 is a fair coin
            if ( nr_heads == 4 || nr_tails == 7 ) break;
        }

        if ( nr_heads == 4 )
            cumulative_value += 1.0;
    }

    cout << "Probability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';

    return 0;
}
