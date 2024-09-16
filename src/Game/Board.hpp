#pragma once

#include "Cell.hpp"

#include <functional>
#include <vector>

// TODO replace by a vector<Cell> for performance
typedef std::vector<std::vector<Cell>> gridOfCells;

class Board {
public:

    [[nodiscard]] const gridOfCells &get_grid_const() const;

    [[nodiscard]] gridOfCells &get_grid();

    [[nodiscard]] std::vector<std::reference_wrapper<Cell>> fillNeighbour(size_t line, size_t column);

    void set_grid(gridOfCells &&newGrid);

    void set_grid(const gridOfCells &newGrid);


private:

    gridOfCells _grid;

};
