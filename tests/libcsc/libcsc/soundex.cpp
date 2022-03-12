#include "libcsc/libcsc/soundex/soundex.hpp"
#include "gtest/gtest.h"

using libcsc::soundex::soundex_hash;
using libcsc::soundex::string_to_hash;

TEST(Soundex, CorrectHash)
{
    EXPECT_EQ(soundex_hash("Emily"), string_to_hash("E540"));
    EXPECT_EQ(soundex_hash("nora"), string_to_hash("N600"));
    EXPECT_EQ(soundex_hash("Aya"), string_to_hash("A000"));
    EXPECT_EQ(soundex_hash("Hewlett"), string_to_hash("H430"));
}

TEST(Soundex, IncorrectHash)
{
    try {
        soundex_hash("");
        FAIL();
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ("Empty string given to soundex_hash", e.what());
    }

    try {
        soundex_hash("Invalid$Character");
        FAIL();
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ("String 'Invalid$Character' includes a character which is neither a letter nor a digit", e.what());
    }
}