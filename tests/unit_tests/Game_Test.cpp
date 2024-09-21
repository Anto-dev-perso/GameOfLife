#include <gtest/gtest.h>
#include "Game/Game.hpp"

#include "../tests_utilities.hpp"

using namespace std;

static Game game;


/****************************************  Tests Suite for applyRulesToTheGame with some 'still lifes' structures ***************************************/
TEST(ApplyRulesStillLifePatterns, BlockPattern) {
    game.set_board(UTILITIES::blockPattern);
    game.applyRulesToTheBoard(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::blockPattern);
    game.applyRulesToTheBoard(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::blockPattern);
}

TEST(ApplyRulesStillLifePatterns, BeeHivePattern) {
    game.set_board(UTILITIES::beeHivePattern);
    game.applyRulesToTheBoard(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::beeHivePattern);
    game.applyRulesToTheBoard(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::beeHivePattern);
}

TEST(ApplyRulesStillLifePatterns, LoafPattern) {
    game.set_board(UTILITIES::loafPattern);
    game.applyRulesToTheBoard(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::loafPattern);
    game.applyRulesToTheBoard(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::loafPattern);
}

TEST(ApplyRulesStillLifePatterns, BoatPattern) {
    game.set_board(UTILITIES::boatPattern);
    game.applyRulesToTheBoard(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::boatPattern);
    game.applyRulesToTheBoard(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::boatPattern);
}

TEST(ApplyRulesStillLifePatterns, tubPattern) {
    game.set_board(UTILITIES::tubPattern);
    game.applyRulesToTheBoard(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::tubPattern);
    game.applyRulesToTheBoard(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::tubPattern);
}

/****************************************  Tests Suite for applyRulesToTheGame with some 'oscillators' structures ***************************************/
TEST(ApplyRulesOscillatorsPatterns, BlinkerPattern) {
    game.set_board(UTILITIES::blinkerPatternG1);
    game.applyRulesToTheBoard(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::blinkerPatternG2);

    game.applyRulesToTheBoard(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::blinkerPatternG1);
}

TEST(ApplyRulesOscillatorsPatterns, ToadPattern) {
    game.set_board(UTILITIES::toadPatternG2);
    game.applyRulesToTheBoard(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::toadPatternG1);
    game.applyRulesToTheBoard(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::toadPatternG2);
}

TEST(ApplyRulesOscillatorsPatterns, BeaconPattern) {
    game.set_board(UTILITIES::beaconPatternG1);
    game.applyRulesToTheBoard(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::beaconPatternG2);
    game.applyRulesToTheBoard(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::beaconPatternG1);
}

TEST(ApplyRulesOscillatorsPatterns, PulsarPattern) {
    game.set_board(UTILITIES::pulsarPatternG1);
    game.applyRulesToTheBoard(1);

    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pulsarPatternG2);

    game.applyRulesToTheBoard(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pulsarPatternG3);

    game.applyRulesToTheBoard(3);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pulsarPatternG1);
}

TEST(ApplyRulesOscillatorsPatterns, PentaDecathlonPattern) {
    game.set_board(UTILITIES::pentaDecathlonPatternG1);

    game.applyRulesToTheBoard(1);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG2.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG2);

    game.applyRulesToTheBoard(2);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG3.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG3);

    game.applyRulesToTheBoard(3);

    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG4.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG4);

    game.applyRulesToTheBoard(4);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG5.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG5);

    game.applyRulesToTheBoard(5);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG6.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG6);

    game.applyRulesToTheBoard(6);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG7.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG7);

    game.applyRulesToTheBoard(7);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG8.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG8);

    game.applyRulesToTheBoard(8);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG9.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG9);

    game.applyRulesToTheBoard(9);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG10.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG10);

    game.applyRulesToTheBoard(10);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG11.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG11);

    game.applyRulesToTheBoard(11);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG12.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG12);

    game.applyRulesToTheBoard(12);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG13.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG13);

    game.applyRulesToTheBoard(13);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG14.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG14);

    game.applyRulesToTheBoard(14);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG15.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG15);

    game.applyRulesToTheBoard(15);
    EXPECT_EQ(game.get_board_const()->get_grid_const().size(), UTILITIES::pentaDecathlonPatternG2.size());
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pentaDecathlonPatternG1);
}

/****************************************  Tests Suite for applyRulesToTheGame robustness ***************************************/

TEST(ApplyRulesRobustness, RobustnessTests) {
    Game emptyGame;
    {
        // Board empty
        emptyGame.applyRulesToTheBoard(1);

        UTILITIES::compareGrid(emptyGame.get_board_const()->get_grid_const(), {});
    }
    {
        // No iteration
        emptyGame.set_board(UTILITIES::blockPattern);
        emptyGame.applyRulesToTheBoard(0);

        UTILITIES::compareGrid(emptyGame.get_board_const()->get_grid_const(), UTILITIES::blockPattern);
    }
}
