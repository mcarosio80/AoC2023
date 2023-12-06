#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include <file_utils.h>

int main(int argc, char **argv)
{
    auto inputFile = AoC::get_input_file_path("input06.txt");

    std::vector<int> times;
    std::vector<int> distances;
    auto f = [&] (const std::string& textLine) -> void
    {
        std::cout << textLine << "\n";

        std::string figures;
        bool readTimes{true};
        if (textLine.substr(0, 5) == "Time:")
        {
            readTimes = true;
            figures = textLine.substr(5, textLine.length() - 5);
        }
        else if (textLine.substr(0, 9) == "Distance:")
        {
            readTimes = false;
            figures = textLine.substr(9, textLine.length() - 9);
        }

        std::stringstream ss(figures);

        while (ss.good())
        {
            int f{0};
            ss >> f;
            if (readTimes)
            {
                times.push_back(f);
            }
            else
            {
                distances.push_back(f);
            }
        }
    };

    if (!AoC::text_iterator(inputFile.c_str(), f))
    {
        std::cout << "Error iterating through " << inputFile << "\n";
    }

    std::vector<int> winningStrategies(times.size(), 0);
    int accumulator{1};
    for (size_t i=0; i<times.size(); ++i)
    {
        std::cout << "Race " << i << ": time = " << times[i] << ", distance = " << distances[i] << "\n";

        for (int t=1; t<times[i]; ++t)
        {
            auto d = (times[i] - t) * t;
            std::cout << "Charging for " << t << " -> distance = " << d << ", record = " << distances[i];
            if (d > distances[i])
            {
                ++winningStrategies[i];
                std::cout << " VICTORY!!";
            }
            std::cout << " \n";
        }
    }

    auto fn = [&](int x) -> void { accumulator *= x; };
    std::for_each(winningStrategies.cbegin(), winningStrategies.cend(), fn);
    std::cout << "Grand total: " << accumulator << "\n";



    uint64_t time{0};
    uint64_t distance{0};
    auto f2 = [&] (const std::string& textLine) -> void
    {
        std::cout << textLine << "\n";

        std::string figures;
        bool readTimes{true};
        if (textLine.substr(0, 5) == "Time:")
        {
            readTimes = true;
            figures = textLine.substr(5, textLine.length() - 5);
        }
        else if (textLine.substr(0, 9) == "Distance:")
        {
            readTimes = false;
            figures = textLine.substr(9, textLine.length() - 9);
        }
        
        figures.erase(std::remove_if(figures.begin(), figures.end(), isspace), figures.end());
        std::cout << "Line: " << figures << "\n";

        std::stringstream ss{figures};
        
        if (readTimes)
        {
            ss >> time;
        }
        else
        {
            ss >> distance;
        }
    };

    if (!AoC::text_iterator(inputFile.c_str(), f2))
    {
        std::cout << "Error iterating through " << inputFile << "\n";
    }

    accumulator = 0;
    
    for (uint64_t t=1; t<time; ++t)
    {
        auto d = (time - t) * t;
        //std::cout << "Charging for " << t << " -> speed = " << t << ", time = " << (time - t) << ", distance = " << d << ", record = " << distance;
        if (d > distance)
        {
            ++accumulator;
            //std::cout << " VICTORY!!";
        }
        //std::cout << " \n";
    }

    std::cout << "Grand total: " << accumulator << "\n";
    return 0;
}