#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

#include <gtest/gtest.h>
#include "Game/Game.hpp"

#include "../tests_utilities.hpp"

using namespace std;

static Game game;

/****************************************  Tests Suite for applyRulesToTheGame with some 'still lifes' structures ***************************************/
TEST(UTApplyRulesStillLifePatterns, BlockPattern)
{
    game.updateBoard(UTILITIES::blockPattern, UTILITIES::blockColumnLength, UTILITIES::blockColumnLength);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::blockPattern);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::blockPattern);
}

TEST(UTApplyRulesStillLifePatterns, BeeHivePattern)
{
    game.updateBoard(UTILITIES::beeHivePattern, UTILITIES::beeHiveColumnLength, UTILITIES::beeHiveColumnLength);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::beeHivePattern);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::beeHivePattern);
}

TEST(UTApplyRulesStillLifePatterns, LoafPattern)
{
    game.updateBoard(UTILITIES::loafPattern, UTILITIES::loafColumnLength, UTILITIES::loafColumnLength);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::loafPattern);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::loafPattern);
}

TEST(UTApplyRulesStillLifePatterns, BoatPattern)
{
    game.updateBoard(UTILITIES::boatPattern, UTILITIES::boatColumnLength, UTILITIES::boatColumnLength);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::boatPattern);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::boatPattern);
}

TEST(UTApplyRulesStillLifePatterns, tubPattern)
{
    game.updateBoard(UTILITIES::tubPattern, UTILITIES::tubColumnLength, UTILITIES::tubColumnLength);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::tubPattern);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::tubPattern);
}

/****************************************  Tests Suite for applyRulesToTheGame with some 'oscillators' structures ***************************************/
TEST(UTApplyRulesOscillatorsPatterns, BlinkerPattern)
{
    game.updateBoard(UTILITIES::blinkerPatternG1, UTILITIES::blinkerColumnLength, UTILITIES::blinkerColumnLength);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::blinkerPatternG2);

    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::blinkerPatternG1);
}

TEST(UTApplyRulesOscillatorsPatterns, ToadPattern)
{
    game.updateBoard(UTILITIES::toadPatternG2, UTILITIES::toadColumnLength, UTILITIES::toadColumnLength);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::toadPatternG1);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::toadPatternG2);
}

TEST(UTApplyRulesOscillatorsPatterns, BeaconPattern)
{
    game.updateBoard(UTILITIES::beaconPatternG1, UTILITIES::beaconColumnLength, UTILITIES::beaconColumnLength);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::beaconPatternG2);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::beaconPatternG1);
}

TEST(UTApplyRulesOscillatorsPatterns, PulsarPattern)
{
    game.updateBoard(UTILITIES::pulsarPatternG1, UTILITIES::pulsarColumnLength, UTILITIES::pulsarColumnLength);
    game.applyRulesToTheBoardForIteration(1);

    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pulsarPatternG2);

    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pulsarPatternG3);

    game.applyRulesToTheBoardForIteration(3);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pulsarPatternG1);
}

TEST(UTApplyRulesOscillatorsPatterns, PentaDecathlonPattern)
{
    game.updateBoard(UTILITIES::pentaDecathlonPatternG1, UTILITIES::pentaDecathlonColumnLength, UTILITIES::pentaDecathlonColumnLength);

    game.applyRulesToTheBoardForIteration(1);

    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG2.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG2);

    game.applyRulesToTheBoardForIteration(2);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG3.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG3);

    game.applyRulesToTheBoardForIteration(3);

    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG4.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG4);

    game.applyRulesToTheBoardForIteration(4);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG5.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG5);

    game.applyRulesToTheBoardForIteration(5);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG6.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG6);

    game.applyRulesToTheBoardForIteration(6);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG7.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG7);

    game.applyRulesToTheBoardForIteration(7);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG8.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG8);

    game.applyRulesToTheBoardForIteration(8);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG9.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG9);

    game.applyRulesToTheBoardForIteration(9);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG10.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG10);

    game.applyRulesToTheBoardForIteration(10);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG11.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG11);

    game.applyRulesToTheBoardForIteration(11);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG12.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG12);

    game.applyRulesToTheBoardForIteration(12);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG13.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG13);

    game.applyRulesToTheBoardForIteration(13);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG14.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG14);

    game.applyRulesToTheBoardForIteration(14);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG15.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG15);

    game.applyRulesToTheBoardForIteration(15);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG2.size());
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::pentaDecathlonPatternG1);
}

/****************************************  Tests Suite for applyRulesToTheGame with some 'spaceship' structures ****************************************/

TEST(UTApplyRulesSpaceshipPatterns, GosperGliderGunPattern)
{
    game.updateBoard(UTILITIES::gosperGliderGunPattern, UTILITIES::gosperGliderGunColumnLength, UTILITIES::gosperGliderGunColumnLength);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.retrieveBoardDataForTest(), UTILITIES::gosperGliderGunPatternG1);
}

/****************************************  Tests Suite for applyRulesToTheGame robustness ***************************************/

TEST(UTApplyRulesRobustness, RobustnessTests)
{
    Game emptyGame;
    {
        // Board empty
        emptyGame.applyRulesToTheBoardForIteration(1);

        UTILITIES::compareGrid(emptyGame.retrieveBoardDataForTest(), {});
    }
    {
        // No iteration
        emptyGame.updateBoard(UTILITIES::blockPattern, UTILITIES::blockColumnLength, UTILITIES::blockColumnLength);
        emptyGame.applyRulesToTheBoardForIteration(0);

        UTILITIES::compareGrid(emptyGame.retrieveBoardDataForTest(), UTILITIES::blockPattern);
    }
}
