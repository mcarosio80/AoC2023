#include <aoc_2023.h>
#include <file_utils.h>

#include <algorithm>

namespace AoC
{
    std::string challenge_01()
    {
        auto inputFile = AoC::get_input_file_path("input01.txt");
        int accumulator{0};

        auto f = [&] (const std::string& textLine) -> void
        {
            auto firstDigit = std::find_if(textLine.begin(), textLine.end(), [](char c) { return std::isdigit(c); });
            auto lastDigit = std::find_if(textLine.rbegin(), textLine.rend(), [](char c) { return std::isdigit(c); });

            int total = (*firstDigit - '0') * 10 + (*lastDigit - '0');
            accumulator += total;

            std::cout << ">> Line[" << textLine << "] - "
                    << *firstDigit << " & " << *lastDigit
                    << " -> " << total << "  (partial total: " << accumulator << ")\n";
        };

        if (!AoC::text_iterator(inputFile.c_str(), f))
        {
            std::cout << "Error iterating through " << inputFile << "\n";
        }

        std::cout << "Grand total: " << accumulator << "\n";
        return "";
    }
}