#include "libcsc/libcsc/time/time.hpp"
#include "gtest/gtest.h"

#include <sstream>

using namespace libcsc::time::literals;
using libcsc::time::Time;
using libcsc::time::TimeSpan;

TEST(Time, TimeLiterals)
{
    EXPECT_EQ(365_d, TimeSpan(365, 0, 0, 0));
    EXPECT_EQ(30_d + 15_h + 50_s, TimeSpan(30, 15, 0, 50));
    EXPECT_EQ(10_d - 16_h, TimeSpan(9, 8, 0, 0));
    EXPECT_EQ(75_m, TimeSpan(0, 1, 15, 0));
}

TEST(Time, TimeOperations)
{
    Time t1(365_d);
    Time t2(355_d + 12_h);

    EXPECT_EQ(t1 - t2, TimeSpan(9, 12, 0, 0));
    EXPECT_EQ(t2 - t1, TimeSpan(9, 12, 0, 0));

    t2 += TimeSpan(9_h);
    EXPECT_EQ(t2, Time(355_d + 21_h));
    t2 -= TimeSpan(12_h);
    EXPECT_EQ(t2, Time(355_d + 9_h));
}

TEST(Time, OstreamPrint)
{
    std::ostringstream os("");
    os << Time(9_h + 50_m + 45_s) << '\n';
    os << TimeSpan(75_s) << '\n';
    os << Time(365_d);
    EXPECT_EQ(os.str(), "00d 09h 50m 45s\n00d 00h 01m 15s\n365d 00h 00m 00s");
}