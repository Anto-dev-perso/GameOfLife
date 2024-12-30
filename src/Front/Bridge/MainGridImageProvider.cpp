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
            drawGridRectangle(row, col, grid);
        }
    }
    _cacheBuster++;
}

void MainGridImageProvider::drawGridRectangle(size_t row, size_t column, const grid_of_cells& grid) noexcept
{
    if (const auto vecId{calculateIndexFromUIRow(row, column)}; vecId.has_value())
    {
        _gridPainter.setBrush(grid.at(vecId.value()).get_isCurrentlyAlive()
                                  ? CELL_ALIVE_COLOR
                                  : CELL_DEAD_COLOR);
    }
    else
    {
        _gridPainter.setBrush(CELL_DEAD_COLOR);
    }
    _gridPainter.drawRect(column * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
}

void MainGridImageProvider::updateImage() noexcept
{
    const auto& board = _backend->get_board_data();
    const auto rowStart{std::min(_oldGridFirstRow, _gridFirstRow)};
    const auto colStart{std::min(_oldGridFirstColumn, _gridFirstColumn)};
    const size_t rowStop{rowStart + board.line};
    const size_t ColStop{colStart + board.column};

    for (size_t row = rowStart; row < rowStop; row++)
    {
        for (size_t column = colStart; column < ColStop; column++)
        {
            drawGridRectangle(row, column, board.grid);
        }
    }
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
        _oldGridFirstColumn = _gridFirstColumn;
        _oldGridFirstRow = _gridFirstRow;
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
    {
        QWriteLocker lock{&_lockBackendRef};
        _backend->changeBoard(patternIndex, gridIndex);
        reDrawTheEntireMainGrid();
    }
}

void MainGridImageProvider::reDrawTheEntireMainGrid() noexcept
{
    updateGridCounters();
    printANewGridImage();
}

void MainGridImageProvider::reDrawGrid()
{
    QReadLocker lock{&_lockBackendRef};
    updateGridCounters();
    updateImage();
}

void MainGridImageProvider::resetMainGrid()
{
    QWriteLocker lock{&_lockBackendRef};
    if (_backend->get_nbOfIterations() != 0)
    {
        _backend->resetBoard();
        updateGridCounters();
        reDrawTheEntireMainGrid();
    }
}

void MainGridImageProvider::clearMainGrid()
{
    QWriteLocker lock{&_lockBackendRef};
    _backend->clearBoard();
    reDrawTheEntireMainGrid();
}

void MainGridImageProvider::editCell(double mouseX, double mouseY, unsigned int uiWidth, unsigned int uiHeight)
{
    const double cellWidth = uiWidth / static_cast<double>(_UIColumnCount);
    const double cellHeight = uiHeight / static_cast<double>(_UILineCount);

    const auto row = static_cast<line_size>(std::floor(mouseY / cellHeight));
    const auto column = static_cast<column_size>(std::floor(mouseX / cellWidth));

    if (auto optIndex{calculateIndexFromUIRow(row, column)}; optIndex.has_value())
    {
        const auto backIndex{optIndex.value()};
        bool newValue;
        {
            QWriteLocker lock{&_lockBackendRef};
            newValue = _backend->change_CellValue(backIndex);
        }
        changeCellInImage({row, column}, newValue);
    }
    else
    {
        const auto rowNb{_backend->get_board_nbLine()};
        const auto colNb{_backend->get_board_nbColumn()};

        size_t diffRow{0}, diffColumn{0};
        if (row < static_cast<line_size>(_gridFirstRow)) { diffRow = _gridFirstRow - row; }
        else if (row > static_cast<line_size>(_gridFirstRow) + rowNb) { diffRow = row - (_gridFirstRow + rowNb - 1); }

        if (column < static_cast<line_size>(_gridFirstColumn)) { diffColumn = _gridFirstColumn - column; }
        else if (column > static_cast<line_size>(_gridFirstColumn) + colNb)
        {
            diffColumn = column - (_gridFirstColumn + colNb - 1);
        }

        const auto expandNumber{std::max(diffRow, diffColumn)};


        if (QWriteLocker lock{&_lockBackendRef}; _backend->expandBoard(expandNumber))
        {
            const auto rowToUpdate{expandNumber + row - _gridFirstRow};
            const auto columnToUpdate{expandNumber + column - _gridFirstColumn};
            const auto indexToUpdate{rowToUpdate * _backend->get_board_nbColumn() + columnToUpdate};

            std::ignore = _backend->change_CellValue(indexToUpdate);
            updateGridCounters();
            updateImage();
        }
    }
    _cacheBuster++;
}
