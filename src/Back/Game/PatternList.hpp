#pragma once

#include <string>
#include <vector>
#include <optional>
#include "Board.hpp"

struct lexicon_pattern_index
{
    int patternIndex{-1};
    int gridIndex{-1};
};

struct pair_of_description_and_pattern
{
    std::string _description{};
    board_data _gridPattern{};
};

using description_and_pattern_type = std::vector<pair_of_description_and_pattern>;

struct pattern
{
    pattern(std::string_view name, const description_and_pattern_type& descAndPattern) : _name(name),
        _descriptionAndPattern(descAndPattern)
    {
    }

    std::string _name{};
    description_and_pattern_type _descriptionAndPattern{};
};

class PatternList
{
public:
    explicit PatternList()
    {
        _list.reserve(MAX_PATTERNS);
    };

    explicit PatternList(const std::vector<pattern>& pattern): _list(pattern)
    {
    };

    void addPattern(std::string_view name, const description_and_pattern_type& descAndPattern)
    {
        _list.emplace_back(name, descAndPattern);
        _numberOfPatternTotal += descAndPattern.size();
    }

    board_data findPatternNamed(std::string_view name, size_t indexOfThePattern = 0) const
    {
        // No exception so we can access to the data directly
        return findPattern(name, indexOfThePattern)->_descriptionAndPattern.at(indexOfThePattern)._gridPattern;
    }

    lexicon_pattern_index findIndexForPatternNamed(std::string_view name, size_t indexOfThePattern = 0) const
    {
        // No exception so we can access to the data directly
        return {
            static_cast<int>(std::distance(_list.cbegin(), findPattern(name, indexOfThePattern))),
            static_cast<int>(indexOfThePattern)
        };
    }

    [[nodiscard]] const std::vector<pattern>& get_list_const_ref() const noexcept { return _list; }
    [[nodiscard]] std::vector<pattern>& get_list_ref() noexcept { return _list; }
    [[nodiscard]] size_t get_numberOfPatternTotal() const noexcept { return _numberOfPatternTotal; }

    [[nodiscard]] board_data getPatternForIndices(int patternIndex, int gridIndex) const
    {
        return _list.at(patternIndex)._descriptionAndPattern.at(gridIndex)._gridPattern;
    }


    std::vector<pattern>::const_iterator findPattern(std::string_view name, size_t indexOfThePattern = 0) const
    {
        const auto found = std::find_if(_list.cbegin(), _list.cend(), [&](const pattern& cur)
        {
            return cur._name == name;
        });
        if (found != _list.end())
        {
            if (indexOfThePattern < found->_descriptionAndPattern.size())
            {
                return found;
            }
            else
            {
                throw std::out_of_range(
                    "ERROR: try to find pattern named " + std::string(name) + " which exist but you ask for the index "
                    + std::to_string(indexOfThePattern) + " but it is not in the bound [0;" + std::to_string(
                        indexOfThePattern < found->_descriptionAndPattern.size()) + "]");
            }
        }

        throw std::runtime_error(
            "ERROR: try to find pattern named " + std::string(name) + " but it doesn't exist in the lexicon !");
    }

private:
    std::vector<pattern> _list{};
    size_t _numberOfPatternTotal{};

    // Obtained by heuristic (launch the program and see the _numberOfPatternTotal)
    static constexpr size_t MAX_PATTERNS{1553};
};
