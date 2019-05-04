//
// Created by svalenti on 5/4/2019.
//

#include <iostream>
#include <sstream>
#include <val/montecarlo/MonteCarloSim_beta.h>

using namespace std;

using Distribution_Structure = Distribution<int, int, uniform_int_distribution>;

bool roll_till_limit_or_won(int nr_rolls, Distribution_Structure& ds, DRE& dre)
{
    bool someone_has_won = false;
    for (int ix = 0; ix < nr_rolls; ++ix)
    {
        ds.reload_random_values(dre);
        if (ds.events[0] == 1)
        {
            someone_has_won = true;
            break;
        }
    }
    return someone_has_won;
}

int main(int argc, char** argv)
{
    Distribution_Structure distribution(1,6,1);

    auto condition_met = []
            (Distribution_Structure& d,
                    double& iv,
                    DRE& dre) -> bool {

        bool someone_has_won = false;
        bool A_has_won = false;
        int nr_rolls = 1;

        while ( !someone_has_won )
        {
            someone_has_won = roll_till_limit_or_won(nr_rolls, d, dre);
            A_has_won = true;

            if (someone_has_won) break;

            someone_has_won = roll_till_limit_or_won(nr_rolls, d, dre);
            A_has_won = false;

            if (someone_has_won) break;
            ++nr_rolls;
        }

        return A_has_won;
    };

    MonteCarloSimulation<int, double, int, uniform_int_distribution>
            monteCarloSimulation(
            20'000'000,
            1,
            condition_met,
            distribution
    );

    monteCarloSimulation.run();

    std::ostringstream o;
    o << "Probability that player A wins = ";
    monteCarloSimulation.change_message(o.str());

    monteCarloSimulation.print_result();

}
