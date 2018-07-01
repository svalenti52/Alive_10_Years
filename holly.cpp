// holly.cpp
// Created by svalenti on 6/3/2018.
//

#include <val/montecarlo/MonteCarloSim_beta.h>

int main(int argc, char** argv)
{
    if (argc != 3) {"usage: number of patients, number that died"; return 1;}
    const int nr_events{static_cast<int>(strtol(argv[1], nullptr, 10))};
    const int nr_dying_threshold{static_cast<int>(strtol(argv[2], nullptr, 10))};

    using DOUBLE_X_INT_U_DISTRIBUTION = Distribution<double, int, std::uniform_real_distribution>;

    //const int nr_dying_threshold(0);
    //const int nr_events(5); // living or dying of awful-itis

    DOUBLE_X_INT_U_DISTRIBUTION distribution(0.0, 1.0, nr_events);

    auto condition_met = [nr_dying_threshold](DOUBLE_X_INT_U_DISTRIBUTION& pd, double& y_axis, DRE& dre)
    {
        const double probability_of_survival = 1.0 / 3.0;
        auto nr_died = std::count_if(pd.events.cbegin(), pd.events.cend(),
                [probability_of_survival](double died){ return died > probability_of_survival;});
        return nr_died <= nr_dying_threshold;
    };

    MonteCarloSimulation<double, double, int, std::uniform_real_distribution>
        monteCarloSimulation(10'000'000, 1, condition_met, distribution);

    monteCarloSimulation.run();

    monteCarloSimulation.print_result();
}
