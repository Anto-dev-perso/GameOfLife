#include <gtest/gtest.h>
#include "Back/Game/Board.hpp"
#include "../tests/Back/tests_utilities.hpp"

using namespace std;

Board boardToTest;
/****************************************  Tests Suite for board_data structure ***************************************/
TEST(UTStructBoard, EmptyTest)
{
    board_data dataToTest{UTILITIES::blockPattern};

    ASSERT_EQ(dataToTest.empty(), false);

    dataToTest = UTILITIES::pentaDecathlonPatternG7;
    ASSERT_EQ(dataToTest.empty(), false);

    dataToTest = {};
    ASSERT_EQ(dataToTest.empty(), true);
}

TEST(UTStructBoard, ClearTest)
{
    board_data dataToTest{UTILITIES::blockPattern};

    dataToTest.clear();
    UTILITIES::compareGrid(dataToTest, board_data{});

    dataToTest = UTILITIES::pentaDecathlonPatternG7;
    dataToTest.clear();
    UTILITIES::compareGrid(dataToTest, board_data{});

    dataToTest = {};
    dataToTest.clear();
    UTILITIES::compareGrid(dataToTest, board_data{});
}


/****************************************  Tests Suite for fillNeighbour ***************************************/

TEST(UTFillNeighbour, BlockPatternTest)
{
    boardToTest.update({UTILITIES::blockPattern});

    // First try at the center of the pattern
    auto resultVec = boardToTest.fillNeighbour(2, 2);
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

    // Then try in the top left corner
    resultVec = boardToTest.fillNeighbour(0, 0);
    ASSERT_EQ(resultVec.size(), 3);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), false);

    // Try in the top right corner
    resultVec = boardToTest.fillNeighbour(0, 3);
    ASSERT_EQ(resultVec.size(), 3);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), false);

    // Try in the bottom left corner
    resultVec = boardToTest.fillNeighbour(3, 0);
    ASSERT_EQ(resultVec.size(), 3);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), false);

    // Try in the bottom right corner
    resultVec = boardToTest.fillNeighbour(3, 3);
    ASSERT_EQ(resultVec.size(), 3);
    EXPECT_EQ(resultVec.at(0).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(0).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isCurrentlyAlive(), false);
    EXPECT_EQ(resultVec.at(1).get().get_isPreviouslyAlive(), false);
    EXPECT_EQ(resultVec.at(2).get().get_isCurrentlyAlive(), true);
    EXPECT_EQ(resultVec.at(2).get().get_isPreviouslyAlive(), true);

    // Try at one of the left border
    resultVec = boardToTest.fillNeighbour(2, 0);
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
    resultVec = boardToTest.fillNeighbour(1, 3);
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
    resultVec = boardToTest.fillNeighbour(0, 2);
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
    resultVec = boardToTest.fillNeighbour(3, 1);
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

TEST(UTFillNeighbour, RobustnessTest)
{
    // grid empty
    boardToTest.update({{}, 0, 0});
    auto resultVec = boardToTest.fillNeighbour(0, 0);
    ASSERT_EQ(resultVec.size(), 0);

    boardToTest.update({UTILITIES::blockPattern});

    // line outside the possible indices
    resultVec = boardToTest.fillNeighbour(9, 0);
    ASSERT_EQ(resultVec.size(), 0);
    resultVec = boardToTest.fillNeighbour(4, 0);
    ASSERT_EQ(resultVec.size(), 0);

    // column outside the possible indices
    resultVec = boardToTest.fillNeighbour(0, 9);
    ASSERT_EQ(resultVec.size(), 0);
    resultVec = boardToTest.fillNeighbour(0, 4);
    ASSERT_EQ(resultVec.size(), 0);

    // line and column outside the possible indices
    resultVec = boardToTest.fillNeighbour(9, 9);
    ASSERT_EQ(resultVec.size(), 0);
    resultVec = boardToTest.fillNeighbour(4, 4);
    ASSERT_EQ(resultVec.size(), 0);
}

/****************************************  Tests Suite for reduceBoard ***************************************/

TEST(UTReduceBoard, TryToReduceBlock)
{
    boardToTest.update({UTILITIES::blockPattern});

    boardToTest.reduceBoard();
    UTILITIES::compareGrid(board_data{
                               boardToTest.get_grid_const(), boardToTest.get_lineLength(), boardToTest.get_colLength()
                           }, UTILITIES::blockPattern);
}

TEST(UTReduceBoard, TryToReduceTub)
{
    boardToTest.update({UTILITIES::tubPattern});

    boardToTest.reduceBoard();
    UTILITIES::compareGrid(board_data{
                               boardToTest.get_grid_const(), boardToTest.get_lineLength(), boardToTest.get_colLength()
                           }, UTILITIES::tubPattern);
}

/****************************************  Tests Suite for expandBoard ***************************************/

TEST(UTExpandBoard, TryToExpandBlock)
{
    boardToTest.update({UTILITIES::blockPattern});

    boardToTest.expandBoard();
    UTILITIES::compareGrid(
        board_data
        {boardToTest.get_grid_const(), boardToTest.get_lineLength(), boardToTest.get_colLength()}, {
            {
                {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'*'},
                {'*'}, {'-'}, {'-'}, {'-'}, {'-'}, {'*'}, {'*'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},
                {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}
            },
            6, 6
        });
}

TEST(UTExpandBoard, TryToExpandTub)
{
    boardToTest.update({UTILITIES::tubPattern});

    boardToTest.expandBoard();
    UTILITIES::compareGrid(board_data{
                               boardToTest.get_grid_const(), boardToTest.get_lineLength(), boardToTest.get_colLength()
                           }, {
                               {
                                   {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},
                                   {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},
                                   {'-'}, {'-'}, {'-'}, {'*'}, {'-'}, {'-'}, {'-'},
                                   {'-'}, {'-'}, {'*'}, {'-'}, {'*'}, {'-'}, {'-'},
                                   {'-'}, {'-'}, {'-'}, {'*'}, {'-'}, {'-'}, {'-'},
                                   {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},
                                   {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},
                               },
                               7, 7
                           }
    );
}

TEST(UTExpandBoard, ExpandMoreThanOne)
{
    board_data expected{
        grid_of_cells{
            {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},
            {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},
            {'-'}, {'-'}, {'*'}, {'*'}, {'-'}, {'-'},
            {'-'}, {'-'}, {'*'}, {'*'}, {'-'}, {'-'},
            {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},
            {'-'}, {'-'}, {'-'}, {'-'}, {'-'}, {'-'},

        },
        6, 6
    };
    boardToTest.update({grid_of_cells(4, {'*'}), 2, 2});

    boardToTest.expandBoard(2);
    UTILITIES::compareGrid(boardToTest.get_board_data(), expected);

    // expand 0 return the same board
    boardToTest.expandBoard(0);
    UTILITIES::compareGrid(boardToTest.get_board_data(), expected);

    // Large grid
    boardToTest.update({grid_of_cells(100, {'*'}), 10, 10});

    expected.clear();
    expected.line = 30;
    expected.column = 30;
    expected.grid.reserve(expected.line * expected.column);

    expected.grid.insert(expected.grid.begin(), 10 * expected.column, '-'); // First 20 lines
    for (size_t row = 10; row < 20; row++)
    {
        for (size_t col = 0; col < expected.column; col++)
        {
            if (col < 10 || col >= 20)
            {
                expected.grid.emplace_back('-');
            }
            else
            {
                expected.grid.emplace_back('*');
            }
        }
    }
    expected.grid.insert(expected.grid.end(), 10 * expected.column, '-'); // Last 10 lines

    boardToTest.expandBoard(10);
    UTILITIES::compareGrid(boardToTest.get_board_data(), expected);
}

/****************************************  Tests Suite for isCellAliveAtIndex ***************************************/

TEST(UTCellAliveAtIndex, CellAliveAtIndexTest)
{
    boardToTest.update({UTILITIES::blockPattern});

    EXPECT_EQ(boardToTest.isCellAliveAtIndex(0), false);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(1), false);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(3), false);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(3), false);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(4), false);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(5), true);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(6), true);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(7), false);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(8), false);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(9), true);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(10), true);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(11), false);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(12), false);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(13), false);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(14), false);
    EXPECT_EQ(boardToTest.isCellAliveAtIndex(15), false);


    try
    {
        std::ignore = boardToTest.isCellAliveAtIndex(boardToTest.get_grid().size());
        EXPECT_EQ(false, true) << "Exception expected";
    }
    catch (const std::out_of_range& e)
    {
        EXPECT_EQ(string(e.what()), "Cell index out of bounds");
    }
}


/****************************************  Tests Suite for changeCellValue ***************************************/


TEST(UTChangeCellValue, ChangeCellValueTest)
{
    auto block{UTILITIES::blockPattern};
    boardToTest.update({UTILITIES::blockPattern});

    block.grid[0] = getAliveChar();
    EXPECT_EQ(boardToTest.changeCellValue(0), true);
    UTILITIES::compareGrid({boardToTest.get_grid_const(), boardToTest.get_lineLength(), boardToTest.get_colLength()},
                           block);

    block.grid[9] = getDeadChar();
    EXPECT_EQ(boardToTest.changeCellValue(9), false);
    UTILITIES::compareGrid({boardToTest.get_grid_const(), boardToTest.get_lineLength(), boardToTest.get_colLength()},
                           block);

    try
    {
        std::ignore = boardToTest.changeCellValue(boardToTest.get_grid().size());
        EXPECT_EQ(false, true) << "Exception expected";
    }
    catch (const std::out_of_range& e)
    {
        EXPECT_EQ(string(e.what()), "Cell index out of bounds");
        UTILITIES::compareGrid(
            {boardToTest.get_grid_const(), boardToTest.get_lineLength(), boardToTest.get_colLength()},
            block);
    }
}

/****************************************  Tests Suite for changeCellValue ***************************************/


TEST(UTMaxSize, LineAndColumnMaxSizeSet)
{
    boardToTest.update(UTILITIES::gosperGliderGunPattern);

    EXPECT_EQ(boardToTest.get_lineLength(), UTILITIES::gosperGliderGunPattern.line);
    EXPECT_EQ(boardToTest.get_colLength(), UTILITIES::gosperGliderGunPattern.column);

    boardToTest.expandBoard();

    EXPECT_EQ(boardToTest.get_lineLength(), UTILITIES::gosperGliderGunPattern.line+2);
    EXPECT_EQ(boardToTest.get_colLength(), UTILITIES::gosperGliderGunPattern.column+2);

    boardToTest.set_gridMaxNbLine(boardToTest.get_lineLength());
    boardToTest.set_gridMaxNbColumn(boardToTest.get_colLength());
    boardToTest.expandBoard();

    EXPECT_EQ(boardToTest.get_lineLength(), UTILITIES::gosperGliderGunPattern.line+2);
    EXPECT_EQ(boardToTest.get_colLength(), UTILITIES::gosperGliderGunPattern.column+2);

    boardToTest.set_gridMaxNbLine(boardToTest.get_lineLength() + 1);
    boardToTest.set_gridMaxNbColumn(boardToTest.get_colLength() + 1);
    boardToTest.expandBoard();

    EXPECT_EQ(boardToTest.get_lineLength(), UTILITIES::gosperGliderGunPattern.line+2);
    EXPECT_EQ(boardToTest.get_colLength(), UTILITIES::gosperGliderGunPattern.column+2);

    boardToTest.set_gridMaxNbLine(boardToTest.get_lineLength() + 2);
    boardToTest.set_gridMaxNbColumn(boardToTest.get_colLength() + 2);
    boardToTest.expandBoard();

    EXPECT_EQ(boardToTest.get_lineLength(), UTILITIES::gosperGliderGunPattern.line+4);
    EXPECT_EQ(boardToTest.get_colLength(), UTILITIES::gosperGliderGunPattern.column+4);
}
