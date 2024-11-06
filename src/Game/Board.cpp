#include "Board.hpp"

#include <utility>

using namespace std;

// Define a minimum size for the line or column
static constexpr size_t minSize{5};

Board::Board(gridOfCells &&readGrid, size_t numberOfLines, size_t numberOfColumn) : _grid(std::move(readGrid)),
                                                                                    _lineLength(numberOfLines),
                                                                                    _colLength(numberOfColumn) {}

std::vector<std::reference_wrapper<Cell>>
Board::fillNeighbour(size_t line, size_t column) noexcept
{

    if (line >= _grid.size() || column >= _colLength)
    {
        return {};
    }

    const bool lineAtUpLimit{line + _colLength == _grid.size()};
    const bool columnAtUpLimit{column + 1 == _colLength};
    const bool lineAtLowLimit{line <= 0};
    const bool columnAtLowLimit{column <= 0};

    // Cast to a reference in order to return a vector a reference_wrapper (avoid copy)
    auto &gridRef = static_cast<gridOfCells &>(_grid);

    // We can do all neighbours
    if (!columnAtUpLimit && !columnAtLowLimit && !lineAtUpLimit && !lineAtLowLimit)
    {
        return {gridRef[(line + _colLength) + (column + 1)],
                gridRef[line + (column + 1)],
                gridRef[(line - _colLength) + (column + 1)],
                gridRef[(line + _colLength) + column],
                gridRef[(line - _colLength) + column],
                gridRef[(line + _colLength) + (column - 1)],
                gridRef[line + (column - 1)],
                gridRef[(line - _colLength) + (column - 1)]};

        // Line -1 isn't possible
    }
    else if (!columnAtUpLimit && !columnAtLowLimit && !lineAtUpLimit && lineAtLowLimit)
    {
        return {gridRef[(line + _colLength) + (column + 1)],
                gridRef[line + (column + 1)],
                gridRef[(line + _colLength) + column],
                gridRef[(line + _colLength) + (column - 1)],
                gridRef[line + (column - 1)]};
    }
    // Line +1 isn't possible
    else if (!columnAtUpLimit && !columnAtLowLimit && lineAtUpLimit && !lineAtLowLimit)
    {
        return {gridRef[line + (column + 1)],
                gridRef[(line - _colLength) + (column + 1)],
                gridRef[(line - _colLength) + column],
                gridRef[line + (column - 1)],
                gridRef[(line - _colLength) + (column - 1)]};
    }
    // Col -1 isn't possible
    else if (!columnAtUpLimit && columnAtLowLimit && !lineAtUpLimit && !lineAtLowLimit)
    {
        return {gridRef[(line + _colLength) + (column + 1)],
                gridRef[line + (column + 1)],
                gridRef[(line - _colLength) + (column + 1)],
                gridRef[(line + _colLength) + column],
                gridRef[(line - _colLength) + column]};
    }
    // Col+1 isn't possible
    else if (columnAtUpLimit && !columnAtLowLimit && !lineAtUpLimit && !lineAtLowLimit)
    {
        return {gridRef[(line + _colLength) + column],
                gridRef[(line - _colLength) + column],
                gridRef[(line + _colLength) + (column - 1)],
                gridRef[line + (column - 1)],
                gridRef[(line - _colLength) + (column - 1)]};
    }
    // Col -1 and Line -1 isn't possible
    else if (!columnAtUpLimit && columnAtLowLimit && !lineAtUpLimit && lineAtLowLimit)
    {
        return {gridRef[(line + _colLength) + (column + 1)],
                gridRef[line + (column + 1)],
                gridRef[(line + _colLength) + column]};
    }
    // Col -1 and Line +1 isn't possible
    else if (!columnAtUpLimit && columnAtLowLimit && lineAtUpLimit && !lineAtLowLimit)
    {
        return {
            gridRef[line + (column + 1)],
            gridRef[(line - _colLength) + (column + 1)],
            gridRef[(line - _colLength) + column]};
    }
    // Col +1 and Line -1 isn't possible
    else if (columnAtUpLimit && !columnAtLowLimit && !lineAtUpLimit && lineAtLowLimit)
    {
        return {
            gridRef[(line + _colLength) + column],
            gridRef[(line + _colLength) + (column - 1)],
            gridRef[line + (column - 1)]};
    }
    // Col +1 and Line +1 isn't possible
    else if (columnAtUpLimit && !columnAtLowLimit && lineAtUpLimit && !lineAtLowLimit)
    {
        return {
            gridRef[(line - _colLength) + column],
            gridRef[line + (column - 1)],
            gridRef[(line - _colLength) + (column - 1)]};
    }
    return {};
}

bool Board::isCellAtBorder(size_t line, size_t column) const noexcept
{
    // Because we have a grid, all lines have the same number of column
    // So we have just to verify that the current line indice is the first or the last one (idem for column)
    return ((column == 0 || column == _colLength - 1) || ((line < _colLength ||
                                                              (_grid.size() - _colLength <= line &&
                                                               line < _grid.size()))));
}

bool Board::isCellBeforeTheBorder(size_t line, size_t column) const noexcept
{
    // Because we have a grid, all lines have the same number of column
    // So we have just to verify that the current line indice is the second or the penultimate (idem for column)
    return ((column == 1 || column == _colLength - 2) || ((_colLength <= line && line < 2 * _colLength) ||
                                                              (((_grid.size() - (2 * _colLength)) <= line) &&
                                                               (line < _grid.size() - _colLength))));
}

// To expand the board, we have to add one line at beginning and end and for each line, add one column at beginning and end
void Board::expandBoard() noexcept
{

    // Keep old length for math
    const size_t oldColumnSize{_colLength};

    set_lineLength(_lineLength + 2);
    set_colLength(_colLength + 2);

    const size_t newSize{_lineLength * _colLength};

    // Reserve the new size needed (may cause re-allocation)
    _grid.reserve(newSize);

    // Insert at the beginning first because vector will have to move all elements so avoid to move the new element insert in the back
    // Insert 1 line + 1 column of the second line because we know we have to add it right after
    _grid.insert(_grid.begin(), _colLength + 1, getDeadChar());

    // Loop through every lines (except first and last one) and add the new column
    // Because we inserted the new first line before, the begin() has been moved 1 line + 1 column after
    // Go directly at the second line by adding the old number of elements per line
    for (size_t line = _colLength + oldColumnSize; line < newSize - (2 * _colLength); line += _colLength)
    {
        // Insert last column of previous line and first column of current line
        _grid.insert(_grid.begin() + line, 2, getDeadChar());
    }

    // Insert penultimate line last column and last line entirely
    for (size_t i = 0; i < _colLength + 1; i++)
    {
        _grid.emplace_back(getDeadChar());
    }
}

// To reduce the board, we have to remove one line at beginning and end and for each line, reùove one column at beginning and end
void Board::reduceBoard() noexcept
{
    // Don't go to low in the size of the board
    if (_lineLength <= minSize || _colLength <= minSize)
    {
        return;
    }

    const size_t oldSize{_grid.size()};
    const size_t oldColLength{_colLength};
    const size_t oldLineLength{_lineLength};

    set_lineLength(oldLineLength - 2);
    set_colLength(oldColLength - 2);

    // Remove the last line + penultimate line last column
    // Reminder: erase is exclusive on the last iterator
    _grid.erase(_grid.begin() + ((oldLineLength * oldColLength) - oldColLength + 1), _grid.end());

    // Loop through every lines and erase the columns
    // Erase at first the last elements to reduce the swapping time
    // Stop at the frst line because we know we will delete it entirely
    for (size_t line = oldSize - oldColLength; line > oldColLength; line -= oldColLength)
    {
        // Remove 2 elements (last column of previous line + first colmun of current line)
        _grid.erase(_grid.begin() + line - 1, _grid.begin() + line + 1);
    }

    // Remove the first line + first column of second line
    _grid.erase(_grid.begin(),
                _grid.begin() + _colLength + 2 + 1); // +1 because erase is exclusive on the last parameter
}


