#include <gtest/gtest.h>
#include "InputChecker.hpp"

#include <tuple>

using namespace std;

InputChecker checker;

/****************************************  Tests Suite for valid inputs only  ***************************************/


TEST(UTValidInputs, AllInputsPresentsAndValids) {
    const int argc{6};
    char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                     string("initial.txt").data(), string("--iterations").data(), string("2000").data(),
                     string("--all").data()};
    const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

    EXPECT_EQ(inputsValids, true);
    EXPECT_STREQ(filePath.data(), string("initial.txt").data());
    EXPECT_EQ(nbOfIterations, 2000);
    EXPECT_EQ(outputAllIterations, true);
}

TEST(UTValidInputs, InputsPresentsAndValidsWithoutAll) {
    const int argc{5};
    char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                     string("initial.txt").data(), string("--iterations").data(), string("2000").data()};
    const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

    EXPECT_EQ(inputsValids, true);
    EXPECT_STREQ(filePath.data(), string("initial.txt").data());
    EXPECT_EQ(nbOfIterations, 2000);
    EXPECT_EQ(outputAllIterations, false);
}

TEST(UTValidInputs, VerifyOrderWithAll) {
    const int argc{6};
    {
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--all").data(), string("--iterations").data(),
                         string("2000").data()};

        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, true);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, true);
    }

    {
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(),
                         string("--iterations").data(),
                         string("2000").data(),
                         string("--all").data(),
                         string("--input").data(), string("initial.txt").data()};

        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, true);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, true);
    }
}

TEST(UTValidInputs, VerifyOrderWithoutAll) {
    const int argc{5};
    char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--iterations").data(), string("2000").data(),
                     string("--input").data(), string("initial.txt").data()};

    const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

    EXPECT_EQ(inputsValids, true);
    EXPECT_STREQ(filePath.data(), string("initial.txt").data());
    EXPECT_EQ(nbOfIterations, 2000);
    EXPECT_EQ(outputAllIterations, false);
}

/****************************************  Tests Suite for unrecognized   arguments  ***************************************/

TEST(UTArgumentsUnknown, ArgumentsUnknownWithAll) {
    {
        const int argc{7};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("2000").data(),
                         string("--all").data(), string("--unknownArg").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{7};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("2000").data(),
                         string("--all").data(), string("RandomString").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, true);
    }
}

TEST(UTArgumentsUnknown, ArgumentsUnknownWithoutAll) {
    {
        const int argc{6};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("2000").data(),
                         string("--unknownArg").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, false);
    }
    {
        const int argc{6};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("2000").data(),
                         string("RandomString").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, false);
    }
}

/****************************************  Tests Suite for mandatory inputs missing  ***************************************/

TEST(UTMissingMandatory, MissingIteration) {
    {
        const int argc{4};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--all").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{3};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTMissingMandatory, MissingInputFile) {
    {
        const int argc{4};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--iterations").data(),
                         string("2000").data(), string("--all").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("").data());
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{3};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--iterations").data(),
                         string("2000").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("").data());
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTMissingMandatory, MissingAllMandatory) {
    {
        const int argc{2};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--all").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("").data());
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{1};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("").data());
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
}



/****************************************  Tests Suite for invalid iterations value  ***************************************/

TEST(UTBadIteration, IterationIsString) {
    {
        const int argc{6};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("AString").data(),
                         string("--all").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
    {
        const int argc{5};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("AString").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTBadIteration, IterationIsNull) {
    {
        const int argc{6};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("0").data(),
                         string("--all").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{5};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("0").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTBadIteration, IterationIsNegative) {
    {
        const int argc{6};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("-1").data(),
                         string("--all").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
    {
        const int argc{5};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("-1").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTBadIteration, IterationIsOneValueBeforeTheIntLimit) {
    {
        const int argc{6};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("2147483646").data(),
                         string("--all").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, true);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 2147483646);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{5};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("2147483646").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, true);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 2147483646);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTBadIteration, IterationAtTheIntLimit) {
    {
        const int argc{6};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("2147483647").data(),
                         string("--all").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, true);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 2147483647);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{5};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("2147483647").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, true);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 2147483647);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTBadIteration, IterationIsOneValueAfterTheIntLimit) {
    {
        const int argc{6};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("2147483648").data(),
                         string("--all").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
    {
        const int argc{5};
        char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                         string("initial.txt").data(), string("--iterations").data(), string("2147483648").data()};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), string("initial.txt").data());
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
}
