#include <gtest/gtest.h>

#include "core/datastructures/FreeList.h"

using namespace Core::DataStructures;

struct SampleStruct {
    int a = 0;
    float b = 0.0f;

    void freeMem() {}
};

TEST(FreeList, Initialization)
{
    FreeList<SampleStruct> list;

    EXPECT_EQ(0, list.size());
}
