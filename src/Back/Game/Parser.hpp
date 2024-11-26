#pragma once

#include "Board.hpp"

#include <string>

class Parser
{
public:
    constexpr explicit Parser(std::string_view inputFile) : _file(inputFile)
    {
    };
    Parser() = default;

    [[nodiscard]] std::tuple<gridOfCells, std::size_t, std::size_t> parseInputFile() const noexcept;

private:
    std::string_view _file{};
};
