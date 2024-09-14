#include <gtest/gtest.h>
#include "InputChecker.hpp"

#include <tuple>

using namespace std;

InputChecker checker;

/****************************************  Tests Suite for valid inputs only  ***************************************/


TEST(ValidInputs, AllInputsPresentsAndValids) {
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

TEST(ValidInputs, InputsPresentsAndValidsWithoutAll) {
    const int argc{5};
    char *argv[argc]{string("Dummy/File/Path/To/Binary").data(), string("--input").data(),
                     string("initial.txt").data(), string("--iterations").data(), string("2000").data()};
    const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

    EXPECT_EQ(inputsValids, true);
    EXPECT_STREQ(filePath.data(), string("initial.txt").data());
    EXPECT_EQ(nbOfIterations, 2000);
    EXPECT_EQ(outputAllIterations, false);
}

TEST(ValidInputs, VerifyOrderWithAll) {
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

TEST(ValidInputs, VerifyOrderWithoutAll) {
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

TEST(ArgumentsUnknown, ArgumentsUnknownWithAll) {
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

TEST(ArgumentsUnknown, ArgumentsUnknownWithoutAll) {
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

TEST(MissingMandatory, MissingIteration) {
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

TEST(MissingMandatory, MissingInputFile) {
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

TEST(MissingMandatory, MissingAllMandatory) {
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

TEST(BadIteration, IterationIsString) {
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

TEST(BadIteration, IterationIsNull) {
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

TEST(BadIteration, IterationIsNegative) {
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

TEST(BadIteration, IterationIsOneValueBeforeTheIntLimit) {
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

TEST(BadIteration, IterationAtTheIntLimit) {
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

TEST(BadIteration, IterationIsOneValueAfterTheIntLimit) {
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
