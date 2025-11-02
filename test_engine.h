#pragma once

#include "optimized_structure.h"

#include <vector>
#include <string>

enum class OpType {
    READ,
    WRITE,
    STRING
};

struct Command {
    OpType type;
    int fieldIndex;
    int value;
};

std::vector<Command> loadCommands(const std::string& filename);

void executeCommands(ThreadSafe& structure, const std::vector<Command>& commands);

