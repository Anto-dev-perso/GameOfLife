#include "UIBridge.hpp"
#include <QTimer>

UIBridge::UIBridge(QObject *parent)
    : QAbstractListModel(parent), _backend(std::make_shared<Game>()),
      _threadProxy(std::make_unique<ThreadProxy>(_backend, calculateWaitTimeFromSlider()))
{
    

    updateGridCounters();

    std::ignore = connect(_threadProxy.get(), &ThreadProxy::iterationNumberFinishedEditing, this,
                          &UIBridge::_iterationNumberChanged);
    std::ignore = connect(_threadProxy.get(), &ThreadProxy::requestModelReset, this, &UIBridge::resetModel);
    std::ignore = connect(_threadProxy.get(), &ThreadProxy::requestDataChange, this, &UIBridge::updateData);
}

QVariant UIBridge::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != ValueRole)
    {
        return QVariant();
    }
    if (const auto vecId{calculateIndexFromUIRow(index)}; vecId.has_value())
    {
        return QVariant(_backend->get_boardCellAliveAt(vecId.value()));
    }

    return QVariant();
}

bool UIBridge::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // TODO if index is larger, update back end grid
    if (!index.isValid() || role != ValueRole)
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

std::optional<size_t> UIBridge::calculateIndexFromUIRow(const QModelIndex &index) const noexcept
{
    if (!index.isValid())
    {
        return std::nullopt;
    }

    const int row = index.row() / _UIColumnCount;
    const int column = index.row() % _UIColumnCount;

    if (row < _gridFirstRow || row >= _gridFirstRow + _backend->get_board_nbLine() ||
        column < _gridFirstColumn || column >= _gridFirstColumn + _backend->get_board_nbColumn())
    {
        return std::nullopt;
    }

    return {(row - _gridFirstRow) * _backend->get_board_nbColumn() + (column - _gridFirstColumn)};
}

void UIBridge::runGame() const noexcept
{
    _threadProxy->run();
}

void UIBridge::stopGame() const noexcept
{
    _threadProxy->stopWork();
}

void UIBridge::runIteration() const noexcept
{
    _threadProxy->processingIteration();
}

[[nodiscard]] QModelIndex UIBridge::calculateUIIndexFromBackId(
    const Game::line_column &pair) const noexcept
{
    const auto &[line, column] = pair;

    const int uiLine = line + _gridFirstRow;
    const int uiColumn = column + _gridFirstColumn;

    return index(uiLine * _UIColumnCount + uiColumn);
}


void UIBridge::resetModel()
{
    beginResetModel();
    endResetModel();
}

void UIBridge::updateData(Game::line_column firstRow, Game::line_column lastRow)
{
    dataChanged(calculateUIIndexFromBackId(firstRow), calculateUIIndexFromBackId(lastRow));
}

void UIBridge::updateUIGrid() noexcept
{
    // TODO data race here for _backend->board (line and column), add mutex
    beginResetModel();
    updateGridCounters();
     emit _dimensionChanged();
    endResetModel();
}
