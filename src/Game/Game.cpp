#include "Game.hpp"

using namespace std;

Game::Game(string_view path, unsigned int iterations, bool all) : _filePath(path),
                                                                  _nbOfIterations(iterations),
                                                                  _outputAllIterations(all),
                                                                  _fileParser(Parser(_filePath)),
                                                                  _outputWriter(make_unique<OutputWriter>(
                                                                          _filePath)) {}

bool Game::init() {
    // Use NRVO to avoid copy
    // Another possibility would be to return an optional (with std::move) but it makes the binary heavier for a non-significant gain
    _board = make_unique<Board>(_fileParser.parseInputFile());

    // If parsing fail, grid is empty. In this case, return that it failed
    return !_board->get_grid_const().empty();
}

bool Game::process() {


    bool processOK{true};

    // Loop for iteration
    for (unsigned int currentIteration = 1; currentIteration <= _nbOfIterations; currentIteration++) {

        applyRulesToTheBoard(0);
        // TODO resize before write
        // For the resize : keep one border of dead cells to be able to always extend the grid

        if (_outputAllIterations) {
            processOK = _outputWriter->writeIteration(_board->get_grid_const(), currentIteration) &&
                        processOK;
        }
    }


    processOK = _outputWriter->writeIteration(_board->get_grid_const()) && processOK;
    return processOK;
}

// Because we will change Cell's alive status, we need to retrieve the reference to the grid
// To avoid looping multiple times (one to know if the cell will be alive or dead and one for editing the value), we set directly the new value and we memorize the old one
// Memmrize also the last iteration at which we modify the value of the cells to avoid using the memrization instead of the actual value
// So the loop use the memory value to the rules and set the values directly
void Game::applyRulesToTheBoard(unsigned int onGoingIteration) const {
    vector<reference_wrapper<Cell>> neighbours;
    neighbours.reserve(8); // Reserve maximum possible number of neighbours to avoid multiple allocation/deallocation

    auto &grid = _board->get_grid();
    for (size_t line = 0; line < grid.size(); line++) {
        for (size_t column = 0; column < grid[line].size(); column++) {
            Cell &cellToApply{grid[line][column]};

            neighbours = _board->fillNeighbour(line, column);

            cellToApply.memorizePreviousAliveValue();

            const bool rule1 = applyRule1(cellToApply, neighbours, onGoingIteration);
            const bool rule2 = applyRule2(cellToApply, neighbours, onGoingIteration);

            cellToApply.set_isCurrentlyAlive((rule1 && rule2) || applyRule3());
            cellToApply.set_lastIterationWhichModif(onGoingIteration);

            neighbours.clear();
        }
    }
}


// Rule 1 of the Game : Any living cell with two or three living neighbours survives
bool Game::applyRule1(Cell &currentCell, const std::vector<std::reference_wrapper<Cell>> &neighbours,
                      unsigned int onGoingIteration) {
    if (!currentCell.isCellAlive(onGoingIteration)) {
        return true;
    }

    short livingNeighbours{0};
    for (const auto &currentNeighbour: neighbours) {
        if (currentNeighbour.get().isCellAlive(onGoingIteration)) { livingNeighbours++; }
    }
    return (livingNeighbours == 2 || livingNeighbours == 3);
}

// Rule 2 of the Game : Any dead cell with three living neighbours survives
bool Game::applyRule2(Cell &currentCell, const vector<std::reference_wrapper<Cell>> &neighbours,
                      unsigned int onGoingIteration) {
    if (currentCell.isCellAlive(onGoingIteration)) {
        return true;
    }

    short livingNeighbours{0};
    for (const auto &currentNeighbour: neighbours) {
        if (currentNeighbour.get().isCellAlive(onGoingIteration)) { livingNeighbours++; }
    }
    return livingNeighbours == 3;
}


const Board *Game::get_board_const() const { return _board.get(); }

void Game::set_board(const gridOfCells &newGrid) {
    _board->set_grid(newGrid);
}
