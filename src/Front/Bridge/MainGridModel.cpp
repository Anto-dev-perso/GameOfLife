
#include "MainGridModel.hpp"

MainGridModel::MainGridModel(std::shared_ptr<Game> backend, QObject *parent) : QAbstractListModel(parent),
                                                                               _backend(std::move(backend))
{
    updateGridCounters();
}

std::optional<QModelIndex> MainGridModel::calculateUIIndexFromBackId(const Game::line_column &pair) const noexcept
{
    if (_gridFirstRow < 0 || _gridFirstColumn < 0)
    {
        return std::nullopt;
    }
    const auto &[line, column] = pair;

    const int uiLine = line + _gridFirstRow;
    const int uiColumn = column + _gridFirstColumn;

    return index(uiLine * _UIColumnCount + uiColumn);
}

QVariant MainGridModel::data(const QModelIndex &index, int role) const
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

std::optional<int> MainGridModel::calculateIndexFromUIRow(const QModelIndex &index) const noexcept
{
    if (!index.isValid())
    {
        return std::nullopt;
    }

    const int row{index.row() / _UIColumnCount};
    const int column{index.row() % _UIColumnCount};

    if (_gridFirstRow < 0 || _gridFirstColumn < 0 || row < _gridFirstRow || row >= _gridFirstRow + static_cast<int>(_backend->get_board_nbLine()) ||
        column < _gridFirstColumn || column >= _gridFirstColumn + static_cast<int>(_backend->get_board_nbColumn()))
    {
        return std::nullopt;
    }

    return {(row - _gridFirstRow) * _backend->get_board_nbColumn() + (column - _gridFirstColumn)};
}

bool MainGridModel::setData(const QModelIndex &index, const QVariant &value, int role)
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
    // Maybe use data in the index of the grid instead of the reset
    beginResetModel();
    updateGridCounters();
    endResetModel();
}

void MainGridModel::changeMainGridWithPatternIndices(int patternIndex, int gridIndex)
{
    // TODO data race here for _backend->board (line and column), add mutex
    // Maybe use data in the index of the grid instead of the reset
    beginResetModel();
    _backend->changeBoard(patternIndex, gridIndex);
    updateGridCounters();
    endResetModel();
}

void MainGridModel::resetMainGrid()
{
    if (_backend->get_nbOfIterations() != 0)
    {
        // TODO data race here for _backend->board (line and column), add mutex
        // Maybe use data in the index of the grid instead of the reset
        beginResetModel();
        _backend->resetBoard();
        updateGridCounters();
        endResetModel();
    }
}

void MainGridModel::clearMainGrid()
{
    // TODO data race here for _backend->board (line and column), add mutex
    // Maybe use data in the index of the grid instead of the reset
    beginResetModel();
    _backend->clearBoard();
    updateGridCounters();
    endResetModel();
}
