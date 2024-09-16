#include <gtest/gtest.h>
#include "Game/Board.hpp"
#include "../tests/tests_utilities.hpp"

using namespace std;

Board bordToTest;

/****************************************  Tests Suite for fillNeighbour ***************************************/


TEST(FillNeighbour, BlockPatternTest) {

    bordToTest.set_grid(UTILITIES::blockPattern);

    // First try at the center of the pattern
    auto resultVec = bordToTest.fillNeighbour(2, 2);
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
    resultVec = bordToTest.fillNeighbour(0, 0);
    ASSERT_EQ(resultVec.size(), 3);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), false);

    // Try at the top right corner
    resultVec = bordToTest.fillNeighbour(0, 3);
    ASSERT_EQ(resultVec.size(), 3);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), false);

    // Try at the bottom left corner
    resultVec = bordToTest.fillNeighbour(3, 0);
    ASSERT_EQ(resultVec.size(), 3);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), false);

    // Try at the bottom right corner
    resultVec = bordToTest.fillNeighbour(3, 3);
    ASSERT_EQ(resultVec.size(), 3);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), true);

    // Try at one of the left border
    resultVec = bordToTest.fillNeighbour(2, 0);
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
    resultVec = bordToTest.fillNeighbour(1, 3);
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
    resultVec = bordToTest.fillNeighbour(0, 2);
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
    resultVec = bordToTest.fillNeighbour(3, 1);
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
TEST(FillNeighbour, RobustnessTest) {

    // grid empty
    bordToTest.set_grid({});
    auto resultVec = bordToTest.fillNeighbour(0, 0);
    ASSERT_EQ(resultVec.size(), 0);

    bordToTest.set_grid(UTILITIES::blockPattern);

    // line outside the possible indices
    resultVec = bordToTest.fillNeighbour(9, 0);
    ASSERT_EQ(resultVec.size(), 0);
    resultVec = bordToTest.fillNeighbour(4, 0);
    ASSERT_EQ(resultVec.size(), 0);

    // column outside the possible indices
    resultVec = bordToTest.fillNeighbour(0, 9);
    ASSERT_EQ(resultVec.size(), 0);
    resultVec = bordToTest.fillNeighbour(0, 4);
    ASSERT_EQ(resultVec.size(), 0);

    // line and column outside the possible indices
    resultVec = bordToTest.fillNeighbour(9, 9);
    ASSERT_EQ(resultVec.size(), 0);
    resultVec = bordToTest.fillNeighbour(4, 4);
    ASSERT_EQ(resultVec.size(), 0);

}
