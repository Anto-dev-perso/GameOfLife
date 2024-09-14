#include "Cell.hpp"

Cell::Cell(bool alive):_isAlive(alive) {}

bool Cell::get_isAlive() const {return _isAlive;}

void Cell::set_isAlive(bool alive)  {_isAlive=alive;}
