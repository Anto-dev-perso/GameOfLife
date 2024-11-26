#pragma once

#include "AllowedChar.hpp"

class Cell {
public:

    Cell(char alive) : Cell(charToBool(alive)) {};

    // Set the two alive booleans to the same value because we don't really needs to memory anything at first
    constexpr Cell(bool alive) : _isPreviouslyAlive(alive), _isCurrentlyAlive(alive) {};

    [[nodiscard]] constexpr bool get_isPreviouslyAlive() const noexcept { return _isPreviouslyAlive; }

    [[nodiscard]] constexpr bool get_isCurrentlyAlive() const noexcept { return _isCurrentlyAlive; }

    constexpr void memorizePreviousAliveValue() noexcept { _isPreviouslyAlive = _isCurrentlyAlive; }

    constexpr void set_isCurrentlyAlive(bool newAlive) noexcept { _isCurrentlyAlive = newAlive; }

    constexpr void
    set_lastIterationWhichModif(unsigned int iteration) noexcept { _lastIterationWhichModif = iteration; }

    [[nodiscard]] constexpr bool isCellAlive(unsigned int iteration) const
    {
        // If we modif on the current iteration, it means that we are looking for an already processed cell
        // Take the memorized value
        return (_lastIterationWhichModif == iteration) ? (_isPreviouslyAlive) : (_isCurrentlyAlive);
    }


private:

    bool _isPreviouslyAlive{false}; // Memory of previous alive state for this cell
    bool _isCurrentlyAlive{false};// State of alive or not for the current iteration
    unsigned int _lastIterationWhichModif{0};
};
