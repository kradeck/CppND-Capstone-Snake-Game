#include "config_file_parser.hpp"

#include <sstream>

std::vector<std::pair<std::string, std::string>> ConfigFileParser::operator()()
{
    std::string variable{}, value{};
    std::string line{};
       
    std::vector<std::pair<std::string, std::string>> parameters{};
        
    while (std::getline(file_, line))
    {
        std::istringstream iss(line);
        iss >> variable >> value;

        // if variable starts with # then the line is a comment
        if (variable[0] != '#')
        {
            parameters.push_back(std::make_pair(variable, value));
        }
    }
    return std::move(parameters);
}
