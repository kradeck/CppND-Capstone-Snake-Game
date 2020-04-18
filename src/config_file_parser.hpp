/*
* ========================================================================= *
*        Project: Udacity - CppND - Capstone                                *
*         Author: Krzysztof Radecki ( radeckikrzysztof@gmail.com )          *
*           Date: 2020                                                      *
* ========================================================================= *
*/

/*
 * The class can parse a file with parameters in the following schema:
 * "variable value #comments",
 * comments are ignored. 
 * The variable, the value ant the comment (if provided) 
 * are separated with white space.
 * Lines starting with # are ignored. 
 * Parameters are loaded as strings into: 
 * std::vector<std::pair<string[variable], string[value]>>.
 * 
 * Usage example:
 * [code]
 * ...
 * ConfigFileParser fp(config_path);
 * auto parameters_vector = fp();
 * ...
 * [/code]
 *
 * where the config_path is the path to the configuration file,
 * parameters_map is the map<string[variable], string[value]> where variables
 * are covering the viariables in the file. 
 * There is no content validation during parsing the file.
 */

#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <utility>

class ConfigFileParser
{
public:
    explicit ConfigFileParser(const std::string& file_name)
    {
        file_.open(file_name, std::ios_base::in);
        if (!file_.is_open())
            throw std::ios_base::failure("Cannot open configuration file");
    }

    ~ConfigFileParser()
    {
        if (!file_.is_open())
            file_.close();
    }

    std::vector<std::pair<std::string, std::string>> operator()();

private:
    std::ifstream file_{};
};
