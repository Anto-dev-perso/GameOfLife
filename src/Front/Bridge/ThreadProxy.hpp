#pragma once


#include <QThread>
#include "Back/Game/Game.hpp"

class ThreadProxy final : public QObject
{
    Q_OBJECT

public:
    explicit ThreadProxy(std::shared_ptr<Game> backend, std::chrono::microseconds timeToWait,
                         QObject* parent = nullptr);
    ~ThreadProxy() override;
    void stopWork() noexcept;
    void doWork() noexcept;
    void run() noexcept;

    auto get_iterationNumber() const noexcept
    {
        return _backend->get_nbOfIterations();
    }

    void processingIteration() noexcept;

    void set_waitTimeMicro(std::chrono::microseconds time) noexcept;


signals
:
    void iterationNumberFinishedEditing();
    void requestModelReset();
    void requestDataChange(const std::vector<Game::indices_with_value>& idToChange);

#ifdef ENABLE_DEBUG

public:
#else
    private:
#endif

    std::shared_ptr<Game> _backend;
    std::atomic<bool> _gameRunning{false};
    std::atomic<bool> _exitThread{false};
    std::atomic<unsigned long> _waitTimeMicro{1000};

    std::mutex _pauseMutex;
    std::condition_variable _pauseCondition;

#ifdef ENABLE_DEBUG

public:
#endif
    QThread _thread;
};
