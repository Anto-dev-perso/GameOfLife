#pragma once
#include <QAbstractListModel>
#include <memory>
#include <qbytearray.h>
#include <qhash.h>
#include <qmetatype.h>
#include <qobject.h>
#include <qvariant.h>
#include <vector>

#include "LexiconModel.hpp"
#include "../Back/Game/Game.hpp"
#include "Game/PatternList.hpp"

class MainGridModel final : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(double _scaleFactor READ get_scaleFactor NOTIFY _scaleFactorChanged)
    Q_PROPERTY(double _zoomValue READ get_zoomValue WRITE set_zoomValue NOTIFY _zoomValueChanged)
    Q_PROPERTY(int _UILineCount READ get_UILineCount NOTIFY _dimensionChanged)
    Q_PROPERTY(int _UIColumnCount READ get_UIColumnCount NOTIFY _dimensionChanged)

public:
    explicit MainGridModel(std::shared_ptr<Game> backend, QObject* parent = nullptr);

    [[nodiscard]] std::optional<QModelIndex> calculateUIIndexFromBackId(const Game::line_column& pair) const noexcept;

    [[nodiscard]] int get_UILineCount() const noexcept
    {
        return _UILineCount;
    }

    [[nodiscard]] int get_UIColumnCount() const noexcept
    {
        return _UIColumnCount;
    }

    [[nodiscard]] double get_zoomValue() const noexcept { return _zoomValue; }
    [[nodiscard]] double get_scaleFactor() const noexcept { return _scaleFactor; }

    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        Q_UNUSED(parent)
        return _UILineCount * _UIColumnCount;
    }

    [[nodiscard]] QVariant data(const QModelIndex& index, const int role = Qt::DisplayRole) const override;
    [[nodiscard]] bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    void updateUIGrid() noexcept;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    [[nodiscard]] constexpr static double calculateLinearValue(double x, double y1, double y2, double x1 = 0,
                                                               double x2 = 100) noexcept
    {
        const double m{(y2 - y1) / (x2 - x1)}; // Slope
        const double b{y1 - m * x1}; // Intercept
        return m * x + b; // Linear value
    }

    void changeMainGridWithPatternIndices(int patternIndex, int gridIndex);
    void resetMainGrid();
    void clearMainGrid();

public slots:
    void set_zoomValue(double newGridSize) noexcept
    {
        if (_zoomValue != newGridSize)
        {
            _zoomValue = newGridSize;
            emit _zoomValueChanged();
            _scaleFactor = calculateLinearValue(_zoomValue, SCALE_MIN, SCALE_MAX);
            emit _scaleFactorChanged();
        }
    }

    void resetModel()
    {
        beginResetModel();
        endResetModel();
    }

    void updateData(const Game::line_column& firstRow, const Game::line_column& lastRow)
    {
        const auto optFrist{calculateUIIndexFromBackId(firstRow)};
        const auto optLast{calculateUIIndexFromBackId(lastRow)};
        if (optFrist.has_value() && optLast.has_value())
        {
            dataChanged(optFrist.value(), optLast.value());
        }
    }

signals:
    void _zoomValueChanged();
    void _dimensionChanged();
    void _scaleFactorChanged();

private:
    void updateGridCounters() noexcept
    {
        _UILineCount = calculateUILines(_zoomValue);
        _UIColumnCount = calculateUIColumns(_zoomValue);

        const auto backNbLine{_backend->get_board_nbLine()};
        const auto backNbCol{_backend->get_board_nbColumn()};
        if (backNbLine > 0 && backNbCol > 0)
        {
            _gridFirstRow = (_UILineCount - _backend->get_board_nbLine()) / 2;
            _gridFirstColumn = (_UIColumnCount - _backend->get_board_nbColumn()) / 2;
        }
        else
        {
            _gridFirstRow = -1;
            _gridFirstColumn = -1;
        }

        emit _dimensionChanged();
    }

    [[nodiscard]] std::optional<int> calculateIndexFromUIRow(const QModelIndex& index) const noexcept;

    [[nodiscard]] static int calculateUIColumns(double sliderValue) noexcept
    {
        return static_cast<int>(std::round(
            calculateLinearValue(sliderValue, NB_UI_COLUMNS_AT_MAX, NB_UI_COLUMNS_AT_MIN)));
    }

    [[nodiscard]] static int calculateUILines(double sliderValue) noexcept
    {
        return static_cast<int>(std::round(
            calculateLinearValue(sliderValue, NB_UI_LINES_AT_MAX, NB_UI_LINES_AT_MIN)));
    }

    enum Roles
    {
        Cell = Qt::UserRole + 1,
    };

    std::shared_ptr<Game> _backend;

    double _zoomValue{50};
    double _scaleFactor{calculateLinearValue(_zoomValue, SCALE_MIN, SCALE_MAX)};

    int _UILineCount{NB_UI_LINES_AT_MAX};
    int _UIColumnCount{NB_UI_COLUMNS_AT_MAX};
    int _gridFirstRow{-1};
    int _gridFirstColumn{-1};

    static constexpr unsigned int NB_UI_COLUMNS_AT_MAX{150};
    static constexpr unsigned int NB_UI_LINES_AT_MAX{75};
    static constexpr unsigned int NB_UI_COLUMNS_AT_MIN{20};
    static constexpr unsigned int NB_UI_LINES_AT_MIN{10};

    static constexpr double SCALE_MIN{1};
    static constexpr double SCALE_MAX{5};
};
