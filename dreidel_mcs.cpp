/**
 * \file dreidel_mcs.cpp
 * \date 2-Sep-2017
 *
 */

#include <sstream>
#include <iostream>
#include <val/montecarlo/MonteCarloSim_beta.h>

int main(int argc, char **argv)
{
    using namespace std;

    int nr_players = 3;
    if ( argc >= 2 ) {
        istringstream i(argv[1]);
        i >> nr_players;
    }



    Distribution<int, int, uniform_int_distribution> distribution(1,4,1);

    auto condition_met = [nr_players] (Distribution<int, int, uniform_int_distribution>& d,
            double& iv,
            DRE& dre) -> bool {

        vector<double> player;
        for ( int ix = 0; ix < nr_players; ++ix )
            player.push_back(0.0);
        auto pot = static_cast<double>(nr_players);
        int current_player = 0;

        while ( d.events[0] != 2 ) {
            switch ( d.events[0] ) {
            case 1 :
                break;
            case 3 :
                player[current_player] += pot / 2.0;
                pot /= 2.0;
                break;
            case 4 :
                player[current_player] -= 1.0;
                pot += 1.0;
                break;
            default:
                break;
            }
            ++current_player;
            current_player %= nr_players;
            d.reload_random_values(dre);
        }

        player[current_player] += pot;

        return current_player == 1;
    };

    MonteCarloSimulation<int, double, int, uniform_int_distribution>
            monteCarloSimulation(
                10'000'000,
                1,
                condition_met,
                distribution
            );

    monteCarloSimulation.run();

    monteCarloSimulation.change_message("probability that the second player wins = ");

    monteCarloSimulation.print_result();
}