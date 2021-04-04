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

std::ostream& operator<<(std::ostream& o, SomeStruct const& value) {
    std::cout << "SomeStruct(\"" << value.name << "\", " << value.number << ")";
    return o;
}

#define FT_DO_TEST(function) { \
        function<int>();\
        function<float>();\
        function<std::string>();\
        function<SomeStruct>();}

template<typename T>
void printValues(std::size_t id, T const& v1, T const& v2) {
    std::cout << id << ": " << v1 << " == " << v2 << std::endl;
}
template<>
void printValues(std::size_t id, std::string const& v1, std::string const& v2) {
    std::cout << id << ": \"" << v1 << "\" == \"" << v2 << '"' << std::endl;
}

template<typename T, typename U>
void testContainersEqual(T const& cont1, U const& cont2) {
    EXPECT_EQ(cont1.empty(), cont2.empty());
    EXPECT_EQ(cont1.size(), cont2.size());
    EXPECT_EQ(cont1.max_size(), cont2.max_size());
    EXPECT_EQ(cont1.capacity(), cont2.capacity());
    EXPECT_EQ(cont1.begin() == cont1.end(), cont2.begin() == cont2.end());
    EXPECT_EQ(cont1.rbegin() == cont1.rend(), cont2.rbegin() == cont2.rend());
    if (cont1.size() || cont2.size()) {
        std::cout << "\ttest and output iterators:" << std::endl;
        typename T::const_iterator it1 = cont1.begin();
        typename U::const_iterator it2 = cont2.begin();
        while (it1 != cont1.end() && it2 != cont2.end()) {
            printValues(it1 - cont1.begin(), *it1, *it2);
            EXPECT_EQ(*it1, *it2);
            ++it1;
            ++it2;
        }
        EXPECT_EQ(it1 == cont1.end(), it2 == cont2.end());
        std::cout << "\ttest and output reverse iterators:" << std::endl;
        typename T::const_reverse_iterator rit1 = cont1.rbegin();
        typename U::const_reverse_iterator rit2 = cont2.rbegin();
        while (rit1 != cont1.rend() && rit2 != cont2.rend()) {
            printValues(cont2.rend() - rit2 - 1, *rit1, *rit2);
            EXPECT_EQ(*rit1, *rit2);
            ++rit1;
            ++rit2;
        }
        EXPECT_EQ(rit1 == cont1.rend(), rit2 == cont2.rend());
        if (it1 != cont1.begin() || rit1 != cont1.rbegin())
            std::cout << std::endl;
    }
}

template<typename T, typename U>
void testEmptyContainersEqual(T const& cont1, U const& cont2) {
    EXPECT_EQ(&(cont1[0]), &(cont2[0]));
    EXPECT_EQ(&(*cont1.end()), &(*cont2.end()));
    testContainersEqual(cont1, cont2);
}

template<typename T>
void printTestName(std::string const& name) {
    (void)*(char*)(&name - &name);
}

template<>
void printTestName<int>(std::string const& name) {
    std::cout << name << " <int>" << std::endl;
}

template<>
void printTestName<float>(std::string const& name) {
    std::cout << name << " <float>" << std::endl;
}

template<>
void printTestName<std::string>(std::string const& name) {
    std::cout << name << " <std::string>" << std::endl;
}

template<>
void printTestName<SomeStruct>(std::string const& name) {
    std::cout << name << " <SomeStruct>" << std::endl;
}

template<typename T>
void defaultConstructorTest() {
    printTestName<T>("Default constructor");
    ft::vector<T> ftv;
    std::vector<T> stv;
    testEmptyContainersEqual(ftv, stv);
}

TEST(CompareVectors, DefaultConstructor) FT_DO_TEST(defaultConstructorTest)

template<typename T>
void zeroElementsConstructorTest() {
    printTestName<T>("Constructor for 0 elements");
    ft::vector<T> ftv(0);
    std::vector<T> stv(0);
    testEmptyContainersEqual(ftv, stv);

}

TEST(CompareVectors, ZeroElementsConstructor) FT_DO_TEST(zeroElementsConstructorTest)

template<typename T>
void twentyElementsConstructorTest() {
    printTestName<T>("Constructor for N elements");
    ft::vector<T> ftv(20);
    std::vector<T> stv(20);
    testContainersEqual(ftv, stv);
}

TEST(CompareVectors, TwentyElementsConstructor) FT_DO_TEST(twentyElementsConstructorTest)

template<typename T>
T getRandomValue();

template<>
int getRandomValue<int>() {
    return 17;
}

template<>
float getRandomValue<float>() {
    return 48.229;
}

template<>
std::string getRandomValue<std::string>() {
    return std::string("emptyString");
}

template<>
SomeStruct getRandomValue<SomeStruct>() {
    return SomeStruct();
}

template<typename T>
void twentyElementsWithDefaultValueConstructorTest() {
    printTestName<T>("Constructor for N elements with value");
    ft::vector<T> ftv(20, getRandomValue<T>());
    std::vector<T> stv(20, getRandomValue<T>());
    testContainersEqual(ftv, stv);
}

TEST(CompareVectors, TwentyElementsWithDefaultValueConstructor) FT_DO_TEST(twentyElementsWithDefaultValueConstructorTest)

template<typename T>
void copyConstructorTest() {
    {
        printTestName<T>("Copy constructor for default container");
        ft::vector<T> ftv_o;
        std::vector<T> stv_o;
        ft::vector<T> ftv(ftv_o);
        std::vector<T> stv(stv_o);
        testEmptyContainersEqual(ftv, stv);
    }
    {
        printTestName<T>("Copy constructor for 0 elements");
        ft::vector<T> ftv_o(0);
        std::vector<T> stv_o(0);
        ft::vector<T> ftv(ftv_o);
        std::vector<T> stv(stv_o);
        testEmptyContainersEqual(ftv, stv);
    }
    {
        printTestName<T>("Copy constructor for N elements");
        ft::vector<T> ftv_o(20);
        std::vector<T> stv_o(20);
        ft::vector<T> ftv(ftv_o);
        std::vector<T> stv(stv_o);
        testContainersEqual(ftv, stv);
    }
    {
        printTestName<T>("Copy constructor for N elements with value");
        ft::vector<T> ftv_o(20, getRandomValue<T>());
        std::vector<T> stv_o(20, getRandomValue<T>());
        ft::vector<T> ftv(ftv_o);
        std::vector<T> stv(stv_o);
        testContainersEqual(ftv, stv);
    }
}

TEST(CompareVectors, CopyConstructor)  FT_DO_TEST(copyConstructorTest)

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
