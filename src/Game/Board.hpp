#pragma once

#include "Cell.hpp"

#include <functional>
#include <vector>

// TODO replace by a vector<Cell> for performance
typedef std::vector<std::vector<Cell>> gridOfCells;

class Board {
public:

    Board() = default;

    Board(const Board &other) = delete;

    Board &operator=(const Board &other) = delete;

    Board(const Board &&other) = delete;

    Board &operator=(const Board &&other) = delete;

    ~Board() = default;

    Board(gridOfCells &&readGrid);

    [[nodiscard]] constexpr const gridOfCells &get_grid_const() const { return _grid; }

    [[nodiscard]] constexpr gridOfCells &get_grid() { return _grid; }

    [[nodiscard]] std::vector<std::reference_wrapper<Cell>> fillNeighbour(size_t line, size_t column);

    void set_grid(gridOfCells &&newGrid);

    void set_grid(const gridOfCells &newGrid);


private:

    gridOfCells _grid{};

};
