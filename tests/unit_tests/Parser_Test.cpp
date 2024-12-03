#include <gtest/gtest.h>
#include "Back/Game/Parser.hpp"

#include "../tests/tests_utilities.hpp"

using namespace std;

/****************************************  Tests Suite for all reading the input files  ***************************************/

TEST(UTParseInputFile, ParseBlockPattern)
{
    UTILITIES::compareGrid(Parser("../tests/input_files/still_lifes/block.txt").parseBoardFile(),
                           UTILITIES::blockPattern);
}

TEST(UTParseInputFile, BeeHivePattern)
{
    UTILITIES::compareGrid(Parser("../tests/input_files/still_lifes/beeHive.txt").parseBoardFile(),
                           UTILITIES::beeHivePattern);
}

TEST(UTParseInputFile, LoafPattern)
{
    UTILITIES::compareGrid(Parser("../tests/input_files/still_lifes/loaf.txt").parseBoardFile(),
                           UTILITIES::loafPattern);
}

TEST(UTParseInputFile, BoatPattern)
{
    UTILITIES::compareGrid(Parser("../tests/input_files/still_lifes/boat.txt").parseBoardFile(),
                           UTILITIES::boatPattern);
}

TEST(UTParseInputFile, TubPattern)
{
    UTILITIES::compareGrid(Parser("../tests/input_files/still_lifes/tub.txt").parseBoardFile(), UTILITIES::tubPattern);
}

TEST(UTParseInputFile, BlinkerPattern)
{
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/blinkerG1.txt").parseBoardFile(),
                           UTILITIES::blinkerPatternG1);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/blinkerG2.txt").parseBoardFile(),
                           UTILITIES::blinkerPatternG2);
}

TEST(UTParseInputFile, ToadPattern)
{
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/toadG1.txt").parseBoardFile(),
                           UTILITIES::toadPatternG1);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/toadG2.txt").parseBoardFile(),
                           UTILITIES::toadPatternG2);
}

TEST(UTParseInputFile, BeaconPattern)
{
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/beaconG1.txt").parseBoardFile(),
                           UTILITIES::beaconPatternG1);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/beaconG2.txt").parseBoardFile(),
                           UTILITIES::beaconPatternG2);
}

TEST(UTParseInputFile, PulsarPattern)
{
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pulsarG1.txt").parseBoardFile(),
                           UTILITIES::pulsarPatternG1);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pulsarG2.txt").parseBoardFile(),
                           UTILITIES::pulsarPatternG2);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pulsarG3.txt").parseBoardFile(),
                           UTILITIES::pulsarPatternG3);
}

TEST(UTParseInputFile, PentaDecathlonPattern)
{
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG1.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG1);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG2.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG2);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG3.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG3);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG4.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG4);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG5.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG5);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG6.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG6);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG7.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG7);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG8.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG8);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG9.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG9);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG10.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG10);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG11.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG11);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG12.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG12);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG13.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG13);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG14.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG14);
    UTILITIES::compareGrid(Parser("../tests/input_files/oscillators/pentaDecathlonG15.txt").parseBoardFile(),
                           UTILITIES::pentaDecathlonPatternG15);
}

/****************************************  Tests Suite for robustness in parsing input file  ***************************************/

TEST(UTRobustnessInput, EmptyFileName)
{
    UTILITIES::compareGrid(Parser("").parseBoardFile(), {});
}

TEST(UTRobustnessInput, BadPath)
{
    UTILITIES::compareGrid(Parser("tests/input_files/block.txt").parseBoardFile(), {});
}

TEST(UTRobustnessInput, BadLengthOfLines)
{
    const auto test = Parser("../tests/input_files/badFile1.txt").parseBoardFile();
    UTILITIES::compareGrid(Parser("../tests/input_files/badFile1.txt").parseBoardFile(), {});
    UTILITIES::compareGrid(Parser("../tests/input_files/badFile2.txt").parseBoardFile(), {});
    UTILITIES::compareGrid(Parser("../tests/input_files/badFile3.txt").parseBoardFile(), {});
    UTILITIES::compareGrid(Parser("../tests/input_files/badFile4.txt").parseBoardFile(), {});
}

TEST(UTRobustnessInput, BadCharacter)
{
    UTILITIES::compareGrid(Parser("../tests/input_files/badFile5.txt").parseBoardFile(), {});
}
