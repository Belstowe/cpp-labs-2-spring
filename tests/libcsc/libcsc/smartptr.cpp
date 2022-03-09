#include "libcsc/libcsc/smartptr/SharedPtr.hpp"
#include "libcsc/libcsc/smartptr/UniquePtr.hpp"
#include "gtest/gtest.h"

#include <iostream>

using libcsc::smartptr::SharedPtr;
using libcsc::smartptr::UniquePtr;

TEST(SmartPointers, UniquePointer)
{
    UniquePtr<std::string> ptr(new std::string("Content Inside UniquePtr"));

    EXPECT_EQ(*ptr, std::string("Content Inside UniquePtr"));
    EXPECT_EQ(*(ptr.get()), std::string("Content Inside UniquePtr"));
    EXPECT_STREQ(ptr->c_str(), "Content Inside UniquePtr");

    ptr = UniquePtr<std::string>(std::move(new std::string("New Content")));
    EXPECT_EQ(*ptr, std::string("New Content"));

    UniquePtr<std::string> ptr2(new std::string("Content of Ptr2"));
    ptr = std::move(ptr2);
    EXPECT_EQ(*(ptr.get()), std::string("Content of Ptr2"));
    EXPECT_EQ(ptr2.get(), nullptr);

    ptr = std::move(ptr);
    EXPECT_EQ(*ptr, std::string("Content of Ptr2"));
}

TEST(SmartPointers, SharedPointer)
{
    SharedPtr<std::string> ptr1(new std::string("Content Inside SharedPtr #1"));
    SharedPtr<std::string> ptr2(ptr1);
    SharedPtr<std::string> ptr3(ptr2);

    EXPECT_STREQ(ptr1->c_str(), "Content Inside SharedPtr #1");
    EXPECT_EQ(*(ptr1.get()), std::string("Content Inside SharedPtr #1"));

    EXPECT_EQ(*ptr1, std::string("Content Inside SharedPtr #1"));
    EXPECT_EQ(*ptr2, std::string("Content Inside SharedPtr #1"));
    EXPECT_EQ(*ptr3, std::string("Content Inside SharedPtr #1"));
    EXPECT_EQ(ptr1.use_count(), 3);
    EXPECT_EQ(ptr2.use_count(), 3);
    EXPECT_EQ(ptr3.use_count(), 3);

    ptr1 = SharedPtr<std::string>(new std::string("Content Inside SharedPtr #2"));

    EXPECT_EQ(*ptr1, std::string("Content Inside SharedPtr #2"));
    EXPECT_EQ(*ptr2, std::string("Content Inside SharedPtr #1"));
    EXPECT_EQ(*ptr3, std::string("Content Inside SharedPtr #1"));
    EXPECT_EQ(ptr1.use_count(), 1);
    EXPECT_EQ(ptr2.use_count(), 2);
    EXPECT_EQ(ptr3.use_count(), 2);

    ptr2.reset();

    EXPECT_EQ(*ptr1, std::string("Content Inside SharedPtr #2"));
    EXPECT_EQ(ptr2.get(), nullptr);
    EXPECT_EQ(*ptr3, std::string("Content Inside SharedPtr #1"));
    EXPECT_EQ(ptr1.use_count(), 1);
    EXPECT_EQ(ptr2.use_count(), 0);
    EXPECT_EQ(ptr3.use_count(), 1);
}