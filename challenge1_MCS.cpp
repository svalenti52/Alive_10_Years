//
// Created by svalenti on 12/23/2018.
//

#include <val/montecarlo/MonteCarloSim_beta.h>

using REAL_X_REAL_P_DISTRIBUTION = Distribution<double, double, std::uniform_real_distribution>;

int main(int argc, char** argv)
{
    const int nr_events = 2;

    REAL_X_REAL_P_DISTRIBUTION distribution(0.0, 1.0, nr_events);

    auto condition_met([](REAL_X_REAL_P_DISTRIBUTION& side, double& nr_obtuse_triangles, DRE& dre)
    {
        const double right_angle_radians = 3.1415926536 / 2.0;

        while (side.events[0] + side.events[1] <= 1.0)
            side.reload_random_values(dre);

        return ( acos( (side.events[0]*side.events[0] + side.events[1] * side.events[1] - 1.0) /
                ( 2.0 * side.events[0] * side.events[1] ) ) > right_angle_radians );
    });

    MonteCarloSimulation<double, double, double, std::uniform_real_distribution>
            monteCarloSimulation(
            10'000'000,
            1,
            condition_met,
            distribution
    );

    monteCarloSimulation.run();

    monteCarloSimulation.print_result();
}
