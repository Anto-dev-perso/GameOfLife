#pragma once

#include "InputChecker.hpp"

#include <optional>
#include <vector>
#include <string>


class InputChecker {
public:
    [[nodiscard]] std::tuple<bool, std::string_view, unsigned int, bool> checkInputs(int argc, char *argv[]) const;

    [[nodiscard]] static std::optional<unsigned int> convertArgForIterations(std::string_view arg_path);

private:


};
