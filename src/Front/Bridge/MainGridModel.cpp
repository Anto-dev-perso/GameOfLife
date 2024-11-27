
#include "MainGridModel.hpp"

MainGridModel::MainGridModel(std::shared_ptr<Game> backend, QObject* parent):
    QAbstractListModel(parent),
    _backend(std::move(backend))
{
    updateGridCounters();
}

QModelIndex MainGridModel::calculateUIIndexFromBackId(const Game::line_column& pair) const noexcept
{
    const auto& [line, column] = pair;

    const int uiLine = line + _gridFirstRow;
    const int uiColumn = column + _gridFirstColumn;

    return index(uiLine * _UIColumnCount + uiColumn);
}


QVariant MainGridModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Cell)
    {
        return QVariant();
    }
    if (const auto vecId{calculateIndexFromUIRow(index)}; vecId.has_value())
    {
        return QVariant(_backend->get_boardCellAliveAt(vecId.value()));
    }

    return QVariant();
}

constexpr std::optional<size_t> MainGridModel::calculateIndexFromUIRow(const QModelIndex& index) const noexcept
{
    if (!index.isValid())
    {
        return std::nullopt;
    }

    const size_t row{index.row() / _UIColumnCount};
    const size_t column{index.row() % _UIColumnCount};

    if (row < _gridFirstRow || row >= _gridFirstRow + _backend->get_board_nbLine() ||
        column < _gridFirstColumn || column >= _gridFirstColumn + _backend->get_board_nbColumn())
    {
        return std::nullopt;
    }

    return {(row - _gridFirstRow) * _backend->get_board_nbColumn() + (column - _gridFirstColumn)};
}


bool MainGridModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    // TODO if index is larger, update back end grid
    if (!index.isValid() || role != Cell)
    {
        return false;
    }
    const auto vecId{calculateIndexFromUIRow(index)};
    if (!vecId.has_value())
    {
        return false;
    }

    if (_backend->get_boardCellAliveAt(vecId.value()) == value.toBool())
    {
        return false;
    }

    _backend->get_board()->get_grid()[vecId.value()] = value.toBool();
    emit dataChanged(index, index, {role});
    return true;
}


QHash<int, QByteArray> MainGridModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Cell] = "cellValue";
    return roles;
}

void MainGridModel::updateUIGrid() noexcept
{
    // TODO data race here for _backend->board (line and column), add mutex
    beginResetModel();
    updateGridCounters();
    emit _dimensionChanged();
    endResetModel();
}
