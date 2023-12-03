#include <iostream>
#include <vector>
#include <sstream>
#include <map>

#include <string.h>

#include <file_utils.h>

struct Colour
{
    static const char *red;
    static const char *green;
    static const char *blue;
};

static const char *game_label = "Game";

static size_t consume_spaces(const std::string& line, const size_t& pos)
{
    size_t offset{0};
    while (isspace(line[pos]))
    {
        ++offset;
    }
    return offset;
}

struct CubeData
{
    int gameId;
    int redCount;
    int greenCount;
    int blueCount;
};

static std::vector<CubeData> parse_line(const std::string& line)
{
    std::vector<CubeData> data;

    std::stringstream ss{line};

    std::string label;

    ss >> label;

    if (label != game_label)
    {
        std::cout << "Malformed input, missing label\n";
        return {};
    }
    
    int gameId{0};
    ss >> gameId;

    char separator{' '};
    ss >> separator;

    while (ss.good())
    {
        int cubesCount{0};
        std::string cubeColour;
        CubeData cubes{};

        ss >> cubesCount;
        ss >> cubeColour;
        auto lastChar = cubeColour.at(cubeColour.length()-1);
        if (lastChar == ',' || lastChar == ';')
        {
            cubeColour = cubeColour.substr(0, cubeColour.length()-1);
        }

        cubes.gameId = gameId;
        if (cubeColour == Colour::red)
        {
            cubes.redCount = cubesCount;
        }
        else if (cubeColour == Colour::green)
        {
            cubes.greenCount = cubesCount;
        }
        else if (cubeColour == Colour::blue)
        {
            cubes.blueCount = cubesCount;
        }

        data.push_back(cubes);
    }

    return data;
}

const char *Colour::red = "red";
const char *Colour::green = "green";
const char *Colour::blue = "blue";

int main(int argc, char **argv)
{
    auto inputFile = AoC::get_input_file_path("input02.txt");
    int accumulator{0};
    bool verbose{false};
    std::map<int, CubeData> games;

    auto f = [&] (const std::string& textLine) -> void
    {
        auto data = parse_line(textLine);

        for (auto& d : data)
        {
            if (games.find(d.gameId) == games.end())
            {
                games[d.gameId] = {d.gameId, d.redCount, d.greenCount, d.blueCount};
            }
            else
            {
                games[d.gameId].redCount = std::max(games[d.gameId].redCount, d.redCount);
                games[d.gameId].greenCount = std::max(games[d.gameId].greenCount, d.greenCount);
                games[d.gameId].blueCount = std::max(games[d.gameId].blueCount, d.blueCount);
            }
        }
    };

    if (!AoC::text_iterator(inputFile.c_str(), f))
    {
        std::cout << "Error iterating through " << inputFile << "\n";
    }

    int limitRed = 12;
    int limitGreen = 13;
    int limitBlue = 14;

    for (auto& g : games)
    {
        if (g.second.redCount <= limitRed && g.second.greenCount <= limitGreen && g.second.blueCount <= limitBlue)
        {
            if (verbose)
            {
                std::cout << "Game " << g.first << " is possible because ("
                        << g.second.redCount << ", " 
                        << g.second.greenCount << ", "
                        << g.second.blueCount << ") is less/equals than ("
                        << limitRed << ", " << limitGreen << ", " << limitBlue << ")\n";
            }
            accumulator += g.first;
        }
    }
    std::cout << "Grand total: " << accumulator << "\n";

    accumulator = 0;
    for (auto& g : games)
    {
        auto cubePower = g.second.redCount * g.second.greenCount * g.second.blueCount;
        if (verbose)
        {
            std::cout << "Game " << g.first << ": the fewest number of cubes of each colous is ("
                        << g.second.redCount << ", " 
                        << g.second.greenCount << ", "
                        << g.second.blueCount << "), the power of the set is"
                        << cubePower << "\n";
        }
        accumulator += cubePower;
    }
    std::cout << "Grand total: " << accumulator << "\n";
}