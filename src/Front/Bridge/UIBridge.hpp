#pragma once

#include "LexiconModel.hpp"
#include "ThreadProxy.hpp"
#include "MainGridImageProvider.hpp"

#include <QTimer>
#include <qcoreapplication.h>
#include <QPainter>

#include <utility>
#include <set>

class UIBridge : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double _gameSpeed READ get_gameSpeed WRITE set_gameSpeed NOTIFY _gameSpeedChanged)
    Q_PROPERTY(unsigned int _iterationNumber READ get_iterationNumber NOTIFY _iterationNumberChanged)
    Q_PROPERTY(double _zoomValue READ get_zoomValue WRITE set_zoomValue NOTIFY _zoomValueChanged)
    Q_PROPERTY(double _scaleFactor READ get_scaleFactor NOTIFY _scaleFactorChanged)

    Q_PROPERTY(LexiconNameModel *_lexiconNameModel READ get_lexiconNameModelPtr CONSTANT)

public:
    explicit UIBridge(QObject* parent = nullptr);


    void initialize(QQmlEngine* engine);
    [[nodiscard]] double get_gameSpeed() const noexcept { return _gameSpeed; }
    [[nodiscard]] unsigned int get_iterationNumber() const noexcept { return _threadProxy->get_iterationNumber(); }

    [[nodiscard]] double get_zoomValue() const noexcept
    {
        return _mainGridImageProvider->get_zoomValue();
    }

    [[nodiscard]] double get_scaleFactor() const noexcept
    {
        return _mainGridImageProvider->get_scaleFactor();
    }


    [[nodiscard]] LexiconNameModel* get_lexiconNameModelPtr() const noexcept { return _lexiconNameModel.get(); }

signals:
    void _zoomValueChanged();
    void _scaleFactorChanged();
    void _imageUpdated();
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

    void set_zoomValue(double newValue) noexcept
    {
        _mainGridImageProvider->set_zoomValue(newValue);
        emit _zoomValueChanged();
        emit _scaleFactorChanged();
    }

    void runGame() const noexcept { _threadProxy->run(); }
    void stopGame() const noexcept { _threadProxy->stopWork(); }

    void runIteration() noexcept
    {
        _threadProxy->processingIteration();
        emit _imageUpdated();
    }

    void reDrawEntirely() noexcept
    {
        _mainGridImageProvider->reDrawMainGrid();
        emit _imageUpdated();
    }

    void updateCells(const std::vector<Game::indices_with_value>& idToChange) noexcept
    {
        _mainGridImageProvider->changeCellColors(idToChange);
        emit _imageUpdated();
    }

    void changePatternBackEnd(int patternIndex, int gridIndex) noexcept;
    void resetPattern() noexcept;
    void clearPattern() noexcept;

    [[nodiscard]] QString getMainGridImage() const noexcept
    {
        return {QURL_IMAGE_PROVIDER + std::to_string(_mainGridImageProvider->_cacheBuster).c_str()};
    }

    [[nodiscard]] bool fileExists(int patternId, int gridId) const noexcept
    {
        return _lexiconNameModel->get_descriptionModel()->checkIfGridIsntEmpty(patternId, gridId);
    }

private:
    [[nodiscard]] constexpr std::chrono::microseconds calculateWaitTimeFromSlider() const noexcept
    {
        // Time calculated in seconds
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<double>{
            MainGridImageProvider::calculateLinearValue(_gameSpeed, WAIT_MAX, WAIT_MIN)
        });
    }

    double _gameSpeed{50};

    std::unique_ptr<ThreadProxy> _threadProxy;

    std::unique_ptr<LexiconNameModel> _lexiconNameModel;
    MainGridImageProvider* _mainGridImageProvider{nullptr};

    static constexpr double WAIT_MAX{1.5}; // seconds
    static constexpr double WAIT_MIN{0.001}; // seconds

    const QString IMAGE_PROVIDER_NAME{"_mainGrid"};
    const QString QURL_IMAGE_PROVIDER{"image://" + IMAGE_PROVIDER_NAME + "/"};
};
