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

TEST(FreeList, OneElement)
{
    FreeList<SampleStruct> list;
    SampleStruct testStruct{};
    testStruct.a = 42;
    testStruct.b = 3.1416f;

    auto id = list.add(testStruct);

    EXPECT_EQ(1, list.size());
    EXPECT_TRUE(list.has(id));

    auto storedStruct = list.get(id);

    EXPECT_EQ(42, storedStruct.a);
    EXPECT_EQ(3.1416f, storedStruct.b);
}

TEST(FreeList, TwoElements)
{
    FreeList<SampleStruct> list;
    SampleStruct testStruct1{};
    testStruct1.a = 42;
    testStruct1.b = 3.1416f;

    SampleStruct testStruct2{};
    testStruct2.a = 11;
    testStruct2.b = 1.61f;

    auto id1 = list.add(testStruct1);
    auto id2 = list.add(testStruct2);

    EXPECT_EQ(2, list.size());
    EXPECT_TRUE(list.has(id1));
    EXPECT_TRUE(list.has(id2));

    auto storedStruct1 = list.get(id1);
    EXPECT_EQ(42, storedStruct1.a);
    EXPECT_EQ(3.1416f, storedStruct1.b);

    auto storedStruct2 = list.get(id2);
    EXPECT_EQ(11, storedStruct2.a);
    EXPECT_EQ(1.61f, storedStruct2.b);
}

TEST(FreeList, RemoveElement)
{
    FreeList<SampleStruct> list;

    SampleStruct testStruct{};
    
    auto id = list.add(testStruct);

    list.remove(id);

    EXPECT_EQ(0, list.size());
    EXPECT_FALSE(list.has(id));
}

// Add an element, remove it and add another one
// the storage size should still be 1 because we are reusing the slot.
TEST(FreeList, StorageSize)
{
    FreeList<SampleStruct> list;
    SampleStruct testStruct{};
    
    auto id = list.add(testStruct);
    list.remove(id);
    list.add(SampleStruct{});

    EXPECT_EQ(1, list.storageSize());
}

TEST(FreeList, FreeListSize)
{
    FreeList<SampleStruct> list;
    SampleStruct testStruct{};
    
    auto id = list.add(testStruct);
    auto id2 = list.add(SampleStruct{});
    list.remove(id);
    list.remove(id2);

    EXPECT_EQ(2, list.freeListSize());
    EXPECT_EQ(2, list.storageSize());
}
