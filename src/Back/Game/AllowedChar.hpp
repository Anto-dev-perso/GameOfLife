#pragma once

#include <array>
#include <stdexcept>

// Define a static array for the char allowed for the alive or not status of each cell
// This ease the maintainability of the program because we can easily change the char for alive and dead cells
inline constexpr std::array<char, 3> allowedCharacters{'*', '-', '.'};

// Function to map a character to a boolean
[[nodiscard]] inline bool charToBool(char c)
{
    if (c == allowedCharacters[0])
        return true;
    else if (c == allowedCharacters[1] || c == allowedCharacters[2])
        return false;
    throw std::invalid_argument("Invalid character for mapping.");
}

// Function to map a boolean back to a character
[[nodiscard]] constexpr inline char boolToChar(bool value) noexcept
{
    return value ? allowedCharacters[0] : allowedCharacters[1];
}

[[nodiscard]] constexpr inline char getAliveChar() noexcept
{
    return allowedCharacters[0];
}

[[nodiscard]] constexpr char getDeadChar() noexcept
{
    return allowedCharacters[1];
}
