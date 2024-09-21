#include "Board.hpp"

#include <utility>

using namespace std;

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
