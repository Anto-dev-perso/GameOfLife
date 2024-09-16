#include <gtest/gtest.h>
#include "Game/Game.hpp"

#include "../tests_utilities.hpp"

using namespace std;

// Set iteration to 1 for speed and to test oscillators
static Game game("Dummy", 1, false);


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
    game.set_board(UTILITIES::blinkerPatternP1);
    game.applyRulesToTheBoard(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::blinkerPatternP2);

    game.applyRulesToTheBoard(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::blinkerPatternP1);
}

TEST(ApplyRulesOscillatorsPatterns, ToadPattern) {
    game.set_board(UTILITIES::toadPatternP1);
    game.applyRulesToTheBoard(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::toadPatternP2);
    game.applyRulesToTheBoard(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::toadPatternP1);
}

TEST(ApplyRulesOscillatorsPatterns, BeaconPattern) {
    game.set_board(UTILITIES::beaconPatternP1);
    game.applyRulesToTheBoard(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::beaconPatternP2);
    game.applyRulesToTheBoard(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::beaconPatternP1);
}

TEST(ApplyRulesOscillatorsPatterns, PulsarPattern) {
    game.set_board(UTILITIES::pulsarPatternP1);
    game.applyRulesToTheBoard(1);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pulsarPatternP2);

    game.applyRulesToTheBoard(2);
    UTILITIES::compareGrid(game.get_board_const()->get_grid_const(), UTILITIES::pulsarPatternP3);
}

/****************************************  Tests Suite for applyRulesToTheGame robustness ***************************************/

TEST(ApplyRulesRobustness, RobustnessTests) {
    {
        // Board empty
        Game emptyGame("", 1, false);
        emptyGame.applyRulesToTheBoard(1);

        UTILITIES::compareGrid(emptyGame.get_board_const()->get_grid_const(), {});
    }
    {
        // No iteration
        Game emptyGame("", 0, false);
        emptyGame.set_board(UTILITIES::blockPattern);
        emptyGame.applyRulesToTheBoard(0);

        UTILITIES::compareGrid(emptyGame.get_board_const()->get_grid_const(), UTILITIES::blockPattern);
    }
}
