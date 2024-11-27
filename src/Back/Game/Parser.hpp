#pragma once

#include "Board.hpp"
#include "PatternList.hpp"

#include <string>
#include <variant>

enum class TypeOfFileToParse
{
    BOARD,
    LEXICON
};

class Parser
{
public:
    explicit Parser(std::string_view inputFile) : _file(inputFile)
    {
    };

    explicit Parser(std::string_view inputFile, TypeOfFileToParse type) : _file(inputFile), _typeOfFileToParse(type)
    {
    };
    Parser() = default;

    [[nodiscard]] inline std::variant<board_data, PatternList> parseFile() const noexcept
    {
        switch (_typeOfFileToParse)
        {
        case TypeOfFileToParse::BOARD:
            return parseBoardFile();
        case TypeOfFileToParse::LEXICON:
            return parseLexiconFile();
        }
    }

#ifdef ENABLE_DEBUG
    [[nodiscard]] bool parseLineOfGrid(board_data& boardRead, std::string& line) const noexcept;
    [[nodiscard]] board_data parseBoardFile() const noexcept;
    [[nodiscard]] PatternList parseLexiconFile() const noexcept;

private:
#else

private:
    [[nodiscard]] bool parseLineOfGrid(board_data& boardRead, std::string& line) const noexcept;
    [[nodiscard]] board_data parseBoardFile() const noexcept;
    [[nodiscard]] PatternList parseLexiconFile() const noexcept;
#endif
    inline static void trimLeadingSpaces(std::string& input) noexcept
    {
        size_t firstNonSpace = input.find_first_not_of('\t');

        if (firstNonSpace != std::string::npos)
        {
            input = input.substr(firstNonSpace);
        }
        size_t firstNonTab = input.find_first_not_of(' ');
        if (firstNonTab != std::string::npos)
        {
            input = input.substr(firstNonTab);
        }
    }

    std::string _file{};
    TypeOfFileToParse _typeOfFileToParse{TypeOfFileToParse::BOARD};

    static constexpr char LEXICON_INTRO_SEPARATOR{'-'};
    static constexpr char LEXICON_NAME_SEPARATOR{':'};
};
