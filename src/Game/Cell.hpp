#pragma once


class Cell {
public:

    Cell(bool alive);

    [[nodiscard]] bool get_isAlive() const;

    void set_isAlive(bool alive);

private:

    bool _isAlive{false};
};
