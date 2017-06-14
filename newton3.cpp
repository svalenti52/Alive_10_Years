/** \file newton3.cpp
 * \brief Three Player Game, A, B, C, A rolls first, B second;
 * roll six, then out of game.
 * \date 28-Apr-2017
 *
 * \details What is the probability of first A, then B tossing a 6?
 * What is the probability of first B, then A tossing a 6?
 * (Just concerned with order, not consecutive 6s.)
 */

#include <iostream>
#include <random>
//#include <boost/circular_buffer.hpp>
#include <deque>

using namespace std;
//using namespace boost;

class Player {
public:
    string name;
    int last_roll;
    Player(const string& s, int lr) : name(s), last_roll(lr) {}
};

enum class roll {
    A_NEXT,
    B_NEXT,
    C_NEXT
};

int main(int argc, char** argv)
{

    default_random_engine dre;
    uniform_int_distribution<int> urid(1, 6);

    dre.seed(1);

    const int nr_trials = 10'000'000;

    double cumulative_value_AB = 0.0;
    double cumulative_value_BA = 0.0;

    for (int ix = 0; ix<nr_trials; ++ix) {

        deque<Player> dq;
        dq.push_back(Player("A", 0));
        dq.push_back(Player("B", 0));
        dq.push_back(Player("C", 0));

        int nr_players = 3;
        bool done_with_game = false;
        roll whose_turn = roll::A_NEXT;

        for ( int jx = 0; jx < 1'000'000; ++jx ) {

            switch (whose_turn) {

            case roll::A_NEXT:
                dq[0].last_roll = urid(dre);
                if ( nr_players == 3 ) {
                    whose_turn = roll::B_NEXT;
                    if ( dq[0].last_roll == 6 ) {
                        dq.pop_front();
                        --nr_players;
                    }
                }
                else {
                    whose_turn = roll::C_NEXT;
                    if ( dq[0].last_roll == 6 ) {
                        cumulative_value_BA += 1.0; // A is leaving second, C wins
                        done_with_game = true;
                    }
                }
                break;

            case roll::B_NEXT:
                whose_turn = roll::C_NEXT;
                if ( nr_players == 3 ) {
                    dq[1].last_roll = urid(dre);
                    if ( dq[1].last_roll == 6 ) {
                        dq.pop_front();
                        --nr_players;
                        dq[0] = Player("A", 0);
                    }
                }
                else {
                    dq[0].last_roll = urid(dre);
                    if ( dq[0].last_roll == 6 ) {
                        cumulative_value_AB += 1.0; // B is leaving second, C wins
                        done_with_game = true;
                    }
                }

                break;

            case roll::C_NEXT:
                auto tmp_roll = urid(dre);
                if ( tmp_roll == 6 ) done_with_game = true; // C not winning
                else if ( nr_players == 3 ) {
                    dq[2].last_roll = tmp_roll;
                    whose_turn = roll::A_NEXT;
                }
                else {
                    dq[1].last_roll = tmp_roll;
                    if ( dq[0].name == "A" )
                        whose_turn = roll::A_NEXT;
                    else
                        whose_turn = roll::B_NEXT;
                }

                break;
            }

            if (done_with_game) break;
        }
    }

    cout << "Probability AB is = " << cumulative_value_AB/static_cast<double>(nr_trials) << '\n';
    cout << "Probability BA is = " << cumulative_value_BA/static_cast<double>(nr_trials) << '\n';

    return 0;
}
