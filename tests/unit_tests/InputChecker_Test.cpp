#include <gtest/gtest.h>
#include "Back/InputChecker.hpp"

#include <tuple>

using namespace std;

InputChecker checker;

/****************************************  Tests Suite for valid inputs only  ***************************************/

TEST(UTValidInputs, AllInputsPresentsAndValids)
{
    const int argc{6};
    char* argv[argc]{
        (char*)"Dummy/File/Path/To/Binary", (char*)"--input",
        (char*)"initial.txt", (char*)"--iterations", (char*)"2000",
        (char*)"--all"
    };

    const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

    EXPECT_EQ(inputsValids, true);
    EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
    EXPECT_EQ(nbOfIterations, 2000);
    EXPECT_EQ(outputAllIterations, true);
}

TEST(UTValidInputs, InputsPresentsAndValidsWithoutAll)
{
    const int argc{5};
    char* argv[argc]{
        (char*)"Dummy/File/Path/To/Binary", (char*)"--input",
        (char*)"initial.txt", (char*)"--iterations", (char*)"2000"
    };
    const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

    EXPECT_EQ(inputsValids, true);
    EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
    EXPECT_EQ(nbOfIterations, 2000);
    EXPECT_EQ(outputAllIterations, false);
}

TEST(UTValidInputs, VerifyOrderWithAll)
{
    const int argc{6};
    {
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--all",
            (char*)"--iterations", (char*)"2000"
        };

        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, true);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, true);
    }

    {
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--iterations", (char*)"2000", (char*)"--all", (char*)"--input",
            (char*)"initial.txt"
        };

        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, true);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, true);
    }
}

TEST(UTValidInputs, VerifyOrderWithoutAll)
{
    const int argc{5};
    char* argv[argc]{
        (char*)"Dummy/File/Path/To/Binary", (char*)"--iterations", (char*)"2000",
        (char*)"--input", (char*)"initial.txt"
    };

    const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

    EXPECT_EQ(inputsValids, true);
    EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
    EXPECT_EQ(nbOfIterations, 2000);
    EXPECT_EQ(outputAllIterations, false);
}

/****************************************  Tests Suite for unrecognized   arguments  ***************************************/

TEST(UTArgumentsUnknown, ArgumentsUnknownWithAll)
{
    {
        const int argc{7};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"2000", (char*)"--all", (char*)"--unknownArg"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{7};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"2000", (char*)"--all", (char*)"RandomString"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, true);
    }
}

TEST(UTArgumentsUnknown, ArgumentsUnknownWithoutAll)
{
    {
        const int argc{6};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"2000", (char*)"--unknownArg"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, false);
    }
    {
        const int argc{6};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input",
            (char*)"initial.txt", (char*)"--iterations", (char*)"2000",
            (char*)"RandomString"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, false);
    }
}

/****************************************  Tests Suite for mandatory inputs missing  ***************************************/

TEST(UTMissingMandatory, MissingIteration)
{
    {
        const int argc{4};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input",
            (char*)"initial.txt", (char*)"--all"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{3};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input",
            (char*)"initial.txt"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTMissingMandatory, MissingInputFile)
{
    {
        const int argc{4};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--iterations",
            (char*)"2000", (char*)"--all"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"");
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{3};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--iterations",
            (char*)"2000"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"");
        EXPECT_EQ(nbOfIterations, 2000);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTMissingMandatory, MissingAllMandatory)
{
    {
        const int argc{2};
        char* argv[argc]{(char*)"Dummy/File/Path/To/Binary", (char*)"--all"};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"");
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{1};
        char* argv[argc]{(char*)"Dummy/File/Path/To/Binary"};
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"");
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
}

/****************************************  Tests Suite for invalid iterations value  ***************************************/

TEST(UTBadIteration, IterationIsString)
{
    {
        const int argc{6};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input",
            (char*)"initial.txt", (char*)"--iterations", (char*)"AString",
            (char*)"--all"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
    {
        const int argc{5};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"AString"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTBadIteration, IterationIsNull)
{
    {
        const int argc{6};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"0", (char*)"--all"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{5};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"0"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTBadIteration, IterationIsNegative)
{
    {
        const int argc{6};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"-1", (char*)"--all"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
    {
        const int argc{5};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"-1"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTBadIteration, IterationIsOneValueBeforeTheIntLimit)
{
    {
        const int argc{6};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"2147483646", (char*)"--all"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, true);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 2147483646);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{5};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"2147483646"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, true);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 2147483646);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTBadIteration, IterationAtTheIntLimit)
{
    {
        const int argc{6};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"2147483647", (char*)"--all"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, true);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 2147483647);
        EXPECT_EQ(outputAllIterations, true);
    }
    {
        const int argc{5};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"2147483647"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, true);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 2147483647);
        EXPECT_EQ(outputAllIterations, false);
    }
}

TEST(UTBadIteration, IterationIsOneValueAfterTheIntLimit)
{
    {
        const int argc{6};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"2147483648", (char*)"--all"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
    {
        const int argc{5};
        char* argv[argc]{
            (char*)"Dummy/File/Path/To/Binary", (char*)"--input", (char*)"initial.txt", (char*)"--iterations",
            (char*)"2147483648"
        };
        const auto [inputsValids, filePath, nbOfIterations, outputAllIterations] = checker.checkInputs(argc, argv);

        EXPECT_EQ(inputsValids, false);
        EXPECT_STREQ(filePath.data(), (char *)"initial.txt");
        EXPECT_EQ(nbOfIterations, 0);
        EXPECT_EQ(outputAllIterations, false);
    }
}
