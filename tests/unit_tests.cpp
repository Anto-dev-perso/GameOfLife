#include <gtest/gtest.h>

int main(int argc, char **argv) {
    // Run only tests beginning by UT (Unit Tests)
    ::testing::GTEST_FLAG(filter) = "UT*";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
