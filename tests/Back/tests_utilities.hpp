#pragma once

#include "../InputsBoards.hpp"

#include <string>

namespace UTILITIES
{
    /****************************************  Functions ***************************************/
    // Helper function to compare the content of the gridOfCells between the actual one and the expected one
    void compareGrid(const board_data& board, const board_data& expected);

    void dumpBoardData(const board_data& board) noexcept;

    // Utility function to read the content of a file into a string
    [[nodiscard]] std::string readFile(std::string_view filename);
};
