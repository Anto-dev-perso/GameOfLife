#pragma once

#include "Board.hpp"

#include <fstream>

class OutputWriter {

    // TODO output file can be at another location
    // TODO file extension can be configurable

public:
    explicit OutputWriter(std::string_view nameWithExtension);

    [[nodiscard]] bool writeIteration(const gridOfCells &grid, unsigned int iteration = 0);

    [[nodiscard]] std::string get_fileName() const;

    [[nodiscard]] std::string_view get_extension() const;

private:

    std::string _fileName{};
    const std::string _extension{"res"};


};
