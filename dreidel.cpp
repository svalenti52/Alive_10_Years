/** \file dreidel.cpp
 *
 */

// dreidel.cpp

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <random>

using namespace std;

class Dreidel {
    string name;
    int face_nr;
public:
    Dreidel(const string&& name, int face_nr) : name(name), face_nr(face_nr) {}

    const string &getName() const {
        return name;
    }

    int getFace_nr() const {
        return face_nr;
    }
};

class Player {
    int id;
    double net;
public:
    explicit Player(int i_id) : id(i_id), net(0.0) {}

    void operator+=(double winnings) { net += winnings; }

    void operator--() { net -= 1.0; }

    int getId() const {
        return id;
    }

    double getNet() const {
        return net;
    }
};

vector<Player> vec_players;
map<const string, Dreidel> dreidel_faces;

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cout << "Usage: provide argument for number of players\n";
        return 1;
    }

    double pot = atof(argv[1]);
    const int nr_players = atoi(argv[1]);

    for (int ix = 0; ix < pot; ++ix) {
        Player p(ix);
        vec_players.push_back(p);
    }

    dreidel_faces = {{"Nun",   Dreidel("Nun", 1)},
                     {"Gimel", Dreidel("Gimel", 2)},
                     {"Hay",   Dreidel("Hay", 3)},
                     {"Shin",  Dreidel("Shin", 4)}};
    auto wins_pot = dreidel_faces.find("Gimel")->second.getFace_nr();

    default_random_engine dre;
    uniform_int_distribution<int> face_up(1, 4);

    const int nr_trials = 10'000'000;

    for (int ix = 0; ix < nr_trials; ++ix) {
        pot = atof(argv[1]);
        int player_id = 0;
        int result_of_spin;

        while ((result_of_spin = face_up(dre)) != wins_pot) {
            switch (result_of_spin) {
                case 1:
                    break;
                case 3:
                    vec_players[player_id] += pot / 2.0;
                    pot -= pot / 2.0;
                    break;
                case 4:
                    --vec_players[player_id];
                    pot += 1.0;
                    break;
                default:
                    break;
            }
            player_id = (player_id + 1) % nr_players;
        }
        vec_players[player_id] += pot;
    }
    for (Player &p : vec_players)
        cout << "Player " << p.getId() << " won " << p.getNet() / static_cast<double>(nr_trials) << '\n';

    return 0;
}
