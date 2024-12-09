#pragma once

#include "Parser.hpp"
#include "OutputWriter.hpp"

#include <memory>

class Game
{
public:
    struct line_column
    {
        size_t line;
        size_t column;

        bool operator==(const line_column& other) const noexcept
        {
            return (line == other.line && column == other.column);
        }
    };

    using indices_with_value = std::pair<line_column, bool>;
    static constexpr line_column EMTPY_PAIR_OF_INDICES{0, 0};

    Game(std::string_view path, unsigned int iterations, bool all) : _filePath(path),
                                                                     _nbOfIterations(iterations),
                                                                     _outputAllIterations(all),
                                                                     _fileParser(Parser(_filePath)),
                                                                     _outputWriter(std::make_unique<OutputWriter>(
                                                                         _filePath))
    {
    }

    Game(std::string_view path, TypeOfFileToParse type) : _filePath(path), _fileParser(Parser(_filePath, type))
    {
    }

#ifdef ENABLE_DEBUG
    Game() : _fileParser(Parser("")), _board(std::make_unique<Board>())
    {
    };

    void updateBoard(board_data newGrid) const noexcept
    {
        _board->update(std::move(newGrid));
    }

    void updateBoard(const PatternList& patterns, lexicon_pattern_index indexOfPattern) noexcept
    {
        _patterns = patterns;
        _boardPattern = indexOfPattern;
        _board->update(
            _patterns.get_list_const_ref().at(indexOfPattern.patternIndex)._descriptionAndPattern.at(
                indexOfPattern.gridIndex)._gridPattern);
    }

    void set_patternsList(const PatternList& newList) noexcept
    {
        _patterns = newList;
    }

    [[nodiscard]] inline auto retrieveBoardDataForTest() const noexcept { return _board->retrieveDataForTest(); }
#endif

    [[nodiscard]] bool init() noexcept;

    [[nodiscard]] bool process() const noexcept;

    [[nodiscard]] std::tuple<bool, bool, std::vector<Game::indices_with_value>>
    applyRulesToTheBoardForIteration(unsigned int onGoingIteration) const noexcept;

    [[nodiscard]] const Board* get_board_const() const noexcept { return _board.get(); }
    [[nodiscard]] Board* get_board() const noexcept { return _board.get(); }
    [[nodiscard]] board_data get_board_data() const noexcept { return _board->get_board_data(); }

    [[nodiscard]] size_t get_board_nbLine() const noexcept { return _board->get_lineLength(); }
    [[nodiscard]] size_t get_board_nbColumn() const noexcept { return _board->get_colLength(); }

    [[nodiscard]] bool get_boardCellAliveAt(size_t index) const noexcept
    {
        return _board->isCellAliveAtIndex(index);
    }

    [[nodiscard]] inline bool change_CellValue(size_t index, bool newValue) const noexcept
    {
        return _board->changeCellValue(index, newValue);
    }

    [[nodiscard]] constexpr unsigned int get_nbOfIterations() const noexcept
    {
        return _nbOfIterations;
    }

    void set_nbOfIterations(unsigned int newIterations) noexcept
    {
        _nbOfIterations = newIterations;
    }

    constexpr inline void increment_nbOfIterations() noexcept
    {
        _nbOfIterations += 1;
    }

    [[nodiscard]] auto applyRulesToTheBoard() const noexcept
    {
        return applyRulesToTheBoardForIteration(_nbOfIterations);
    }

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

    [[nodiscard]] std::pair<std::vector<pattern>&, size_t> get_lexiconPatterns() noexcept
    {
        return {_patterns.get_list_ref(), _patterns.get_numberOfPatternTotal()};
    }

    [[nodiscard]] std::pair<const std::vector<pattern>&, size_t> get_lexiconPatterns_const() const noexcept
    {
        return {_patterns.get_list_const_ref(), _patterns.get_numberOfPatternTotal()};
    }

    void changeBoard(int patternIndex, int gridIndex)
    {
        _boardPattern = {patternIndex, gridIndex};
        resetBoard();
    }

    void resetBoard()
    {
        _board->update(_patterns.getPatternForIndices(_boardPattern.patternIndex, _boardPattern.gridIndex));
        _nbOfIterations = 0;
    }

    void clearBoard() noexcept
    {
        _board->clear();
        _boardPattern = {};
        _nbOfIterations = 0;
    }

    [[nodiscard]] lexicon_pattern_index get_boardPattern() const noexcept { return _boardPattern; }


    bool boardEmpty() const noexcept
    {
        return _board->get_grid_const().empty();
    }

private
:
    [[nodiscard]] static bool applyRule1(const Cell& currentCell,
                                         const std::vector<std::reference_wrapper<Cell>>& neighbours,
                                         unsigned int onGoingIteration) noexcept;

    [[nodiscard]] static bool applyRule2(const Cell& currentCell,
                                         const std::vector<std::reference_wrapper<Cell>>& neighbours,
                                         unsigned int onGoingIteration) noexcept;

    // Rule 3 of the Game : All others live cells die in the next generation and all other dead cells stay dead
    // Return false directly because a living cell shall die and a dead cell shall stay dead
    // Keep a function for this rule for consistency and understanding
    // If the rule change, the function can be useful
    [[nodiscard]] static inline constexpr bool applyRule3() noexcept { return false; }

    std::string_view _filePath{};
    unsigned int _nbOfIterations{0};
    bool _outputAllIterations{false};

    lexicon_pattern_index _boardPattern{};

    Parser _fileParser{};
    PatternList _patterns{};
    std::unique_ptr<Board> _board{};
    std::unique_ptr<OutputWriter> _outputWriter{};
};
