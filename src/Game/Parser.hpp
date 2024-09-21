#pragma once

#include "Board.hpp"

#include <string>

class Parser {
public:
    constexpr explicit Parser(std::string_view inputFile) : _file(inputFile) {};

    [[nodiscard]] gridOfCells parseInputFile();

private:

    std::string_view _file;
};
