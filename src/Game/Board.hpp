#pragma once

#include "Cell.hpp"

#include <functional>
#include <vector>
#include <iostream>

typedef std::vector<Cell> gridOfCells;

class Board
{
public:
#ifdef ENABLE_DEBUG
    [[nodiscard]] std::tuple<gridOfCells, std::size_t, std::size_t> retrieveDataForTest() { return {_grid, _lineLength, _colLength}; }
    void update(const gridOfCells &newGrid, std::size_t lineLength, std::size_t columnLength)
    {
        _grid = newGrid;
        set_lineLength(lineLength);
        set_colLength(columnLength);
    }
#endif

    Board() = default;

    Board(const Board &other) = delete;

    Board &operator=(const Board &other) = delete;

    Board(const Board &&other) = delete;

    Board &operator=(const Board &&other) = delete;

    ~Board() = default;

    Board(gridOfCells &&readGrid, size_t numberOfLines, size_t numberOfColumn);

    [[nodiscard]] constexpr const gridOfCells &get_grid_const() const { return _grid; }

    [[nodiscard]] constexpr gridOfCells &get_grid() { return _grid; }

    [[nodiscard]] std::vector<std::reference_wrapper<Cell>> fillNeighbour(size_t line, size_t column);

    [[nodiscard]] bool isCellAtBorder(size_t line, size_t column) const;

    [[nodiscard]] bool isCellBeforeTheBorder(size_t line, size_t column) const;

    void expandBoard();

    void reduceBoard();

    [[nodiscard]] size_t get_lineLength() const;
    [[nodiscard]] size_t get_colLength() const;

private:
    void set_colLength(size_t newLength);
    void set_lineLength(size_t newLength);

    gridOfCells _grid{};
    size_t _lineLength{0};
    size_t _colLength{0};
};
