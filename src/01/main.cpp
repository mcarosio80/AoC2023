#include <iostream>
#include <algorithm>
#include <string.h>
#include <cstring>

#include <file_utils.h>

static const char *words[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
static const char *sdrow[] = { "orez", "eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin"};
static const char *numbers[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

int find_digit(const std::string& line, bool includeWords, bool reverse)
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

int main(int argc, char **argv)
{
    auto inputFile = AoC::get_input_file_path("input01.txt");
    int accumulator{0};
    bool checkWords = false;
    bool verbose{false};

    auto f = [&] (const std::string& textLine) -> void
    {
        auto firstDigit = find_digit(textLine, checkWords, false);

        std::string reversed(textLine);
        std::reverse(reversed.begin(), reversed.end());
        auto lastDigit = find_digit(reversed, checkWords, true);

        int total = (firstDigit * 10) + (lastDigit);
        accumulator += total;

        if (verbose)
        {
            std::cout << ">> Line[" << textLine << "] - "
                    << firstDigit << " & " << lastDigit
                    << " -> " << total << "  (partial total: " << accumulator << ")\n";
        }
    };

    if (!AoC::text_iterator(inputFile.c_str(), f))
    {
        std::cout << "Error iterating through " << inputFile << "\n";
    }
    std::cout << "Grand total: " << accumulator << "\n";

    accumulator = 0;
    checkWords = true;
    if (!AoC::text_iterator(inputFile.c_str(), f))
    {
        std::cout << "Error iterating through " << inputFile << "\n";
    }
    std::cout << "Grand total: " << accumulator << "\n";

    return 0;
}