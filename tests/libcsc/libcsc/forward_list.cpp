#include "libcsc/libcsc/forward_list/ForwardIterator.hpp"
#include "libcsc/libcsc/forward_list/ForwardList.hpp"
#include "gtest/gtest.h"

#include <numeric>

using libcsc::forward_list::ForwardList;

TEST(ForwardList, CorrectInitialization)
{
    ForwardList<int> list{4, 8, -2, 0};

    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(std::accumulate(list.begin(), list.end(), 0), 10);
    EXPECT_EQ(*(list.begin()), 4);
}