#pragma once

#include "Board.hpp"

#include <fstream>

class OutputWriter {

    // TODO output file can be at another location
    // TODO file extension can be configurable

public:
    explicit OutputWriter(std::string_view nameWithExtension);

    [[nodiscard]] bool writeIteration(const gridOfCells &grid, size_t numColumn, unsigned int iteration = 0) const noexcept;

    [[nodiscard]] inline std::string_view get_fileName() const noexcept{ return _fileName; }

    [[nodiscard]] inline std::string get_extension() const noexcept{ return _extension; }

private:
    std::string_view _fileName{};
    const std::string _extension{"res"};
};
