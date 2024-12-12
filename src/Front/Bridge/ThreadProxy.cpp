

#include "ThreadProxy.hpp"

ThreadProxy::ThreadProxy(std::shared_ptr<Game> backend, std::chrono::microseconds timeToWait,
                         QObject* parent) : QObject(parent), _backend(std::move(backend)),
                                            _waitTimeMicro(timeToWait.count())
{
    moveToThread(&_thread);
    std::ignore = connect(&_thread, &QThread::started, this, &ThreadProxy::doWork);
    _thread.start();
}

ThreadProxy::~ThreadProxy()
{
    _exitThread.store(true);
    _gameRunning.store(false);
    _pauseCondition.notify_one();

    _thread.quit();
    _thread.wait();
}

void ThreadProxy::stopWork() noexcept
{
    _gameRunning.store(false);
}

void ThreadProxy::doWork() noexcept
{
    while (!_exitThread.load())
    {
        {
            std::unique_lock lock{_pauseMutex};

            _pauseCondition.wait(lock, [this]()
            {
                return _gameRunning.load() || _exitThread.load();
            });

            if (_exitThread.load())
            {
                break;
            }
        }
        while (_gameRunning.load())
        {
            const auto startTime = std::chrono::high_resolution_clock::now();
            processingIteration();
            const auto endTime{std::chrono::high_resolution_clock::now()};
            const auto duration{std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime)};

            const auto remainingTime{
                std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::microseconds{_waitTimeMicro.load()} - duration)
            };
            if (remainingTime.count() > 0)
            {
                QThread::currentThread()->usleep(remainingTime.count());
            }
        }
    }
}

void ThreadProxy::run() noexcept
{
    _gameRunning.store(true);
    _pauseCondition.notify_one();
}

void ThreadProxy::processingIteration() noexcept
{
    QWriteLocker lock{&_lockBackend};
    // In case we have clear the board, it makes no sense to run the processing
    if (_backend->boardEmpty())
    {
        _gameRunning.store(false);
        return;
    }
    _backend->increment_nbOfIterations();

    const auto [expand, reduce, idModified] = _backend->applyRulesToTheBoard();
    if (_backend->checkIfBoardNeedToBeResize(expand, reduce))
    {
        requestModelReset();
    }
    else
    {
        requestDataChange(idModified);
    }
    emit iterationNumberFinishedEditing();
}

void ThreadProxy::set_waitTimeMicro(std::chrono::microseconds time) noexcept
{
    _waitTimeMicro.store(time.count());
}
