#pragma once

#include "OutputWriter.hpp"

#include <string>
#include <memory>

class Game {

public:
    Game(std::string_view path, unsigned int iterations, bool all);

    [[nodiscard]] bool process();

public:
    void applyRulesToTheBoard(unsigned int onGoingIteration) const;

    [[nodiscard]] const Board *get_board_const() const;

    void set_board(const gridOfCells &newGrid);

private:


    [[nodiscard]] static bool applyRule1(Cell &currentCell, const std::vector<std::reference_wrapper<Cell>> &neighbours,
                                         unsigned int onGoingIteration);

    [[nodiscard]] static bool applyRule2(Cell &currentCell, const std::vector<std::reference_wrapper<Cell>> &neighbours,
                                         unsigned int onGoingIteration);

    // Rule 3 of the Game : All other live cells die in the next generation and all other dead cells stay dead
    // Return false directly because a living cell shall die and a dead cell shall stay dead
    // Keep a function for this rule for consistency and understanding
    // If the rule change, the function can be useful
    [[nodiscard]] static constexpr bool applyRule3() { return false; }

    std::string_view _filePath{};
    unsigned int _nbOfIterations{0};
    bool _outputAllIterations{false};

    std::unique_ptr<Board> _board;
    std::unique_ptr<OutputWriter> _outputWriter;

};
