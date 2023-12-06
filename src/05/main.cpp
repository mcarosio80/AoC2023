#include <iostream>
#include <sstream>
#include <map>
#include <optional>

#include <file_utils.h>

enum class MapType
{
    None,
    SeedToSoil,
    SoilToFertilizer,
    FertilizerToWater,
    WaterToLight,
    LightToTemperature,
    TemperatureToHumidity,
    HumidityToLocatio,
};

std::map<std::pair<uint64_t, uint64_t>, uint64_t> mapSeedToSoil;
std::map<std::pair<uint64_t, uint64_t>, uint64_t> mapSoilToFertilizer;
std::map<std::pair<uint64_t, uint64_t>, uint64_t> mapFertilizerToWater;
std::map<std::pair<uint64_t, uint64_t>, uint64_t> mapWaterToLight;
std::map<std::pair<uint64_t, uint64_t>, uint64_t> mapLightToTemperature;
std::map<std::pair<uint64_t, uint64_t>, uint64_t> mapTemperatureToHumidity;
std::map<std::pair<uint64_t, uint64_t>, uint64_t> mapHumidityLocation;

static void add_to_map(uint64_t destinationId, uint64_t sourceId, uint64_t len, std::map<std::pair<uint64_t, uint64_t>, uint64_t>& map)
{
    map[std::make_pair(sourceId, len)] = destinationId;
}


static void parse_map(const std::string& line, std::map<std::pair<uint64_t, uint64_t>, uint64_t>& map)
{
    std::stringstream ss(line);
    while (ss.good())
    {
        uint64_t destId{0};
        uint64_t srcId{0};
        uint64_t len{0};
        ss >> destId;
        ss >> srcId;
        ss >> len;
        add_to_map(destId, srcId, len, map);
    }
}

static uint64_t lookup(const uint64_t& id, const std::map<std::pair<uint64_t, uint64_t>, uint64_t>& map)
{
    uint64_t result{id};
    for (auto it=map.cbegin(); it!=map.cend(); ++it)
    {
        if (id >= it->first.first && id < it->first.first + it->first.second)
        {
            return it->second + (id - it->first.first);
        }
    }
    return result;
}

static uint64_t get_location(const uint64_t& seed)
{
    //std::cout << "Checking seed " << seed << "\n";

    uint64_t soil = lookup(seed, mapSeedToSoil);
    //std::cout << "Seed " << seed << " needs soil " << soil << "\n";

    uint64_t fertilizer = lookup(soil, mapSoilToFertilizer);
    //std::cout << "Soil " << soil << " needs fertilizer " << fertilizer << "\n";

    uint64_t water = lookup(fertilizer, mapFertilizerToWater);
    //std::cout << "Fertilizer " << fertilizer << " needs water " << water << "\n";

    uint64_t light = lookup(water, mapWaterToLight);
    //std::cout << "Water " << water << " needs light " << light << "\n";

    uint64_t temperature = lookup(light, mapLightToTemperature);
    //std::cout << "Light " << light << " needs temperature " << temperature << "\n";

    uint64_t humidity = lookup(temperature, mapTemperatureToHumidity);
    //std::cout << "Temperature " << temperature << " needs humidity " << humidity << "\n";

    uint64_t location = lookup(humidity, mapHumidityLocation);
    //std::cout << "Humidity " << humidity << " needs location " << location << "\n";

    return location;
}

int main(int argc, char **argv)
{
    auto inputFile = AoC::get_input_file_path("input05.txt");

    MapType parsingMap{MapType::None};
    std::vector<uint64_t> seedIds;

    auto f = [&] (const std::string& textLine) -> void
    {
        std::cout << textLine << "\n";

        if (textLine.substr(0, 7) == "seeds: ")
        {
            auto seeds = textLine.substr(7, textLine.length()-7);
            std::stringstream ss(seeds);
            while (ss.good())
            {
                uint64_t id{0};
                ss >> id;
                //std::cout << "Seed id : " << id << "\n";
                seedIds.push_back(id);
            }
        }
        if (textLine.empty())
        {
            return;
        }
        else if (textLine == "seed-to-soil map:")
        {
            parsingMap = MapType::SeedToSoil;
        }
        else if (textLine == "soil-to-fertilizer map:")
        {
            parsingMap = MapType::SoilToFertilizer;
        }
        else if (textLine == "fertilizer-to-water map:")
        {
            parsingMap = MapType::FertilizerToWater   ;
        }
        else if (textLine == "water-to-light map:")
        {
            parsingMap = MapType::WaterToLight;
        }
        else if (textLine == "light-to-temperature map:")
        {
            parsingMap = MapType::LightToTemperature;
        }
        else if (textLine == "temperature-to-humidity map:")
        {
            parsingMap = MapType::TemperatureToHumidity;
        }
        else if (textLine == "humidity-to-location map:")
        {
            parsingMap = MapType::HumidityToLocatio;
        }
        else if (parsingMap == MapType::SeedToSoil)
        {
            //std::cout << "Adding data [" << textLine << "] to mapSeedToSoil\n";
            parse_map(textLine, mapSeedToSoil);
        }
        else if (parsingMap == MapType::SoilToFertilizer)
        {
            //std::cout << "Adding data [" << textLine << "] to mapSoilToFertilizer\n";
            parse_map(textLine, mapSoilToFertilizer);
        }
        else if (parsingMap == MapType::FertilizerToWater)
        {
            //std::cout << "Adding data [" << textLine << "] to mapFertilizerToWater\n";
            parse_map(textLine, mapFertilizerToWater);
        }
        else if (parsingMap == MapType::WaterToLight)
        {
            //std::cout << "Adding data [" << textLine << "] to mapWaterToLight\n";
            parse_map(textLine, mapWaterToLight);
        }
        else if (parsingMap == MapType::LightToTemperature)
        {
            //std::cout << "Adding data [" << textLine << "] to mapLightToTemperature\n";
            parse_map(textLine, mapLightToTemperature);
        }
        else if (parsingMap == MapType::TemperatureToHumidity)
        {
            //std::cout << "Adding data [" << textLine << "] to mapTemperatureToHumidity\n";
            parse_map(textLine, mapTemperatureToHumidity);
        }
        else if (parsingMap == MapType::HumidityToLocatio)
        {
            //std::cout << "Adding data [" << textLine << "] to mapHumidityLocation\n";
            parse_map(textLine, mapHumidityLocation);
        }
    };

    if (!AoC::text_iterator(inputFile.c_str(), f))
    {
        std::cout << "Error iterating through " << inputFile << "\n";
    }

    std::optional<uint64_t> minLocation = std::nullopt;
    for (auto& seedId : seedIds)
    {
        std::cout << "Looking for seed id : " << seedId << "\n";
        auto location = get_location(seedId);
        if (!minLocation.has_value())
        {
            minLocation = location;
        }
        else
        {
            minLocation = std::min(minLocation.value(), location);
        }
    }

    std::cout << "Grand total: " << minLocation.value() << "\n";



    // seedIds.clear();
    // mapSeedToSoil.clear();
    // mapSoilToFertilizer.clear();
    // mapFertilizerToWater.clear();
    // mapWaterToLight.clear();
    // mapLightToTemperature.clear();
    // mapTemperatureToHumidity.clear();
    // mapHumidityLocation.clear();

    minLocation = std::nullopt;

    // if (!AoC::text_iterator(inputFile.c_str(), f))
    // {
    //     std::cout << "Error iterating through " << inputFile << "\n";
    // }

    for (auto it=seedIds.cbegin(); it!=seedIds.cend(); ++it)
    {
        auto seedId = *it;
        ++it;
        auto len = *it;
        std::cout << "Checking for " << len << " seeds from " << seedId << " to " << seedId+len << "\n";
        for (int i=0; i<len; ++i)
        {
            auto location = get_location(seedId+i);
            if (!minLocation.has_value())
            {
                minLocation = location;
            }
            else
            {
                minLocation = std::min(minLocation.value(), location);
            }
        }
        std::cout << "Batch result: " << minLocation.value() << "\n";
    }

    std::cout << "Grand total: " << minLocation.value() << "\n";

    return 0;
}