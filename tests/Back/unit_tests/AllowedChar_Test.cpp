#include <gtest/gtest.h>
#include <iostream>
#include <cstdlib>

#include "Back/Game/AllowedChar.hpp"

using namespace std;


/****************************************  Tests Suite for static patterns ***************************************/

TEST(UTAllowed, CharToBoolTest)
{
    ASSERT_EQ(charToBool('*'), true);
    ASSERT_EQ(charToBool('-'), false);
    ASSERT_EQ(charToBool('.'), false);

    try
    {
        std::ignore = charToBool('!');
        ASSERT_EQ(true, false) << "Exception should have been raised";
    }
    catch (const std::invalid_argument& e)
    {
        ASSERT_EQ(string(e.what()), "Invalid character for mapping.");
    }
}

TEST(UTAllowed, BoolToCharTest)
{
    ASSERT_EQ(boolToChar(true), '*');
    ASSERT_EQ(boolToChar(false), '-');
}

TEST(UTAllowed, GetterTest)
{
    ASSERT_EQ(getAliveChar(), '*');
    ASSERT_EQ(getDeadChar(), '-');
}
