#include "Cell.hpp"

// Set the two alive booleans to the same value because we don't really needs to memory anything at first
Cell::Cell(bool alive) : _isPreviouslyAlive(alive), _isCurrentlyAlive(alive) {}

bool Cell::get_isPreviouslyAlive() const { return _isPreviouslyAlive; }

bool Cell::get_isCurrentlyAlive() const { return _isCurrentlyAlive; }

void Cell::set_isPreviouslyAlive(bool newAlive) { _isPreviouslyAlive = newAlive; }

void Cell::set_isCurrentlyAlive(bool newAlive) { _isCurrentlyAlive = newAlive; }

void Cell::set_lastIterationWhichModif(unsigned int iteration) {_lastIterationWhichModif=iteration;}

bool Cell::isCellAlive(unsigned int iteration) {
    // If we modif on the current iteration, it means that we are looking for an already processed cell
    // Take the memorized value
    return( _lastIterationWhichModif==iteration)?(_isPreviouslyAlive):(_isCurrentlyAlive);
}

void Cell::memorizePreviousAliveValue() {_isPreviouslyAlive=_isCurrentlyAlive;}
