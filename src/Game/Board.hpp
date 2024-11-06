#pragma once

#include "Cell.hpp"

#include <functional>
#include <vector>
#include <iostream>

typedef std::vector<Cell> gridOfCells;

class Board {
public:
#ifdef ENABLE_DEBUG

    [[nodiscard]] inline std::tuple<gridOfCells, std::size_t, std::size_t> retrieveDataForTest() const noexcept {
        return {_grid, _lineLength, _colLength};
    }

    void update(const gridOfCells &newGrid, std::size_t lineLength, std::size_t columnLength) {
        _grid = newGrid;
        set_lineLength(lineLength);
        set_colLength(columnLength);
    }

    inline void dumpGrid() const noexcept {
        for (size_t line = 0; line < _grid.size(); line += _colLength) {
            for (size_t column = 0; column < _colLength; column++) {
                std::cout << boolToChar(_grid[line + column].get_isCurrentlyAlive());
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

#endif

    Board() = default;

    Board(const Board &other) = delete;

    Board &operator=(const Board &other) = delete;

    Board(const Board &&other) = delete;

    Board &operator=(const Board &&other) = delete;

    ~Board() = default;

    Board(gridOfCells &&readGrid, size_t numberOfLines, size_t numberOfColumn);

    [[nodiscard]] constexpr inline const gridOfCells &get_grid_const() const noexcept { return _grid; }

    [[nodiscard]] constexpr inline gridOfCells &get_grid() noexcept{ return _grid; }

    [[nodiscard]] std::vector<std::reference_wrapper<Cell>> fillNeighbour(size_t line, size_t column) noexcept;

    [[nodiscard]] bool isCellAtBorder(size_t line, size_t column) const noexcept;

    [[nodiscard]] bool isCellBeforeTheBorder(size_t line, size_t column) const noexcept;

    void expandBoard() noexcept;

    void reduceBoard() noexcept;

    [[nodiscard]] inline size_t get_lineLength() const noexcept { return _lineLength; }

    [[nodiscard]] inline size_t get_colLength() const noexcept { return _colLength; }

private:
    inline void set_colLength(size_t newLength) noexcept { _colLength = newLength; }

    inline void set_lineLength(size_t newLength) noexcept { _lineLength = newLength; }

    gridOfCells _grid{};
    size_t _lineLength{0};
    size_t _colLength{0};
};
