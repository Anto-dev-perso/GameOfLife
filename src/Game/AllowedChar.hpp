#pragma once

#include <array>
#include <stdexcept>

// Define a static array for the char allowed for the alive or not status of each cell
// This ease the maintainability of the program because we can easily change the char for alive and dead cells
constexpr std::array<char, 2> allowedCharacters{'*', '-'};

// Function to map a character to a boolean
[[nodiscard]]static bool charToBool(char c) {
    if (c == allowedCharacters[0]) return true;
    else if (c == allowedCharacters[1]) return false;
    throw std::invalid_argument("Invalid character for mapping.");
}

// Function to map a boolean back to a character
[[nodiscard]] constexpr char boolToChar(bool value) {
    return value ? allowedCharacters[0] : allowedCharacters[1];
}

[[nodiscard]] constexpr char getAliveChar() {
    return allowedCharacters[0];
}

[[nodiscard]] constexpr char getDeadChar() {
    return allowedCharacters[1];
}
