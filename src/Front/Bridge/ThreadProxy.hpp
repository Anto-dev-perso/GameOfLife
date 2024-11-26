#pragma once


#include <QThread>
#include "../Back/Game/Game.hpp"

class ThreadProxy : public QObject
{
    Q_OBJECT

public:
    explicit ThreadProxy(std::shared_ptr<Game> backend, std::chrono::microseconds timeToWait,
                         QObject* parent = nullptr);
    ~ThreadProxy();
    void stopWork() noexcept;
    void doWork() noexcept;
    void run() noexcept;
    void processingIteration() noexcept;

    void set_waitTimeMicro(std::chrono::microseconds time) noexcept;

signals:
    void iterationNumberFinishedEditing();
    void requestModelReset();
    void requestDataChange(Game::line_column firstRow, Game::line_column lastRow);

private:
    std::shared_ptr<Game> _backend;
    std::atomic<bool> _gameRunning{false};
    std::atomic<bool> _exitThread{false};
    std::atomic<unsigned long> _waitTimeMicro{1000};

    std::mutex _pauseMutex;
    std::condition_variable _pauseCondition;
    QThread _thread;
};
