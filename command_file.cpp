#include "command_file.h"

#include <random>
#include <iostream>
#include <fstream>
#include <stdexcept>

void generateCommandFile(const std::string filename,
                        const std::vector<double>& percentages,
                        int numCommands) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Error: Could not create file: " + filename);
    }

    for (int i = 0; i < numCommands; ++i) {
        double r = dis(gen);
        
        if (r < percentages[0]) {
            outFile << "read 0\n";
        } else if (r < percentages[1]) {
            outFile << "write 0 1\n";
        } else if (r < percentages[2]) {
            outFile << "read 1\n";
        } else if (r < percentages[3]) {
            outFile << "write 1 1\n";
        } else {
            outFile << "string\n";
        }
    }
}

void generate_files() {
    const int COMMANDS_PER_FILE = 1000000;

    const std::vector<double> percentages_a = {0.20, 0.30, 0.55, 0.65, 1.00};
    const std::vector<double> percentages_b = {0.20, 0.40, 0.60, 0.80, 1.00};
    const std::vector<double> percentages_c = {0.025, 0.050, 0.075, 0.100, 1.00};

    generateCommandFile("commands_a1.txt", percentages_a, COMMANDS_PER_FILE);
    generateCommandFile("commands_a2.txt", percentages_a, COMMANDS_PER_FILE);
    generateCommandFile("commands_a3.txt", percentages_a, COMMANDS_PER_FILE);

    generateCommandFile("commands_b1.txt", percentages_b, COMMANDS_PER_FILE);
    generateCommandFile("commands_b2.txt", percentages_b, COMMANDS_PER_FILE);
    generateCommandFile("commands_b3.txt", percentages_b, COMMANDS_PER_FILE);

    generateCommandFile("commands_c1.txt", percentages_c, COMMANDS_PER_FILE);
    generateCommandFile("commands_c2.txt", percentages_c, COMMANDS_PER_FILE);
    generateCommandFile("commands_c3.txt", percentages_c, COMMANDS_PER_FILE);
}