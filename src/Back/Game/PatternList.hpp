#pragma once

#include <string>
#include <vector>
#include <optional>
#include "Board.hpp"

struct pair_of_description_and_pattern
{
    std::string _description{};
    board_data _gridPattern{};
};

using description_and_pattern_type = std::vector<pair_of_description_and_pattern>;

struct pattern
{
    pattern(std::string_view name, const description_and_pattern_type& descAndPattern):
        _name(name),
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

    void addPattern(std::string_view name, const description_and_pattern_type& descAndPattern)
    {
        _list.emplace_back(name, descAndPattern);
        _numberOfPatternTotal += descAndPattern.size();
    }

    pattern findPatternNamed(std::string_view name) const
    {
        const auto found = std::find_if(_list.cbegin(), _list.cend(), [&](const pattern& cur)
        {
            return cur._name == name;
        });
        if (found != _list.end())
        {
            return *found;
        }

        throw std::runtime_error(
            "ERROR: try to find pattern named " + std::string(name) + " but it doesn't exist in the lexicon !");
    }

    [[nodiscard]] const std::vector<pattern>& get_list_const_ref() const noexcept { return _list; }
    [[nodiscard]] std::vector<pattern>& get_list_ref() noexcept { return _list; }
    [[nodiscard]] size_t get_numberOfPatternTotal() const noexcept { return _numberOfPatternTotal; }

    [[nodiscard]] board_data getPatternForIndices(int patternIndex, int gridIndex) const noexcept
    {
        return _list.at(patternIndex)._descriptionAndPattern.at(gridIndex)._gridPattern;
    }

private
:
    std::vector<pattern> _list{};
    size_t _numberOfPatternTotal{};

    static constexpr size_t MAX_PATTERNS{1553};
    // Obtained by heuristic (launch the program and see the _numberOfPatternTotal)
};
