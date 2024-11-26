#pragma once

#include <QAbstractListModel>
#include <QTimer>

#include "../Back/Game/Game.hpp"
#include <memory>
#include <utility>
#include <set>

#include "ThreadProxy.hpp"

class UIBridge : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(double _gameSpeed READ get_gameSpeed WRITE set_gameSpeed NOTIFY _gameSpeedChanged)
    Q_PROPERTY(double _zoomValue READ get_zoomValue WRITE set_zoomValue NOTIFY _zoomValueChanged)
    Q_PROPERTY(double _scaleFactor READ get_scaleFactor NOTIFY _scaleFactorChanged)
    Q_PROPERTY(size_t _iterationNumber READ get_iterationNumber NOTIFY _iterationNumberChanged)
    Q_PROPERTY(size_t _UILineCount READ get_UILineCount NOTIFY _dimensionChanged)
    Q_PROPERTY(size_t _UIColumnCount READ get_UIColumnCount NOTIFY _dimensionChanged)

    enum Roles
    {
        ValueRole = Qt::UserRole + 1
    };

public:
    explicit UIBridge(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        Q_UNUSED(parent)
        return _UILineCount * _UIColumnCount;
    }

    [[nodiscard]] inline int get_board_nbLine() const noexcept
    {
        return _backend->get_board_nbLine();
    }

    [[nodiscard]] inline int get_board_nbColumn() const noexcept
    {
        return _backend->get_board_nbColumn();
    }

    [[nodiscard]] inline double get_gameSpeed() const noexcept { return _gameSpeed; }

    [[nodiscard]] inline double get_zoomValue() const noexcept { return _zoomValue; }
    [[nodiscard]] inline double get_scaleFactor() const noexcept { return _scaleFactor; }

    [[nodiscard]] inline size_t get_iterationNumber() const noexcept { return _backend->get_nbOfIterations(); }

    [[nodiscard]] inline int get_UILineCount() const noexcept
    {
        return _UILineCount;
    }

    [[nodiscard]] inline int get_UIColumnCount() const noexcept
    {
        return _UIColumnCount;
    }

    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    [[nodiscard]] inline QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[ValueRole] = "value";
        return roles;
    }

signals:
    void _gameSpeedChanged();
    void _zoomValueChanged();
    void _iterationNumberChanged();
    void _dimensionChanged();
    void _scaleFactorChanged();

public slots:
    inline void set_gameSpeed(double newSpeed) noexcept
    {
        if (_gameSpeed != newSpeed)
        {
            _gameSpeed = newSpeed;
            _threadProxy->set_waitTimeMicro(calculateWaitTimeFromSlider());
            emit _gameSpeedChanged();
        }
    }

    inline void set_zoomValue(double newGridSize) noexcept
    {
        if (_zoomValue != newGridSize)
        {
            _zoomValue = newGridSize;
            emit _zoomValueChanged();
            _scaleFactor = calculateLinearValue(_zoomValue, _scaleMin, _scaleMax);
            emit _scaleFactorChanged();
        }
    }

    void runGame() const noexcept;
    void stopGame() const noexcept;
    void runIteration() const noexcept;

    void resetModel();
    void updateData(Game::line_column firstRow, Game::line_column lastRow);

private:
    inline void updateFirstLine() noexcept
    {
        _gridFirstRow = (_UILineCount - _backend->get_board_nbLine()) / 2;
    }

    inline void updateFirstColumn() noexcept
    {
        _gridFirstColumn = (_UIColumnCount - _backend->get_board_nbColumn()) / 2;
    }

    [[nodiscard]] std::optional<size_t> calculateIndexFromUIRow(const QModelIndex &index) const noexcept;
    [[nodiscard]] QModelIndex calculateUIIndexFromBackId(
        const Game::line_column &pair) const noexcept;

    [[nodiscard]] constexpr inline std::chrono::microseconds calculateWaitTimeFromSlider() const noexcept
    {
        // Time calculated in seconds
        const auto calculatedWaitTime = calculateLinearValue(_gameSpeed, _waitMax, _waitMin);
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<double>{calculatedWaitTime});
    }

    [[nodiscard]] constexpr static double calculateLinearValue(double x, double y1, double y2, double x1 = 0,
                                                               double x2 = 100) noexcept
    {
        // Slope
        const double m{(y2 - y1) / (x2 - x1)};
        // Intercept
        const double b{y1 - m * x1};
        // Linear value
        return m * x + b;
    }

    [[nodiscard]] constexpr static int calculateUIColumns(double sliderValue) noexcept
    {
        return static_cast<int>(std::round(
            calculateLinearValue(sliderValue, _nbUIColumnsAtMax, _nbUIColumnsAtMin)));
    }

    [[nodiscard]] static constexpr int calculateUILines(double sliderValue) noexcept
    {
        return static_cast<int>(std::round(
            calculateLinearValue(sliderValue, _nbUILinesAtMax, _nbUILinesAtMin)));
    }

    inline void updateGridCounters() noexcept
    {
        _UILineCount = calculateUILines(_zoomValue);
        _UIColumnCount = calculateUIColumns(_zoomValue);
        _gridFirstRow = (_UILineCount - _backend->get_board_nbLine()) / 2;
        _gridFirstColumn = (_UIColumnCount - _backend->get_board_nbColumn()) / 2;
    }

    void updateUIGrid() noexcept;

    double _gameSpeed{50};
    double _zoomValue{50};
    double _scaleFactor{_scaleMin};

    std::shared_ptr<Game> _backend;
    std::unique_ptr<ThreadProxy> _threadProxy;
    size_t _UILineCount{_nbUILinesAtMax};
    size_t _UIColumnCount{_nbUIColumnsAtMax};

    size_t _gridFirstRow{0};
    size_t _gridFirstColumn{0};

    static constexpr double _waitMax{2};     // seconds
    static constexpr double _waitMin{0.005}; // seconds

    static constexpr unsigned int _nbUIColumnsAtMax{150};
    static constexpr unsigned int _nbUILinesAtMax{75};
    static constexpr unsigned int _nbUIColumnsAtMin{30};
    static constexpr unsigned int _nbUILinesAtMin{15};

    static constexpr double _scaleMin{1};
    static constexpr double _scaleMax{3};
};
