#pragma once


class Cell {
public:


    Cell(bool alive);


    [[nodiscard]] bool get_isPreviouslyAlive() const;

    [[nodiscard]] bool get_isCurrentlyAlive() const;

    void memorizePreviousAliveValue();


    void set_isPreviouslyAlive(bool newAlive);

    void set_isCurrentlyAlive(bool newAlive);

    void set_lastIterationWhichModif(unsigned int iteration);

    [[nodiscard]] bool isCellAlive(unsigned int iteration);

private:

    bool _isPreviouslyAlive{false}; // Memory of previous alive state for this cell
    bool _isCurrentlyAlive{false};// State of alive or not for the current iteration
    unsigned int _lastIterationWhichModif{0};
};
