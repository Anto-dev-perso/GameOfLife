#include "MainGridImageProvider.hpp"

#include "Back/Game/Board.hpp"


MainGridImageProvider::MainGridImageProvider(std::shared_ptr<Game> backend, QReadWriteLock& lock) :
    QQuickImageProvider(QQuickImageProvider::Image), _backend(std::move(backend)), _lockBackendRef(lock)

{
    _backend->set_maximumLineAndColumn(NB_UI_LINES_AT_MAX, NB_UI_COLUMNS_AT_MAX);
    updateGridCounters();
    _gridPainter.begin(&_gridImage);

    _gridPen.setWidth(1);
    _gridPainter.setPen(_gridPen);

    printANewGridImage();
}

void MainGridImageProvider::changeCellColors(const std::vector<Game::indices_with_value>& indicesToChanges)
{
    bool changed{false};
    QReadLocker lock{&_lockBackendRef};
    for (const auto& [idBack,newValue] : indicesToChanges)
    {
        const auto convertedIds{calculateUIIndexFromBackId(idBack)};
        if (convertedIds.has_value())
        {
            changed = true;
            changeCellInImage(convertedIds.value(), newValue);
        }
    }
    if (changed)
    {
        _cacheBuster++;
    }
}

void MainGridImageProvider::printANewGridImage() noexcept
{
    const auto& grid = _backend->get_board_data().grid;

    for (size_t row = 0; row < _UILineCount; row++)
    {
        for (size_t col = 0; col < _UIColumnCount; col++)
        {
            if (const auto vecId{calculateIndexFromUIRow(row, col)}; vecId.has_value())
            {
                _gridPainter.setBrush(grid.at(vecId.value()).get_isCurrentlyAlive()
                                          ? CELL_ALIVE_COLOR
                                          : CELL_DEAD_COLOR);
            }
            else
            {
                _gridPainter.setBrush(CELL_DEAD_COLOR);
            }

            _gridPainter.drawRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
        }
    }
    _cacheBuster++;
}


void MainGridImageProvider::changeCellInImage(const Game::line_column& indices, bool value) noexcept
{
    _gridPainter.setBrush(value ? CELL_ALIVE_COLOR : CELL_DEAD_COLOR);
    _gridPainter.drawRect(indices.column * CELL_SIZE, indices.line * CELL_SIZE, CELL_SIZE, CELL_SIZE);
}

QImage MainGridImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    Q_UNUSED(id)
    Q_UNUSED(size)
    Q_UNUSED(requestedSize)
    return _gridImage;
}


std::optional<Game::line_column>
MainGridImageProvider::calculateUIIndexFromBackId(const Game::line_column& pair) const noexcept
{
    // No need to lock here because this function is always called inside an already locked function
    if (_gridFirstRow < 0 || pair.line >= _backend->get_board_nbLine() || pair.column >= _backend->get_board_nbColumn()
        || _gridFirstColumn < 0)
    {
        return std::nullopt;
    }
    return Game::line_column{pair.line + _gridFirstRow, pair.column + _gridFirstColumn};
}

void MainGridImageProvider::updateGridCounters() noexcept
{
    // No need to lock here because this function is always called inside an already locked function
    const auto backNbLine{_backend->get_board_nbLine()};
    const auto backNbCol{_backend->get_board_nbColumn()};
    if (backNbLine > 0 && backNbCol > 0 && backNbLine <= NB_UI_LINES_AT_MAX && backNbCol <= NB_UI_COLUMNS_AT_MAX)
    {
        _gridFirstRow = (_UILineCount - _backend->get_board_nbLine()) / 2;
        _gridFirstColumn = (_UIColumnCount - _backend->get_board_nbColumn()) / 2;
    }
    else
    {
        _gridFirstRow = -1;
        _gridFirstColumn = -1;
    }
}

std::optional<size_t> MainGridImageProvider::calculateIndexFromUIRow(size_t row, size_t column) const noexcept
{
    // No need to lock here because this function is always called inside an already locked function
    if (_gridFirstRow < 0 || _gridFirstColumn < 0 || static_cast<int>(row) < _gridFirstRow || static_cast<int>(row) >=
        _gridFirstRow + static_cast<int>(
            _backend->get_board_nbLine()) ||
        static_cast<int>(column) < _gridFirstColumn || static_cast<int>(column) >= _gridFirstColumn + static_cast<int>(
            _backend->get_board_nbColumn()))
    {
        return std::nullopt;
    }

    return {(row - _gridFirstRow) * _backend->get_board_nbColumn() + (column - _gridFirstColumn)};
}

void MainGridImageProvider::changeMainGridWithPatternIndices(int patternIndex, int gridIndex)
{
    // TODO Maybe use data in the index of the grid instead of the reset
    {
        QWriteLocker lock{&_lockBackendRef};
        _backend->changeBoard(patternIndex, gridIndex);
    }
    reDrawMainGrid();
}

void MainGridImageProvider::reDrawMainGrid()
{
    // TODO Maybe use data in the index of the grid instead of the reset
    QReadLocker lock{&_lockBackendRef};
    updateGridCounters();
    printANewGridImage();
}

void MainGridImageProvider::resetMainGrid()
{
    QWriteLocker lock{&_lockBackendRef};
    if (_backend->get_nbOfIterations() != 0)
    {
        // TODO Maybe use data in the index of the grid instead of the reset
        _backend->resetBoard();
        updateGridCounters();
        printANewGridImage();
    }
}

void MainGridImageProvider::clearMainGrid()
{
    // TODO Maybe use data in the index of the grid instead of the reset
    QWriteLocker lock{&_lockBackendRef}; // TODO double lock
    _backend->clearBoard();
    updateGridCounters();
    printANewGridImage();
}
