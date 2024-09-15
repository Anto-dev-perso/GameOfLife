#include "Game.hpp"

using namespace std;

Game::Game(string_view path, unsigned int iterations, bool all) : _filePath(path),
                                                                  _nbOfIterations(iterations),
                                                                  _outputAllIterations(all),
                                                                  _board(make_unique<Board>()), _outputWriter(
                make_unique<OutputWriter>(_filePath)) {}

bool Game::process() {

    bool processOK{true};

    for (unsigned int currentIteration = 1; currentIteration <= _nbOfIterations; currentIteration++) {

        if (_outputAllIterations) {
            processOK = _outputWriter->writeIteration(_board->get_grid(), currentIteration) &&
                        processOK;
        }
    }

    processOK = _outputWriter->writeIteration(_board->get_grid()) && processOK;
    return processOK;
}
