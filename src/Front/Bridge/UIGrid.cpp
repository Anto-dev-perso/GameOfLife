#include "UIGrid.hpp"

#include <iostream>

UIGrid::UIGrid(QObject* parent)
    : QAbstractListModel(parent)
{
}


int UIGrid::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return _UILineCount * _UIColumnCount;
}

QVariant UIGrid::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != ValueRole)
    {
        return QVariant();
    }
    if (const auto vecId{calculateIndexFromUIRow(index)}; vecId.has_value())
    {
        return QVariant(_gridUI[vecId.value()]);
    }

    return QVariant();
}

bool UIGrid::setData(const QModelIndex& index, const QVariant& value, int role)
{
    // TODO if index is larger, update back end grid
    if (!index.isValid() || role != ValueRole)
    {
        return false;
    }
    const auto vecId{calculateIndexFromUIRow(index)};
    if (!vecId.has_value()) { return false; }

    if (_gridUI[vecId.value()] == value.toBool()) { return false; }

    _gridUI[vecId.value()] = value.toBool();
    emit dataChanged(index, index, {role});
    return true;
}

std::optional<size_t> UIGrid::calculateIndexFromUIRow(const QModelIndex& index) const noexcept
{
    if (!index.isValid())
    {
        return std::nullopt;
    }

    const int row = index.row() / _UIColumnCount;
    const int column = index.row() % _UIColumnCount;

    if (row < _gridFirstRow || row >= _gridFirstRow + _lineCount ||
        column < _gridFirstColumn || column >= _gridFirstColumn + _columnCount) { return std::nullopt; }

    return {(row - _gridFirstRow) * _columnCount + (column - _gridFirstColumn)};
}

