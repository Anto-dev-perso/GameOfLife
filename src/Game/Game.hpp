#pragma once

#include "Parser.hpp"
#include "OutputWriter.hpp"

#include <string>
#include <memory>

class Game
{

public:
    Game(std::string_view path, unsigned int iterations, bool all);

#ifdef ENABLE_DEBUG
    Game() : _fileParser(Parser("")), _board(std::make_unique<Board>()) {};
    void updateBoard(const gridOfCells &newGrid, std::size_t lineLength, std::size_t columnLength) noexcept
    {
        _board->update(newGrid,lineLength,columnLength);
    }

    [[nodiscard]] inline auto retrieveBoardDataForTest() const noexcept  { return _board->retrieveDataForTest(); }
#endif

    [[nodiscard]] bool init() noexcept;

    [[nodiscard]] bool process() noexcept;

public:
    [[nodiscard]] std::tuple<bool, bool> applyRulesToTheBoardForIteration(unsigned int onGoingIteration) const  noexcept;

    [[nodiscard]] inline const Board *get_board_const() const noexcept { return _board.get(); }

private:
    [[nodiscard]] bool applyRule1(Cell &currentCell, const std::vector<std::reference_wrapper<Cell>> &neighbours,
                                         unsigned int onGoingIteration) const noexcept;

    [[nodiscard]] bool applyRule2(Cell &currentCell, const std::vector<std::reference_wrapper<Cell>> &neighbours,
                                         unsigned int onGoingIteration) const noexcept;

    // Rule 3 of the Game : All other live cells die in the next generation and all other dead cells stay dead
    // Return false directly because a living cell shall die and a dead cell shall stay dead
    // Keep a function for this rule for consistency and understanding
    // If the rule change, the function can be useful
    [[nodiscard]] inline constexpr bool applyRule3() const noexcept { return false; }

    std::string_view _filePath{};
    unsigned int _nbOfIterations{0};
    bool _outputAllIterations{false};

    Parser _fileParser;
    std::unique_ptr<Board> _board;
    std::unique_ptr<OutputWriter> _outputWriter;
};
