#include <vector>
#include "vector.hpp"
#include "gtest/gtest.h"

struct SomeStruct {
    std::string name;
    float       number;
    SomeStruct() : name("empty"), number(15.51) {}
    SomeStruct(SomeStruct const& other) : name(other.name), number(other.number) {}
    SomeStruct& operator=(SomeStruct const& other) { name = other.name; number = other.number; return *this; }
    ~SomeStruct() {}
};

template<typename T, typename U>
void testContainersEqual(T const& cont1, U const& cont2) {
    EXPECT_EQ(cont1.empty(), cont2.empty());
    EXPECT_EQ(cont1.size(), cont2.size());
    EXPECT_EQ(cont1.max_size(), cont2.max_size());
    EXPECT_EQ(cont1.capacity(), cont2.capacity());
    EXPECT_EQ(cont1.begin() == cont1.end(), cont2.begin() == cont2.end());
    EXPECT_EQ(cont1.rbegin() == cont1.rend(), cont2.rbegin() == cont2.rend());
}

template<typename T, typename U>
void testEmptyContainersEqual(T const& cont1, U const& cont2) {
    testContainersEqual(cont1, cont2);
    EXPECT_EQ(&(cont1[0]), &(cont2[0]));
    EXPECT_EQ(&(*cont1.end()), &(*cont2.end()));
}

template<typename T>
void defaultConstructorTest() {
    ft::vector<T> ftv;
    std::vector<T> stv;
    testEmptyContainersEqual(ftv, stv);
}

TEST(CompareVectors, DefaultConstructorInt)         { defaultConstructorTest<int>(); }
TEST(CompareVectors, DefaultConstructorFloat)       { defaultConstructorTest<float>(); }
TEST(CompareVectors, DefaultConstructorString)      { defaultConstructorTest<std::string>(); }
TEST(CompareVectors, DefaultConstructorSomeStruct)  { defaultConstructorTest<SomeStruct>(); }

template<typename T>
void zeroElementsConstructorTest() {
    ft::vector<T> ftv(0);
    std::vector<T> stv(0);
    testEmptyContainersEqual(ftv, stv);

}

TEST(CompareVectors, ZeroElementsConstructorInt)        { zeroElementsConstructorTest<int>(); }
TEST(CompareVectors, ZeroElementsConstructorFloat)      { zeroElementsConstructorTest<float>(); }
TEST(CompareVectors, ZeroElementsConstructorString)     { zeroElementsConstructorTest<std::string>(); }
TEST(CompareVectors, ZeroElementsConstructorSomeStruct) { zeroElementsConstructorTest<SomeStruct>(); }

template<typename T>
void twentyElementsConstructorTest() {
    ft::vector<T> ftv(20);
    std::vector<T> stv(20);
    testContainersEqual(ftv, stv);
}

TEST(CompareVectors, TwentyElementsConstructorInt)          { twentyElementsConstructorTest<int>(); }
TEST(CompareVectors, TwentyElementsConstructorFloat)        { twentyElementsConstructorTest<float>(); }
TEST(CompareVectors, TwentyElementsConstructorString)       { twentyElementsConstructorTest<std::string>(); }
TEST(CompareVectors, TwentyElementsConstructorSomeStruct)   { twentyElementsConstructorTest<SomeStruct>(); }

template<typename T>
void twentyElementsWithDefaultValueConstructorTest() {
    ft::vector<T> ftv(20, 17);
    std::vector<T> stv(20, 17);
    testContainersEqual(ftv, stv);
}

TEST(CompareVectors, TwentyElementsWithDefaultValueConstructorInt)          { twentyElementsConstructorTest<int>(); }
TEST(CompareVectors, TwentyElementsWithDefaultValueConstructorFloat)        { twentyElementsConstructorTest<float>(); }
TEST(CompareVectors, TwentyElementsWithDefaultValueConstructorString)       { twentyElementsConstructorTest<std::string>(); }
TEST(CompareVectors, TwentyElementsWithDefaultValueConstructorSomeStruct)   { twentyElementsConstructorTest<SomeStruct>(); }

template<typename T>
void copyConstructorTest() {
    {
        ft::vector<int> ftv_o(20, 17);
        std::vector<int> stv_o(20, 17);
        ft::vector<int> ftv(ftv_o);
        std::vector<int> stv(stv_o);
        testContainersEqual(ftv, stv);
    }
    {
        ft::vector<int> ftv_o;
        std::vector<int> stv_o;
        ft::vector<int> ftv(ftv_o);
        std::vector<int> stv(stv_o);
        testEmptyContainersEqual(ftv, stv);
    }
    {
        ft::vector<int> ftv_o(0);
        std::vector<int> stv_o(0);
        ft::vector<int> ftv(ftv_o);
        std::vector<int> stv(stv_o);
        testEmptyContainersEqual(ftv, stv);
    }
    {
        ft::vector<int> ftv_o(20);
        std::vector<int> stv_o(20);
        ft::vector<int> ftv(ftv_o);
        std::vector<int> stv(stv_o);
        testContainersEqual(ftv, stv);
    }
}

TEST(CompareVectors, CopyConstructorInt)        { copyConstructorTest<int>(); }
TEST(CompareVectors, CopyConstructorFloat)      { copyConstructorTest<float>(); }
TEST(CompareVectors, CopyConstructorString)     { copyConstructorTest<std::string>(); }
TEST(CompareVectors, CopyConstructorSomeStruct) { copyConstructorTest<SomeStruct>(); }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
