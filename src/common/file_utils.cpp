#include <file_utils.h>
#include <config.h>

#include <fstream>

namespace AoC
{

std::string get_input_file_path(const char *fileName)
{
    std::stringstream ss;
    ss << AoC::Settings::input_directory << "/" << fileName;

    return std::move(ss.str());
}

bool text_iterator(const char *fileName, const std::function<void(const std::string&)>& cbk)
{
    std::ifstream data(fileName);
    if (!data.is_open())
    {
        return false;
    }

    std::string line;
    while (getline(data, line))
    {
        if (!line.empty())
        {
            cbk(line);
        }
    }
    data.close();
    return true;
}
    
} // namespace AoC