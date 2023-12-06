#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>

#include <file_utils.h>

static int read_number(const std::vector<char>& data, size_t col)
{
    int number{0};
    //std::cout << "Reading v[" << col << "] = " << data[col] << " (limit : " << data.size() << "\n";
    while (col < data.size() && isdigit(data.at(col)))
    {
        number *= 10;
        number += data.at(col) - '0';
        //std::cout << "number : " << number << ", col : " << col << "\n";
        ++col;
    }
    return number;
}

static bool is_symbol(const std::vector<std::vector<char>>& data, const size_t& row, const size_t& col)
{
    auto& c = data[row][col];
    return !isalnum(c) && c != '.'; 
}

static bool is_gear(const std::vector<std::vector<char>>& data, const size_t& row, const size_t& col)
{
    return data[row][col] == '*'; 
}

int safe_coord(const int& c, const size_t& limit)
{
    return std::min<int>(limit-1, std::max<int>(c, 0));
}

static bool look_around(const std::vector<std::vector<char>>& data, const int& row, const int& col, const int& len)
{
    auto safeCol = safe_coord(col-1, data.size());
    //std::cout << "Checking " << data[row][safeCol] << " (" << row << "," << safeCol << ")\n";
    if (is_symbol(data, row, safeCol))
    {
        //std::cout << "(" << row << "," << safeCol << ") Near symbol!!!\n";
        return true;
    }
    safeCol = safe_coord(col+len, data.size());
    //std::cout << "Checking " << data[row][safeCol] << " (" << row << "," << safeCol << ")\n";
    if (is_symbol(data, row, safeCol))
    {
        //std::cout << "(" << row << "," << safeCol << ") Near symbol!!!\n";
        return true;
    }
    
    for (auto offset : {-1,1})
    {
        auto safeRow = safe_coord(row + offset, data.size());
        for (int c=col-1; c<=col+len; ++c)
        {
            auto safeCol = safe_coord(c, data.size());
            //std::cout << "Checking coord (" << safeRow << "," << safeCol << ") = " << data[safeRow][safeCol] << "\n";
            if (is_symbol(data, safeRow, safeCol))
            {
                return true;
            }
        }
    }
    return false;
}

static std::tuple<bool, int, int> close_to_gear(const std::vector<std::vector<char>>& data, const int& row, const int& col, const int& len)
{
    auto safeCol = safe_coord(col-1, data.size());
    //std::cout << "Checking " << data[row][safeCol] << " (" << row << "," << safeCol << ")\n";
    if (is_gear(data, row, safeCol))
    {
        //std::cout << "(" << row << "," << safeCol << ") Near symbol!!!\n";
        return std::make_tuple(true, row, safeCol);
    }
    safeCol = safe_coord(col+len, data.size());
    //std::cout << "Checking " << data[row][safeCol] << " (" << row << "," << safeCol << ")\n";
    if (is_gear(data, row, safeCol))
    {
        //std::cout << "(" << row << "," << safeCol << ") Near symbol!!!\n";
        return std::make_tuple(true, row, safeCol);
    }
    
    for (auto offset : {-1,1})
    {
        auto safeRow = safe_coord(row + offset, data.size());
        for (int c=col-1; c<=col+len; ++c)
        {
            auto safeCol = safe_coord(c, data.size());
            //std::cout << "Checking coord (" << safeRow << "," << safeCol << ") = " << data[safeRow][safeCol] << "\n";
            if (is_gear(data, safeRow, safeCol))
            {
                //std::cout << "Gear detected at (" << safeRow << "," << safeCol << ")\n";
                return std::make_tuple(true, safeRow, safeCol);
            }
        }
    }
    return std::make_tuple(false, 0, 0);
}

int number_length(const int& number)
{
    return std::max(1, static_cast<int>(std::ceil(std::log10(number))));
}

int main(int argc, char **argv)
{
    auto inputFile = AoC::get_input_file_path("input03.txt");
    int accumulator{0};
    bool verbose{false};

    std::vector<std::vector<char>> data;
    size_t lineCount{0};

    auto f = [&] (const std::string& textLine) -> void
    {
        std::vector<char> line{};
        std::copy(textLine.cbegin(), textLine.cend(), std::back_inserter(line));
        data.push_back(line);
        // for (char c: line)
        //     std::cout << c << ' ';
        // std::cout << "\n";
    };

    if (!AoC::text_iterator(inputFile.c_str(), f))
    {
        std::cout << "Error iterating through " << inputFile << "\n";
    }

    for (size_t i=0; i<data.size(); ++i)
    {
        for (size_t j=0; j<data[i].size(); ++j)
        {
            //std::cout << "Checking " << data[i][j] << " (" << i << "," << j << ")\n";
            if (isdigit(data[i][j]))
            {
                int number = read_number(data[i], j);
                auto numLen = number_length(number);
                //std::cout << "Number " << number << " at (" << i << "," << j << ") is " << numLen << " chars long\n";
                auto nearSymbol = look_around(data, i, j, numLen);
                if (nearSymbol)
                {
                    //std::cout << "Number " << number << " at (" << i << "," << j << ") is considered\n";
                    accumulator += number;
                    j += numLen-1;
                }
            }
        }
    }
    //std::cout << "Grand total: " << accumulator << "\n";

    std::map<std::pair<int, int>, std::vector<int>> gears;
    for (size_t i=0; i<data.size(); ++i)
    {
        for (size_t j=0; j<data[i].size(); ++j)
        {
            //std::cout << "Checking " << data[i][j] << " (" << i << "," << j << ")\n";
            if (isdigit(data[i][j]))
            {
                int number = read_number(data[i], j);
                auto numLen = number_length(number);
                //std::cout << "Number " << number << " at (" << i << "," << j << ") is " << numLen << " chars long\n";
                auto nearGear = close_to_gear(data, i, j, numLen);
                if (std::get<0>(nearGear))
                {
                    // std::cout << "Number " << number << " at (" << i << "," << j
                    //         << ") is close to gear (" << std::get<1>(nearGear) << "," << std::get<2>(nearGear)
                    //         << ")\n";
                    //accumulator += number;
                    auto key = std::make_pair(std::get<1>(nearGear), std::get<2>(nearGear));
                    gears[key].push_back(number);
                    j += numLen;
                }
            }
        }
    }

    int count = 0;
    accumulator = 0;
    //std::cout << "Gears count is " << gears.size() << "\n";
    for (auto& g : gears)
    {
        std::cout << "Gear at (" << g.first.first+1 << "," << g.first.second+1 << ") - is connected to:";
        for (auto n : g.second)
        {
            std::cout << "\t" << n;
        }
        std::cout << "\n";
        if (g.second.size() == 2)
        {
            ++count;
            auto gearPower = g.second[0] * g.second[1];
            accumulator += gearPower;
            // std::cout << "Gear at (" << g.first.first+1 << "," << g.first.second+1 << ") - Power: "
            //     << gearPower << " acc: " << accumulator << " is connected to:";
            // for (auto n : g.second)
            // {
            //     std::cout << "\t" << n;
            // }
            // std::cout << "\n";
        }
    }
    std::cout << "Gears to sum: " << count << "\n";
    //80249444
    std::cout << "Grand total: " << accumulator << "\n";
}