#pragma once


#include <optional>
#include "InputChecker.hpp"


class InputChecker {
public:
    [[nodiscard]] std::tuple<bool, std::string, unsigned int, bool> checkInputs(int argc, char **argv) const;

private:

};
