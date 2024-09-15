#include <array>

// Define a static array for the char allowed for the alive or not status of each cell
// This ease the maintainability of the program because we can easily change the char for alive and dead cells
constexpr std::array<char, 2> allowedCharacters{'*', '-'};

// Function to map a character to a boolean
[[nodiscard]] constexpr bool charToBool(char c) {
    if (c == '*') return true;
    else if (c == '-') return false;
}

// Function to map a boolean back to a character
[[nodiscard]] constexpr char boolToChar(bool value) {
    return value ? '*' : '-';
}
