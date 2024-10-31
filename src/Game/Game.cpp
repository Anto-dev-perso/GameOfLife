#include "Game.hpp"

#include<algorithm>
#include<execution>

using namespace std;

Game::Game(string_view path, unsigned int iterations, bool all) : _filePath(path),
                                                                  _nbOfIterations(iterations),
                                                                  _outputAllIterations(all),
                                                                  _fileParser(Parser(_filePath)),
                                                                  _outputWriter(make_unique<OutputWriter>(
                                                                      _filePath))
{
}

bool Game::init()
{
    auto [grid, lineLength, columnLength] = _fileParser.parseInputFile();
    _board = make_unique<Board>(std::move(grid), lineLength, columnLength);

    // If parsing fail, grid is empty. In this case, return that it failed
    return !_board->get_grid_const().empty();
}

bool Game::process()
{
    bool processOK{true};

    // Loop for iteration
    for (unsigned int currentIteration = 1; currentIteration <= _nbOfIterations; currentIteration++)
    {
        const auto [expand, reduce] = applyRulesToTheBoardForIteration(currentIteration);
        if (expand)
        {
            _board->expandBoard();
        }
        else if (reduce)
        {
            _board->reduceBoard();
        }

        if (_outputAllIterations)
        {
            processOK = _outputWriter->writeIteration(_board->get_grid_const(), _board->get_colLength(),
                                                      currentIteration) &&
                processOK;
        }
    }

    processOK = _outputWriter->writeIteration(_board->get_grid_const(), _board->get_colLength()) && processOK;

    return processOK;
}

// Because we will change Cell's alive status, we need to retrieve the reference to the grid
// To avoid looping multiple times (one to know if the cell will be alive or dead and one for editing the value), we set directly the new value and we memorize the old one
// Memmrize also the last iteration at which we modify the value of the cells to avoid using the memrization instead of the actual value
// So the loop use the memory value to the rules and set the values directly
std::tuple<bool, bool> Game::applyRulesToTheBoardForIteration(unsigned int onGoingIteration) const
{
    bool expandSizeOfGrid{false}; // Boolean to detect if the grid should be expanded
    bool reduceSizeOfGrid{true}; // Boolean to detect if the grid could be reduce

    // Put the loop in a scope to not keep all of these when we will resize the board
    // We avoid keeping a reference to the grid while this object change (resize)
    {
        vector<reference_wrapper<Cell>> neighbours;
        neighbours.reserve(
            8); // Reserve maximum possible number of neighbours to avoid multiple allocation/deallocation

        auto& grid{_board->get_grid()};
        const auto& numColumn{_board->get_colLength()};

        for_each(execution::par_unseq, grid.begin(), grid.end(), [&](Cell& cellToApply)
        {
            const size_t currentId{static_cast<size_t>(&cellToApply - &grid[0])};
            const size_t column{currentId % numColumn};
            const size_t line{currentId - column};

            neighbours = _board->fillNeighbour(line, column);

            cellToApply.memorizePreviousAliveValue();

            const bool rule1{applyRule1(cellToApply, neighbours, onGoingIteration)};
            const bool rule2{applyRule2(cellToApply, neighbours, onGoingIteration)};
            const bool resultOfRules{(rule1 && rule2) || applyRule3()};

            cellToApply.set_isCurrentlyAlive(resultOfRules);
            cellToApply.set_lastIterationWhichModif(onGoingIteration);

            neighbours.clear();

            // Before to continue the loop, check if we are at the border of the board and if so, if we have to expand or reduce
            if (_board->isCellAtBorder(line, column))
            {
                // expand means that at least one cell at the border is alive
                expandSizeOfGrid = expandSizeOfGrid || resultOfRules;

                // reduce means that all cells at the border are dead (resultOfRules==false)
                reduceSizeOfGrid = reduceSizeOfGrid && !resultOfRules;
            }
            else if (_board->isCellBeforeTheBorder(line, column))
            {
                // reduce means that all cells at before border are dead (resultOfRules==false)
                reduceSizeOfGrid = reduceSizeOfGrid && !resultOfRules;
            }
        });
    }
    return {expandSizeOfGrid, reduceSizeOfGrid};
}

// Rule 1 of the Game : Any living cell with two or three living neighbours survives
bool Game::applyRule1(Cell& currentCell, const std::vector<std::reference_wrapper<Cell>>& neighbours,
                      unsigned int onGoingIteration)
{
    if (!currentCell.isCellAlive(onGoingIteration))
    {
        return true;
    }

    short livingNeighbours{0};
    for (const auto& currentNeighbour : neighbours)
    {
        if (currentNeighbour.get().isCellAlive(onGoingIteration))
        {
            livingNeighbours++;
        }
    }
    return (livingNeighbours == 2 || livingNeighbours == 3);
}

// Rule 2 of the Game : Any dead cell with three living neighbours survives
bool Game::applyRule2(Cell& currentCell, const vector<std::reference_wrapper<Cell>>& neighbours,
                      unsigned int onGoingIteration)
{
    if (currentCell.isCellAlive(onGoingIteration))
    {
        return true;
    }

    short livingNeighbours{0};
    for (const auto& currentNeighbour : neighbours)
    {
        if (currentNeighbour.get().isCellAlive(onGoingIteration))
        {
            livingNeighbours++;
        }
    }
    return livingNeighbours == 3;
}

const Board* Game::get_board_const() const { return _board.get(); }
