#ifndef FILE_UTILS
#define FILE_UTILS

#include <sstream>
#include <functional>

namespace AoC
{

std::string get_input_file_path(const char *fileName);
bool text_iterator(const char *fileName, const std::function<void(const std::string&)>& cbk);
    
} // namespace AoC

 #endif // FILE_UTILS