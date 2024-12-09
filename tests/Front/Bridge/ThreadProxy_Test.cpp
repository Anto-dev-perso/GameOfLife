#include <gtest/gtest.h>
#include "Front/Bridge/ThreadProxy.hpp"


#include "../tests_utilities.hpp"
#include "../../Back/tests_utilities.hpp"

#include <QSignalSpy>

using namespace std;

class ThreadProxyTest : public ::testing::Test
{
protected:
    std::shared_ptr<Game> backend;
    std::unique_ptr<ThreadProxy> threadProxy;

    void SetUp() override
    {
        backend = std::make_shared<Game>("../src/Front/assets/lexicon.txt", TypeOfFileToParse::LEXICON);
        std::ignore = backend->init();
        threadProxy = std::make_unique<ThreadProxy>(backend, std::chrono::microseconds(1000));
    }

    void TearDown() override
    {
        threadProxy.reset();
    }
};

TEST_F(ThreadProxyTest, ThreadLifecycle)
{
    // Ensure thread starts in the constructor
    ASSERT_TRUE(threadProxy->_thread.isRunning());

    // Destructor should clean up the thread
    threadProxy.reset();
    EXPECT_EQ(threadProxy, nullptr);
}

TEST_F(ThreadProxyTest, StopWork)
{
    threadProxy->run();
    threadProxy->stopWork();
    ASSERT_FALSE(threadProxy->_gameRunning.load());
}


TEST_F(ThreadProxyTest, ProcessingIteration)
{
    backend->increment_nbOfIterations();
    std::ignore = backend->applyRulesToTheBoard();
    // Verify signals are emitted
    QSignalSpy iterationSpy(threadProxy.get(), &ThreadProxy::iterationNumberFinishedEditing);
    QSignalSpy dataResetSpy(threadProxy.get(), &ThreadProxy::requestModelReset);
    QSignalSpy dataChangeSpy(threadProxy.get(), &ThreadProxy::requestDataChange);

    threadProxy->processingIteration();

    ASSERT_EQ(iterationSpy.count(), 1);
    ASSERT_EQ(dataResetSpy.count(), 1);
    ASSERT_EQ(dataChangeSpy.count(), 0);

    backend->updateBoard(UTILITIES::blockPattern);

    threadProxy->processingIteration();

    ASSERT_EQ(iterationSpy.count(), 2);
    ASSERT_EQ(dataResetSpy.count(), 1);
    ASSERT_EQ(dataChangeSpy.count(), 1);
}

TEST_F(ThreadProxyTest, SetWaitTimeMicro)
{
    threadProxy->set_waitTimeMicro(std::chrono::microseconds(500));
    ASSERT_EQ(threadProxy->_waitTimeMicro.load(), 500);
}
