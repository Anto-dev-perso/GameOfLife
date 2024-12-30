#pragma once

#include "InputChecker.hpp"

#include <optional>
#include <vector>
#include <string>

class InputChecker
{
public:
    [[nodiscard]] static std::tuple<bool, std::string, unsigned int, bool> checkInputs(int argc, char* argv[]) noexcept;

    [[nodiscard]] static std::optional<unsigned int> convertArgForIterations(std::string_view arg_path) noexcept;
};
