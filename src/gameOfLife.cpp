#include "InputChecker.hpp"
#include "Game/Game.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    static InputChecker checker;
    const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

    if (!inputsValids) { return 1; }

    static Game gameOfLife(filePath, nbOfIterations, outputAllIterations);

    // True==1 but 1 is an error return so return the opposite of the return
    return !gameOfLife.process();
}
