#include <iostream>
#include <algorithm>
#include <string.h>
#include <cstring>

#include <file_utils.h>
#include "day01.h"

namespace AoC
{
    const char *Day01::words[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    const char *Day01::sdrow[] = { "orez", "eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin"};
    const char *Day01::numbers[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

    Day01::Day01()
        : Challenge()
    {
    }

    Day01::~Day01()
    {
    }

    int Day01::find_digit(const std::string& line, bool includeWords, bool reverse)
    {   
        for (int start=0; start<line.length(); ++start)
        {
            for (int i=0; i<10; ++i)
            {
                const char* w = (reverse) ? sdrow[i] : words[i];

                auto s = line.substr(start, strlen(w));
                if (includeWords && strncmp(s.c_str(), w, s.length()) == 0)
                {
                    return i;
                }
                else if (strncmp(line.substr(start, 1).c_str(), numbers[i], 1) == 0)
                {
                    return i;
                }
            }
        }
        return 0;
    }
    
    std::string Day01::get_answer(const ChallengePart& part) const override
    {
        auto inputFile = AoC2023::get_instance().get_data_file_name(Day::day01);

        int accumulator{0};
        bool checkWords = false;

        auto f = [&] (const std::string& textLine) -> void
        {
            auto firstDigit = find_digit(textLine, checkWords, false);

            std::string reversed(textLine);
            std::reverse(reversed.begin(), reversed.end());
            auto lastDigit = find_digit(reversed, checkWords, true);

            int total = (firstDigit * 10) + (lastDigit);
            accumulator += total;

            if (verbose())
            {
                std::cout << ">> Line[" << textLine << "] - "
                        << firstDigit << " & " << lastDigit
                        << " -> " << total << "  (partial total: " << accumulator << ")\n";
            }
        };

        checkWords = (part == ChallengePart::first);
        
        if (!AoC::text_iterator(inputFile.c_str(), f))
        {
            std::stringstream err;
            err << "Error iterating through " << inputFile;
            AoC2023::get_instance().error(err.str());
        }

        return AoC2023::get_instance().format_answer<int>(accumulator);
    }

} // namespace AoC