// breaking_sticks_MCS.cpp
// Created by svalenti on 5/6/2018.
//

#include <val/montecarlo/MonteCarloSim_beta.h>
#include <val/montecarlo/Chronology.h>

using DOUBLE_X_INT_U_DISTRIBUTION = Distribution<double, int, std::uniform_real_distribution>;

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Arguments Incorrect... First Argument: Number of Invisible Marks," <<
                     "Second Argument: Number of Segments\n";
        return 1;
    }

    const auto nr_invisible_marks = static_cast<int>(strtol(argv[1], argv, 10));
    const auto nr_segments = static_cast<int>(strtol(argv[2], argv, 10));
    if (nr_invisible_marks < 2 || nr_segments < 2)
    {
        std::cout << "Argument should be at least two...\n";
        return 2;
    }
    const int nr_breaks = nr_segments - 1;
    const int total_nr_elements = nr_invisible_marks + nr_breaks;

    //-------------------------------------------------------------------------
    DOUBLE_X_INT_U_DISTRIBUTION distribution(0.0, 1.0, total_nr_elements);

    auto condition_met (
            [nr_invisible_marks, nr_breaks] (DOUBLE_X_INT_U_DISTRIBUTION& pd,
            double& iv_y_axis,
            DRE& dre)
            {
                std::vector<double> iv_marks(static_cast<unsigned>(nr_invisible_marks), 0.0);
                std::vector<double> breaks(static_cast<unsigned>(nr_breaks), 0.0);
                for (int ix = 0; ix < nr_invisible_marks; ++ix)
                    iv_marks[ix] = pd.events[ix];
                for (int ix = 0; ix < nr_breaks; ++ix)
                    breaks[ix] = pd.events[ix+nr_invisible_marks];

                std::sort(breaks.begin(), breaks.end());

                bool AllMarksOnSameSegment = true;
                for (auto segment : breaks)
                {
                    if (std::none_of(iv_marks.begin(), iv_marks.end(), [segment](auto marks) {return marks < segment;}))
                        continue;
                    else
                    {
                        AllMarksOnSameSegment = std::all_of(iv_marks.begin(), iv_marks.end(),
                                [segment](auto marks) { return marks < segment; });
                        break;
                    }
                }

                return AllMarksOnSameSegment; // iv_y_axis defaults to 1.0
            }
        );

    MonteCarloSimulation<double, double, int, std::uniform_real_distribution>
            monteCarloSimulation(
            10'000'000,
            1,
            condition_met,
            distribution
    );

    monteCarloSimulation.run();

    monteCarloSimulation.print_result();
}

