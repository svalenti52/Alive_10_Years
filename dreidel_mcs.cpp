/**
 * \file dreidel_mcs.cpp
 * \date 2-Sep-2017
 *
 */

#include <sstream>
#include <iostream>
#include <val/montecarlo/MonteCarloSim_beta.h>

enum class Dreidel_Face
{
    Nun,
    Hay,
    Gimel,
    Shin
};

int main(int argc, char **argv)
{
    using namespace std;

    int nr_players = 3;
    if ( argc >= 2 ) {
        istringstream i(argv[1]);
        i >> nr_players;
    }

    vector<double> player;
    const auto chosen_player = 0; // vary to 0, 1, 2, 3 corresponding to first, second, etc.

    Distribution<int, int, uniform_int_distribution> distribution(1,4,1);

    auto condition_met = [chosen_player, nr_players, &player]
            (Distribution<int, int, uniform_int_distribution>& d,
            double& iv,
            DRE& dre) -> bool {

        for ( int ix = 0; ix < nr_players; ++ix )
            player.push_back(0.0);
        auto pot = static_cast<double>(nr_players);
        int current_player = 0;

        while ( d.events[0] != static_cast<int>(Dreidel_Face::Gimel) ) {
            switch ( d.events[0] ) {
            case static_cast<int>(Dreidel_Face::Nun) :
                break;
            case static_cast<int>(Dreidel_Face::Hay) :
                player[current_player] += pot / 2.0;
                pot /= 2.0;
                break;
            case static_cast<int>(Dreidel_Face::Shin) :
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

        return current_player == chosen_player;
    };

    MonteCarloSimulation<int, double, int, uniform_int_distribution>
            monteCarloSimulation(
                10'000'000,
                1,
                condition_met,
                distribution
            );

    monteCarloSimulation.run();

    std::stringstream o;
    o << "Probability that player number " << chosen_player+1 << " wins = ";
    monteCarloSimulation.change_message(o.str());

    monteCarloSimulation.print_result();
}