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
    bool operator==(SomeStruct const& other) const { return name == other.name && number == other.number; }
};

#define FT_DO_TEST(function) { \
        function<int>();\
        function<float>();\
        function<std::string>();\
        function<SomeStruct>();}

template<typename T, typename U>
void testContainersEqual(T const& cont1, U const& cont2) {
    EXPECT_EQ(cont1.empty(), cont2.empty());
    EXPECT_EQ(cont1.size(), cont2.size());
    EXPECT_EQ(cont1.max_size(), cont2.max_size());
    EXPECT_EQ(cont1.capacity(), cont2.capacity());
    EXPECT_EQ(cont1.begin() == cont1.end(), cont2.begin() == cont2.end());
    EXPECT_EQ(cont1.rbegin() == cont1.rend(), cont2.rbegin() == cont2.rend());
    typename T::const_iterator it1 = cont1.begin();
    typename U::const_iterator it2 = cont2.begin();
    while (it1 != cont1.end() && it2 != cont2.end()) {
        EXPECT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
    EXPECT_EQ(it1 == cont1.end(), it2 == cont2.end());
    typename T::const_reverse_iterator rit1 = cont1.rbegin();
    typename U::const_reverse_iterator rit2 = cont2.rbegin();
    while (rit1 != cont1.rend() && rit2 != cont2.rend()) {
        EXPECT_EQ(*rit1, *rit2);
        ++rit1;
        ++rit2;
    }
    EXPECT_EQ(rit1 == cont1.rend(), rit2 == cont2.rend());
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

TEST(CompareVectors, DefaultConstructor) FT_DO_TEST(defaultConstructorTest)

template<typename T>
void zeroElementsConstructorTest() {
    ft::vector<T> ftv(0);
    std::vector<T> stv(0);
    testEmptyContainersEqual(ftv, stv);

}

TEST(CompareVectors, ZeroElementsConstructor) FT_DO_TEST(zeroElementsConstructorTest)

template<typename T>
void twentyElementsConstructorTest() {
    ft::vector<T> ftv(20);
    std::vector<T> stv(20);
    testContainersEqual(ftv, stv);
}

TEST(CompareVectors, TwentyElementsConstructor) FT_DO_TEST(twentyElementsConstructorTest)

template<typename T>
void twentyElementsWithDefaultValueConstructorTest() {
    ft::vector<T> ftv(20, 17);
    std::vector<T> stv(20, 17);
    testContainersEqual(ftv, stv);
}

TEST(CompareVectors, TwentyElementsWithDefaultValueConstructor) FT_DO_TEST(twentyElementsWithDefaultValueConstructorTest)

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

TEST(CompareVectors, CopyConstructor)  FT_DO_TEST(copyConstructorTest)

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
