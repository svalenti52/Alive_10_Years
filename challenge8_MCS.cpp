/**
 * \file challenge8_MCS.cpp
 * \date 30-Jun-2017
 *
 * \brief Probability of any team in a league of 6, all equal ability,
 * winning championship 3 years in a row.
 *
 * \details A team winning a championship 3 years in a row gets to
 * retire the trophy permanently. The main problem is determining how
 * many years are required before the probability reaches one-half that
 * the trophy is retired. Calculate also for 10 teams as well as 6.
 */

#include <iostream>
#include <fstream>
#include <random>
#include <val/montecarlo/Histogram.h>
#include <deque>
#include <val/montecarlo/MonteCarloSim.h>
#include <val/montecarlo/Chronology.h>

using namespace std;

using DIST = DistributionType;

int main(int argc, char** argv)
{

    if ( argc != 2 ) { cout << "usage: ./a <nr of teams>\n"; return 1; }
    const int max = atoi(argv[1]);

    int max_nr_seasons_tracked = 300;

    Histogram<int, int> histogram(2, max_nr_seasons_tracked, 1);

    auto condition_met ( [&histogram, max_nr_seasons_tracked](Distribution<int, DIST::UniformIntegral>& pd,
            Distribution<int, DIST::UniformIntegral>& latest_three_seasons,
            double& nr_of_seasons) -> bool {

        nr_of_seasons = 3.0;
        while (latest_three_seasons.events[0] != latest_three_seasons.events[1] ||
                latest_three_seasons.events[1] != latest_three_seasons.events[2]) {

            nr_of_seasons += 1.0;
            latest_three_seasons.events.pop_front();
            latest_three_seasons.add_random_value_to_end();
        }
        if ( nr_of_seasons >static_cast<double>(max_nr_seasons_tracked))
            histogram.increment_bin(max_nr_seasons_tracked);
        else histogram.increment_bin(static_cast<int>(nr_of_seasons));

        latest_three_seasons.reload_random_values();
        return true;
    } );

    MonteCarloSimulation<int, int, DIST::UniformIntegral, DIST::UniformIntegral>
    monteCarloSimulation(1'000'000,
                            condition_met,
                            1, 6, 0, 1,
                            1, max, 3, 1);


    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();

    cout << "Approximate location of 50% probability at "
         << histogram.get_midpoint() << " seasons\n";

    std::ofstream histogram_file("/home/graph/histogram.txt");

    histogram_file << histogram << '\n';

    return 0;
}

