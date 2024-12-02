#pragma once

#include "LexiconModel.hpp"
#include "MainGridModel.hpp"
#include "ThreadProxy.hpp"

#include <QTimer>
#include <qcoreapplication.h>

#include <memory>
#include <utility>
#include <set>

class UIBridge : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double _gameSpeed READ get_gameSpeed WRITE set_gameSpeed NOTIFY _gameSpeedChanged)
    Q_PROPERTY(size_t _iterationNumber READ get_iterationNumber NOTIFY _iterationNumberChanged)

    Q_PROPERTY(LexiconNameModel *_lexiconNameModel READ get_lexiconNameModelPtr CONSTANT)
    Q_PROPERTY(MainGridModel *_mainGridModel READ get_mainGridModel CONSTANT)

public:
    explicit UIBridge(QObject *parent = nullptr);

    [[nodiscard]] double get_gameSpeed() const noexcept { return _gameSpeed; }
    [[nodiscard]] size_t get_iterationNumber() const noexcept { return _backend->get_nbOfIterations(); }

    [[nodiscard]] LexiconNameModel *get_lexiconNameModelPtr() const noexcept { return _lexiconNameModel.get(); }
    [[nodiscard]] MainGridModel *get_mainGridModel() const noexcept { return _mainGridModel.get(); }

signals:
    void _gameSpeedChanged();
    void _iterationNumberChanged();

public slots:
    void set_gameSpeed(double newSpeed) noexcept
    {
        if (_gameSpeed != newSpeed)
        {
            _gameSpeed = newSpeed;
            _threadProxy->set_waitTimeMicro(calculateWaitTimeFromSlider());
            emit _gameSpeedChanged();
        }
    }

    void runGame() const noexcept { _threadProxy->run(); }
    void stopGame() const noexcept { _threadProxy->stopWork(); }
    void runIteration() const noexcept { _threadProxy->processingIteration(); }

public slots:
    void changePatternBackEnd(int patternIndex, int gridIndex) noexcept;
    void resetPattern() noexcept;
    void clearPattern() noexcept;

private:
    [[nodiscard]] constexpr std::chrono::microseconds calculateWaitTimeFromSlider() const noexcept
    {
        // Time calculated in seconds
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<double>{MainGridModel::calculateLinearValue(_gameSpeed, WAIT_MAX, WAIT_MIN)});
    }

    double _gameSpeed{50};

    std::shared_ptr<Game> _backend; // TODO Bridge doesn't need anymore the backend
    std::unique_ptr<ThreadProxy> _threadProxy;

    std::unique_ptr<LexiconNameModel> _lexiconNameModel;
    std::unique_ptr<MainGridModel> _mainGridModel;

    static constexpr double WAIT_MAX{1.5};   // seconds
    static constexpr double WAIT_MIN{0.001}; // seconds
};
