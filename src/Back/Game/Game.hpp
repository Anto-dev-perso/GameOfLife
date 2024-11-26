#pragma once

#include "Parser.hpp"
#include "OutputWriter.hpp"

#include <memory>

class Game
{
public:
    using line_column = std::pair<size_t, size_t>;

    using pairOfIndices = std::pair<line_column, line_column>;

    static constexpr line_column emptyPairOfIndices{0, 0};

    Game(std::string_view path, unsigned int iterations, bool all);

    Game() : _board(std::make_unique<Board>(gridOfCells{
                                                false, false, false, false, false,
                                                false, false, true, false, false,
                                                false, false, true, false, false,
                                                false, false, true, false, false,
                                                false, false, false, false, false},
                                            5, 5))
    {
    }

#ifdef ENABLE_DEBUG
    // Game() : _fileParser(Parser("")), _board(std::make_unique<Board>()) {};
    void updateBoard(const gridOfCells &newGrid, std::size_t lineLength, std::size_t columnLength) const noexcept
    {
        _board->update(newGrid, lineLength, columnLength);
    }

    [[nodiscard]] inline auto retrieveBoardDataForTest() const noexcept { return _board->retrieveDataForTest(); }
#endif

    [[nodiscard]] bool init() noexcept;

    [[nodiscard]] bool process() noexcept;

public:
    [[nodiscard]] std::tuple<bool, bool, std::vector<Game::pairOfIndices>>
    applyRulesToTheBoardForIteration(unsigned int onGoingIteration) const noexcept;

    [[nodiscard]] inline const Board *get_board_const() const noexcept { return _board.get(); }
    [[nodiscard]] inline Board *get_board() const noexcept { return _board.get(); }

    [[nodiscard]] inline size_t get_board_nbLine() const noexcept { return _board->get_lineLength(); }
    [[nodiscard]] inline size_t get_board_nbColumn() const noexcept { return _board->get_colLength(); }

    [[nodiscard]] inline bool get_boardCellAliveAt(size_t index) const noexcept
    {
        return _board->isCellAliveAtIndex(index);
    }

    [[nodiscard]] constexpr inline bool change_CellValue(size_t index, bool newValue) const noexcept
    {
        return _board->changeCellValue(index, newValue);
    }

    [[nodiscard]] constexpr inline unsigned int get_nbOfIterations() const noexcept
    {
        return _nbOfIterations;
    }

    constexpr inline void increment_nbOfIterations() noexcept
    {
        _nbOfIterations += 1;
    }

    auto applyRulesToTheBoard() const noexcept { return applyRulesToTheBoardForIteration(_nbOfIterations); }

    [[maybe_unused]] constexpr bool checkIfBoardNeedToBeResize(bool expand, bool reduce) const noexcept
    {
        if (expand)
        {
            _board->expandBoard();
            return true;
        }
        if (reduce)
        {
            _board->reduceBoard();
            return true;
        }
        return false;
    }

private:
    [[nodiscard]] bool applyRule1(Cell &currentCell, const std::vector<std::reference_wrapper<Cell>> &neighbours,
                                  unsigned int onGoingIteration) const noexcept;

    [[nodiscard]] bool applyRule2(Cell &currentCell, const std::vector<std::reference_wrapper<Cell>> &neighbours,
                                  unsigned int onGoingIteration) const noexcept;

    // Rule 3 of the Game : All others live cells die in the next generation and all other dead cells stay dead
    // Return false directly because a living cell shall die and a dead cell shall stay dead
    // Keep a function for this rule for consistency and understanding
    // If the rule change, the function can be useful
    [[nodiscard]] static inline constexpr bool applyRule3() noexcept { return false; }

    std::string_view _filePath{""};
    unsigned int _nbOfIterations{0};
    bool _outputAllIterations{false};

    Parser _fileParser;
    std::unique_ptr<Board> _board;
    std::unique_ptr<OutputWriter> _outputWriter;
};
