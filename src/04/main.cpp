#include <iostream>
#include <sstream>
#include <string>

#include <file_utils.h>

static int read_number(const std::string& data)
{
    int number{0};
    for (auto& c : data)
    {
        number *= 10;
        number += c - '0';
    }
    return number;
}

int main(int argc, char **argv)
{
    auto inputFile = AoC::get_input_file_path("input04.txt");

    std::vector<std::vector<int>> winningNumbers;
    std::vector<std::vector<int>> cardNumbers;

    auto f = [&] (const std::string& textLine) -> void
    {
        std::cout << textLine << "\n";

        std::stringstream ss{textLine};

        std::string label;
        ss >> label;

        int cardId{0};
        ss >> cardId;

        char separator{' '};
        ss >> separator;

        std::string nextToken;
        bool isWinning{true};
        std::vector<int> winningNums;
        std::vector<int> cardNums;
        while (ss.good())
        {
            ss >> nextToken;
            //std::cout << "nextToken : " << nextToken << "\n";
            if (nextToken == "|")
            {
                isWinning = false;
            }
            else
            {
                auto num = read_number(nextToken);
                if (isWinning)
                {
                    winningNums.push_back(num);
                }
                else
                {
                    cardNums.push_back(num);
                }
            }
        }

        winningNumbers.push_back(winningNums);
        cardNumbers.push_back(cardNums);
    };

    if (!AoC::text_iterator(inputFile.c_str(), f))
    {
        std::cout << "Error iterating through " << inputFile << "\n";
    }

    int accumulator{0};
    
    for (int i=0; i<winningNumbers.size(); ++i)
    {
        int partial{0};
        std::for_each(cardNumbers[i].cbegin(), cardNumbers[i].cend(), [&] (int x)
        {
            auto it = std::find(winningNumbers[i].cbegin(), winningNumbers[i].cend(), x);
            if (it != winningNumbers[i].cend())
            {
                partial = (partial == 0) ? 1 : partial << 1;

                std::cout << "Card " << i+1 << " number " << *it << " is winning, card worth " << partial << " points \n";
            }
        }
        );
        accumulator += partial;
    }
    std::cout << "Grand total: " << accumulator << "\n";

    accumulator = 0;

    std::vector<int> copyCount(winningNumbers.size(), 1);
    for (int i=0; i<winningNumbers.size(); ++i)
    {
        int winningCount{0};
        std::for_each(cardNumbers[i].cbegin(), cardNumbers[i].cend(), [&] (int x)
        {
            auto it = std::find(winningNumbers[i].cbegin(), winningNumbers[i].cend(), x);
            if (it != winningNumbers[i].cend())
            {
                ++winningCount;
            }
        }
        );
        std::cout << "Card " << i+1 << " is winning " << winningCount << " copies \n";

        for (int w=0; w<winningCount && w+i<winningNumbers.size(); ++w)
        {
            copyCount[w+i+1] += copyCount[i];
        }
    }

    for (int i=0; i<copyCount.size(); ++i)
    {
        std::cout << "Card " << i+1 << " has " << copyCount[i] << " copies \n";
        accumulator += copyCount[i];
    }

    // for (int i=0; i<winningNumbers.size(); ++i)
    // {
    //     int partial{0};
    //     std::for_each(cardNumbers[i].cbegin(), cardNumbers[i].cend(), [&] (int x)
    //     {
    //         auto it = std::find(winningNumbers[i].cbegin(), winningNumbers[i].cend(), x);
    //         if (it != winningNumbers[i].cend())
    //         {
    //             partial = (partial == 0) ? 1 : partial << 1;

    //             std::cout << "Card " << i+1 << " number " << *it << " is winning, card worth "
    //                     << partial << " points (times " << copyCount[i] << " = "
    //                     << partial * copyCount[i] << ") \n";
    //         }
    //     });
    //     std::cout << "Accumulator +=  " << partial << " * " << copyCount[i] << "\n";
    //     accumulator += partial * copyCount[i];
    // }
    std::cout << "Grand total: " << accumulator << "\n";

    return 0;
}