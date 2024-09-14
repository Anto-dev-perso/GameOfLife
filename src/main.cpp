#include <iostream>

#include "InputChecker.hpp"
#include "Game/Game.hpp"

using namespace std;

int main(int argc, char **argv) {

    std::cout << "Hello, World!" << std::endl;

    InputChecker checker;
    auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

    if (!inputsValids) { return 1; }

    Game gameOfLife(filePath, nbOfIterations, outputAllIterations);

    return 0;
}
