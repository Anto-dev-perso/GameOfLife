#include "Board.hpp"

#include <utility>

using namespace std;

// Define a minimum size for the line or column
static constexpr size_t minSize{5};

Board::Board(gridOfCells &&readGrid) : _grid(std::move(readGrid)) {}

std::vector<std::reference_wrapper<Cell>>
Board::fillNeighbour(size_t line, size_t column) {

    if (line >= _grid.size() || column >= _grid.size()) { return {}; }

    const bool lineAtUpLimit{line + 1 == _grid.size()};
    const bool columnAtUpLimit{column + 1 == _grid[line].size()};
    const bool lineAtLowLimit{line <= 0};
    const bool columnAtLowLimit{column <= 0};

    // Cast to a reference in order to return a vector a reference_wrapper (avoid copy)
    auto &gridRef = static_cast<gridOfCells &>(_grid);

    // We can do all neighbours
    if (!columnAtUpLimit && !columnAtLowLimit && !lineAtUpLimit && !lineAtLowLimit) {
        return {{gridRef[line + 1][column + 1],
                 gridRef[line][column + 1],
                 gridRef[line - 1][column + 1],
                 gridRef[line + 1][column],
                 gridRef[line - 1][column],
                 gridRef[line + 1][column - 1],
                 gridRef[line][column - 1],
                 gridRef[line - 1][column - 1]}};

    }
        // Line -1 isn't possible
    else if (!columnAtUpLimit && !columnAtLowLimit && !lineAtUpLimit && lineAtLowLimit) {
        return {gridRef[line + 1][column + 1],
                gridRef[line][column + 1],
                gridRef[line + 1][column],
                gridRef[line + 1][column - 1],
                gridRef[line][column - 1]};
    }
        // Line +1 isn't possible
    else if (!columnAtUpLimit && !columnAtLowLimit && lineAtUpLimit && !lineAtLowLimit) {
        return {gridRef[line][column + 1],
                gridRef[line - 1][column + 1],
                gridRef[line - 1][column],
                gridRef[line][column - 1],
                gridRef[line - 1][column - 1]};
    }
        // Col -1 isn't possible
    else if (!columnAtUpLimit && columnAtLowLimit && !lineAtUpLimit && !lineAtLowLimit) {
        return {gridRef[line + 1][column + 1],
                gridRef[line][column + 1],
                gridRef[line - 1][column + 1],
                gridRef[line + 1][column],
                gridRef[line - 1][column]};
    }
        // Col+1 isn't possible
    else if (columnAtUpLimit && !columnAtLowLimit && !lineAtUpLimit && !lineAtLowLimit) {
        return {gridRef[line + 1][column],
                gridRef[line - 1][column],
                gridRef[line + 1][column - 1],
                gridRef[line][column - 1],
                gridRef[line - 1][column - 1]};
    }
        // Col -1 and Line -1 isn't possible
    else if (!columnAtUpLimit && columnAtLowLimit && !lineAtUpLimit && lineAtLowLimit) {
        return {gridRef[line + 1][column + 1],
                gridRef[line][column + 1],
                gridRef[line + 1][column]};
    }
        // Col -1 and Line +1 isn't possible
    else if (!columnAtUpLimit && columnAtLowLimit && lineAtUpLimit && !lineAtLowLimit) {
        return {
                gridRef[line][column + 1],
                gridRef[line - 1][column + 1],
                gridRef[line - 1][column]};
    }
        // Col +1 and Line -1 isn't possible
    else if (columnAtUpLimit && !columnAtLowLimit && !lineAtUpLimit && lineAtLowLimit) {
        return {
                gridRef[line + 1][column],
                gridRef[line + 1][column - 1],
                gridRef[line][column - 1]};
    }
        // Col +1 and Line +1 isn't possible
    else if (columnAtUpLimit && !columnAtLowLimit && lineAtUpLimit && !lineAtLowLimit) {
        return {
                gridRef[line - 1][column],
                gridRef[line][column - 1],
                gridRef[line - 1][column - 1]};
    } else {// All case are dealt with the if/else if but return empty
        return {};
    }
}

void Board::set_grid(gridOfCells &&newGrid) {
    _grid.clear();
    _grid = std::move(newGrid);
}

void Board::set_grid(const gridOfCells &newGrid) {
    _grid.clear();
    _grid = newGrid;
}

bool Board::isCellAtBorder(size_t line, size_t column) const {
    // Because we have a grid, all lines have the same number of column
    // So we have just to verify that the current line indice is the first or the last one (idem for column)
    return (((line == 0) || (line == _grid.size() - 1)) || ((column == 0) || (column == _grid.begin()->size() - 1)));
}

bool Board::isCellBeforeTheBorder(size_t line, size_t column) const {
    // Because we have a grid, all lines have the same number of column
    // So we have just to verify that the current line indice is the second or the penultimate (idem for column)
    return (((line == 1) || (line == _grid.size() - 2)) || ((column == 1) || (column == _grid.begin()->size() - 2)));
}

// To expand the board, we have to add one line at beginning and end and for each line, add one column at beginning and end
void Board::expandBoard() {
    const size_t newColumnSize{_grid.begin()->size() + 2};

    // Reserve the new size needed (may cause re-allocation)
    _grid.reserve(_grid.size() + 2);

    // Insert at the beginning first because vector will have to move all elements so avoid to move the new element insert in the back
    _grid.emplace(_grid.begin(), lineOfGrid(newColumnSize, getDeadChar()));
    _grid.emplace_back(lineOfGrid(newColumnSize, getDeadChar()));

    // Loop through every lines (except first and last one) and add the new column
    for (unsigned line = 1; line < _grid.size() - 1; ++line) {
        auto &currentLine{_grid[line]};

        // Reserve the new size needed (may cause re-allocation)
        currentLine.reserve(newColumnSize);

        // Insert at the beginning first because vector will have to move all elements so avoid to move the new element insert in the back
        currentLine.emplace(currentLine.begin(), getDeadChar());
        currentLine.emplace_back(getDeadChar());
    }
}

// To reduce the board, we have to remove one line at beginning and end and for each line, reùove one column at beginning and end
void Board::reduceBoard() {
    // Don't go to low in the size of the board
    if (_grid.size() <= minSize || _grid.begin()->size() <= minSize) { return; }

    _grid.erase(_grid.begin());
    _grid.pop_back();

    // Loop through every lines and erase the columns
    for (unsigned line = 0; line < _grid.size(); ++line) {
        auto &currentLine{_grid[line]};

        // Insert at the beginning first because vector will have to move all elements so avoid to move the new element insert in the back
        currentLine.erase(currentLine.begin());
        currentLine.pop_back();
    }
}
