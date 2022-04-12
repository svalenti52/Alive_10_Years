// holly.cpp
// Created by svalenti on 6/3/2018.
//

#include <val/montecarlo/MonteCarloSim_beta.h>

bool numeric_arguments_check(int argc, char**argv, const std::string& s, const int target_count, int& arg1, int& arg2)
{
    if (argc != target_count)
    {
        std::cout << s;
        return false;
    }
    arg1 = static_cast<int>(strtol(argv[1], nullptr, 10));
    arg2 = static_cast<int>(strtol(argv[2], nullptr, 10));
    return true;
}

int main(int argc, char** argv)
{
    int nr_patients, nr_dying_threshold;
    if (!numeric_arguments_check(argc, argv,
                                 std::string("usage: number of patients, number that died\n"),
                                 3, nr_patients, nr_dying_threshold)) return 1;
    if (nr_patients < nr_dying_threshold) {std::cout
                << "usage: number of patients cannot be less than number that died\n"; return 2;}

    using DOUBLE_X_INT_U_DISTRIBUTION = Distribution<double, int, std::uniform_real_distribution>;

    // const int nr_dying_threshold(0);
    // const int nr_patients(5); // living or dying of unspecified

    DOUBLE_X_INT_U_DISTRIBUTION distribution(0.0, 1.0, nr_patients);

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
