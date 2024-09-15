#pragma once

#include "Cell.hpp"
#include <vector>

typedef std::vector<std::vector<Cell>> gridOfCells;

class Board {
public:

    [[nodiscard]] const gridOfCells &get_grid() const;

private:

    gridOfCells _grid;

};
