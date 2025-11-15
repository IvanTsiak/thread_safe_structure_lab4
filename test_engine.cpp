#include "test_engine.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<Command> loadCommands(const std::string& filename) {
    std::vector<Command> commands;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open command file: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string op;
        ss >> op;

        if (op == "read") {
            int index;
            ss >> index;
            commands.push_back({OpType::READ, index, 0});
        } else if (op == "write") {
            int index, value;
            ss >> index >> value;
            commands.push_back({OpType::WRITE, index, value});
        } else if (op == "string") {
            commands.push_back({OpType::STRING, 0, 0});
        }
    }
    return commands;
}

void executeCommands(ThreadSafe& structure, const std::vector<Command>& commands) {
    for (const auto& cmd : commands) {
        switch (cmd.type) {
            case OpType::READ:
                if (cmd.fieldIndex == 0) {
                    structure.getField0();
                } else {
                    structure.getField1();
                }
                break;
            case OpType::WRITE:
                if (cmd.fieldIndex == 0) {
                    structure.setField0(cmd.value);
                } else {
                    structure.setField1(cmd.value);
                }
                break;
            case OpType::STRING:
                (void)static_cast<std::string>(structure);
                break;
        }
    }
}