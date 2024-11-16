#include <gtest/gtest.h>
#include "Back/Game/Board.hpp"
#include "../tests/tests_utilities.hpp"

using namespace std;

Board boardToTest;

/****************************************  Tests Suite for fillNeighbour ***************************************/

TEST(UTFillNeighbour, BlockPatternTest)
{
    boardToTest.update(UTILITIES::blockPattern, UTILITIES::blockColumnLength, UTILITIES::blockColumnLength);

    // First try at the center of the pattern
    auto resultVec = boardToTest.fillNeighbour(2 * boardToTest.get_lineLength(), 2);
    ASSERT_EQ(resultVec.size(), 8);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(3).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(3).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(4).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(4).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(5).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(5).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(6).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(6).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(7).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(7).get().get_isPreviouslyAlive(), true);

    // Then try at the top left corner
    resultVec = boardToTest.fillNeighbour(0 * boardToTest.get_lineLength(), 0);
    ASSERT_EQ(resultVec.size(), 3);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), false);

    // Try at the top right corner
    resultVec = boardToTest.fillNeighbour(0 * boardToTest.get_lineLength(), 3);
    ASSERT_EQ(resultVec.size(), 3);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), false);

    // Try at the bottom left corner
    resultVec = boardToTest.fillNeighbour(3 * boardToTest.get_lineLength(), 0);
    ASSERT_EQ(resultVec.size(), 3);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), false);

    // Try at the bottom right corner
    resultVec = boardToTest.fillNeighbour(3 * boardToTest.get_lineLength(), 3);
    ASSERT_EQ(resultVec.size(), 3);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), true);

    // Try at one of the left border
    resultVec = boardToTest.fillNeighbour(2 * boardToTest.get_lineLength(), 0);
    ASSERT_EQ(resultVec.size(), 5);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(3).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(3).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(4).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(4).get().get_isPreviouslyAlive(), false);

    // Try at one of the right border
    resultVec = boardToTest.fillNeighbour(1 * boardToTest.get_lineLength(), 3);
    ASSERT_EQ(resultVec.size(), 5);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(3).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(3).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(4).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(4).get().get_isPreviouslyAlive(), false);

    // Try at one of the top border
    resultVec = boardToTest.fillNeighbour(0 * boardToTest.get_lineLength(), 2);
    ASSERT_EQ(resultVec.size(), 5);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(3).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(3).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(4).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(4).get().get_isPreviouslyAlive(), false);

    // Try at one of the bottom border
    resultVec = boardToTest.fillNeighbour(3 * boardToTest.get_lineLength(), 1);
    ASSERT_EQ(resultVec.size(), 5);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(3).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(3).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(4).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(4).get().get_isPreviouslyAlive(), false);
}

// Do not test the negative indices because it can't happen in current implementation
// TODO consider adding this check
TEST(UTFillNeighbour, RobustnessTest)
{
    // grid empty
    boardToTest.update({}, 0, 0);
    auto resultVec = boardToTest.fillNeighbour(0 * boardToTest.get_lineLength(), 0);
    ASSERT_EQ(resultVec.size(), 0);

    boardToTest.update(UTILITIES::blockPattern, UTILITIES::blockColumnLength, UTILITIES::blockColumnLength);

    // line outside the possible indices
    resultVec = boardToTest.fillNeighbour(9 * boardToTest.get_lineLength(), 0);
    ASSERT_EQ(resultVec.size(), 0);
    resultVec = boardToTest.fillNeighbour(4 * boardToTest.get_lineLength(), 0);
    ASSERT_EQ(resultVec.size(), 0);

    // column outside the possible indices
    resultVec = boardToTest.fillNeighbour(0 * boardToTest.get_lineLength(), 9);
    ASSERT_EQ(resultVec.size(), 0);
    resultVec = boardToTest.fillNeighbour(0 * boardToTest.get_lineLength(), 4);
    ASSERT_EQ(resultVec.size(), 0);

    // line and column outside the possible indices
    resultVec = boardToTest.fillNeighbour(9 * boardToTest.get_lineLength(), 9);
    ASSERT_EQ(resultVec.size(), 0);
    resultVec = boardToTest.fillNeighbour(4 * boardToTest.get_lineLength(), 4);
    ASSERT_EQ(resultVec.size(), 0);
}

/****************************************  Tests Suite for reduceBoard ***************************************/

TEST(UTReduceBoard, TryToReduceBlock)
{
    boardToTest.update(UTILITIES::blockPattern, UTILITIES::blockColumnLength, UTILITIES::blockColumnLength);

    boardToTest.reduceBoard();
    UTILITIES::compareGrid(tuple<gridOfCells, size_t, size_t>{
                               boardToTest.get_grid_const(), boardToTest.get_lineLength(), boardToTest.get_colLength()
                           }, UTILITIES::blockPattern);
}

TEST(UTReduceBoard, TryToReduceTub)
{
    boardToTest.update(UTILITIES::tubPattern, UTILITIES::tubColumnLength, UTILITIES::tubColumnLength);

    boardToTest.reduceBoard();
    UTILITIES::compareGrid(tuple<gridOfCells, size_t, size_t>{
                               boardToTest.get_grid_const(), boardToTest.get_lineLength(), boardToTest.get_colLength()
                           }, UTILITIES::tubPattern);
}

/****************************************  Tests Suite for expandBoard ***************************************/

TEST(UTExpandBoard, TryToExpandBlock)
{
    boardToTest.update(UTILITIES::blockPattern, UTILITIES::blockColumnLength, UTILITIES::blockColumnLength);

    boardToTest.expandBoard();
    UTILITIES::compareGrid(
        tuple<gridOfCells, size_t, size_t>
        {boardToTest.get_grid_const(), boardToTest.get_lineLength(), boardToTest.get_colLength()}, {
            {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'*'},
            {'*'}, {'-'}, {'-'}, {'-'}, {'-'}, {'*'}, {'*'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},
            {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}
        });
}

TEST(UTExpandBoard, TryToExpandTub)
{
    boardToTest.update(UTILITIES::tubPattern, UTILITIES::tubColumnLength, UTILITIES::tubColumnLength);

    boardToTest.expandBoard();
    UTILITIES::compareGrid(tuple<gridOfCells, size_t, size_t>{
                               boardToTest.get_grid_const(), boardToTest.get_lineLength(), boardToTest.get_colLength()
                           }, {
                               {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},
                               {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},
                               {'-'}, {'-'}, {'-'}, {'*'}, {'-'}, {'-'}, {'-'},
                               {'-'}, {'-'}, {'*'}, {'-'}, {'*'}, {'-'}, {'-'},
                               {'-'}, {'-'}, {'-'}, {'*'}, {'-'}, {'-'}, {'-'},
                               {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},
                               {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},
                           }
    );
}
