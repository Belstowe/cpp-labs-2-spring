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

TEST(ForwardList, LoopDetection)
{
    ForwardList<int> node1(4);
    ForwardList<int> node2(8);
    ForwardList<int> node3(-2);
    ForwardList<int> node4(0);

    node1.chain(node2);
    node2.chain(node3);
    node3.chain(node4);
    node4.chain(node2);

    auto turtle_it = node1.begin();
    auto rabbit_it = node1.begin();

    do {
        ++turtle_it;
        ++rabbit_it;
        ++rabbit_it;
    } while (turtle_it != rabbit_it);

    EXPECT_EQ(turtle_it, rabbit_it);
}