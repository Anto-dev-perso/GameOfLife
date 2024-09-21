#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

#include <gtest/gtest.h>
#include "Game/Game.hpp"

#include "../tests_utilities.hpp"

using namespace std;

static Game game;


/****************************************  Tests Suite for applyRulesToTheGame with some 'still lifes' structures ***************************************/
TEST(UTApplyRulesStillLifePatterns, BlockPattern) {
    game.set_board(UTILITIES::blockPattern);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::blockPattern);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::blockPattern);
}

TEST(UTApplyRulesStillLifePatterns, BeeHivePattern) {
    game.set_board(UTILITIES::beeHivePattern);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::beeHivePattern);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::beeHivePattern);
}

TEST(UTApplyRulesStillLifePatterns, LoafPattern) {
    game.set_board(UTILITIES::loafPattern);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::loafPattern);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::loafPattern);
}

TEST(UTApplyRulesStillLifePatterns, BoatPattern) {
    game.set_board(UTILITIES::boatPattern);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::boatPattern);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::boatPattern);
}

TEST(UTApplyRulesStillLifePatterns, tubPattern) {
    game.set_board(UTILITIES::tubPattern);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::tubPattern);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::tubPattern);
}

/****************************************  Tests Suite for applyRulesToTheGame with some 'oscillators' structures ***************************************/
TEST(UTApplyRulesOscillatorsPatterns, BlinkerPattern) {
    game.set_board(UTILITIES::blinkerPatternG1);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::blinkerPatternG2);

    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::blinkerPatternG1);
}

TEST(UTApplyRulesOscillatorsPatterns, ToadPattern) {
    game.set_board(UTILITIES::toadPatternG2);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::toadPatternG1);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::toadPatternG2);
}

TEST(UTApplyRulesOscillatorsPatterns, BeaconPattern) {
    game.set_board(UTILITIES::beaconPatternG1);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::beaconPatternG2);
    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::beaconPatternG1);
}

TEST(UTApplyRulesOscillatorsPatterns, PulsarPattern) {
    game.set_board(UTILITIES::pulsarPatternG1);
    game.applyRulesToTheBoardForIteration(1);

    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pulsarPatternG2);

    game.applyRulesToTheBoardForIteration(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pulsarPatternG3);

    game.applyRulesToTheBoardForIteration(3);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pulsarPatternG1);
}

TEST(UTApplyRulesOscillatorsPatterns, PentaDecathlonPattern) {
    game.set_board(UTILITIES::pentaDecathlonPatternG1);

    game.applyRulesToTheBoardForIteration(1);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG2.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG2);

    game.applyRulesToTheBoardForIteration(2);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG3.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG3);

    game.applyRulesToTheBoardForIteration(3);

    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG4.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG4);

    game.applyRulesToTheBoardForIteration(4);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG5.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG5);

    game.applyRulesToTheBoardForIteration(5);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG6.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG6);

    game.applyRulesToTheBoardForIteration(6);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG7.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG7);

    game.applyRulesToTheBoardForIteration(7);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG8.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG8);

    game.applyRulesToTheBoardForIteration(8);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG9.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG9);

    game.applyRulesToTheBoardForIteration(9);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG10.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG10);

    game.applyRulesToTheBoardForIteration(10);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG11.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG11);

    game.applyRulesToTheBoardForIteration(11);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG12.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG12);

    game.applyRulesToTheBoardForIteration(12);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG13.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG13);

    game.applyRulesToTheBoardForIteration(13);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG14.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG14);

    game.applyRulesToTheBoardForIteration(14);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG15.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG15);

    game.applyRulesToTheBoardForIteration(15);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG2.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG1);
}

/****************************************  Tests Suite for applyRulesToTheGame with some 'spaceship' structures ****************************************/

TEST(UTApplyRulesSpaceshipPatterns, GosperGliderGunPattern) {
    game.set_board(UTILITIES::gosperGliderGunPattern);
    game.applyRulesToTheBoardForIteration(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::gosperGliderGunPatternG1);
}

/****************************************  Tests Suite for applyRulesToTheGame robustness ***************************************/

TEST(UTApplyRulesRobustness, RobustnessTests) {
    Game emptyGame;
    {
        // Board empty
        emptyGame.applyRulesToTheBoardForIteration(1);

        UTILITIES::compareGrid(emptyGame.get_board_const()->get_grid_const(), {});
    }
    {
        // No iteration
        emptyGame.set_board(UTILITIES::blockPattern);
        emptyGame.applyRulesToTheBoardForIteration(0);

        UTILITIES::compareGrid(emptyGame.get_board_const()->get_grid_const(), UTILITIES::blockPattern);
    }
}
