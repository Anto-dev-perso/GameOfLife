#include "Game.hpp"

#include <algorithm>

using namespace std;

bool Game::init() noexcept
{
    board_data readBoard;
    if (const auto varFileParse{_fileParser.parseFile()}; std::holds_alternative<board_data>(varFileParse))
    {
        readBoard = std::get<board_data>(varFileParse);
    }

    else if (std::holds_alternative<PatternList>(varFileParse))
    {
        _patterns = std::get<PatternList>(varFileParse);

        boardPattern = _patterns.findIndexForPatterNamed("glider");
        readBoard = _patterns.getPatternForIndices(boardPattern.patternIndex, boardPattern.gridIndex);
    }

    _board = make_unique<Board>(std::move(readBoard));
    // If parsing fail, grid is empty. In this case, return that it failed
    return !_board->get_grid_const().empty();
}

bool Game::process() const noexcept
{
    bool processOK{true};

    // Loop for iteration
    for (unsigned int currentIteration = 1; currentIteration <= _nbOfIterations; currentIteration++)
    {
        const auto [expand, reduce, unused] = applyRulesToTheBoardForIteration(currentIteration);
        std::ignore = checkIfBoardNeedToBeResize(expand, reduce);

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
// To avoid looping multiple times (one to know if the cell will be alive or dead and one for editing the value), we set directly the new value, and we memorize the old one
// Memorize also the last iteration at which we modify the value of the cells to avoid using the memorization instead of the actual value
std::tuple<bool, bool, std::vector<Game::pair_of_indices>> Game::applyRulesToTheBoardForIteration(
    unsigned int onGoingIteration) const noexcept
{
    // macro this to appear only on the Qt part
    std::vector<pair_of_indices> indicesModified;

    bool expandSizeOfGrid{false}; // Boolean to detect if the grid should be expanded
    bool reduceSizeOfGrid{true};  // Boolean to detect if the grid could be reduced

    // Put the loop in a scope to not keep all of these when we will resize the board
    // We avoid keeping a reference to the grid while this object change (resize)
    {
        vector<reference_wrapper<Cell>> neighbours;
        neighbours.reserve(8);
        // Reserve maximum possible number of neighbours to avoid multiple allocation/reallocation

        auto &grid{_board->get_grid()};
        const auto &numColumn{_board->get_colLength()};

        // TODO have counter of alive cell ?
        indicesModified.reserve(grid.size() / 4);

        for_each(grid.begin(), grid.end(), [&](Cell &cellToApply)
                 {
            const size_t currentId{static_cast<size_t>(&cellToApply - &grid[0])};
            const size_t column{currentId % numColumn};
            const size_t line{currentId / numColumn};


            neighbours = _board->fillNeighbour(line, column);

            cellToApply.memorizePreviousAliveValue();

            const bool rule1{applyRule1(cellToApply, neighbours, onGoingIteration)};
            const bool rule2{applyRule2(cellToApply, neighbours, onGoingIteration)};
            const bool resultOfRules{(rule1 && rule2) || applyRule3()};

            if (cellToApply.get_isPreviouslyAlive() != resultOfRules)
            {
                cellToApply.set_isCurrentlyAlive(resultOfRules);
                // Push back directly if it is the first element or if the last pair inserted is complete (second is not null)
                if (indicesModified.empty() || indicesModified.rbegin()->second != EMTPY_PAIR_OF_INDICES)
                {
                    indicesModified.emplace_back(line_column{line, column}, EMTPY_PAIR_OF_INDICES);
                }
            }
            else
            {
                // Use the value of the current id even if it hasn't been modified to avoid if/else madness for nothing
                if (!indicesModified.empty() && indicesModified.rbegin()->second == EMTPY_PAIR_OF_INDICES)
                {
                    indicesModified.rbegin()->second = {currentId / numColumn, column};
                }
            }

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
            } });
    }
    return {expandSizeOfGrid, reduceSizeOfGrid, std::move(indicesModified)};
}

// So the loop use the memory value to the rules and set the values directly

// Rule 1 of the Game : Any living cell with two or three living neighbours survives
bool Game::applyRule1(const Cell &currentCell, const std::vector<std::reference_wrapper<Cell>> &neighbours,
                      unsigned int onGoingIteration) noexcept
{
    if (!currentCell.isCellAlive(onGoingIteration))
    {
        return true;
    }

    short livingNeighbours{0};
    for (const auto &currentNeighbour : neighbours)
    {
        if (currentNeighbour.get().isCellAlive(onGoingIteration))
        {
            livingNeighbours++;
        }
    }
    return (livingNeighbours == 2 || livingNeighbours == 3);
}

// Rule 2 of the Game : Any dead cell with three living neighbours survives
bool Game::applyRule2(const Cell &currentCell, const vector<std::reference_wrapper<Cell>> &neighbours,
                      unsigned int onGoingIteration) noexcept
{
    if (currentCell.isCellAlive(onGoingIteration))
    {
        return true;
    }

    short livingNeighbours{0};
    for (const auto &currentNeighbour : neighbours)
    {
        if (currentNeighbour.get().isCellAlive(onGoingIteration))
        {
            livingNeighbours++;
        }
    }
    return livingNeighbours == 3;
}
