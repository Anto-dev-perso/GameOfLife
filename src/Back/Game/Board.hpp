#pragma once

#include "Cell.hpp"

#include <functional>
#include <vector>
#include <iostream>

using grid_of_cells = std::vector<Cell>;
using line_size = std::size_t;
using column_size = std::size_t;

struct board_data
{
    grid_of_cells grid{};
    line_size line{0};
    column_size column{0};

    [[nodiscard]] bool empty() const noexcept { return grid.empty(); }

    void clear() noexcept
    {
        grid.clear();
        line = 0;
        column = 0;
    }
};

class Board
{
public:
#ifdef ENABLE_DEBUG

    [[nodiscard]] inline board_data retrieveDataForTest() const noexcept
    {
        return {_grid, _lineLength, _colLength};
    }

    inline void dumpGrid() const noexcept
    {
        for (size_t line = 0; line < _grid.size(); line += _colLength)
        {
            for (size_t column = 0; column < _colLength; column++)
            {
                std::cout << boolToChar(_grid[line + column].get_isCurrentlyAlive());
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

#endif

    Board() = default;

    Board(const Board& other) = delete;

    Board& operator=(const Board& other) = delete;

    Board(const Board&& other) = delete;

    Board& operator=(const Board&& other) = delete;

    ~Board() = default;

    explicit Board(board_data&& readGrid) : _grid(readGrid.grid),
                                            _lineLength(readGrid.line),
                                            _colLength(readGrid.column)
    {
    }

    Board(grid_of_cells& readGrid, size_t numberOfLines, size_t numberOfColumn) : _grid(readGrid),
        _lineLength(numberOfLines),
        _colLength(numberOfColumn)
    {
    }

    [[nodiscard]] constexpr inline const grid_of_cells& get_grid_const() const noexcept { return _grid; }

    [[nodiscard]] constexpr inline grid_of_cells& get_grid() noexcept { return _grid; }

    [[nodiscard]] std::vector<std::reference_wrapper<Cell>> fillNeighbour(size_t line, size_t column) noexcept;

    [[nodiscard]] bool isCellAtBorder(size_t line, size_t column) const noexcept;

    [[nodiscard]] bool isCellBeforeTheBorder(size_t line, size_t column) const noexcept;

    void expandBoard() noexcept;

    void reduceBoard() noexcept;

    [[nodiscard]] constexpr size_t get_lineLength() const noexcept { return _lineLength; }

    [[nodiscard]] constexpr size_t get_colLength() const noexcept { return _colLength; }

    [[nodiscard]] bool isCellAliveAtIndex(size_t index) const
    {
        if (index >= _grid.size())
        {
            throw std::out_of_range("Cell index out of bounds");
        }
        return _grid.at(index).get_isCurrentlyAlive();
    };

    [[nodiscard]] bool changeCellValue(size_t index, bool newValue)
    {
        if (index >= _grid.size())
        {
            throw std::out_of_range("Cell index out of bounds");
        }
        if (_grid.at(index).get_isCurrentlyAlive() == newValue)
        {
            return false;
        }
        auto& cell = _grid[index];
        cell.memorizePreviousAliveValue();
        cell.set_isCurrentlyAlive(newValue);
        return true;
    };

    void update(const board_data& grid) noexcept
    {
        _grid = grid.grid;
        _lineLength = grid.line;
        _colLength = grid.column;
    }

    void clear() noexcept
    {
        _grid.clear();
        _lineLength = 0;
        _colLength = 0;
    }

private:
    inline void set_colLength(size_t newLength) noexcept { _colLength = newLength; }

    inline void set_lineLength(size_t newLength) noexcept { _lineLength = newLength; }

    grid_of_cells _grid{};
    size_t _lineLength{0};
    size_t _colLength{0};
};
