/** \file bingo.cpp
 *
 */

//
// Created by svalenti on 4/30/2017.
//

#include <iostream>
#include <random>
#include <algorithm>
#include <functional>
//#include <Eigen/Dense>

using namespace std;
//using namespace Eigen;

class BingoCard {
    vector<pair<int, bool>> card;
    bool bingo;
public:
    bool isBingo() const
    {
        return bingo;
    }

    void setBingo(bool bingo)
    {
        BingoCard::bingo = bingo;
        for ( pair<int, bool>& pr : card )
            pr.second = false;
    }

public:
    BingoCard(int f, int s, int t, int ft) : bingo(false) {
        card.push_back(make_pair(f, false));
        card.push_back(make_pair(s, false));
        card.push_back(make_pair(t, false));
        card.push_back(make_pair(ft, false));
    }

    void is_matching(int n) {
        for ( pair<int, bool>& pr : card )  {
            if ( pr.first == n )
                pr.second = true;
        }
        bingo = ( card[0].second && card[1].second ) || ( card[2].second && card[3].second );
    }
};

//-----------------------------------------------------

int main(int argc, char** argv)
{

    default_random_engine dre;
    uniform_real_distribution<double> urd;

    dre.seed(4);

    int nr_A_wins = 0;
    int nr_B_wins = 0;

    vector<BingoCard> cards;
    //cards.push_back(BingoCard(1,2,3,4));
    cards.push_back(BingoCard(2,4,5,6));
    cards.push_back(BingoCard(1,3,4,5));
    //cards.push_back(BingoCard(1,5,2,6));

    vector<int> vec_bingo = { 1, 2, 3, 4, 5, 6 };

    function<void(void)> reset_cards =
            [&cards]() { for ( BingoCard& b : cards) b.setBingo(false); };

    int tot_perms = 0;

    do {
        ++tot_perms;
        for ( int call : vec_bingo ) {
            for ( BingoCard& n : cards ) {
                n.is_matching(call);
            }
            if ( cards[0].isBingo() || cards[1].isBingo() ) break;
        }
        if ( cards[0].isBingo() && cards[1].isBingo() ) {
            reset_cards();
            continue;
        }
        if ( cards[0].isBingo() ) ++nr_A_wins;
        else ++nr_B_wins;
        reset_cards();
    }
    while (next_permutation(vec_bingo.begin(), vec_bingo.end()));

    cout << "Total Nr Perms = " << tot_perms << '\n';

    if ( nr_A_wins == nr_B_wins )
        cout << "It's a Tie: " << nr_A_wins << " to " << nr_B_wins << '\n';
    else if ( nr_A_wins > nr_B_wins )
        cout << "A wins: " << nr_A_wins << " to " << nr_B_wins << '\n';
    else
        cout << "B wins: " << nr_B_wins << " to " << nr_A_wins << '\n';

    return 0;
}
