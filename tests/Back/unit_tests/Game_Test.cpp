
#include <gtest/gtest.h>
#include "Back/Game/Game.hpp"

#include "../tests/Back/tests_utilities.hpp"

using namespace std;

static Game game;
static PatternList patternTest{
    {
        {"blinkerPatternG1", {{"blinkerPatternG1 description", UTILITIES::blinkerPatternG1}}},
        {"toadPatternG1", {{"toadPatternG1 description", UTILITIES::toadPatternG1}}},
        {
            "pulsarPattern",
            {
                {"pulsarPatternG1 description", UTILITIES::pulsarPatternG1},
                {"pulsarPatternG2 description", UTILITIES::pulsarPatternG2},
                {"pulsarPatternG3description", UTILITIES::pulsarPatternG3}
            }
        },

    }
};

/****************************************  Tests Suite for applyRulesToTheGame with some 'still lifes' structures ***************************************/
TEST(UTApplyRulesStillLifePatterns, BlockPattern)
{
    game.updateBoard({UTILITIES::blockPattern});
    std::ignore = game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::blockPattern);
    std::ignore = game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::blockPattern);
}

TEST(UTApplyRulesStillLifePatterns, BeeHivePattern)
{
    game.updateBoard({UTILITIES::beeHivePattern});
    std::ignore = game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::beeHivePattern);
    std::ignore = game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::beeHivePattern);
}

TEST(UTApplyRulesStillLifePatterns, LoafPattern)
{
    game.updateBoard({UTILITIES::loafPattern});
    std::ignore = game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::loafPattern);
    std::ignore = game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::loafPattern);
}

TEST(UTApplyRulesStillLifePatterns, BoatPattern)
{
    game.updateBoard({UTILITIES::boatPattern});
    std::ignore = game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::boatPattern);
    std::ignore = game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::boatPattern);
}

TEST(UTApplyRulesStillLifePatterns, tubPattern)
{
    game.updateBoard({UTILITIES::tubPattern});
    std::ignore = game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::tubPattern);
    std::ignore = game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::tubPattern);
}

/****************************************  Tests Suite for applyRulesToTheGame with some 'oscillators' structures ***************************************/
TEST(UTApplyRulesOscillatorsPatterns, BlinkerPattern)
{
    game.updateBoard({UTILITIES::blinkerPatternG1});
    std::ignore = game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::blinkerPatternG2);

    std::ignore = game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::blinkerPatternG1);
}

TEST(UTApplyRulesOscillatorsPatterns, ToadPattern)
{
    game.updateBoard({UTILITIES::toadPatternG2});
    std::ignore = game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::toadPatternG1);
    std::ignore = game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::toadPatternG2);
}

TEST(UTApplyRulesOscillatorsPatterns, BeaconPattern)
{
    game.updateBoard({UTILITIES::beaconPatternG1});
    std::ignore = game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::beaconPatternG2);
    std::ignore = game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::beaconPatternG1);
}

TEST(UTApplyRulesOscillatorsPatterns, PulsarPattern)
{
    game.updateBoard({UTILITIES::pulsarPatternG1});
    std::ignore = game.applyRulesToTheBoardForIteration(1);

    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pulsarPatternG2);

    std::ignore = game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pulsarPatternG3);

    std::ignore = game.applyRulesToTheBoardForIteration(3);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pulsarPatternG1);

    // Do the same with the applyRulesToTheBoard method
    game.updateBoard({UTILITIES::pulsarPatternG1});
    game.set_nbOfIterations(0);

    game.increment_nbOfIterations();
    std::ignore = game.applyRulesToTheBoard();

    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pulsarPatternG2);

    game.increment_nbOfIterations();
    std::ignore = game.applyRulesToTheBoard();
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pulsarPatternG3);

    game.increment_nbOfIterations();
    std::ignore = game.applyRulesToTheBoard();
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pulsarPatternG1);
}

TEST(UTApplyRulesOscillatorsPatterns, PentaDecathlonPattern)
{
    game.updateBoard({
        UTILITIES::pentaDecathlonPatternG1
    });


    std::ignore = game.applyRulesToTheBoardForIteration(1);

    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG2.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG2);

    std::ignore = game.applyRulesToTheBoardForIteration(2);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG3.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG3);

    std::ignore = game.applyRulesToTheBoardForIteration(3);

    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG4.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG4);

    std::ignore = game.applyRulesToTheBoardForIteration(4);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG5.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG5);

    std::ignore = game.applyRulesToTheBoardForIteration(5);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG6.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG6);

    std::ignore = game.applyRulesToTheBoardForIteration(6);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG7.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG7);

    std::ignore = game.applyRulesToTheBoardForIteration(7);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG8.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG8);

    std::ignore = game.applyRulesToTheBoardForIteration(8);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG9.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG9);

    std::ignore = game.applyRulesToTheBoardForIteration(9);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG10.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG10);

    std::ignore = game.applyRulesToTheBoardForIteration(10);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG11.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG11);

    std::ignore = game.applyRulesToTheBoardForIteration(11);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG12.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG12);

    std::ignore = game.applyRulesToTheBoardForIteration(12);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG13.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG13);

    std::ignore = game.applyRulesToTheBoardForIteration(13);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG14.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG14);

    std::ignore = game.applyRulesToTheBoardForIteration(14);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG15.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG15);

    std::ignore = game.applyRulesToTheBoardForIteration(15);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG2.grid.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG1);
}

/****************************************  Tests Suite for applyRulesToTheGame with some 'spaceship' structures ****************************************/

TEST(UTApplyRulesSpaceshipPatterns, GosperGliderGunPattern)
{
    game.updateBoard({
        UTILITIES::gosperGliderGunPattern
    });
    std::ignore = game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::gosperGliderGunPatternG1);
}

/****************************************  Tests Suite for applyRulesToTheGame robustness ***************************************/

TEST(UTApplyRulesRobustness, RobustnessTests)
{
    Game emptyGame;
    {
        // Board empty
        std::ignore = emptyGame.applyRulesToTheBoardForIteration(1);

        UTILITIES::compareGrid(emptyGame.retrieveBoardDataForTest(), {});
    }
    {
        // No iteration
        emptyGame.updateBoard({UTILITIES::blockPattern});
        std::ignore = emptyGame.applyRulesToTheBoardForIteration(0);

        UTILITIES::compareGrid(emptyGame.retrieveBoardDataForTest(), UTILITIES::blockPattern);
    }
}


/****************************************  Tests Suite for resetBoard ***************************************/

TEST(UTResetBoard, ResetTest)
{
    game.updateBoard(patternTest, {0, 0});

    std::ignore = game.applyRulesToTheBoardForIteration(0);

    game.resetBoard();

    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::blinkerPatternG1);
}


/****************************************  Tests Suite for changeBoard ***************************************/

TEST(UTChangeBoard, ChangeBoardTest)
{
    game.updateBoard(patternTest, {0, 0});

    game.changeBoard(1, 0);
    auto boardPatternIndices{game.get_boardPattern()};

    ASSERT_EQ(boardPatternIndices.patternIndex, 1);
    ASSERT_EQ(boardPatternIndices.gridIndex, 0);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::toadPatternG1);

    game.changeBoard(2, 0);
    boardPatternIndices = game.get_boardPattern();

    ASSERT_EQ(boardPatternIndices.patternIndex, 2);
    ASSERT_EQ(boardPatternIndices.gridIndex, 0);
    UTILITIES::compareGrid(
        game.retrieveBoardDataForTest(), UTILITIES::pulsarPatternG1);

    game.changeBoard(2, 1);
    boardPatternIndices = game.get_boardPattern();

    ASSERT_EQ(boardPatternIndices.patternIndex, 2);
    ASSERT_EQ(boardPatternIndices.gridIndex, 1);
    UTILITIES::compareGrid(
        game.retrieveBoardDataForTest(), UTILITIES::pulsarPatternG2);

    game.changeBoard(2, 2);
    boardPatternIndices = game.get_boardPattern();

    ASSERT_EQ(boardPatternIndices.patternIndex, 2);
    ASSERT_EQ(boardPatternIndices.gridIndex, 2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pulsarPatternG3);
}
