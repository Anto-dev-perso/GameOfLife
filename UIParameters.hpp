#pragma once

#include <QObject>

class UIParameters : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int _gameSpeed READ get_gameSpeed WRITE set_gameSpeed NOTIFY _gameSpeedChanged FINAL)
    Q_PROPERTY(int _gridSize READ get_gridSize WRITE set_gridSize NOTIFY _gridSizeChanged FINAL)
    Q_PROPERTY(size_t _iterationNumber READ get_iterationNumber WRITE set_iterationNumber NOTIFY _iterationNumberChanged FINAL)

public:
    explicit UIParameters(QObject *parent = nullptr);

    [[nodiscard]]inline  int get_gameSpeed() const noexcept{return   _gameSpeed;  }
    [[nodiscard]]inline  int get_gridSize() const noexcept{return   _gameSpeed;  }
    [[nodiscard]]inline  size_t get_iterationNumber() const noexcept{return   _iterationNumber;  }

    inline  void set_gameSpeed(int newSpeed)noexcept{
        if(_gameSpeed!=newSpeed){
            _gameSpeed=newSpeed;
            emit _gameSpeedChanged();
        }
    }

    inline  void set_gridSize(int newGridSize) noexcept{
        if(_gridSize!=newGridSize)  {
            _gridSize=newGridSize;
            emit _gridSizeChanged();
        }
    }

    inline  void set_iterationNumber(int newiteration) noexcept{
        if(_iterationNumber!=newiteration)  {
            _iterationNumber=newiteration;
            emit _iterationNumberChanged();
        }
    }

signals:
    void _gameSpeedChanged();
    void _gridSizeChanged();
    void _iterationNumberChanged();
private:

    int _gameSpeed{50};
    int _gridSize{50};
    size_t _iterationNumber{0};

};
