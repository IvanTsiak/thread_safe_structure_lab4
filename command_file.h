#pragma once
#include <string>
#include <vector>

void generateCommandFile(const std::string filename,
                        const std::vector<double>& percentages,
                        int numCommands);

void generate_files();