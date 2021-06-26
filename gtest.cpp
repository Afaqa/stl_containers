#include <vector>
#include "vector.hpp"
#include <list>
#include "list.hpp"
#include <map>
#include "map.hpp"
#include "gtest/gtest.h"
#include <fstream>

#define COLOR_BLACK	"\033[0;30m"
#define COLOR_RED		"\033[0;31m"
#define COLOR_GREEN	"\033[0;32m"
#define COLOR_ORANGE	"\033[0;33m"
#define COLOR_BLUE	"\033[0;34m"
#define COLOR_PURPLE	"\033[0;35m"
#define COLOR_CYAN	"\033[0;36m"
#define COLOR_LGRAY	"\033[0;37m"
#define COLOR_DGRAY	"\033[1;30m"
#define COLOR_LRED	"\033[1;31m"
#define COLOR_LGREEN	"\033[1;32m"
#define COLOR_YELLOW	"\033[1;33m"
#define COLOR_LBLUE	"\033[1;34m"
#define COLOR_LPURPLE	"\033[1;35m"
#define COLOR_LCYAN	"\033[1;36m"
#define COLOR_WHITE	"\033[1;37m"
#define COLOR_RESET	"\033[0m"

struct SomeStruct {
    std::string name;
    float       number;
    SomeStruct() : name("empty"), number(15.51) {}
    SomeStruct(std::string const& name, float number) : name(name), number(number) {}
    SomeStruct(SomeStruct const& other) : name(other.name), number(other.number) {}
    SomeStruct& operator=(SomeStruct const& other) {
        name = other.name;
        number = other.number;
        return *this;
    }
    ~SomeStruct() {}
    bool operator==(SomeStruct const& other) const { return name == other.name && number == other.number; }
    bool operator!=(SomeStruct const& other) const { return !(*this == other); }
    bool operator<(SomeStruct const& other) const { return name < other.name || (!(other.name < name) && number < other.number); }
    bool operator<=(SomeStruct const& other) const { return !(other < *this); }
    bool operator>(SomeStruct const& other) const { return other < *this; }
    bool operator>=(SomeStruct const& other) const { return !(*this < other); }
};

std::ostream& operator<<(std::ostream& o, SomeStruct const& value) {
    std::cout << "SomeStruct(\"" << value.name << "\", " << value.number << ")";
    return o;
}

#define FT_DO_TEST(function) {\
        function<int>();\
        function<float>();\
        function<std::string>();\
        function<SomeStruct>();}

template<typename T>
void printValues(std::size_t id, T const& v1, T const& v2) {
    std::cout << id << ": " << v1 << COLOR_RED " == " COLOR_RESET << v2 << std::endl;
}
template<>
void printValues(std::size_t id, std::string const& v1, std::string const& v2) {
    std::cout << id << ": \"" << v1 << '"' << COLOR_RED " == " COLOR_RESET << '"' << v2 << '"' << std::endl;
}

template<typename T, typename U>
void testContainersEqual(T const& cont1, U const& cont2) {
    EXPECT_EQ(cont1.empty(), cont2.empty());
    std::cout << "Empty " << cont1.empty() << " == " << cont2.empty() << std::endl;
    EXPECT_EQ(cont1.size(), cont2.size());
    std::cout << "Size " << cont1.size() << " == " << cont2.size() << std::endl;
    EXPECT_EQ(cont1.max_size(), cont2.max_size());
    std::cout << "Max size " << cont1.max_size() << " == " << cont2.max_size() << std::endl;
    EXPECT_EQ(cont1.capacity(), cont2.capacity());
    std::cout << "Capacity " << cont1.capacity() << " == " << cont2.capacity() << std::endl;
    EXPECT_EQ(cont1.begin() == cont1.end(), cont2.begin() == cont2.end());
    EXPECT_EQ(cont1.rbegin() == cont1.rend(), cont2.rbegin() == cont2.rend());
    if (cont1.size() || cont2.size()) {
        EXPECT_EQ(cont1.front(), cont2.front());
        std::cout << "front " << cont1.front() << " == " << cont2.front() << std::endl;
        EXPECT_EQ(cont1.back(), cont2.back());
        std::cout << "back " << cont1.back() << " == " << cont2.back() << std::endl;
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
void testListContainersEqual(T const& cont1, U const& cont2) {
    const char *equals = COLOR_RED " == " COLOR_RESET;
    EXPECT_EQ(cont1.empty(), cont2.empty());
    std::cout << "Empty " << cont1.empty() << equals << cont2.empty() << std::endl;
    EXPECT_EQ(cont1.size(), cont2.size());
    std::cout << "Size " << cont1.size() << equals << cont2.size() << std::endl;
    EXPECT_EQ(cont1.begin() == cont1.end(), cont2.begin() == cont2.end());
    EXPECT_EQ(cont1.rbegin() == cont1.rend(), cont2.rbegin() == cont2.rend());
    if (cont1.size() && cont2.size()) {
        EXPECT_EQ(cont1.front(), cont2.front());
        std::cout << "front " << cont1.front() << equals << cont2.front() << std::endl;
        EXPECT_EQ(cont1.back(), cont2.back());
        std::cout << "back " << cont1.back() << equals << cont2.back() << std::endl;
        std::cout << "\ttest and output iterators:" << std::endl;
        typename T::const_iterator it1 = cont1.begin();
        typename U::const_iterator it2 = cont2.begin();
        typename T::size_type i = 0;
        while (it1 != cont1.end() && it2 != cont2.end()) {
            printValues(i++, *it1, *it2);
            ++it1;
            ++it2;
        }
        it1 = cont1.begin();
        it2 = cont2.begin();
        i = 0;
        while (it1 != cont1.end() && it2 != cont2.end()) {
            EXPECT_EQ(*it1, *it2);
            ++it1;
            ++it2;
        }
        EXPECT_EQ(it1 == cont1.end(), it2 == cont2.end());
        std::cout << "\ttest and output reverse iterators:" << std::endl;
        typename T::const_reverse_iterator rit1 = cont1.rbegin();
        typename U::const_reverse_iterator rit2 = cont2.rbegin();
        i = typename T::size_type();
        while (rit1 != cont1.rend() && rit2 != cont2.rend()) {
            printValues(cont2.size() - i - 1, *rit1, *rit2);
            EXPECT_EQ(*rit1, *rit2);
            ++rit1;
            ++rit2;
            ++i;
        }
        EXPECT_EQ(rit1 == cont1.rend(), rit2 == cont2.rend());
        if (it1 != cont1.begin() || rit1 != cont1.rbegin())
            std::cout << std::endl;
    }
}

namespace ft {
    template<class T1, class T2>
    bool operator==(const ft::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template<class T1, class T2>
    bool operator!=(const ft::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) { return !(lhs == rhs); }

    template<class T1, class T2>
    bool operator<(const ft::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template<class T1, class T2>
    bool operator<=(const ft::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) { return !(rhs < lhs); }

    template<class T1, class T2>
    bool operator>(const ft::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) { return rhs < lhs; }

    template<class T1, class T2>
    bool operator>=(const ft::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) { return !(lhs < rhs); }
}

template<typename T, typename U>
void testMapContainersEqual(T const& cont1, U const& cont2) {
    const char *equals = COLOR_RED " == " COLOR_RESET;
    EXPECT_EQ(cont1.empty(), cont2.empty());
    std::cout << "Empty " << cont1.empty() << equals << cont2.empty() << std::endl;
    EXPECT_EQ(cont1.size(), cont2.size());
    std::cout << "Size " << cont1.size() << equals << cont2.size() << std::endl;
    EXPECT_EQ(cont1.begin() == cont1.end(), cont2.begin() == cont2.end());
    EXPECT_EQ(cont1.rbegin() == cont1.rend(), cont2.rbegin() == cont2.rend());
    if (cont1.size() && cont2.size()) {
        std::cout << "\ttest and output iterators:" << std::endl;
        typename T::const_iterator it1 = cont1.begin();
        typename U::const_iterator it2 = cont2.begin();
        typename T::size_type i = 0;
        while (it1 != cont1.end() && it2 != cont2.end()) {
            printValues(i, it1->first, it2->first);
            printValues(i++, it1->second, it2->second);
            EXPECT_EQ(*it1, *it2);
            ++it1;
            ++it2;
        }
        EXPECT_EQ(it1 == cont1.end(), it2 == cont2.end());
        std::cout << "\ttest and output reverse iterators:" << std::endl;
        typename T::const_reverse_iterator rit1 = cont1.rbegin();
        typename U::const_reverse_iterator rit2 = cont2.rbegin();
        i = typename T::size_type();
        while (rit1 != cont1.rend() && rit2 != cont2.rend()) {
            printValues(cont2.size() - i - 1, rit1->first, rit2->first);
            printValues(cont2.size() - i - 1, rit1->second, rit2->second);
            EXPECT_EQ(*rit1, *rit2);
            ++rit1;
            ++rit2;
            ++i;
        }
        EXPECT_EQ(rit1 == cont1.rend(), rit2 == cont2.rend());
        if (it1 != cont1.begin() || rit1 != cont1.rbegin())
            std::cout << std::endl;
    }
}

template<typename T, typename U>
void testContainersEqualNoprint(T const& cont1, U const& cont2) {
    EXPECT_EQ(cont1.empty(), cont2.empty());
    EXPECT_EQ(cont1.size(), cont2.size());
    EXPECT_EQ(cont1.max_size(), cont2.max_size());
    EXPECT_EQ(cont1.capacity(), cont2.capacity());
    EXPECT_EQ(cont1.begin() == cont1.end(), cont2.begin() == cont2.end());
    EXPECT_EQ(cont1.rbegin() == cont1.rend(), cont2.rbegin() == cont2.rend());
    if (cont1.size() || cont2.size()) {
        typename T::const_iterator it1 = cont1.begin();
        typename U::const_iterator it2 = cont2.begin();
        while (it1 != cont1.end() && it2 != cont2.end()) {
            printValues(it1 - cont1.begin(), *it1, *it2);
            EXPECT_EQ(*it1, *it2);
            ++it1;
            ++it2;
        }
        EXPECT_EQ(it1 == cont1.end(), it2 == cont2.end());
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
void printTestName(std::string const& name);

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
T getRandomValue();

template<>
int getRandomValue<int>() {
//    return rand() % 10101010 - rand() % 5050505;
    return rand() % 10000;
}

template<>
float getRandomValue<float>() {
    return rand() % 10101010 / (float)(rand() % 1010101);
}

template<>
std::string getRandomValue<std::string>() {
    const int length = rand() % 35 + 15;
    char str[length + 1];
    str[length] = 0;
    for (int i = 0; i < length; ++i) {
        str[i] = rand() % 94 + 32;
    }
    return std::string(str);
}

template<>
SomeStruct getRandomValue<SomeStruct>() {
    return SomeStruct(getRandomValue<std::string>(), getRandomValue<float>());
}

template<typename T>
void defaultConstructorTest() {
    printTestName<T>("Default constructor");
    ft::vector<T> ftv;
    std::vector<T> stv;
    testEmptyContainersEqual(ftv, stv);
}

template<typename T>
void zeroElementsConstructorTest() {
    printTestName<T>("Constructor for 0 elements");
    ft::vector<T> ftv(0);
    std::vector<T> stv(0);
    testEmptyContainersEqual(ftv, stv);

}

template<typename T>
void twentyElementsConstructorTest() {
    printTestName<T>("Constructor for N elements");
    ft::vector<T> ftv(20);
    std::vector<T> stv(20);
    testContainersEqual(ftv, stv);
}

template<typename T>
void twentyElementsWithDefaultValueConstructorTest() {
    printTestName<T>("Constructor for N elements with value");
    T value = getRandomValue<T>();
    ft::vector<T> ftv(20, value);
    std::vector<T> stv(20, value);
    testContainersEqual(ftv, stv);
}

template<typename T>
void iteratorConstructorTest() {
    printTestName<T>("Constructor for iterators begin and end");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> fiter;
    std::vector<T>   siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value      = getRandomValue<T>();
        fiter.push_back(value);
        siter.push_back(value);
    }

    ft::vector<T> ftv(fiter.begin() + 2, fiter.end() - 3);
    std::vector<T> stv(siter.begin() + 2, siter.end() - 3);
    testContainersEqual(ftv, stv);
}

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
        ft::vector<T>  ftv_o(20);
        std::vector<T> stv_o(20);
        ft::vector<T>  ftv(ftv_o);
        std::vector<T> stv(stv_o);
        testContainersEqual(ftv, stv);
    }
    {
        printTestName<T>("Copy constructor for N elements with value");
        T value = getRandomValue<T>();
        ft::vector<T> ftv_o(20, value);
        std::vector<T> stv_o(20, value);
        ft::vector<T> ftv(ftv_o);
        std::vector<T> stv(stv_o);
        testContainersEqual(ftv, stv);
    }
    {
        printTestName<T>("Copy constructor for iterators begin and end");

        std::size_t numOfItems = rand() % 20 + 10;
        ft::vector<T>    fiter;
        std::vector<T>   siter;
        for (std::size_t i = 0; i < numOfItems; ++i) {
            T value = getRandomValue<T>();
            fiter.push_back(value);
            siter.push_back(value);
        }

        ft::vector<T> ftv_o(fiter.begin() + 2, fiter.end() - 3);
        std::vector<T> stv_o(siter.begin() + 2, siter.end() - 3);

        ft::vector<T> ftv(ftv_o);
        std::vector<T> stv(stv_o);

        testContainersEqual(ftv, stv);
    }
}

template<typename T>
void assignationOperatorToMoreCapTest() {
    printTestName<T>("Assignation operator to the bigger capacity");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> fiter;
    std::vector<T> siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
        siter.push_back(value);
    }

    ft::vector<T> ftv_o(fiter.begin() + 2, fiter.end() - 3);
    std::vector<T> stv_o(siter.begin() + 2, siter.end() - 3);
    ft::vector<T> ftv(fiter.rbegin(), fiter.rend() - 9);
    std::vector<T> stv(siter.rbegin(), siter.rend() - 9);

    ftv = ftv_o;
    stv = stv_o;

    testContainersEqual(ftv, stv);
}


template<typename T>
void assignationOperatorToMoreSizeTest() {
    printTestName<T>("Assignation operator to the bigger size");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> fiter;
    std::vector<T> siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
        siter.push_back(value);
    }

    ft::vector<T> ftv_o(fiter.begin() + 2, fiter.end() - 3);
    std::vector<T> stv_o(siter.begin() + 2, siter.end() - 3);
    ft::vector<T> ftv(fiter.rbegin(), fiter.rend() - 9);
    std::vector<T> stv(siter.rbegin(), siter.rend() - 9);

    ftv.reserve(fiter.size());
    stv.reserve(siter.size());
    ftv = ftv_o;
    stv = stv_o;

    testContainersEqual(ftv, stv);
}

template<typename T>
void assignationOperatorToLessTest() {
    printTestName<T>("Assignation operator to the lesser size");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> fiter;
    std::vector<T> siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
        siter.push_back(value);
    }

    ft::vector<T> ftv_o(fiter.begin() + 5, fiter.end() - 4);
    std::vector<T> stv_o(siter.begin() + 5, siter.end() - 4);
    ft::vector<T> ftv(fiter.rbegin(), fiter.rend() - 2);
    std::vector<T> stv(siter.rbegin(), siter.rend() - 2);

    ftv = ftv_o;
    stv = stv_o;

    testContainersEqual(ftv, stv);
}

template<typename T>
void assignationOperatorToSameTest() {
    printTestName<T>("Assignation operator to the same size");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> fiter;
    std::vector<T> siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
        siter.push_back(value);
    }

    ft::vector<T> ftv_o(fiter.begin() + 5, fiter.end() - 4);
    std::vector<T> stv_o(siter.begin() + 5, siter.end() - 4);
    ft::vector<T> ftv(fiter.rbegin() + 2, fiter.rend() - 7);
    std::vector<T> stv(siter.rbegin() + 2, siter.rend() - 7);

    ftv = ftv_o;
    stv = stv_o;

    testContainersEqual(ftv, stv);
}

template<typename T>
void resizeLessTest() {
    printTestName<T>("Resize to a lesser value");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(ftv, stv);

    ftv.resize(numOfItems - 5);
    stv.resize(numOfItems - 5);

    testContainersEqual(ftv, stv);
}

template<typename T>
void resizeMoreTest() {
    printTestName<T>("Resize to a bigger value");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv(5);
    std::vector<T> stv(5);
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    std::cout << "Initial data: " << std::endl;
    std::cout << "empty: " << ftv.empty() << " | " << stv.empty() << std::endl;
    std::cout << "size: " << ftv.size() << " | " << stv.size() << std::endl;
    std::cout << "capacity: " << ftv.capacity() << " | " << stv.capacity() << std::endl;

    ftv.resize(15 + ftv.capacity());
    stv.resize(15 + stv.capacity());

    std::cout << "Resized data: " << std::endl;
    std::cout << "empty: " << ftv.empty() << " | " << stv.empty() << std::endl;
    std::cout << "size: " << ftv.size() << " | " << stv.size() << std::endl;
    std::cout << "capacity: " << ftv.capacity() << " | " << stv.capacity() << std::endl;

    testContainersEqual(ftv, stv);
}

template<typename T>
void resizeSameTest() {
    printTestName<T>("Resize to the same value");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(ftv, stv);

    ftv.resize(ftv.size());
    stv.resize(stv.size());

    testContainersEqual(ftv, stv);
}

template<typename T>
void reserveLessTest() {
    printTestName<T>("Reserve lesser capacity");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    typename ft::vector<T>::iterator fit_before = ftv.begin();
    typename std::vector<T>::iterator sit_before = stv.begin();

    testContainersEqual(ftv, stv);

    ftv.reserve(ftv.capacity() / 2);
    stv.reserve(stv.capacity() / 2);

    testContainersEqual(ftv, stv);
    EXPECT_EQ(fit_before == ftv.begin(), sit_before == stv.begin());
}

template<typename T>
void reserveMoreTest() {
    printTestName<T>("Reserve bigger capacity");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    typename ft::vector<T>::iterator fit_before = ftv.begin();
    typename std::vector<T>::iterator sit_before = stv.begin();

    testContainersEqual(ftv, stv);

    ftv.reserve(ftv.capacity() * 2);
    stv.reserve(stv.capacity() * 2);

    testContainersEqual(ftv, stv);
    EXPECT_EQ(fit_before == ftv.begin(), sit_before == stv.begin());
}

template<typename T>
void reserveSameTest() {
    printTestName<T>("Reserve the same capacity");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    typename ft::vector<T>::iterator fit_before = ftv.begin();
    typename std::vector<T>::iterator sit_before = stv.begin();

    testContainersEqual(ftv, stv);

    ftv.reserve(ftv.capacity());
    stv.reserve(stv.capacity());

    testContainersEqual(ftv, stv);
    EXPECT_EQ(fit_before == ftv.begin(), sit_before == stv.begin());
}

template<typename T>
void reserveGreaterThanMaxTest() {
    printTestName<T>("Reserver to capacity bigger than max_size");

    ft::vector<T> ftv(0);
    std::vector<T> stv(0);

    std::string ferr = "success";
    std::string serr = "success";
    try {
        ftv.reserve(ftv.max_size() + 1);
    }
    catch (std::length_error &e) {
        ferr = e.what();
    }
    try {
        stv.reserve(stv.max_size() + 1);
    }
    catch (std::length_error &e) {
        serr = e.what();
    }

    testContainersEqual(ftv, stv);
    EXPECT_EQ(ferr, serr);
}

template<typename T>
void OperatorBracketsAccessTest() {
    printTestName<T>("Testing operator[]");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(ftv, stv);

    std::size_t i = 0;

    while (i < ftv.size() && i < stv.size()) {
        EXPECT_EQ(ftv[i], stv[i]);
        ++i;
    }
}

template<typename T>
void FunctionAtTest() {
    printTestName<T>("Testing function at");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(ftv, stv);

    std::size_t i = 0;

    while (i < ftv.size() && i < stv.size()) {
        EXPECT_EQ(ftv.at(i), stv.at(i));
        ++i;
    }
    for (int j = 0; j < 5; ++j) {
        std::string ferr = "success";
        std::string serr = "success";
        try { ftv.at(i); }
        catch (std::out_of_range &e) { ferr = e.what(); }
        try { stv.at(i); }
        catch (std::out_of_range &e) { serr = e.what(); }
        EXPECT_EQ(ferr, serr);
        ++i;
    }
    ftv.clear();
    stv.clear();
    std::string ferr = "success";
    std::string serr = "success";
    try { ftv.at(0); }
    catch (std::out_of_range &e) { ferr = e.what(); }
    try { stv.at(0); }
    catch (std::out_of_range &e) { serr = e.what(); }
    EXPECT_EQ(ferr, serr);
}

template<typename T>
void FunctionFrontTest() {
    printTestName<T>("Testing function front");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(ftv, stv);
    EXPECT_EQ(ftv.front(), stv.front());
}

template<typename T>
void FunctionBackTest() {
    printTestName<T>("Testing function back");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(ftv, stv);
    EXPECT_EQ(ftv.back(), stv.back());
}

template<typename T>
void AssignFillLessTest() {
    printTestName<T>("Testing assign with size lesser than cap");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(ftv, stv);

    T value = getRandomValue<T>();
    ftv.assign(ftv.capacity() * .7, value);
    stv.assign(stv.capacity() * .7, value);

    testContainersEqual(ftv, stv);
}

template<typename T>
void AssignFillBetweenSizeCapTest() {
    printTestName<T>("Testing assign with size between size and cap");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(ftv, stv);

    ftv.resize(ftv.capacity() * 2);
    stv.resize(stv.capacity() * 2);
    T value = getRandomValue<T>();
    ftv.assign(ftv.capacity() * 1.5, value);
    stv.assign(stv.capacity() * 1.5, value);

    testContainersEqual(ftv, stv);
}

template<typename T>
void AssignFillMoreTest() {
    printTestName<T>("Testing assign with size more than cap");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(ftv, stv);

    T value = getRandomValue<T>();
    ftv.assign(ftv.capacity() * 1.6, value);
    stv.assign(stv.capacity() * 1.6, value);

    testContainersEqual(ftv, stv);
}

template<typename T>
void AssignFillMaxSizeTest() {
    printTestName<T>("Testing assign with maximum size");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(ftv, stv);

    bool serr = false, ferr = serr;
    std::string fmsg = "success";
    std::string smsg = "success";
    T value = getRandomValue<T>();
    try {
        ftv.assign(ftv.max_size(), value);
    } catch(std::exception& e) { fmsg = e.what(); ferr = true; }
    try {
        stv.assign(stv.max_size(), value);
    } catch(std::exception& e) { smsg = e.what(); serr = true; }
    EXPECT_EQ(ferr, serr);
    EXPECT_EQ(fmsg, smsg);
    testContainersEqual(ftv, stv);
}

template<typename T>
void AssignFillMoreThanMaxTest() {
    printTestName<T>("Testing assign with size more than the maximum cap");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(ftv, stv);

    bool err = false;
    std::string fmsg = "success";
    std::string smsg = "success";
    T value = getRandomValue<T>();
    try {
        ftv.assign(ftv.max_size() + 1, value);
    } catch(std::exception& e) { fmsg = e.what(); err = true; }
    try {
        stv.assign(stv.max_size() + 1, value);
    } catch(std::exception& e) { smsg = e.what(); err = true; }

    EXPECT_EQ(fmsg, smsg);
    testContainersEqual(ftv, stv);

    value = getRandomValue<T>();
    ftv.push_back(value);
    stv.push_back(value);

    testContainersEqual(ftv, stv);
}

template<typename T>
void AssignFillSameTest() {
    printTestName<T>("Testing assign with same size as cap");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(ftv, stv);

    T value = getRandomValue<T>();
    ftv.assign(ftv.capacity(), value);
    stv.assign(stv.capacity(), value);

    testContainersEqual(ftv, stv);
}

template<typename T>
void PushBackTest() {
    printTestName<T>("Testing push back on empty container with few values");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(ftv, stv);
}

template<typename T>
void PopBackTest() {
    printTestName<T>("Testing pop back on small container size with every delete state check (overkill?)");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }

    while (!(ftv.empty() || stv.empty())) {
        ftv.pop_back();
        stv.pop_back();
        testContainersEqual(ftv, stv);
    }

    testContainersEqual(ftv, stv);
}

template<typename T>
void SwapTest() {
    printTestName<T>("Testing swap for a slightly filled container");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(ftv, stv);

    ft::vector<T> ftv_sw;
    std::vector<T> stv_sw;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv_sw.push_back(value);
        stv_sw.push_back(value);
    }
    testContainersEqualNoprint(ftv_sw, stv_sw);

    ft::swap(ftv, ftv_sw);
    std::swap(stv, stv_sw);

    testContainersEqualNoprint(ftv_sw, stv_sw);
    testContainersEqual(ftv, stv);
}

template<typename T>
void SwapOneEmptyTest() {
    printTestName<T>("Testing swap with one of containers initially empty");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(ftv, stv);

    ft::vector<T> ftv_sw;
    std::vector<T> stv_sw;
    testContainersEqualNoprint(ftv_sw, stv_sw);

    ft::swap(ftv, ftv_sw);
    std::swap(stv, stv_sw);

    testContainersEqual(ftv_sw, stv_sw);
    testContainersEqual(ftv, stv);
}

template<typename T>
void SwapOneClearedTest() {
    printTestName<T>("Testing swap with one of containers cleared");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(ftv, stv);

    ft::vector<T> ftv_sw;
    std::vector<T> stv_sw;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv_sw.push_back(value);
        stv_sw.push_back(value);
    }
    ftv_sw.clear();
    stv_sw.clear();
    testContainersEqualNoprint(ftv_sw, stv_sw);

    ft::swap(ftv, ftv_sw);
    std::swap(stv, stv_sw);

    testContainersEqual(ftv_sw, stv_sw);
    testContainersEqual(ftv, stv);
}

template<typename T>
void SwapEmptyTest() {
    printTestName<T>("Testing swap with both containers initially empty");

    ft::vector<T> ftv;
    std::vector<T> stv;
    testContainersEqualNoprint(ftv, stv);

    ft::vector<T> ftv_sw;
    std::vector<T> stv_sw;
    testContainersEqualNoprint(ftv_sw, stv_sw);

    ft::swap(ftv, ftv_sw);
    std::swap(stv, stv_sw);

    testContainersEqual(ftv_sw, stv_sw);
    testContainersEqual(ftv, stv);
}

template<typename T>
void SwapClearedTest() {
    printTestName<T>("Testing swap with both containers cleared");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }
    ftv.clear();
    stv.clear();
    testContainersEqualNoprint(ftv, stv);

    ft::vector<T> ftv_sw;
    std::vector<T> stv_sw;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv_sw.push_back(value);
        stv_sw.push_back(value);
    }
    ftv_sw.clear();
    stv_sw.clear();
    testContainersEqualNoprint(ftv_sw, stv_sw);

    ft::swap(ftv, ftv_sw);
    std::swap(stv, stv_sw);

    testContainersEqual(ftv_sw, stv_sw);
    testContainersEqual(ftv, stv);
}

template<typename T>
void ClearTest() {
    printTestName<T>("Testing clear on slightly filled container");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(ftv, stv);

    ftv.clear();
    stv.clear();
    testContainersEqual(ftv, stv);
}

template<typename T>
void ClearEmptyTest() {
    printTestName<T>("Testing clear on initially empty container");

    ft::vector<T> ftv;
    std::vector<T> stv;
    testContainersEqualNoprint(ftv, stv);

    ftv.clear();
    stv.clear();
    testContainersEqual(ftv, stv);
}

template<typename T>
void ClearDoubleTest() {
    printTestName<T>("Testing clear on already cleared container");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(ftv, stv);

    ftv.clear();
    stv.clear();
    testContainersEqualNoprint(ftv, stv);

    ftv.clear();
    stv.clear();
    testContainersEqual(ftv, stv);
}

template<typename T>
void InsertTest() {
    printTestName<T>("Testing insert single value into container");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(ftv, stv);

    T value = getRandomValue<T>();
    ftv.insert(++++++++ftv.begin(), value);
    stv.insert(++++++++stv.begin(), value);
    value = getRandomValue<T>();
    ftv.insert(----------------ftv.end(), value);
    stv.insert(----------------stv.end(), value);
    testContainersEqual(ftv, stv);
}

template<typename T>
void InsertMultipleTest() {
    printTestName<T>("Testing insert multiple copies of value into container");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(ftv, stv);

    T value = getRandomValue<T>();
    ftv.insert(++++++++ftv.begin(), 12, value);
    stv.insert(++++++++stv.begin(), 12, value);
    value = getRandomValue<T>();
    ftv.insert(--------------------ftv.end(), 7, value);
    stv.insert(--------------------stv.end(), 7, value);
    testContainersEqual(ftv, stv);
}

template<typename T>
void InsertRangeTest() {
    printTestName<T>("Testing insert iterators range into container");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    std::vector<T> range;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
        range.push_back(value);
    }
    testContainersEqualNoprint(ftv, stv);

    ftv.insert(++++++++ftv.begin(), range.begin(), range.end());
    stv.insert(++++++++stv.begin(), range.begin(), range.end());
    ftv.insert(----------------ftv.end(), ++++++++range.begin(), ----range.end());
    stv.insert(----------------stv.end(), ++++++++range.begin(), ----range.end());
    testContainersEqual(ftv, stv);
}

template<typename T>
void EraseTest() {
    printTestName<T>("Testing erase single value from container");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(ftv, stv);

    auto ferend = ftv.erase(++++++++ftv.begin());
    auto serend = stv.erase(++++++++stv.begin());
    EXPECT_EQ(*ferend, *serend);
    ferend = ftv.erase(----------------ftv.end());
    serend = stv.erase(----------------stv.end());
    EXPECT_EQ(*ferend, *serend);
    testContainersEqual(ftv, stv);
}

template<typename T>
void EraseRangeTest() {
    printTestName<T>("Testing erase range of values from container");

    std::size_t numOfItems = rand() % 20 + 20;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(ftv, stv);

    auto ferend = ftv.erase(++++++++++++++ftv.begin(), ------ftv.end());
    auto serend = stv.erase(++++++++++++++stv.begin(), ------stv.end());
    EXPECT_EQ(*ferend, *serend);
    ferend = ftv.erase(----------------ftv.end(), ftv.end());
    serend = stv.erase(----------------stv.end(), stv.end());
    EXPECT_EQ(*--ferend, *--serend);
    testContainersEqual(ftv, stv);
}

template<typename T>
void defaultListConstructorTest() {
    printTestName<T>("Default constructor");
    ft::list<T> ftv;
    std::list<T> stv;
    testListContainersEqual(ftv, stv);
}

template<typename T>
void zeroElementsListConstructorTest() {
    printTestName<T>("Constructor for 0 elements");
    ft::list<T> ftv(0);
    std::list<T> stv(0);
    testListContainersEqual(ftv, stv);

}

template<typename T>
void twentyElementsListConstructorTest() {
    printTestName<T>("Constructor for N elements");
    ft::list<T> ftv(20);
    std::list<T> stv(20);
    testListContainersEqual(ftv, stv);
}

template<typename T>
void twentyElementsWithDefaultValueListConstructorTest() {
    printTestName<T>("Constructor for N elements with value");
    T value = getRandomValue<T>();
    ft::list<T> ftv(20, value);
    std::list<T> stv(20, value);
    testListContainersEqual(ftv, stv);
}

template<typename T>
void iteratorListConstructorTest() {
    printTestName<T>("Constructor for iterators begin and end");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::list<T> fiter;
    std::list<T>   siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value      = getRandomValue<T>();
        fiter.push_back(value);
        siter.push_back(value);
    }

    typename ft::list<T>::iterator lit = fiter.begin();
    ft::advance(lit, 2);
    typename ft::list<T>::iterator rit = fiter.begin();
    ft::advance(rit, -3);
    ft::list<T> ftv(lit, rit);
    typename std::list<T>::iterator lsit = siter.begin();
    ft::advance(lsit, 2);
    typename std::list<T>::iterator rsit = siter.begin();
    ft::advance(rsit, -3);
    std::list<T> stv(lsit, rsit);
    testListContainersEqual(ftv, stv);
}

template<typename T>
void copyListConstructorTest() {
    {
        printTestName<T>("Copy constructor for default container");
        ft::list<T> ftv_o;
        std::list<T> stv_o;
        ft::list<T> ftv(ftv_o);
        std::list<T> stv(stv_o);
        testListContainersEqual(ftv, stv);
    }
    {
        printTestName<T>("Copy constructor for 0 elements");
        ft::list<T> ftv_o(0);
        std::list<T> stv_o(0);
        ft::list<T> ftv(ftv_o);
        std::list<T> stv(stv_o);
        testListContainersEqual(ftv, stv);
    }
    {
        printTestName<T>("Copy constructor for N elements");
        ft::list<T>  ftv_o(20);
        std::list<T> stv_o(20);
        ft::list<T>  ftv(ftv_o);
        std::list<T> stv(stv_o);
        testListContainersEqual(ftv, stv);
    }
    {
        printTestName<T>("Copy constructor for N elements with value");
        T value = getRandomValue<T>();
        ft::list<T> ftv_o(20, value);
        std::list<T> stv_o(20, value);
        ft::list<T> ftv(ftv_o);
        std::list<T> stv(stv_o);
        testListContainersEqual(ftv, stv);
    }
    {
        printTestName<T>("Copy constructor for iterators begin and end");

        std::size_t numOfItems = rand() % 20 + 10;
        ft::list<T>    fiter;
        std::list<T>   siter;
        for (std::size_t i = 0; i < numOfItems; ++i) {
            T value = getRandomValue<T>();
            fiter.push_back(value);
            siter.push_back(value);
        }

        typename ft::list<T>::iterator lit = fiter.begin();
        ft::advance(lit, 2);
        typename ft::list<T>::iterator rit = fiter.begin();
        ft::advance(rit, -3);
        ft::list<T> ftv_o(lit, rit);
        typename std::list<T>::iterator lsit = siter.begin();
        ft::advance(lsit, 2);
        typename std::list<T>::iterator rsit = siter.begin();
        ft::advance(rsit, -3);
        std::list<T> stv_o(lsit, rsit);

        ft::list<T> ftv(ftv_o);
        std::list<T> stv(stv_o);

        testListContainersEqual(ftv, stv);
    }
}

template<typename T>
void listAssignationBothEmptyTest() {
    printTestName<T>("List Assignation operator of empty lists");

    ft::list<T> ftv_o;
    std::list<T> stv_o;
    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv, stv);

    ftv = ftv_o;
    stv = stv_o;

    testListContainersEqual(ftv, stv);
}

template<typename T>
void listAssignationBothNotEmptyTest() {
    printTestName<T>("List Assignation operator of non empty lists");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> fiter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
    }

    ft::list<T> ftv_o(fiter.begin() + 2, fiter.end() - 3);
    std::list<T> stv_o(fiter.begin() + 2, fiter.end() - 3);
    ft::list<T> ftv(fiter.rbegin(), fiter.rend() - 9);
    std::list<T> stv(fiter.rbegin(), fiter.rend() - 9);

    testListContainersEqual(ftv_o, stv_o);
    testListContainersEqual(ftv, stv);

    ftv = ftv_o;
    stv = stv_o;

    testListContainersEqual(ftv, stv);
}

template<typename T>
void listAssignationToEmptyTest() {
    printTestName<T>("List Assignation operator to empty lists");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> fiter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
    }

    ft::list<T> ftv_o(fiter.begin() + 2, fiter.end() - 3);
    std::list<T> stv_o(fiter.begin() + 2, fiter.end() - 3);
    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv_o, stv_o);
    testListContainersEqual(ftv, stv);

    ftv = ftv_o;
    stv = stv_o;

    testListContainersEqual(ftv, stv);
}

template<typename T>
void listAssignationFromEmptyTest() {
    printTestName<T>("List Assignation operator From empty lists");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> fiter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
    }

    ft::list<T> ftv_o;
    std::list<T> stv_o;
    ft::list<T> ftv(fiter.rbegin(), fiter.rend() - 9);
    std::list<T> stv(fiter.rbegin(), fiter.rend() - 9);

    testListContainersEqual(ftv_o, stv_o);
    testListContainersEqual(ftv, stv);

    ftv = ftv_o;
    stv = stv_o;

    testListContainersEqual(ftv, stv);
}

template<typename T>
void listAssignationFunctionBothEmptyTest() {
    printTestName<T>("List Assignation function of empty lists");

    ft::list<T> ftv_o;
    std::list<T> stv_o;
    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv, stv);

    ftv.assign(ftv_o.begin(), ftv_o.end());
    stv.assign(stv_o.begin(), stv_o.end());

    testListContainersEqual(ftv, stv);
}

template<typename T>
void listAssignationFunctionBothNotEmptyTest() {
    printTestName<T>("List Assignation function of non empty lists");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> fiter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
    }

    ft::list<T> ftv_o(fiter.begin() + 2, fiter.end() - 3);
    std::list<T> stv_o(fiter.begin() + 2, fiter.end() - 3);
    ft::list<T> ftv(fiter.rbegin(), fiter.rend() - 9);
    std::list<T> stv(fiter.rbegin(), fiter.rend() - 9);

    testListContainersEqual(ftv_o, stv_o);
    testListContainersEqual(ftv, stv);

    ftv.assign(ftv_o.begin(), ftv_o.end());
    stv.assign(stv_o.begin(), stv_o.end());

    testListContainersEqual(ftv, stv);
}

template<typename T>
void listAssignationFunctionToEmptyTest() {
    printTestName<T>("List Assignation function to empty lists");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> fiter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
    }

    ft::list<T> ftv_o(fiter.begin() + 2, fiter.end() - 3);
    std::list<T> stv_o(fiter.begin() + 2, fiter.end() - 3);
    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv_o, stv_o);
    testListContainersEqual(ftv, stv);

    ftv.assign(ftv_o.begin(), ftv_o.end());
    stv.assign(stv_o.begin(), stv_o.end());

    testListContainersEqual(ftv, stv);
}

template<typename T>
void listAssignationFunctionFromEmptyTest() {
    printTestName<T>("List Assignation function From empty lists");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> fiter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
    }

    ft::list<T> ftv_o;
    std::list<T> stv_o;
    ft::list<T> ftv(fiter.rbegin(), fiter.rend() - 9);
    std::list<T> stv(fiter.rbegin(), fiter.rend() - 9);

    testListContainersEqual(ftv_o, stv_o);
    testListContainersEqual(ftv, stv);

    ftv.assign(ftv_o.begin(), ftv_o.end());
    stv.assign(stv_o.begin(), stv_o.end());

    testListContainersEqual(ftv, stv);
}

template<typename T>
void listAssignationFunctionSizeZeroTest() {
    printTestName<T>("List Assignation function with size 0 and default value");

    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv, stv);

    ftv.assign(0, T());
    stv.assign(0, T());

    testListContainersEqual(ftv, stv);
}

template<typename T>
void listAssignationFunctionSizeZeroValTest() {
    printTestName<T>("List Assignation function with size 0 and random value");

    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv, stv);

    T val = getRandomValue<T>();
    ftv.assign(0, val);
    stv.assign(0, val);

    testListContainersEqual(ftv, stv);
}

template<typename T>
void listAssignationFunctionSizeNoValTest() {
    printTestName<T>("List Assignation function with random size and default value");

    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv, stv);

    int size = rand() % 20 + 10;
    ftv.assign(size, T());
    stv.assign(size, T());

    testListContainersEqual(ftv, stv);
}

template<typename T>
void listAssignationFunctionSizeValTest() {
    printTestName<T>("List Assignation function with random size and random value");

    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv, stv);

    int size = rand() % 20 + 10;
    T val = getRandomValue<T>();
    ftv.assign(size, val);
    stv.assign(size, val);

    testListContainersEqual(ftv, stv);
}

template<typename T>
void listPushPopFrontTest() {
    printTestName<T>("List push_front some values, then pop_front values until empty with middle checks");

    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv, stv);
    int size = rand() % 20 + 20;
    int i = 0;
    for (; i < size / 2; ++i) {
        T val = getRandomValue<T>();
        ftv.push_front(val);
        stv.push_front(val);
    }
    testListContainersEqual(ftv, stv);
    for (; i < size; ++i) {
        T val = getRandomValue<T>();
        ftv.push_front(val);
        stv.push_front(val);
    }
    testListContainersEqual(ftv, stv);
    for (i = 0; i < size / 3; ++i) {
        ftv.pop_front();
        stv.pop_front();
    }
    testListContainersEqual(ftv, stv);
    for (; i < size; ++i) {
        ftv.pop_front();
        stv.pop_front();
    }
    testListContainersEqual(ftv, stv);
}

template<typename T>
void listPushPopBackTest() {
    printTestName<T>("List push_back some values, then pop_back values until empty with middle checks");

    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv, stv);
    int size = rand() % 20 + 20;
    int i = 0;
    for (; i < size / 2; ++i) {
        T val = getRandomValue<T>();
        ftv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(ftv, stv);
    for (; i < size; ++i) {
        T val = getRandomValue<T>();
        ftv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(ftv, stv);
    for (i = 0; i < size / 3; ++i) {
        ftv.pop_back();
        stv.pop_back();
    }
    testListContainersEqual(ftv, stv);
    for (; i < size; ++i) {
        ftv.pop_back();
        stv.pop_back();
    }
    testListContainersEqual(ftv, stv);
}

template<typename T>
void listPushFrontPopBackTest() {
    printTestName<T>("List push_front some values, then pop_back values until empty with middle checks");

    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv, stv);
    int size = rand() % 20 + 20;
    int i = 0;
    for (; i < size / 2; ++i) {
        T val = getRandomValue<T>();
        ftv.push_front(val);
        stv.push_front(val);
    }
    testListContainersEqual(ftv, stv);
    for (; i < size; ++i) {
        T val = getRandomValue<T>();
        ftv.push_front(val);
        stv.push_front(val);
    }
    testListContainersEqual(ftv, stv);
    for (i = 0; i < size / 3; ++i) {
        ftv.pop_back();
        stv.pop_back();
    }
    testListContainersEqual(ftv, stv);
    for (; i < size; ++i) {
        ftv.pop_back();
        stv.pop_back();
    }
    testListContainersEqual(ftv, stv);
}

template<typename T>
void listPushBackPopFrontTest() {
    printTestName<T>("List push_back some values, then pop_front values until empty with middle checks");

    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv, stv);
    int size = rand() % 20 + 20;
    int i = 0;
    for (; i < size / 2; ++i) {
        T val = getRandomValue<T>();
        ftv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(ftv, stv);
    for (; i < size; ++i) {
        T val = getRandomValue<T>();
        ftv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(ftv, stv);
    for (i = 0; i < size / 3; ++i) {
        ftv.pop_front();
        stv.pop_front();
    }
    testListContainersEqual(ftv, stv);
    for (; i < size; ++i) {
        ftv.pop_front();
        stv.pop_front();
    }
    testListContainersEqual(ftv, stv);
}

template<typename T>
void listInsertSingleValuesTest() {
    printTestName<T>("List inset single values into different positions");

    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv, stv);

    int size = rand() % 10 + 10;
    ftv.insert(ftv.end(), T());
    stv.insert(stv.end(), T());
    ftv.insert(ftv.begin(), T());
    stv.insert(stv.begin(), T());
    for (int i = 2; i < size; ++i) {
        T val = getRandomValue<T>();
        ftv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(ftv, stv);

    typename ft::list<T>::iterator fit;
    typename std::list<T>::iterator sit;
    for (int i = 0; i < 8; ++i) {
        int position = rand() % (size + i + 1);
        T value = getRandomValue<T>();
        fit = ftv.begin();
        ft::advance(fit, position);
        typename ft::list<T>::iterator fret = ftv.insert(fit, value);
        EXPECT_EQ(--fit, fret);
        sit = stv.begin();
        while (position--)
            ++sit;
        typename std::list<T>::iterator sret = stv.insert(sit, value);
        EXPECT_EQ(--sit, sret);
    }
    testListContainersEqual(ftv, stv);
}

template<typename T>
void listInsertSeveralValuesTest() {
    printTestName<T>("List inset multiple values into different positions");

    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv, stv);

    int size = rand() % 10 + 10;
    for (int i = 0; i < size; ++i) {
        T val = getRandomValue<T>();
        ftv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(ftv, stv);

    typename ft::list<T>::iterator fit;
    typename std::list<T>::iterator sit;
    for (int i = 0; i < 8; ++i) {
        int position = rand() % (size + i + 1);
        int amount = rand() % 5 + 1;
        T value = getRandomValue<T>();
        fit = ftv.begin();
        ft::advance(fit, position);
        ftv.insert(fit, amount, value);
        sit = stv.begin();
        while (position--)
            ++sit;
        stv.insert(sit, amount, value);
    }
    testListContainersEqual(ftv, stv);
}

template<typename T>
void listInsertIteratorPointedValuesTest() {
    printTestName<T>("List inset iterated data into different positions");

    const int data_len = 20;
    T data[data_len];
    for (int i = 0; i < data_len; ++i) {
        data[i] = getRandomValue<T>();
    }

    ft::list<T> ftv;
    std::list<T> stv;

    testListContainersEqual(ftv, stv);

    int size = rand() % 10 + 10;
    for (int i = 0; i < size; ++i) {
        T val = getRandomValue<T>();
        ftv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(ftv, stv);

    typename ft::list<T>::iterator fit;
    typename std::list<T>::iterator sit;
    for (int i = 0; i < 8; ++i) {
        int position = rand() % (size + i + 1);
        int iter_start = rand() % data_len;
        int iter_end = rand() % data_len;
        if (iter_start > iter_end)
            ft::swap(iter_start, iter_end);
        fit = ftv.begin();
        ft::advance(fit, position);
        ftv.insert(fit, ft::input_iterator<T>(data + iter_start), ft::input_iterator<T>(data + iter_end));
        sit = stv.begin();
        while (position--)
            ++sit;
        stv.insert(sit, ft::input_iterator<T>(data + iter_start), ft::input_iterator<T>(data + iter_end));
    }
    testListContainersEqual(ftv, stv);
}

template<typename T>
void listEraseSingleValuesTest() {
    printTestName<T>("List erase single values from different positions");

    ft::list<T> ftv;
    std::list<T> stv;

    int size = rand() % 50 + 50;
    for (int i = 0; i < size; ++i) {
        T val = getRandomValue<T>();
        ftv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(ftv, stv);

    typename ft::list<T>::iterator fit;
    typename std::list<T>::iterator sit;
    for (int i = 0; i < 25; ++i) {
        int position = rand() % (ftv.size() - 10);
        fit = ftv.begin();
        ft::advance(fit, position);
        sit = stv.begin();
        while (position--)
            ++sit;
        typename ft::list<T>::iterator ffin;
        typename std::list<T>::iterator sfin;
        typename ft::list<T>::iterator ffinpre = fit;
        --ffinpre;
        typename std::list<T>::iterator sfinpre = sit;
        --sfinpre;
        ffin = ftv.erase(fit);
        sfin = stv.erase(sit);
        EXPECT_EQ(ffin, ++ffinpre);
        EXPECT_EQ(sfin, ++sfinpre);
    }
    testListContainersEqual(ftv, stv);
}

template<typename T>
void listEraseIteratorPointedValuesTest() {
    printTestName<T>("List erase iterated data from different positions");

    ft::list<T> ftv;
    std::list<T> stv;

    int size = rand() % 50 + 50;
    for (int i = 0; i < size; ++i) {
        T val = getRandomValue<T>();
        ftv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(ftv, stv);

    typename ft::list<T>::iterator fitst;
    typename ft::list<T>::iterator fiten;
    typename std::list<T>::iterator sitst;
    typename std::list<T>::iterator siten;
    for (int i = 0; i < 4; ++i) {
        int iter_start = rand() % (ftv.size() - 10);
        int iter_end = rand() % 10;
        fitst = ftv.begin();
        ft::advance(fitst, iter_start);
        fiten = fitst;
        ft::advance(fiten, iter_end);
        sitst = stv.begin();
        while (iter_start--)
            ++sitst;
        siten = sitst;
        while (iter_end--)
            ++siten;
        typename ft::list<T>::iterator ffin;
        typename std::list<T>::iterator sfin;
        typename ft::list<T>::iterator ffinpre = fitst;
        ffinpre--;
        typename std::list<T>::iterator sfinpre = sitst;
        sfinpre--;
        ffin = ftv.erase(fitst, fiten);
        sfin = stv.erase(sitst, siten);
        EXPECT_EQ(ffin, ++ffinpre);
        EXPECT_EQ(sfin, ++sfinpre);
    }
    testListContainersEqual(ftv, stv);
}

template<typename T>
void listSwapTest() {
    printTestName<T>("Testing list swap");
    ft::list<T> ftlist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ft::list<T> ftlist2;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        ftlist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
    ftlist.swap(ftlist2);
    stdlist.swap(stdlist2);
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
}

template<typename T>
void listSwapLEmptyTest() {
    printTestName<T>("Testing list swap");
    ft::list<T> ftlist;
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ft::list<T> ftlist2;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        ftlist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
    ftlist.swap(ftlist2);
    stdlist.swap(stdlist2);
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
}

template<typename T>
void listSwapREmptyTest() {
    printTestName<T>("Testing list swap");
    ft::list<T> ftlist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ft::list<T> ftlist2;
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
    ftlist.swap(ftlist2);
    stdlist.swap(stdlist2);
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
}

template<typename T>
void listSwapBothEmptyTest() {
    printTestName<T>("Testing list swap");
    ft::list<T> ftlist;
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ft::list<T> ftlist2;
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
    ftlist.swap(ftlist2);
    stdlist.swap(stdlist2);
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
}

template<typename T>
void listNonMemberSwapTest() {
    printTestName<T>("Testing list non-member swap");
    ft::list<T> ftlist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ft::list<T> ftlist2;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        ftlist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
    ft::swap(ftlist, ftlist2);
    std::swap(stdlist, stdlist2);
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
}

template<typename T>
void listNonMemberSwapLEmptyTest() {
    printTestName<T>("Testing list non-member swap");
    ft::list<T> ftlist;
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ft::list<T> ftlist2;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        ftlist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
    ft::swap(ftlist, ftlist2);
    std::swap(stdlist, stdlist2);
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
}

template<typename T>
void listNonMemberSwapREmptyTest() {
    printTestName<T>("Testing list non-member swap");
    ft::list<T> ftlist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ft::list<T> ftlist2;
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
    ft::swap(ftlist, ftlist2);
    std::swap(stdlist, stdlist2);
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
}

template<typename T>
void listNonMemberSwapBothEmptyTest() {
    printTestName<T>("Testing list non-member swap");
    ft::list<T> ftlist;
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ft::list<T> ftlist2;
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
    ft::swap(ftlist, ftlist2);
    std::swap(stdlist, stdlist2);
    testListContainersEqual(ftlist, stdlist);
    testListContainersEqual(ftlist2, stdlist2);
}

template<typename T>
void listResizeWithoutDefaultTest() {
    printTestName<T>("Testing list resize without default value");
    ft::list<T> ftlist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    testListContainersEqual(ftlist, stdlist);
    ftlist.resize(50);
    stdlist.resize(50);
    testListContainersEqual(ftlist, stdlist);
    ftlist.resize(12);
    stdlist.resize(12);
    testListContainersEqual(ftlist, stdlist);
    ftlist.resize(27);
    stdlist.resize(27);
    testListContainersEqual(ftlist, stdlist);
    ftlist.resize(0);
    stdlist.resize(0);
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listResizeWithDefaultTest() {
    printTestName<T>("Testing list resize with default value");
    ft::list<T> ftlist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    testListContainersEqual(ftlist, stdlist);
    T value = getRandomValue<T>();
    ftlist.resize(50, value);
    stdlist.resize(50, value);
    testListContainersEqual(ftlist, stdlist);
    value = getRandomValue<T>();
    ftlist.resize(12, value);
    stdlist.resize(12, value);
    testListContainersEqual(ftlist, stdlist);
    value = getRandomValue<T>();
    ftlist.resize(0, value);
    stdlist.resize(0, value);
    testListContainersEqual(ftlist, stdlist);
    value = getRandomValue<T>();
    ftlist.resize(27, value);
    stdlist.resize(27, value);
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listClearTest() {
    printTestName<T>("Testing clear on empty and not empty list");
    ft::list<T> ftlist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    testListContainersEqual(ftlist, stdlist);
    ftlist.clear();
    stdlist.clear();
    testListContainersEqual(ftlist, stdlist);
    ftlist.clear();
    stdlist.clear();
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listSpliceBeginTest() {
    printTestName<T>("Testing list splice full list into begin");
    ft::list<T> ftlist;
    ft::list<T> ftlist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    typename ft::list<T>::iterator fit = ftlist.begin();
    typename std::list<T>::iterator sit = stdlist.begin();
    ftlist.splice(fit, ftlist2);
    stdlist.splice(sit, stdlist2);
    testListContainersEqual(ftlist, stdlist);
    ftlist.splice(fit, ftlist2);
    stdlist.splice(sit, stdlist2);
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listSpliceEndTest() {
    printTestName<T>("Testing list splice full list into end");
    ft::list<T> ftlist;
    ft::list<T> ftlist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    typename ft::list<T>::iterator fit = ftlist.end();
    typename std::list<T>::iterator sit = stdlist.end();
    ftlist.splice(fit, ftlist2);
    stdlist.splice(sit, stdlist2);
    testListContainersEqual(ftlist, stdlist);
    ftlist.splice(fit, ftlist2);
    stdlist.splice(sit, stdlist2);
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listSpliceRandomTest() {
    printTestName<T>("Testing list splice full list into random position");
    ft::list<T> ftlist;
    ft::list<T> ftlist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    int position = rand() % (ftlist.size() - 1) + 1;
    typename ft::list<T>::iterator fit = ftlist.begin();
    ft::advance(fit, position);
    typename std::list<T>::iterator sit = stdlist.begin();
    for (int i = position; i--;)
        ++sit;
    ftlist.splice(fit, ftlist2);
    stdlist.splice(sit, stdlist2);
    testListContainersEqual(ftlist, stdlist);
    ftlist.splice(fit, ftlist2);
    stdlist.splice(sit, stdlist2);
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listSpliceOneBeginTest() {
    printTestName<T>("Testing list splice one iterator of list into begin");
    ft::list<T> ftlist;
    ft::list<T> ftlist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    // position where to place
    typename ft::list<T>::iterator fit = ftlist.begin();
    typename std::list<T>::iterator sit = stdlist.begin();
    // position what to place
    int x_pos = rand() % (ftlist2.size() - 1);
    typename ft::list<T>::iterator xfit = ftlist2.begin();
    ft::advance(xfit, x_pos);
    typename std::list<T>::iterator xsit = stdlist2.begin();
    for (int i = x_pos; i--;)
        ++xsit;
    ftlist.splice(fit, ftlist2, xfit);
    stdlist.splice(sit, stdlist2, xsit);
    testListContainersEqual(ftlist, stdlist);
    // position what to place
    x_pos = rand() % (ftlist2.size() - 1);
    xfit = ftlist2.begin();
    ft::advance(xfit, x_pos);
    xsit = stdlist2.begin();
    for (int i = x_pos; i--;)
        ++xsit;
    ftlist.splice(fit, ftlist2, xfit);
    stdlist.splice(sit, stdlist2, xsit);
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listSpliceOneEndTest() {
    printTestName<T>("Testing list splice one iterator of list into end");
    ft::list<T> ftlist;
    ft::list<T> ftlist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    // position where to place
    typename ft::list<T>::iterator fit = ftlist.end();
    typename std::list<T>::iterator sit = stdlist.end();
    // position what to place
    int x_pos = rand() % (ftlist2.size() - 1);
    typename ft::list<T>::iterator xfit = ftlist2.begin();
    ft::advance(xfit, x_pos);
    typename std::list<T>::iterator xsit = stdlist2.begin();
    for (int i = x_pos; i--;)
        ++xsit;
    ftlist.splice(fit, ftlist2, xfit);
    stdlist.splice(sit, stdlist2, xsit);
    testListContainersEqual(ftlist, stdlist);
    // position what to place
    x_pos = rand() % (ftlist2.size() - 1);
    xfit = ftlist2.begin();
    ft::advance(xfit, x_pos);
    xsit = stdlist2.begin();
    for (int i = x_pos; i--;)
        ++xsit;
    ftlist.splice(fit, ftlist2, xfit);
    stdlist.splice(sit, stdlist2, xsit);
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listSpliceOneRandomTest() {
    printTestName<T>("Testing list splice one iterator of list into random position");
    ft::list<T> ftlist;
    ft::list<T> ftlist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    // position where to place
    int position = rand() % (ftlist.size() - 1) + 1;
    typename ft::list<T>::iterator fit = ftlist.begin();
    ft::advance(fit, position);
    typename std::list<T>::iterator sit = stdlist.begin();
    for (int i = position; i--;)
        ++sit;
    // position what to place
    int x_pos = rand() % (ftlist2.size() - 1);
    typename ft::list<T>::iterator xfit = ftlist2.begin();
    ft::advance(xfit, x_pos);
    typename std::list<T>::iterator xsit = stdlist2.begin();
    for (int i = x_pos; i--;)
        ++xsit;
    ftlist.splice(fit, ftlist2, xfit);
    stdlist.splice(sit, stdlist2, xsit);
    testListContainersEqual(ftlist, stdlist);
    // position what to place
    x_pos = rand() % (ftlist2.size() - 1);
    xfit = ftlist2.begin();
    ft::advance(xfit, x_pos);
    xsit = stdlist2.begin();
    for (int i = x_pos; i--;)
        ++xsit;
    ftlist.splice(fit, ftlist2, xfit);
    stdlist.splice(sit, stdlist2, xsit);
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listSpliceIterBeginTest() {
    printTestName<T>("Testing list splice iterator range of list into begin");
    ft::list<T> ftlist;
    ft::list<T> ftlist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    // position where to place
    typename ft::list<T>::iterator fit = ftlist.begin();
    typename std::list<T>::iterator sit = stdlist.begin();
    // position what to place (left end)
    int x_pos_left = rand() % (ftlist2.size() - 9) + 1;
    typename ft::list<T>::iterator xfitlft = ftlist2.begin();
    ft::advance(xfitlft, x_pos_left);
    typename std::list<T>::iterator xsitlft = stdlist2.begin();
    for (int i = x_pos_left; i--;)
        ++xsitlft;
    // position what to place (right end)
    int x_pos_right = rand() % (ftlist2.size() - x_pos_left - 3) + 1;
    typename ft::list<T>::iterator xfitrht = xfitlft;
    ft::advance(xfitrht, x_pos_right);
    typename std::list<T>::iterator xsitrht = xsitlft;
    for (int i = x_pos_right; i--;)
        ++xsitrht;
    ftlist.splice(fit, ftlist2, xfitlft, xfitrht);
    stdlist.splice(sit, stdlist2, xsitlft, xsitrht);
    testListContainersEqual(ftlist, stdlist);
    // position what to place (left end)
    x_pos_left = rand() % (ftlist2.size() - 2) + 1;
    xfitlft = ftlist2.begin();
    ft::advance(xfitlft, x_pos_left);
    xsitlft = stdlist2.begin();
    for (int i = x_pos_left; i--;)
        ++xsitlft;
    // position what to place (right end)
    x_pos_right = rand() % (ftlist2.size() - x_pos_left - 1) + 1;
    xfitrht = xfitlft;
    ft::advance(xfitrht, x_pos_right);
    xsitrht = xsitlft;
    for (int i = x_pos_right; i--;)
        ++xsitrht;
    ftlist.splice(fit, ftlist2, xfitlft, xfitrht);
    stdlist.splice(sit, stdlist2, xsitlft, xsitrht);
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listSpliceIterEndTest() {
    printTestName<T>("Testing list splice iterator range of list into end");
    ft::list<T> ftlist;
    ft::list<T> ftlist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    // position where to place
    typename ft::list<T>::iterator fit = ftlist.end();
    typename std::list<T>::iterator sit = stdlist.end();
    // position what to place (left end)
    int x_pos_left = rand() % (ftlist2.size() - 2) + 1;
    typename ft::list<T>::iterator xfitlft = ftlist2.begin();
    ft::advance(xfitlft, x_pos_left);
    typename std::list<T>::iterator xsitlft = stdlist2.begin();
    for (int i = x_pos_left; i--;)
        ++xsitlft;
    // position what to place (right end)
    int x_pos_right = rand() % (ftlist2.size() - x_pos_left - 1) + 1;
    typename ft::list<T>::iterator xfitrht = xfitlft;
    ft::advance(xfitrht, x_pos_right);
    typename std::list<T>::iterator xsitrht = xsitlft;
    for (int i = x_pos_right; i--;)
        ++xsitrht;
    ftlist.splice(fit, ftlist2, xfitlft, xfitrht);
    stdlist.splice(sit, stdlist2, xsitlft, xsitrht);
    testListContainersEqual(ftlist, stdlist);
    // position what to place (left end)
    x_pos_left = rand() % (ftlist2.size() - 2) + 1;
    xfitlft = ftlist2.begin();
    ft::advance(xfitlft, x_pos_left);
    xsitlft = stdlist2.begin();
    for (int i = x_pos_left; i--;)
        ++xsitlft;
    // position what to place (right end)
    x_pos_right = rand() % (ftlist2.size() - x_pos_left - 1) + 1;
    xfitrht = xfitlft;
    ft::advance(xfitrht, x_pos_right);
    xsitrht = xsitlft;
    for (int i = x_pos_right; i--;)
        ++xsitrht;
    ftlist.splice(fit, ftlist2, xfitlft, xfitrht);
    stdlist.splice(sit, stdlist2, xsitlft, xsitrht);
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listSpliceIterRandomTest() {
    printTestName<T>("Testing list splice iterator range of list into random position");
    ft::list<T> ftlist;
    ft::list<T> ftlist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    std::list<T> stdlist2(ftlist2.begin(), ftlist2.end());
    // position where to place
    int position = rand() % (ftlist.size() - 1) + 1;
    typename ft::list<T>::iterator fit = ftlist.begin();
    ft::advance(fit, position);
    typename std::list<T>::iterator sit = stdlist.begin();
    for (int i = position; i--;)
        ++sit;
    // position what to place (left end)
    int x_pos_left = rand() % (ftlist2.size() - 2) + 1;
    typename ft::list<T>::iterator xfitlft = ftlist2.begin();
    ft::advance(xfitlft, x_pos_left);
    typename std::list<T>::iterator xsitlft = stdlist2.begin();
    for (int i = x_pos_left; i--;)
        ++xsitlft;
    // position what to place (right end)
    int x_pos_right = rand() % (ftlist2.size() - x_pos_left - 1) + 1;
    typename ft::list<T>::iterator xfitrht = xfitlft;
    ft::advance(xfitrht, x_pos_right);
    typename std::list<T>::iterator xsitrht = xsitlft;
    for (int i = x_pos_right; i--;)
        ++xsitrht;
    ftlist.splice(fit, ftlist2, xfitlft, xfitrht);
    stdlist.splice(sit, stdlist2, xsitlft, xsitrht);
    testListContainersEqual(ftlist, stdlist);
    // position what to place (left end)
    x_pos_left = rand() % (ftlist2.size() - 2) + 1;
    xfitlft = ftlist2.begin();
    ft::advance(xfitlft, x_pos_left);
    xsitlft = stdlist2.begin();
    for (int i = x_pos_left; i--;)
        ++xsitlft;
    // position what to place (right end)
    x_pos_right = rand() % (ftlist2.size() - x_pos_left - 1) + 1;
    xfitrht = xfitlft;
    ft::advance(xfitrht, x_pos_right);
    xsitrht = xsitlft;
    for (int i = x_pos_right; i--;)
        ++xsitrht;
    ftlist.splice(fit, ftlist2, xfitlft, xfitrht);
    stdlist.splice(sit, stdlist2, xsitlft, xsitrht);
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listRemoveNotRandomTest() {
    printTestName<T>("Testing list remove with not random lists");
    ft::list<T> ftlist;
    T values[] = {10, 12, 12, 12, 12, 12, 10, 12, 12, 12, 4, 12};
    for (std::size_t i = 0; i < sizeof(values) / sizeof(*values); ++i) {
        ftlist.push_back(values[i]);
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    typename std::list<T>::iterator it;
    for (int i = 0; i < 3; ++i) {
        for (it = stdlist.begin(); it != stdlist.end(); ++it) {
            if (rand() % 10 == 0 || *it == stdlist.back())
                break;
        }
        ftlist.remove(*it);
        stdlist.remove(*it);
        testListContainersEqual(ftlist, stdlist);
    }
}

template<>
void listRemoveNotRandomTest<std::string>() {
    typedef std::string T;
    printTestName<T>("Testing list remove with not random lists");
    ft::list<T> ftlist;
    T values[] = {"", "a", "", "", "", "b", "b", "", "a"};
    for (std::size_t i = 0; i < sizeof(values) / sizeof(*values); ++i) {
        ftlist.push_back(values[i]);
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    typename std::list<T>::iterator it;
    for (int i = 0; i < 3; ++i) {
        for (it = stdlist.begin(); it != stdlist.end(); ++it) {
            if (rand() % 10 == 0 || *it == stdlist.back())
                break;
        }
        ftlist.remove(*it);
        stdlist.remove(*it);
        testListContainersEqual(ftlist, stdlist);
    }
}

template<>
void listRemoveNotRandomTest<SomeStruct>() {
    typedef SomeStruct T;
    printTestName<T>("Testing list remove with not random lists");
    ft::list<T> ftlist;
    T values[] = {
        SomeStruct("a", 0), SomeStruct("a", 1),
        SomeStruct("a", 1), SomeStruct("b", 0),
        SomeStruct("b", 0), SomeStruct("a", 0)
    };
    for (std::size_t i = 0; i < sizeof(values) / sizeof(*values); ++i) {
        ftlist.push_back(values[i]);
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    typename std::list<T>::iterator it;
    for (int i = 0; i < 3; ++i) {
        for (it = stdlist.begin(); it != stdlist.end(); ++it) {
            if (rand() % 10 == 0 || *it == stdlist.back())
                break;
        }
        ftlist.remove(*it);
        stdlist.remove(*it);
        testListContainersEqual(ftlist, stdlist);
    }
}

template<typename T>
void listRemoveTest() {
    printTestName<T>("Testing list remove");
    ft::list<T> ftlist;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    typename std::list<T>::iterator it;
    for (int i = 0; i < 3; ++i) {
        for (it = stdlist.begin(); it != stdlist.end(); ++it) {
            if (rand() % 10 == 0 || *it == stdlist.back())
                break;
        }
        ftlist.remove(*it);
        stdlist.remove(*it);
        testListContainersEqual(ftlist, stdlist);
    }
}

template<typename T>
void listRemoveAllTest() {
    printTestName<T>("Testing list remove all elements by one");
    ft::list<T> ftlist;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    typename std::list<T>::iterator tmp;
    for (typename std::list<T>::iterator it = stdlist.begin(); it != stdlist.end(); ++it) {
        tmp = it;
        --tmp;
        ftlist.remove(*it);
        stdlist.remove(*it);
        it = tmp;
        testListContainersEqual(ftlist, stdlist);
    }
}

template<typename T>
void listRemoveAllSameTest() {
    printTestName<T>("Testing list remove all when all list is the same");
    ft::list<T> ftlist(40, getRandomValue<T>());
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ftlist.remove(ftlist.front());
    stdlist.remove(stdlist.front());
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
bool remove_if_compare(const T &val) {
    return val < 100;
}

template<> bool remove_if_compare<std::string>(const std::string &val) {
    return val.length() < 25;
}

template<> bool remove_if_compare<SomeStruct>(const SomeStruct &val) {
    return val < SomeStruct("", 100);
}

template<typename T>
void listRemoveIfTest() {
    printTestName<T>("Testing list remove with special compare");
    ft::list<T> ftlist;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ftlist.remove(ftlist.front());
    stdlist.remove(stdlist.front());
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listUniqueTest() {
    printTestName<T>("Testing list unique");
    ft::list<T> ftlist;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ftlist.unique();
    stdlist.unique();
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listUniqueSortedTest() {
    printTestName<T>("Testing list unique when sorted");
    ft::list<T> ftlist;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    ftlist.sort();
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ftlist.unique();
    stdlist.unique();
    testListContainersEqual(ftlist, stdlist);
}

template<class T>
bool unique_compare(const T &val1, const T &val2) {
    return val1 < val2;
}

template<>
bool unique_compare<std::string>(const std::string &val1, const std::string &val2) {
    return val1.length() < val2.length();
}

template<>
bool unique_compare<SomeStruct>(const SomeStruct &val1, const SomeStruct &val2) {
    return val1.name.length() < val2.name.length();
}

template<typename T>
void listUniqueCompareTest() {
    printTestName<T>("Testing list unique");
    ft::list<T> ftlist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> backup(ftlist.begin(), ftlist.end());
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ftlist.unique(unique_compare<T>);
    stdlist.unique(unique_compare<T>);
    std::list<T> ftstd(ftlist.begin(), ftlist.end());
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listUniqueSortedCompareTest() {
    printTestName<T>("Testing list unique when sorted");
    ft::list<T> ftlist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    ftlist.sort();
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    ftlist.unique(unique_compare<T>);
    stdlist.unique(unique_compare<T>);
    testListContainersEqual(ftlist, stdlist);
}

template<class T>
bool mergeCompare(T first, T second) {
    return first < second;
}

template<>
bool mergeCompare<float>(float first, float second) {
    return int(first) < int(second);
}

template<>
bool mergeCompare<std::string>(std::string first, std::string second) {
    return first[0] < second[0];
}

template<typename T>
void listMergeTest() {
    ft::list<T> flst, flst2;

    int size = rand() % 20 + 10;
    for (int i = 0; i < size; ++i) {
        flst.push_back(getRandomValue<T>());
    }
    flst.sort();
    std::list<T> slst(flst.begin(), flst.end());
    size = rand() % 20 + 10;
    for (int i = 0; i < size; ++i) {
        flst2.push_back(getRandomValue<T>());
    }
    flst2.sort();
    std::list<T> slst2(flst2.begin(), flst2.end());

    flst.merge(flst2);
    slst.merge(slst2);
    testListContainersEqual(flst, slst);

    T value = getRandomValue<T>();
    flst2.push_back(value);
    slst2.push_back(value);
    flst.merge(flst2, mergeCompare<T>);
    slst.merge(slst2, mergeCompare<T>);
    testListContainersEqual(flst, slst);
}

template<class T>
bool compare_nocase(const T& first, const T& second)
{
    return first < second;
}

template<>
bool compare_nocase<std::string>(const std::string& first, const std::string& second)
{
    unsigned int i=0;
    while ( (i<first.length()) && (i<second.length()) )
    {
        if (tolower(first[i])<tolower(second[i])) return true;
        else if (tolower(first[i])>tolower(second[i])) return false;
        ++i;
    }
    return ( first.length() < second.length() );
}

template<typename T>
void listSortExampleTest() {
    printTestName<T>("Testing list sort as in cplusplus example");
    ft::list<T> ftlist;
    for (std::size_t i = 0; i < 12; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    testListContainersEqual(ftlist, stdlist);
    ftlist.reverse();
    ftlist.sort();
    stdlist.sort();
    testListContainersEqual(ftlist, stdlist);
    ftlist.sort(compare_nocase<T>);
    stdlist.sort(compare_nocase<T>);
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listReverseTest() {
    printTestName<T>("Testing list reverse (empty and not empty)");
    ft::list<T> ftlist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    testListContainersEqual(ftlist, stdlist);
    ftlist.reverse();
    stdlist.reverse();
    testListContainersEqual(ftlist, stdlist);
    ftlist.reverse();
    stdlist.reverse();
    testListContainersEqual(ftlist, stdlist);
    ftlist.clear();
    stdlist.clear();
    ftlist.reverse();
    stdlist.reverse();
    testListContainersEqual(ftlist, stdlist);
}

template<typename T>
void listCompareEqualsTest() {
    printTestName<T>("Testing compare operator ==");
    ft::list<T> ftlist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    // equal
    ft::list<T> ftlisteq = ftlist;
    std::list<T> stdlisteq = stdlist;
    // less in size
    ft::list<T> ftlistlt = ftlist;
    ftlistlt.pop_back();
    std::list<T> stdlistlt = stdlist;
    stdlistlt.pop_back();
    // less in element
    T tmp;
    do { tmp = getRandomValue<T>(); } while (tmp >= ftlist.back());
    ft::list<T> ftlistlt2 = ftlist;
    ftlistlt2.back() = tmp;
    std::list<T> stdlistlt2 = stdlist;
    stdlistlt2.back() = tmp;
    // greater in size
    ft::list<T> ftlistgt = ftlist;
    ftlistgt.push_back(getRandomValue<T>());
    std::list<T> stdlistgt = stdlist;
    stdlistgt.push_back(getRandomValue<T>());
    // greater in element
    do { tmp = getRandomValue<T>(); } while (tmp <= ftlist.back());
    ft::list<T> ftlistgt2 = ftlist;
    ftlistgt2.back() = tmp;
    std::list<T> stdlistgt2 = stdlist;
    stdlistgt2.back() = tmp;
    EXPECT_EQ(ftlist == ftlisteq, stdlist == stdlisteq);
    EXPECT_EQ(ftlist == ftlistlt, stdlist == stdlistlt);
    EXPECT_EQ(ftlist == ftlistlt2, stdlist == stdlistlt2);
    EXPECT_EQ(ftlist == ftlistgt, stdlist == stdlistgt);
    EXPECT_EQ(ftlist == ftlistgt2, stdlist == stdlistgt2);
}

template<typename T>
void listCompareNotEqualsTest() {
    printTestName<T>("Testing compare operator !=");
    ft::list<T> ftlist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    // equal
    ft::list<T> ftlisteq = ftlist;
    std::list<T> stdlisteq = stdlist;
    // less in size
    ft::list<T> ftlistlt = ftlist;
    ftlistlt.pop_back();
    std::list<T> stdlistlt = stdlist;
    stdlistlt.pop_back();
    // less in element
    T tmp;
    do { tmp = getRandomValue<T>(); } while (tmp >= ftlist.back());
    ft::list<T> ftlistlt2 = ftlist;
    ftlistlt2.back() = tmp;
    std::list<T> stdlistlt2 = stdlist;
    stdlistlt2.back() = tmp;
    // greater in size
    ft::list<T> ftlistgt = ftlist;
    ftlistgt.push_back(getRandomValue<T>());
    std::list<T> stdlistgt = stdlist;
    stdlistgt.push_back(getRandomValue<T>());
    // greater in element
    do { tmp = getRandomValue<T>(); } while (tmp <= ftlist.back());
    ft::list<T> ftlistgt2 = ftlist;
    ftlistgt2.back() = tmp;
    std::list<T> stdlistgt2 = stdlist;
    stdlistgt2.back() = tmp;
    EXPECT_EQ(ftlist != ftlisteq, stdlist != stdlisteq);
    EXPECT_EQ(ftlist != ftlistlt, stdlist != stdlistlt);
    EXPECT_EQ(ftlist != ftlistlt2, stdlist != stdlistlt2);
    EXPECT_EQ(ftlist != ftlistgt, stdlist != stdlistgt);
    EXPECT_EQ(ftlist != ftlistgt2, stdlist != stdlistgt2);
}

template<typename T>
void listCompareLessThanTest() {
    printTestName<T>("Testing compare operator <");
    ft::list<T> ftlist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    // equal
    ft::list<T> ftlisteq = ftlist;
    std::list<T> stdlisteq = stdlist;
    // less in size
    ft::list<T> ftlistlt = ftlist;
    ftlistlt.pop_back();
    std::list<T> stdlistlt = stdlist;
    stdlistlt.pop_back();
    // less in element
    T tmp;
    do { tmp = getRandomValue<T>(); } while (tmp >= ftlist.back());
    ft::list<T> ftlistlt2 = ftlist;
    ftlistlt2.back() = tmp;
    std::list<T> stdlistlt2 = stdlist;
    stdlistlt2.back() = tmp;
    // greater in size
    ft::list<T> ftlistgt = ftlist;
    ftlistgt.push_back(getRandomValue<T>());
    std::list<T> stdlistgt = stdlist;
    stdlistgt.push_back(getRandomValue<T>());
    // greater in element
    do { tmp = getRandomValue<T>(); } while (tmp <= ftlist.back());
    ft::list<T> ftlistgt2 = ftlist;
    ftlistgt2.back() = tmp;
    std::list<T> stdlistgt2 = stdlist;
    stdlistgt2.back() = tmp;
    EXPECT_EQ(ftlist < ftlisteq, stdlist < stdlisteq);
    EXPECT_EQ(ftlist < ftlistlt, stdlist < stdlistlt);
    EXPECT_EQ(ftlist < ftlistlt2, stdlist < stdlistlt2);
    EXPECT_EQ(ftlist < ftlistgt, stdlist < stdlistgt);
    EXPECT_EQ(ftlist < ftlistgt2, stdlist < stdlistgt2);
}

template<typename T>
void listCompareGreaterThanTest() {
    printTestName<T>("Testing compare operator >");
    ft::list<T> ftlist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    // equal
    ft::list<T> ftlisteq = ftlist;
    std::list<T> stdlisteq = stdlist;
    // less in size
    ft::list<T> ftlistlt = ftlist;
    ftlistlt.pop_back();
    std::list<T> stdlistlt = stdlist;
    stdlistlt.pop_back();
    // less in element
    T tmp;
    do { tmp = getRandomValue<T>(); } while (tmp >= ftlist.back());
    ft::list<T> ftlistlt2 = ftlist;
    ftlistlt2.back() = tmp;
    std::list<T> stdlistlt2 = stdlist;
    stdlistlt2.back() = tmp;
    // greater in size
    ft::list<T> ftlistgt = ftlist;
    ftlistgt.push_back(getRandomValue<T>());
    std::list<T> stdlistgt = stdlist;
    stdlistgt.push_back(getRandomValue<T>());
    // greater in element
    do { tmp = getRandomValue<T>(); } while (tmp <= ftlist.back());
    ft::list<T> ftlistgt2 = ftlist;
    ftlistgt2.back() = tmp;
    std::list<T> stdlistgt2 = stdlist;
    stdlistgt2.back() = tmp;
    EXPECT_EQ(ftlist > ftlisteq, stdlist > stdlisteq);
    EXPECT_EQ(ftlist > ftlistlt, stdlist > stdlistlt);
    EXPECT_EQ(ftlist > ftlistlt2, stdlist > stdlistlt2);
    EXPECT_EQ(ftlist > ftlistgt, stdlist > stdlistgt);
    EXPECT_EQ(ftlist > ftlistgt2, stdlist > stdlistgt2);
}

template<typename T>
void listCompareLTETest() {
    printTestName<T>("Testing compare operator <=");
    ft::list<T> ftlist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    // equal
    ft::list<T> ftlisteq = ftlist;
    std::list<T> stdlisteq = stdlist;
    // less in size
    ft::list<T> ftlistlt = ftlist;
    ftlistlt.pop_back();
    std::list<T> stdlistlt = stdlist;
    stdlistlt.pop_back();
    // less in element
    T tmp;
    do { tmp = getRandomValue<T>(); } while (tmp >= ftlist.back());
    ft::list<T> ftlistlt2 = ftlist;
    ftlistlt2.back() = tmp;
    std::list<T> stdlistlt2 = stdlist;
    stdlistlt2.back() = tmp;
    // greater in size
    ft::list<T> ftlistgt = ftlist;
    ftlistgt.push_back(getRandomValue<T>());
    std::list<T> stdlistgt = stdlist;
    stdlistgt.push_back(getRandomValue<T>());
    // greater in element
    do { tmp = getRandomValue<T>(); } while (tmp <= ftlist.back());
    ft::list<T> ftlistgt2 = ftlist;
    ftlistgt2.back() = tmp;
    std::list<T> stdlistgt2 = stdlist;
    stdlistgt2.back() = tmp;
    EXPECT_EQ(ftlist <= ftlisteq, stdlist <= stdlisteq);
    EXPECT_EQ(ftlist <= ftlistlt, stdlist <= stdlistlt);
    EXPECT_EQ(ftlist <= ftlistlt2, stdlist <= stdlistlt2);
    EXPECT_EQ(ftlist <= ftlistgt, stdlist <= stdlistgt);
    EXPECT_EQ(ftlist <= ftlistgt2, stdlist <= stdlistgt2);
}

template<typename T>
void listCompareGTETest() {
    printTestName<T>("Testing compare operator >=");
    ft::list<T> ftlist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        ftlist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(ftlist.begin(), ftlist.end());
    // equal
    ft::list<T> ftlisteq = ftlist;
    std::list<T> stdlisteq = stdlist;
    // less in size
    ft::list<T> ftlistlt = ftlist;
    ftlistlt.pop_back();
    std::list<T> stdlistlt = stdlist;
    stdlistlt.pop_back();
    // less in element
    T tmp;
    do { tmp = getRandomValue<T>(); } while (tmp >= ftlist.back());
    ft::list<T> ftlistlt2 = ftlist;
    ftlistlt2.back() = tmp;
    std::list<T> stdlistlt2 = stdlist;
    stdlistlt2.back() = tmp;
    // greater in size
    ft::list<T> ftlistgt = ftlist;
    ftlistgt.push_back(getRandomValue<T>());
    std::list<T> stdlistgt = stdlist;
    stdlistgt.push_back(getRandomValue<T>());
    // greater in element
    do { tmp = getRandomValue<T>(); } while (tmp <= ftlist.back());
    ft::list<T> ftlistgt2 = ftlist;
    ftlistgt2.back() = tmp;
    std::list<T> stdlistgt2 = stdlist;
    stdlistgt2.back() = tmp;
    EXPECT_EQ(ftlist >= ftlisteq, stdlist >= stdlisteq);
    EXPECT_EQ(ftlist >= ftlistlt, stdlist >= stdlistlt);
    EXPECT_EQ(ftlist >= ftlistlt2, stdlist >= stdlistlt2);
    EXPECT_EQ(ftlist >= ftlistgt, stdlist >= stdlistgt);
    EXPECT_EQ(ftlist >= ftlistgt2, stdlist >= stdlistgt2);
}

template<typename T>
void defaultMapConstructorTest() {
    printTestName<T>("Default constructor");
    ft::map<T, T> ftv;
    std::map<T, T> stv;
    testMapContainersEqual(ftv, stv);
}

template<typename T>
void iteratorMapConstructorTest() {
    printTestName<T>("Constructor for iterators begin and end");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> fiter;
    std::map<T, T>   siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        fiter.insert(ft::make_pair(key, value));
        siter.insert(std::make_pair(key, value));
    }
    fiter.print_map();

    typename ft::map<T, T>::iterator lit = fiter.begin();
    ft::advance(lit, 2);
    typename ft::map<T, T>::iterator rit = fiter.end();
    ft::advance(rit, -3);
    ft::map<T, T> ftv(lit, rit);
    typename std::map<T, T>::iterator lsit = siter.begin();
    ft::advance(lsit, 2);
    typename std::map<T, T>::iterator rsit = siter.end();
    ft::advance(rsit, -3);
    std::map<T, T> stv(lsit, rsit);
    testMapContainersEqual(ftv, stv);
}

template<class T>
bool map_constructor_greater_compare(T a, T b) {
    return a > b;
}

template<typename T>
void defaultMapWithCompareTest() {
    printTestName<T>("Default constructor with compare function");
    ft::map<T, T, bool (*)(T a, T b)> ftv(map_constructor_greater_compare<T>);
    std::map<T, T, bool (*)(T a, T b)> stv(map_constructor_greater_compare<T>);
    testMapContainersEqual(ftv, stv);
}

template<typename T>
void iteratorMapWithCompareTest() {
    printTestName<T>("Constructor for iterators begin and end");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T, bool (*)(T a, T b)> fiter(map_constructor_greater_compare<T>);
    std::map<T, T, bool (*)(T a, T b)>   siter(map_constructor_greater_compare<T>);
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        fiter.insert(ft::make_pair(key, value));
        siter.insert(std::make_pair(key, value));
    }
    fiter.print_map();

    typename ft::map<T, T, bool (*)(T a, T b)>::iterator lit = fiter.begin();
    ft::advance(lit, 2);
    typename ft::map<T, T, bool (*)(T a, T b)>::iterator rit = fiter.end();
    ft::advance(rit, -3);
    ft::map<T, T, bool (*)(T a, T b)> ftv(lit, rit, map_constructor_greater_compare<T>);

    typename std::map<T, T, bool (*)(T a, T b)>::iterator lsit = siter.begin();
    ft::advance(lsit, 2);
    typename std::map<T, T, bool (*)(T a, T b)>::iterator rsit = siter.end();
    ft::advance(rsit, -3);
    std::map<T, T, bool (*)(T a, T b)> stv(lsit, rsit, map_constructor_greater_compare<T>);

    testMapContainersEqual(ftv, stv);
}

template<typename T>
void copyMapConstructorTest() {
    {
        printTestName<T>("Copy constructor for default container");
        ft::map<T, T> ftv_o;
        std::map<T, T> stv_o;
        ft::map<T, T> ftv(ftv_o);
        std::map<T, T> stv(stv_o);
        testMapContainersEqual(ftv, stv);
    }
    {
        printTestName<T>("Copy constructor for iterators begin and end");

        std::size_t numOfItems = rand() % 20 + 10;
        ft::map<T, T>    fiter;
        std::map<T, T>   siter;
        for (std::size_t i = 0; i < numOfItems; ++i) {
            T key = getRandomValue<T>();
            T value = getRandomValue<T>();
            fiter.insert(ft::make_pair(key, value));
            siter.insert(std::make_pair(key, value));
        }

        typename ft::map<T, T>::iterator lit = fiter.begin();
        ft::advance(lit, 2);
        typename ft::map<T, T>::iterator rit = fiter.end();
        ft::advance(rit, -3);
        ft::map<T, T> ftv_o(lit, rit);
        typename std::map<T, T>::iterator lsit = siter.begin();
        ft::advance(lsit, 2);
        typename std::map<T, T>::iterator rsit = siter.end();
        ft::advance(rsit, -3);
        std::map<T, T> stv_o(lsit, rsit);

        ft::map<T, T> ftv(ftv_o);
        std::map<T, T> stv(stv_o);

        testMapContainersEqual(ftv, stv);
    }
}

template<typename T>
void assignOperatorEmptyTest() {
    printTestName<T>("Assignation operator of empty container");
    ft::pair<T, T> farr[5] = {
        { getRandomValue<T>(), getRandomValue<T>() },
        { getRandomValue<T>(), getRandomValue<T>() },
        { getRandomValue<T>(), getRandomValue<T>() },
        { getRandomValue<T>(), getRandomValue<T>() },
        { getRandomValue<T>(), getRandomValue<T>() }
    };
    std::pair<T, T> sarr[5] = {
        { farr[0].first, farr[0].second },
        { farr[1].first, farr[1].second },
        { farr[2].first, farr[2].second },
        { farr[3].first, farr[3].second },
        { farr[4].first, farr[4].second },
    };
    ft::map<T, T> ftv_o;
    std::map<T, T> stv_o;
    testMapContainersEqual(ftv_o, stv_o);
    ft::map<T, T> ftv(farr, farr + 5);
    std::map<T, T> stv(sarr, sarr + 5);
    ftv = ftv_o;
    stv = stv_o;
    testMapContainersEqual(ftv_o, stv_o);
}

template<typename T>
void assignOperatorNotEmptyTest() {
    printTestName<T>("Assignation operator of a container");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> fiter;
    std::map<T, T>   siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        fiter.insert(ft::make_pair(key, value));
        siter.insert(std::make_pair(key, value));
    }

    ft::map<T, T> ftv;
    std::map<T, T> stv;
    ftv = fiter;
    stv = siter;
    testMapContainersEqual(ftv, stv);
}

template<typename T>
void assignOperatorEmptyWithCmpTest() {
    printTestName<T>("Assignation operator of empty container with cmp fucntion");
    ft::pair<T, T> farr[5] = {
        { getRandomValue<T>(), getRandomValue<T>() },
        { getRandomValue<T>(), getRandomValue<T>() },
        { getRandomValue<T>(), getRandomValue<T>() },
        { getRandomValue<T>(), getRandomValue<T>() },
        { getRandomValue<T>(), getRandomValue<T>() }
    };
    std::pair<T, T> sarr[5] = {
        { farr[0].first, farr[0].second },
        { farr[1].first, farr[1].second },
        { farr[2].first, farr[2].second },
        { farr[3].first, farr[3].second },
        { farr[4].first, farr[4].second },
    };
    ft::map<T, T, bool (*)(T a, T b)> ftv_o(map_constructor_greater_compare<T>);
    std::map<T, T, bool (*)(T a, T b)> stv_o(map_constructor_greater_compare<T>);
    testMapContainersEqual(ftv_o, stv_o);
    ft::map<T, T, bool (*)(T a, T b)> ftv(farr, farr + 5, map_constructor_greater_compare<T>);
    std::map<T, T, bool (*)(T a, T b)> stv(sarr, sarr + 5, map_constructor_greater_compare<T>);
    ftv = ftv_o;
    stv = stv_o;
    testMapContainersEqual(ftv, stv);
}

template<typename T>
void assignOperatorNotEmptyWithCmpTest() {
    printTestName<T>("Assignation operator of a container with cmp fucntion");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T, bool (*)(T a, T b)> fiter(map_constructor_greater_compare<T>);
    std::map<T, T, bool (*)(T a, T b)>   siter(map_constructor_greater_compare<T>);
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        fiter.insert(ft::make_pair(key, value));
        siter.insert(std::make_pair(key, value));
    }

    ft::map<T, T, bool (*)(T a, T b)> ftv;
    std::map<T, T, bool (*)(T a, T b)> stv;
    ftv = fiter;
    stv = siter;
    testMapContainersEqual(ftv, stv);
}

template<typename T>
void mapInsertHintTest() {
    printTestName<T>("Testing map insert hint");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> ftv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        ftv.insert(ftv.begin(),ft::make_pair(key, value));
        stv.insert(stv.begin(),std::make_pair(key, value));
    }

    testMapContainersEqual(ftv, stv);
}

template<typename T>
void mapInsertIteratorsTest() {
    printTestName<T>("Testing map insert iterators");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> fiter;
    std::map<T, T>   siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        fiter.insert(ft::make_pair(key, value));
        siter.insert(std::make_pair(key, value));
    }

    ft::map<T,T> ftv;
    std::map<T,T> stv;
    ftv.insert(fiter.rbegin(), fiter.rend());
    stv.insert(siter.rbegin(), siter.rend());
    testMapContainersEqual(ftv, stv);
}

template<typename T>
void mapEraseSingleTest() {
    printTestName<T>("Testing map erase single iterator");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> ftv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        ftv.insert(ft::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    ftv.erase(ftv.begin());
    stv.erase(stv.begin());

    typename ft::map<T,T>::iterator fit;
    typename std::map<T,T>::iterator sit;
    for (int i = 0; i < 5; ++i) {
        int pos = rand() % stv.size();
        fit = ftv.begin();
        ft::advance(fit, pos);
        sit = stv.begin();
        std::advance(sit, pos);
        ftv.erase(fit);
        stv.erase(sit);
    }
    testMapContainersEqual(ftv, stv);
    while (!ftv.empty())
        ftv.erase(ftv.begin());
    while (!stv.empty())
        stv.erase(stv.begin());
    testMapContainersEqual(ftv, stv);
}

template<typename T>
void mapEraseKeyTest() {
    printTestName<T>("Testing map erase by key");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> ftv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        std::cout << key << std::endl;
        ftv.insert(ft::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    ftv.print_map();
    std::cout << "erase start: " << ftv.begin()->first << std::endl;
    ftv.erase(ftv.begin());
    stv.erase(stv.begin());
    ftv.print_map();
    testMapContainersEqual(ftv, stv);

    typename ft::map<T,T>::iterator fit;
    typename std::map<T,T>::iterator sit;
    for (int i = 0; i < 5; ++i) {
        int pos = rand() % stv.size();
        sit = stv.begin();
        std::advance(sit, pos);
        std::cout << "erase " << sit->first << std::endl;
        ftv.erase(sit->first);
        stv.erase(sit->first);
        ftv.print_map();
    }
    testMapContainersEqual(ftv, stv);
}

template<typename T>
void mapEraseIteratorsTest() {
    printTestName<T>("Testing map erase iterators range");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> ftv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        ftv.insert(ft::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    ftv.erase(ftv.begin());
    stv.erase(stv.begin());

    typename ft::map<T,T>::iterator fit = ftv.begin();
    typename std::map<T,T>::iterator sit = stv.begin();
    int pos = rand() % stv.size();
    ft::advance(fit, pos);
    std::advance(sit, pos);
    typename ft::map<T,T>::iterator fen = fit;
    typename std::map<T,T>::iterator sen = sit;
    int pos1 = rand() % (ftv.size() - pos);
    ft::advance(fen, pos1);
    std::advance(sen, pos1);

    std::cout << "delete range " << pos << '-' << pos1 << std::endl;
    ftv.print_map();
    ftv.erase(fit, fen);
    stv.erase(sit, sen);
    ftv.print_map();
    testMapContainersEqual(ftv, stv);
}

template<typename T>
void mapSwapEmptyTest() {
    printTestName<T>("Testing map swap when both empty");

    ft::map<T, T> ftv1;
    std::map<T, T>   stv1;
    ft::map<T, T> ftv2;
    std::map<T, T>   stv2;

    ftv1.swap(ftv2);
    stv1.swap(stv2);
    testMapContainersEqual(ftv1, stv1);
    testMapContainersEqual(ftv2, stv2);
}

template<typename T>
void mapSwapOneEmptyTest() {
    printTestName<T>("Testing map swap when one empty");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> ftv1;
    std::map<T, T>   stv1;
    ft::map<T, T> ftv2;
    std::map<T, T>   stv2;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        ftv2.insert(ft::make_pair(key, value));
        stv2.insert(std::make_pair(key, value));
    }

    ftv1.swap(ftv2);
    stv1.swap(stv2);
    testMapContainersEqual(ftv1, stv1);
    testMapContainersEqual(ftv2, stv2);
}

template<typename T>
void mapSwapNotEmptyTest() {
    printTestName<T>("Testing map swap when filled");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> ftv1;
    std::map<T, T>   stv1;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        ftv1.insert(ft::make_pair(key, value));
        stv1.insert(std::make_pair(key, value));
    }
    numOfItems = rand() % 20 + 10;
    ft::map<T, T> ftv2;
    std::map<T, T>   stv2;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        ftv2.insert(ft::make_pair(key, value));
        stv2.insert(std::make_pair(key, value));
    }

    ftv1.swap(ftv2);
    stv1.swap(stv2);
    testMapContainersEqual(ftv1, stv1);
    testMapContainersEqual(ftv2, stv2);
}

template<typename T>
void mapClearTest() {
    printTestName<T>("Testing map clear");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> ftv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        ftv.insert(ft::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    ftv.clear();
    stv.clear();
    testMapContainersEqual(ftv, stv);
    ftv.clear();
    stv.clear();
    testMapContainersEqual(ftv, stv);
    for (std::size_t i = 9; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        ftv.insert(ft::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }
    testMapContainersEqual(ftv, stv);
}

template<typename T>
void mapKeyCompTest() {
    printTestName<T>("Testing map key compare function");

    bool(*function)(T,T) = map_constructor_greater_compare<T>;
    ft::map<T,T,bool(*)(T,T)>  ftv(function);
    std::map<T,T,bool(*)(T,T)> stv(function);

    EXPECT_EQ(ftv.key_comp(), function);
    EXPECT_EQ(stv.key_comp(), function);
    EXPECT_EQ(ftv.key_comp(), stv.key_comp());
}

template<typename T>
void mapValCompTest() {
    printTestName<T>("Testing map value compare function");

    bool(*function)(T,T) = map_constructor_greater_compare<T>;
    ft::map<T,T,bool(*)(T,T)>  ftv(function);
    std::map<T,T,bool(*)(T,T)> stv(function);

    typename ft::map<T,T,bool(*)(T,T)>::value_compare ftcmp = ftv.value_comp();
    typename std::map<T,T,bool(*)(T,T)>::value_compare stcmp = stv.value_comp();

    ft::pair<T,T> fp1 = ft::make_pair(getRandomValue<T>(), getRandomValue<T>());
    std::pair<T,T> sp1 = std::make_pair(fp1.first, fp1.second);

    ft::pair<T,T> fp2 = ft::make_pair(getRandomValue<T>(), getRandomValue<T>());
    std::pair<T,T> sp2 = std::make_pair(fp2.first, fp2.second);

    EXPECT_EQ(ftcmp(fp1, fp2), stcmp(sp1, sp2));
    EXPECT_EQ(ftcmp(fp1, fp1), stcmp(sp1, sp1));
}

template<typename T>
void mapFindExistTest() {
    printTestName<T>("Testing map find when keys exist");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> ftv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        ftv.insert(ft::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    for (typename std::map<T,T>::iterator it = stv.begin(); it != stv.end(); ++it) {
        typename ft::map<T,T>::iterator fit = ftv.find(it->first);
        typename std::map<T,T>::iterator sit = stv.find(it->first);
        EXPECT_EQ(fit == ftv.end(), sit == stv.end());
        EXPECT_EQ(fit->first, sit->first);
        EXPECT_EQ(fit->second, sit->second);
    }
    testMapContainersEqual(ftv, stv);
}

template<typename T>
void mapFindNotExistTest() {
    printTestName<T>("Testing map find when keys not exist");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> ftv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        ftv.insert(ft::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    for (int i = 0; i < 100; ++i) {
        T key = getRandomValue<T>();
        typename ft::map<T,T>::iterator fit = ftv.find(key);
        typename std::map<T,T>::iterator sit = stv.find(key);
        EXPECT_EQ(fit == ftv.end(), sit == stv.end());
    }
}

template<typename T>
void mapCountEmptyTest() {
    printTestName<T>("Testing map count on empty containers");

    ft::map<T, T> ftv;
    std::map<T, T>   stv;

    for (int i = 0; i < 100; ++i) {
        T key = getRandomValue<T>();
        EXPECT_EQ(ftv.count(key), stv.count(key));
    }
}

template<typename T>
void mapCountExistTest() {
    printTestName<T>("Testing map count when keys exist");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> ftv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        ftv.insert(ft::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    for (typename std::map<T,T>::iterator it = stv.begin(); it != stv.end(); ++it) {
        EXPECT_EQ(ftv.count(it->first), stv.count(it->first));
    }
    testMapContainersEqual(ftv, stv);
}

template<typename T>
void mapCountNotExistTest() {
    printTestName<T>("Testing map count when keys not exist");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::map<T, T> ftv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        ftv.insert(ft::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    for (int i = 0; i < 100; ++i) {
        T key = getRandomValue<T>();
        EXPECT_EQ(ftv.count(key), stv.count(key));
    }
}

/*** VECTOR TESTS ***/

//TEST(VectorConstructors, DefaultConstructor) FT_DO_TEST(defaultConstructorTest)
//TEST(VectorConstructors, ZeroElementsConstructor) FT_DO_TEST(zeroElementsConstructorTest)
//TEST(VectorConstructors, TwentyElementsConstructor) FT_DO_TEST(twentyElementsConstructorTest)
//TEST(VectorConstructors, TwentyElementsWithDefaultValueConstructor) FT_DO_TEST(twentyElementsWithDefaultValueConstructorTest)
//TEST(VectorConstructors, IteratorConstructor)  FT_DO_TEST(iteratorConstructorTest)
//TEST(VectorConstructors, CopyConstructor)  FT_DO_TEST(copyConstructorTest)
//
//TEST(VectorAssignation, AssignationOperatorToMoreCap) FT_DO_TEST(assignationOperatorToMoreCapTest)
//TEST(VectorAssignation, AssignationOperatorToMoreSize) FT_DO_TEST(assignationOperatorToMoreSizeTest)
//TEST(VectorAssignation, AssignationOperatorToLess) FT_DO_TEST(assignationOperatorToLessTest)
//TEST(VectorAssignation, AssignationOperatorToSame) FT_DO_TEST(assignationOperatorToSameTest)
//
//TEST(VectorCapacity, ResizeLess) FT_DO_TEST(resizeLessTest)
//TEST(VectorCapacity, ResizeMore) FT_DO_TEST(resizeMoreTest)
//TEST(VectorCapacity, ResizeSame) FT_DO_TEST(resizeSameTest)
//
//TEST(VectorCapacity, ReserveLess) FT_DO_TEST(reserveLessTest)
//TEST(VectorCapacity, ReserveMore) FT_DO_TEST(reserveMoreTest)
//TEST(VectorCapacity, ReserveSame) FT_DO_TEST(reserveSameTest)
//TEST(VectorCapacity, ReserveGreaterThanMax) FT_DO_TEST(reserveGreaterThanMaxTest)
//
//TEST(VectorElementAccess, operatorBracketsAccess) FT_DO_TEST(OperatorBracketsAccessTest)
//TEST(VectorElementAccess, functionAt) FT_DO_TEST(FunctionAtTest)
//TEST(VectorElementAccess, functionFront) FT_DO_TEST(FunctionFrontTest)
//TEST(VectorElementAccess, functionBack) FT_DO_TEST(FunctionBackTest)
//
//TEST(VectorAssign, assignFillLess) FT_DO_TEST(AssignFillLessTest)
//TEST(VectorAssign, assignFillBetweenSizeCap) FT_DO_TEST(AssignFillBetweenSizeCapTest)
//TEST(VectorAssign, assignFillMore) FT_DO_TEST(AssignFillMoreTest)
//TEST(VectorAssign, assignFillMaxSize) FT_DO_TEST(AssignFillMaxSizeTest)
//TEST(VectorAssign, assignFillMoreThanMax) FT_DO_TEST(AssignFillMoreThanMaxTest)
//TEST(VectorAssign, assignFillSame) FT_DO_TEST(AssignFillSameTest)
//
//TEST(VectorPushBack, pushBack) FT_DO_TEST(PushBackTest)
//TEST(VectorPopBack, popBack) FT_DO_TEST(PopBackTest)
//
//TEST(VectorSwap, swap) FT_DO_TEST(SwapTest)
//TEST(VectorSwap, swapOneEmpty) FT_DO_TEST(SwapOneEmptyTest)
//TEST(VectorSwap, swapOneCleared) FT_DO_TEST(SwapOneClearedTest)
//TEST(VectorSwap, swapEmpty) FT_DO_TEST(SwapEmptyTest)
//TEST(VectorSwap, swapCleared) FT_DO_TEST(SwapClearedTest)
//
//TEST(VectorClear, clear) FT_DO_TEST(ClearTest)
//TEST(VectorClear, clearEmpty) FT_DO_TEST(ClearEmptyTest)
//TEST(VectorClear, clearDouble) FT_DO_TEST(ClearDoubleTest)
//
//TEST(VectorInsert, insert) FT_DO_TEST(InsertTest)
//TEST(VectorInsert, insertMultiple) FT_DO_TEST(InsertMultipleTest)
//TEST(VectorInsert, insertRange) FT_DO_TEST(InsertRangeTest)
//TEST(VectorErase, erase) FT_DO_TEST(EraseTest)
//TEST(VectorErase, eraseRange) FT_DO_TEST(EraseRangeTest)
//
///*** LIST TESTS ***/
//
//TEST(ListConstructors, DefaultConstructor) FT_DO_TEST(defaultListConstructorTest)
//TEST(ListConstructors, ZeroElementsConstructor) FT_DO_TEST(zeroElementsListConstructorTest)
//TEST(ListConstructors, TwentyElementsConstructor) FT_DO_TEST(twentyElementsListConstructorTest)
//TEST(ListConstructors, TwentyElementsWithDefaultValueConstructor) FT_DO_TEST(twentyElementsWithDefaultValueListConstructorTest)
//TEST(ListConstructors, IteratorConstructor)  FT_DO_TEST(iteratorListConstructorTest)
//TEST(ListConstructors, CopyConstructor)  FT_DO_TEST(copyListConstructorTest)
//
//TEST(ListAssignation, ListAssignationBothEmpty) FT_DO_TEST(listAssignationBothEmptyTest)
//TEST(ListAssignation, ListAssignationBothNotEmpty) FT_DO_TEST(listAssignationBothNotEmptyTest)
//TEST(ListAssignation, ListAssignationToEmpty) FT_DO_TEST(listAssignationToEmptyTest)
//TEST(ListAssignation, ListAssignationFromEmpty) FT_DO_TEST(listAssignationFromEmptyTest)
//
//TEST(ListAssignationFunction, ListAssignationFunctionBothEmpty) FT_DO_TEST(listAssignationFunctionBothEmptyTest)
//TEST(ListAssignationFunction, ListAssignationFunctionBothNotEmpty) FT_DO_TEST(listAssignationFunctionBothNotEmptyTest)
//TEST(ListAssignationFunction, ListAssignationFunctionToEmpty) FT_DO_TEST(listAssignationFunctionToEmptyTest)
//TEST(ListAssignationFunction, ListAssignationFunctionFromEmpty) FT_DO_TEST(listAssignationFunctionFromEmptyTest)
//TEST(ListAssignationFunction, ListAssignationFunctionSizeZero) FT_DO_TEST(listAssignationFunctionSizeZeroTest)
//TEST(ListAssignationFunction, ListAssignationFunctionSizeZeroVal) FT_DO_TEST(listAssignationFunctionSizeZeroValTest)
//TEST(ListAssignationFunction, ListAssignationFunctionSizeNoVal) FT_DO_TEST(listAssignationFunctionSizeNoValTest)
//TEST(ListAssignationFunction, ListAssignationFunctionSizeVal) FT_DO_TEST(listAssignationFunctionSizeValTest)
//
//TEST(ListPushPop, ListPushPopFront) FT_DO_TEST(listPushPopFrontTest)
//TEST(ListPushPop, ListPushPopBack) FT_DO_TEST(listPushPopBackTest)
//TEST(ListPushPop, ListPushFrontPopBack) FT_DO_TEST(listPushFrontPopBackTest)
//TEST(ListPushPop, ListPushBackPopFront) FT_DO_TEST(listPushBackPopFrontTest)
//
//TEST(ListInsert, ListInsertSingleValues) FT_DO_TEST(listInsertSingleValuesTest)
//TEST(ListInsert, ListInsertSeveralValues) FT_DO_TEST(listInsertSeveralValuesTest)
//TEST(ListInsert, ListInsertIteratorPointedValues) FT_DO_TEST(listInsertIteratorPointedValuesTest)
//
//TEST(ListErase, ListEraseSingleValues) FT_DO_TEST(listEraseSingleValuesTest)
//TEST(ListErase, ListEraseIteratorPointedValues) FT_DO_TEST(listEraseIteratorPointedValuesTest)
//
//TEST(ListSwap, ListSwap) FT_DO_TEST(listSwapTest)
//TEST(ListSwap, ListSwapLEmpty) FT_DO_TEST(listSwapLEmptyTest)
//TEST(ListSwap, ListSwapREmpty) FT_DO_TEST(listSwapREmptyTest)
//TEST(ListSwap, ListSwapEmpty) FT_DO_TEST(listSwapBothEmptyTest)
//TEST(ListSwap, ListNonMemberSwap) FT_DO_TEST(listNonMemberSwapTest)
//TEST(ListSwap, ListNonMemberSwapLEmpty) FT_DO_TEST(listNonMemberSwapLEmptyTest)
//TEST(ListSwap, ListNonMemberSwapREmpty) FT_DO_TEST(listNonMemberSwapREmptyTest)
//TEST(ListSwap, ListNonMemberSwapEmpty) FT_DO_TEST(listNonMemberSwapBothEmptyTest)
//
//TEST(ListResize, ListResizeWithoutDefault) FT_DO_TEST(listResizeWithoutDefaultTest)
//TEST(ListResize, ListResizeWithDefault) FT_DO_TEST(listResizeWithDefaultTest)
//
//TEST(ListClear, ListClear) FT_DO_TEST(listClearTest)
//
//TEST(ListSplice, ListSpliceBegin) FT_DO_TEST(listSpliceBeginTest)
//TEST(ListSplice, ListSpliceEnd) FT_DO_TEST(listSpliceEndTest)
//TEST(ListSplice, ListSpliceRandom) FT_DO_TEST(listSpliceRandomTest)
//TEST(ListSplice, ListSpliceOneBegin) FT_DO_TEST(listSpliceOneBeginTest)
//TEST(ListSplice, ListSpliceOneEnd) FT_DO_TEST(listSpliceOneEndTest)
//TEST(ListSplice, ListSpliceOneRandom) FT_DO_TEST(listSpliceOneRandomTest)
//TEST(ListSplice, ListSpliceIterBegin) FT_DO_TEST(listSpliceIterBeginTest)
//TEST(ListSplice, ListSpliceIterEnd) FT_DO_TEST(listSpliceIterEndTest)
//TEST(ListSplice, ListSpliceIterRandom) FT_DO_TEST(listSpliceIterRandomTest)
//
//TEST(ListRemove, ListRemoveNotRandom) FT_DO_TEST(listRemoveNotRandomTest)
//TEST(ListRemove, ListRemove) FT_DO_TEST(listRemoveTest)
//TEST(ListRemove, ListRemoveAll) FT_DO_TEST(listRemoveAllTest)
//TEST(ListRemove, ListRemoveAllSame) FT_DO_TEST(listRemoveAllSameTest)
//TEST(ListRemove, ListRemoveIf) FT_DO_TEST(listRemoveIfTest)
//
//TEST(ListUnique, ListUnique) FT_DO_TEST(listUniqueTest)
//TEST(ListUnique, ListUniqueSorted) FT_DO_TEST(listUniqueSortedTest)
//TEST(ListUnique, ListUniqueCompare) FT_DO_TEST(listUniqueCompareTest)
//TEST(ListUnique, ListUniqueSortedCompare) FT_DO_TEST(listUniqueSortedCompareTest)
//
//TEST(ListMerge, ListMerge)  FT_DO_TEST(listMergeTest)
//
//TEST(ListSort, ListSortExample)  FT_DO_TEST(listSortExampleTest)
//
//TEST(ListReverse, ListReverse) FT_DO_TEST(listReverseTest)
//
//TEST(ListCompare, ListCompareEquals) FT_DO_TEST(listCompareEqualsTest)
//TEST(ListCompare, ListCompareNotEquals) FT_DO_TEST(listCompareNotEqualsTest)
//TEST(ListCompare, ListCompareLessThan) FT_DO_TEST(listCompareLessThanTest)
//TEST(ListCompare, ListCompareGreaterThan) FT_DO_TEST(listCompareGreaterThanTest)
//TEST(ListCompare, ListCompareLTE) FT_DO_TEST(listCompareLTETest)
//TEST(ListCompare, ListCompareGTE) FT_DO_TEST(listCompareGTETest)

/*** MAP TESTS ***/

TEST(MapConstructors, DefaultConstructor) FT_DO_TEST(defaultMapConstructorTest)
TEST(MapConstructors, IteratorConstructor)  FT_DO_TEST(iteratorMapConstructorTest)
TEST(MapConstructors, DefaultWithCompare) FT_DO_TEST(defaultMapWithCompareTest)
TEST(MapConstructors, IteratorWithCompare)  FT_DO_TEST(iteratorMapWithCompareTest)
TEST(MapConstructors, CopyConstructor)  FT_DO_TEST(copyMapConstructorTest)
TEST(MapConstructors, AssignOperatorEmpty) FT_DO_TEST(assignOperatorEmptyTest)
TEST(MapConstructors, AssignOperatorNotEmpty)  FT_DO_TEST(assignOperatorNotEmptyTest)
TEST(MapConstructors, AssignOperatorEmptyWithCmp) FT_DO_TEST(assignOperatorEmptyWithCmpTest)
TEST(MapConstructors, AssignOperatorNotEmptyWithCmp)  FT_DO_TEST(assignOperatorNotEmptyWithCmpTest)

TEST(MapOperatorSquare, OperSqtest) {
    std::map<char, std::string> ftv;
    std::map<char, std::string> stv;

    std::string keys = getRandomValue<std::string>();

    int i = 0;
    char k[4];

    for (std::string::size_type s = 0; s < keys.length() && s < 23; ++s) {
        std::string val = getRandomValue<std::string>();
        ftv[keys[s]] = val;
        stv[keys[s]] = val;
        if (s % 5 == 0)
            k[i++] = keys[s];
    }

    ftv[k[0]] = ftv[k[1]];
    ftv[k[2]] = ftv[k[3]];
    stv[k[0]] = stv[k[1]];
    stv[k[2]] = stv[k[3]];

    testMapContainersEqual(ftv, stv);
}

TEST(MapOperatorSquare, OperSqtestCmp) {
    std::map<char, std::string, bool (*)(char, char)> ftv(map_constructor_greater_compare<char>);
    std::map<char, std::string, bool (*)(char, char)> stv(map_constructor_greater_compare<char>);

    std::string keys = getRandomValue<std::string>();

    int i = 0;
    char k[4];

    for (std::string::size_type s = 0; s < keys.length() && s < 23; ++s) {
        std::string val = getRandomValue<std::string>();
        ftv[keys[s]] = val;
        stv[keys[s]] = val;
        if (s % 5 == 0)
            k[i++] = keys[s];
    }

    ftv[k[0]] = ftv[k[1]];
    ftv[k[2]] = ftv[k[3]];
    stv[k[0]] = stv[k[1]];
    stv[k[2]] = stv[k[3]];

    testMapContainersEqual(ftv, stv);
}

TEST(MapInsert, InsertHint)  FT_DO_TEST(mapInsertHintTest)
TEST(MapInsert, InsertIterators)  FT_DO_TEST(mapInsertIteratorsTest)

TEST(MapErase, EraseSingle)  FT_DO_TEST(mapEraseSingleTest)
TEST(MapErase, EraseKey)  FT_DO_TEST(mapEraseKeyTest)
TEST(MapErase, EraseIterators)  FT_DO_TEST(mapEraseIteratorsTest)

TEST(MapSwap, SwapEmpty)  FT_DO_TEST(mapSwapEmptyTest)
TEST(MapSwap, SwapOneEmpty)  FT_DO_TEST(mapSwapOneEmptyTest)
TEST(MapSwap, SwapNotEmpty)  FT_DO_TEST(mapSwapNotEmptyTest)

TEST(MapClear, Clear)  FT_DO_TEST(mapClearTest)
TEST(MapKeyComp, KeyComp)  FT_DO_TEST(mapKeyCompTest)
TEST(MapValComp, KeyComp)  FT_DO_TEST(mapValCompTest)

TEST(MapFind, FindExist)  FT_DO_TEST(mapFindExistTest)
TEST(MapFind, FindNotExist)  FT_DO_TEST(mapFindNotExistTest)

TEST(MapCount, CountEmpty)  FT_DO_TEST(mapCountEmptyTest)
TEST(MapCount, CountExist)  FT_DO_TEST(mapCountExistTest)
TEST(MapCount, CountNotExist)  FT_DO_TEST(mapCountNotExistTest)

//TEST(MapLowerBound, BelowMin)  FT_DO_TEST(mapLowerBoundBelowMinTest)
//TEST(MapLowerBound, AboveMax)  FT_DO_TEST(mapLowerBoundAboveMaxTest)
//TEST(MapLowerBound, Existant)  FT_DO_TEST(mapLowerBoundExistantTest)
//TEST(MapLowerBound, Random)    FT_DO_TEST(mapLowerBoundRandomTest)
//
//TEST(MapUpperBound, BelowMin)  FT_DO_TEST(mapUpperBoundBelowMinTest)
//TEST(MapUpperBound, AboveMax)  FT_DO_TEST(mapUpperBoundAboveMaxTest)
//TEST(MapUpperBound, Existant)  FT_DO_TEST(mapUpperBoundExistantTest)
//TEST(MapUpperBound, Random)    FT_DO_TEST(mapUpperBoundRandomTest)
//
//TEST(MapEqualRange, BelowMin)  FT_DO_TEST(mapEqualRangeBelowMinTest)
//TEST(MapEqualRange, AboveMax)  FT_DO_TEST(mapEqualRangeAboveMaxTest)
//TEST(MapEqualRange, Existant)  FT_DO_TEST(mapEqualRangeExistantTest)
//TEST(MapEqualRange, Random)    FT_DO_TEST(mapEqualRangeRandomTest)

/*** STACK TESTS ***/
/*** QUEUE TESTS ***/

int main(int argc, char **argv) {
    srand(time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
