#include <gtest/gtest.h>
#include "Game/Parser.hpp"
#include "../tests/tests_utilities.hpp"

using namespace std;

static const std::string toto{"../tests/input_files/"};

/****************************************  Tests Suite for all reading the input files  ***************************************/

TEST(ParseInputFile, ParseBlockPattern) {
    UTILITIES::compareGrid(Parser("../tests/input_files/still_lifes/block.txt").parseInputFile(),
                           UTILITIES::blockPattern);
}

TEST(ParseInputFile, BeeHivePattern) {
    UTILITIES::compareGrid(Parser("../tests/input_files/still_lifes/beeHive.txt").parseInputFile(),
                           UTILITIES::beeHivePattern);
}

TEST(ParseInputFile, LoafPattern) {
    UTILITIES::compareGrid(Parser("../tests/input_files/still_lifes/loaf.txt").parseInputFile(),
                           UTILITIES::loafPattern);
}

TEST(ParseInputFile, BoatPattern) {
    UTILITIES::compareGrid(Parser("../tests/input_files/still_lifes/boat.txt").parseInputFile(),
                           UTILITIES::boatPattern);
}

TEST(ParseInputFile, TubPattern) {
    UTILITIES::compareGrid(Parser("../tests/input_files/still_lifes/tub.txt").parseInputFile(), UTILITIES::tubPattern);
}

TEST(ParseInputFile, BlinkerPattern) {
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/blinkerG1.txt").parseInputFile(),
                           UTILITIES::blinkerPatternG1);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/blinkerG2.txt").parseInputFile(),
                           UTILITIES::blinkerPatternG2);
}

TEST(ParseInputFile, ToadPattern) {
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/toadG1.txt").parseInputFile(),
                           UTILITIES::toadPatternG1);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/toadG2.txt").parseInputFile(),
                           UTILITIES::toadPatternG2);
}

TEST(ParseInputFile, BeaconPattern) {
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/beaconG1.txt").parseInputFile(),
                           UTILITIES::beaconPatternG1);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/beaconG2.txt").parseInputFile(),
                           UTILITIES::beaconPatternG2);
}

TEST(ParseInputFile, PulsarPattern) {
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pulsarG1.txt").parseInputFile(),
                           UTILITIES::pulsarPatternG1);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pulsarG2.txt").parseInputFile(),
                           UTILITIES::pulsarPatternG2);
    UTILITIES::compareGrid(Parser("../tests/input_files/pulsarG3.txt").parseInputFile(), UTILITIES::pulsarPatternG3);
}

TEST(ParseInputFile, PentaDecathlonPattern) {
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG1.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG1);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG2.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG2);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG3.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG3);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG4.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG4);
    UTILITIES::compareGrid(Parser("../tests/input_files/pentaDecathlonG5.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG5);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG6.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG6);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG7.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG7);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG8.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG8);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG9.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG9);
    UTILITIES::compareGrid(Parser("../tests/input_files/pentaDecathlonG10.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG10);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG11.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG11);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG12.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG12);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG13.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG13);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG14.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG14);
    UTILITIES::compareGrid(Parser("../tests/input_files/pentaDecathlonG15.txt").parseInputFile(),
                           UTILITIES::pentaDecathlonPatternG15);
}

/****************************************  Tests Suite for robustness in parsing input file  ***************************************/

TEST(RobustnessInput, EmptyFileName) {
    UTILITIES::compareGrid(Parser("").parseInputFile(), {});
}

TEST(RobustnessInput, BadPath) {
    UTILITIES::compareGrid(Parser("tests/input_files/block.txt").parseInputFile(), {});
}

TEST(RobustnessInput, BadLengthOfLines) {
    UTILITIES::compareGrid(Parser("../tests/input_files/badFile1.txt").parseInputFile(), {});
    UTILITIES::compareGrid(Parser("../tests/input_files/badFile2.txt").parseInputFile(), {});
    UTILITIES::compareGrid(Parser("../tests/input_files/badFile3.txt").parseInputFile(), {});
    UTILITIES::compareGrid(Parser("../tests/input_files/badFile4.txt").parseInputFile(), {});
}

TEST(RobustnessInput, BadCharacter) {
    UTILITIES::compareGrid(Parser("../tests/input_files/badFile5.txt").parseInputFile(), {});
}
