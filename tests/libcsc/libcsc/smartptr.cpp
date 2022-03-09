#include "libcsc/libcsc/smartptr/UniquePtr.hpp"
#include "gtest/gtest.h"

#include <iostream>

using libcsc::smartptr::UniquePtr;

TEST(SmartPointers, UniquePointerAccess)
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
}