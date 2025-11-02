#include "command_file.h"
#include "optimized_structure.h"
#include "test_engine.h"

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <functional>
#include <iomanip>

void runScenarioTests(ThreadSafe& structure,
    const std::vector<std::vector<Command>>& allCommands,
    int baseIndex
) {
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double, std::milli> duration;

    start = std::chrono::high_resolution_clock::now();
    executeCommands(structure, allCommands[baseIndex]);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "1 thread: " << duration.count() << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    {
        std::thread t1(executeCommands, std::ref(structure), std::cref(allCommands[baseIndex]));
        std::thread t2(executeCommands, std::ref(structure), std::cref(allCommands[baseIndex + 1]));
        t1.join();
        t2.join();
    }
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "2 threads: " << duration.count() << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    {
        std::thread t1(executeCommands, std::ref(structure), std::cref(allCommands[baseIndex]));
        std::thread t2(executeCommands, std::ref(structure), std::cref(allCommands[baseIndex + 1]));
        std::thread t3(executeCommands, std::ref(structure), std::cref(allCommands[baseIndex + 2]));
        t1.join();
        t2.join();
        t3.join();
    }
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "3 threads: " << duration.count() << " ms" << std::endl;
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    try {
        std::vector<std::vector<Command>> commands(9);

        commands[0] = loadCommands("commands_a1.txt");
        commands[1] = loadCommands("commands_a2.txt");
        commands[2] = loadCommands("commands_a3.txt");
        commands[3] = loadCommands("commands_b1.txt");
        commands[4] = loadCommands("commands_b2.txt");
        commands[5] = loadCommands("commands_b3.txt");
        commands[6] = loadCommands("commands_c1.txt");
        commands[7] = loadCommands("commands_c2.txt");
        commands[8] = loadCommands("commands_c3.txt");

        ThreadSafe sharedStructure;

        std::cout << "\nScenario  A:" << std::endl;
        runScenarioTests(sharedStructure, commands, 0);
        std::cout << "\nScenario  B:" << std::endl;
        runScenarioTests(sharedStructure, commands, 3);
        std::cout << "\nScenario  C:" << std::endl;
        runScenarioTests(sharedStructure, commands, 6);
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    return 0;
}