/** \file challenge10.cpp
 *
 */

// challenge10.cpp
// Created by svalenti on 4/28/2017.
//

#include <iostream>
#include <random>
#include <val/montecarlo/Chronology.h>

using namespace std;

enum class Color { Black, White };

class ball {
    Color color; // == black
    bool discard;
public:
    ball(Color c) : color(c), discard(false) {}
    bool isDiscard() const
    {
        return discard;
    }

    void setDiscard()
    {
        discard = true;
    }

    Color getColor() const
    {
        return color;
    }
};

class ballCollection {
public:
    vector<ball> collection;
    Color matching_color;
    bool oneLeft;
public:
    ballCollection(int nrBlack, int nrWhite) {
        for ( int ix = 0; ix < nrBlack; ++ix )
            collection.push_back(ball(Color::Black));
        for ( int ix = 0; ix < nrWhite; ++ix )
            collection.push_back(ball(Color::White));
    }
    bool isOneLeft() {
        int count = 0;
        for ( ball b : collection ) {
            if ( !b.isDiscard() ) {
                ++count;
                if ( count > 1 ) {
                    oneLeft = false;
                    return false;
                }
            }
        }
        oneLeft = (count == 1);
        return count == 1;
    }
    unsigned long getSize() {
        return collection.size();
    }
    Color getColorLeft() {
        for ( ball b : collection )
            if ( !b.isDiscard() ) return b.getColor();
        throw;
    }
};

int main(int argc, char** argv)
{
    if ( argc != 3 ) {
        cout << "usage: ./challenge10 <nr_black> <nr_white>\n";
        return 1;
    }

    int nr_black = atoi(argv[1]);
    int nr_white = atoi(argv[2]);

    if ( nr_black + nr_white <= 1 ) {
        cout << "At least two balls for input\n";
        return 2;
    }

    default_random_engine dre;
    uniform_real_distribution<double> urd;
    dre.seed(4);

    const int nr_trials = 1'000'000;

    double cumulative_value = 0.0;

    StopWatch sw;

    for (int ix = 0; ix<nr_trials; ++ix) {

        ballCollection jar(nr_black, nr_white);

        uniform_int_distribution<int> uid(0, static_cast<int>(jar.getSize()-1));

        while ( true ) {

            int selected = uid(dre);

            while ( jar.collection[selected].isDiscard() ) selected = uid(dre);

            jar.matching_color = jar.collection[selected].getColor();

            do {
                jar.collection[selected].setDiscard();
                if ( jar.isOneLeft() ) break;
                while ( jar.collection[selected].isDiscard() ) selected = uid(dre);
            } while ( jar.matching_color == jar.collection[selected].getColor() );

            if ( jar.oneLeft ) break;

            /*PickAnother:

            if ( jar.isOneLeft() ) break;

            while ( jar.collection[selected].isDiscard() ) selected = uid(dre);

            if ( jar.matching_color == jar.collection[selected].getColor() ) {
                jar.collection[selected].setDiscard();
                goto PickAnother;
            }*/
        }

        if ( jar.getColorLeft() == Color::Black )
            cumulative_value += 1.0;
    }

    cout << "Probability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';

    sw.stop();

    return 0;
}
