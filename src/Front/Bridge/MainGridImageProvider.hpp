
#pragma once

#include <QQuickImageProvider>
#include <QPainter>
#include <QReadWriteLock>


#include "Back/Game/Board.hpp"
#include "Back/Game/Game.hpp"
#include "Front/Bridge/MainGridImageProvider.hpp"

const QColor BORDER_COLOR{"#989898"};
const QColor CELL_ALIVE_COLOR{"#ffff00"};
const QColor CELL_DEAD_COLOR{"#7e7e7e"};
static constexpr int CELL_SIZE{10};

class MainGridImageProvider : public QQuickImageProvider
{
public:
    MainGridImageProvider(std::shared_ptr<Game> backend, QReadWriteLock& lock);

    ~MainGridImageProvider() override
    {
        _gridPainter.end();
    }

    void printANewGridImage() noexcept;

    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;

    [[nodiscard]] std::optional<Game::line_column>
    calculateUIIndexFromBackId(const Game::line_column& pair) const noexcept;

    [[nodiscard]] size_t get_UILineCount() const noexcept
    {
        return _UILineCount;
    }

    [[nodiscard]] size_t get_UIColumnCount() const noexcept
    {
        return _UIColumnCount;
    }

    [[nodiscard]] double get_zoomValue() const noexcept { return _zoomValue; }
    [[nodiscard]] double get_scaleFactor() const noexcept { return _scaleFactor; }

    [[nodiscard]] constexpr static double calculateLinearValue(double x, double y1, double y2, double x1 = 0,
                                                               double x2 = 100)
    {
        if (x1 == x2) { throw std::invalid_argument("ERROR: X1 and X2 can't have the same value"); }
        const double m{(y2 - y1) / (x2 - x1)}; // Slope
        const double b{y1 - m * x1}; // Intercept
        return m * x + b; // Linear value
    }

    void changeMainGridWithPatternIndices(int patternIndex, int gridIndex);
    void reDrawThenEntireMainGrid() noexcept;
    void reDrawGrid();
    void resetMainGrid();
    void clearMainGrid();

    void set_zoomValue(double newGridSize) noexcept
    {
        if (_zoomValue != newGridSize)
        {
            _zoomValue = newGridSize;
            _scaleFactor = calculateLinearValue(_zoomValue, SCALE_MIN, SCALE_MAX);
            updateGridCounters();
        }
    }


    void changeCellColors(const std::vector<Game::indices_with_value>& indicesToChanges);

#ifdef ENABLE_DEBUG

    [[nodiscard]] int get_gridFirstColumn() const noexcept { return _gridFirstColumn; }
    [[nodiscard]] int get_gridFirstRow() const noexcept { return _gridFirstRow; }

    void set_gridFirstColumn(int firstCol) noexcept { _gridFirstColumn = firstCol; }
    void set_gridFirstRow(int firstRow) noexcept { _gridFirstRow = firstRow; }

#endif

    void updateGridCounters() noexcept;
    [[nodiscard]] std::optional<size_t> calculateIndexFromUIRow(size_t row, size_t column) const noexcept;

#ifdef ENABLE_DEBUG

private:
#endif

    void changeCellInImage(const Game::line_column& indices, bool value) noexcept;

    [[nodiscard]] static size_t calculateUIColumns(double sliderValue) noexcept
    {
        return static_cast<size_t>(std::round(
            calculateLinearValue(sliderValue, NB_UI_COLUMNS_AT_MAX, NB_UI_COLUMNS_AT_MIN)));
    }

    [[nodiscard]] static size_t calculateUILines(double sliderValue) noexcept
    {
        return static_cast<size_t>(std::round(
            calculateLinearValue(sliderValue, NB_UI_LINES_AT_MAX, NB_UI_LINES_AT_MIN)));
    }

    void drawGridRectangle(size_t row, size_t column, const grid_of_cells& grid) noexcept;
    void updateImage() noexcept;

    std::shared_ptr<Game> _backend;

    double _zoomValue{50};
    double _scaleFactor{calculateLinearValue(_zoomValue, SCALE_MIN, SCALE_MAX)};

    int _gridFirstRow{-1};
    int _gridFirstColumn{-1};
    int _oldGridFirstRow{-1};
    int _oldGridFirstColumn{-1};

    size_t _UILineCount{NB_UI_LINES_AT_MAX};
    size_t _UIColumnCount{NB_UI_COLUMNS_AT_MAX};

    static constexpr double SCALE_MIN{1};
    static constexpr double SCALE_MAX{10};


    QPen _gridPen{BORDER_COLOR};
    QPainter _gridPainter;
    QImage _gridImage{NB_UI_COLUMNS_AT_MAX * CELL_SIZE, NB_UI_LINES_AT_MAX * CELL_SIZE, QImage::Format_ARGB32};

    QReadWriteLock& _lockBackendRef;

public:
    static constexpr size_t NB_UI_COLUMNS_AT_MAX{400};
    static constexpr size_t NB_UI_LINES_AT_MAX{200};
    static constexpr size_t NB_UI_COLUMNS_AT_MIN{20};
    static constexpr size_t NB_UI_LINES_AT_MIN{10};

    unsigned int _cacheBuster{0};
};
