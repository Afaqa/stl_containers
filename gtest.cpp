#include <vector>
#include "vector.hpp"
#include <list>
#include "list.hpp"
#include <map>
#include "map.hpp"
#include <stack>
#include "stack.hpp"
#include <queue>
#include "queue.hpp"
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

#define STL_DO_TEST(function) {\
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

namespace stl {
    template<class T1, class T2>
    bool operator==(const stl::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template<class T1, class T2>
    bool operator!=(const stl::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) { return !(lhs == rhs); }

    template<class T1, class T2>
    bool operator<(const stl::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template<class T1, class T2>
    bool operator<=(const stl::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) { return !(rhs < lhs); }

    template<class T1, class T2>
    bool operator>(const stl::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) { return rhs < lhs; }

    template<class T1, class T2>
    bool operator>=(const stl::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) { return !(lhs < rhs); }
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
void testStackContainersEqual(T const& cont1, U const& cont2) {
    const char *equals = COLOR_RED " == " COLOR_RESET;
    EXPECT_EQ(cont1.empty(), cont2.empty());
    std::cout << "Empty " << cont1.empty() << equals << cont2.empty() << std::endl;
    EXPECT_EQ(cont1.size(), cont2.size());
    std::cout << "Size " << cont1.size() << equals << cont2.size() << std::endl;
    if (cont1.size() && cont2.size()) {
        std::cout << "Top " << cont1.top() << equals << cont2.top() << std::endl;
        EXPECT_EQ(cont1.top(), cont2.top());
        std::cout << "\ttest and output values:" << std::endl;
        T contlft = cont1;
        U contrht = cont2;
        typename T::size_type i = 0;
        while (!contlft.empty() && !contrht.empty()) {
            typename T::value_type a = contlft.top();
            typename T::value_type b = contrht.top();
            contlft.pop();
            contrht.pop();
            printValues(i++, a, b);
            EXPECT_EQ(a, b);
        }
        EXPECT_EQ(contlft.size(), contrht.size());
    }
}

template<typename T, typename U>
void testQueueContainersEqual(T const& cont1, U const& cont2) {
    const char *equals = COLOR_RED " == " COLOR_RESET;
    EXPECT_EQ(cont1.empty(), cont2.empty());
    std::cout << "Empty " << cont1.empty() << equals << cont2.empty() << std::endl;
    EXPECT_EQ(cont1.size(), cont2.size());
    std::cout << "Size " << cont1.size() << equals << cont2.size() << std::endl;
    if (cont1.size() && cont2.size()) {
        std::cout << "Front " << cont1.front() << equals << cont2.front() << std::endl;
        EXPECT_EQ(cont1.front(), cont2.front());
        std::cout << "Back " << cont1.front() << equals << cont2.front() << std::endl;
        EXPECT_EQ(cont1. back(), cont2.back());
        std::cout << "\ttest and output values:" << std::endl;
        T contlft = cont1;
        U contrht = cont2;
        typename T::size_type i = 0;
        while (!contlft.empty() && !contrht.empty()) {
            typename T::value_type a = contlft.front();
            typename T::value_type b = contrht.front();
            contlft.pop();
            contrht.pop();
            printValues(i++, a, b);
            EXPECT_EQ(a, b);
        }
        EXPECT_EQ(contlft.size(), contrht.size());
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
    return rand() % 10101010 - rand() % 5050505;
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
    stl::vector<T> myv;
    std::vector<T> stv;
    testEmptyContainersEqual(myv, stv);
}

template<typename T>
void zeroElementsConstructorTest() {
    printTestName<T>("Constructor for 0 elements");
    stl::vector<T> myv(0);
    std::vector<T> stv(0);
    testEmptyContainersEqual(myv, stv);

}

template<typename T>
void twentyElementsConstructorTest() {
    printTestName<T>("Constructor for N elements");
    stl::vector<T> myv(20);
    std::vector<T> stv(20);
    testContainersEqual(myv, stv);
}

template<typename T>
void twentyElementsWithDefaultValueConstructorTest() {
    printTestName<T>("Constructor for N elements with value");
    T value = getRandomValue<T>();
    stl::vector<T> myv(20, value);
    std::vector<T> stv(20, value);
    testContainersEqual(myv, stv);
}

template<typename T>
void iteratorConstructorTest() {
    printTestName<T>("Constructor for iterators begin and end");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> fiter;
    std::vector<T>   siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value      = getRandomValue<T>();
        fiter.push_back(value);
        siter.push_back(value);
    }

    stl::vector<T> myv(fiter.begin() + 2, fiter.end() - 3);
    std::vector<T> stv(siter.begin() + 2, siter.end() - 3);
    testContainersEqual(myv, stv);
}

template<typename T>
void copyConstructorTest() {
    {
        printTestName<T>("Copy constructor for default container");
        stl::vector<T> myv_o;
        std::vector<T> stv_o;
        stl::vector<T> myv(myv_o);
        std::vector<T> stv(stv_o);
        testEmptyContainersEqual(myv, stv);
    }
    {
        printTestName<T>("Copy constructor for 0 elements");
        stl::vector<T> myv_o(0);
        std::vector<T> stv_o(0);
        stl::vector<T> myv(myv_o);
        std::vector<T> stv(stv_o);
        testEmptyContainersEqual(myv, stv);
    }
    {
        printTestName<T>("Copy constructor for N elements");
        stl::vector<T>  myv_o(20);
        std::vector<T> stv_o(20);
        stl::vector<T>  myv(myv_o);
        std::vector<T> stv(stv_o);
        testContainersEqual(myv, stv);
    }
    {
        printTestName<T>("Copy constructor for N elements with value");
        T value = getRandomValue<T>();
        stl::vector<T> myv_o(20, value);
        std::vector<T> stv_o(20, value);
        stl::vector<T> myv(myv_o);
        std::vector<T> stv(stv_o);
        testContainersEqual(myv, stv);
    }
    {
        printTestName<T>("Copy constructor for iterators begin and end");

        std::size_t numOfItems = rand() % 20 + 10;
        stl::vector<T>    fiter;
        std::vector<T>   siter;
        for (std::size_t i = 0; i < numOfItems; ++i) {
            T value = getRandomValue<T>();
            fiter.push_back(value);
            siter.push_back(value);
        }

        stl::vector<T> myv_o(fiter.begin() + 2, fiter.end() - 3);
        std::vector<T> stv_o(siter.begin() + 2, siter.end() - 3);

        stl::vector<T> myv(myv_o);
        std::vector<T> stv(stv_o);

        testContainersEqual(myv, stv);
    }
}

template<typename T>
void assignationOperatorToMoreCapTest() {
    printTestName<T>("Assignation operator to the bigger capacity");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> fiter;
    std::vector<T> siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
        siter.push_back(value);
    }

    stl::vector<T> myv_o(fiter.begin() + 2, fiter.end() - 3);
    std::vector<T> stv_o(siter.begin() + 2, siter.end() - 3);
    stl::vector<T> myv(fiter.rbegin(), fiter.rend() - 9);
    std::vector<T> stv(siter.rbegin(), siter.rend() - 9);

    myv = myv_o;
    stv = stv_o;

    testContainersEqual(myv, stv);
}


template<typename T>
void assignationOperatorToMoreSizeTest() {
    printTestName<T>("Assignation operator to the bigger size");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> fiter;
    std::vector<T> siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
        siter.push_back(value);
    }

    stl::vector<T> myv_o(fiter.begin() + 2, fiter.end() - 3);
    std::vector<T> stv_o(siter.begin() + 2, siter.end() - 3);
    stl::vector<T> myv(fiter.rbegin(), fiter.rend() - 9);
    std::vector<T> stv(siter.rbegin(), siter.rend() - 9);

    myv.reserve(fiter.size());
    stv.reserve(siter.size());
    myv = myv_o;
    stv = stv_o;

    testContainersEqual(myv, stv);
}

template<typename T>
void assignationOperatorToLessTest() {
    printTestName<T>("Assignation operator to the lesser size");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> fiter;
    std::vector<T> siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
        siter.push_back(value);
    }

    stl::vector<T> myv_o(fiter.begin() + 5, fiter.end() - 4);
    std::vector<T> stv_o(siter.begin() + 5, siter.end() - 4);
    stl::vector<T> myv(fiter.rbegin(), fiter.rend() - 2);
    std::vector<T> stv(siter.rbegin(), siter.rend() - 2);

    myv = myv_o;
    stv = stv_o;

    testContainersEqual(myv, stv);
}

template<typename T>
void assignationOperatorToSameTest() {
    printTestName<T>("Assignation operator to the same size");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> fiter;
    std::vector<T> siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
        siter.push_back(value);
    }

    stl::vector<T> myv_o(fiter.begin() + 5, fiter.end() - 4);
    std::vector<T> stv_o(siter.begin() + 5, siter.end() - 4);
    stl::vector<T> myv(fiter.rbegin() + 2, fiter.rend() - 7);
    std::vector<T> stv(siter.rbegin() + 2, siter.rend() - 7);

    myv = myv_o;
    stv = stv_o;

    testContainersEqual(myv, stv);
}

template<typename T>
void resizeLessTest() {
    printTestName<T>("Resize to a lesser value");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(myv, stv);

    myv.resize(numOfItems - 5);
    stv.resize(numOfItems - 5);

    testContainersEqual(myv, stv);
}

template<typename T>
void resizeMoreTest() {
    printTestName<T>("Resize to a bigger value");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv(5);
    std::vector<T> stv(5);
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    std::cout << "Initial data: " << std::endl;
    std::cout << "empty: " << myv.empty() << " | " << stv.empty() << std::endl;
    std::cout << "size: " << myv.size() << " | " << stv.size() << std::endl;
    std::cout << "capacity: " << myv.capacity() << " | " << stv.capacity() << std::endl;

    myv.resize(15 + myv.capacity());
    stv.resize(15 + stv.capacity());

    std::cout << "Resized data: " << std::endl;
    std::cout << "empty: " << myv.empty() << " | " << stv.empty() << std::endl;
    std::cout << "size: " << myv.size() << " | " << stv.size() << std::endl;
    std::cout << "capacity: " << myv.capacity() << " | " << stv.capacity() << std::endl;

    testContainersEqual(myv, stv);
}

template<typename T>
void resizeSameTest() {
    printTestName<T>("Resize to the same value");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(myv, stv);

    myv.resize(myv.size());
    stv.resize(stv.size());

    testContainersEqual(myv, stv);
}

template<typename T>
void reserveLessTest() {
    printTestName<T>("Reserve lesser capacity");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    typename stl::vector<T>::iterator fit_before = myv.begin();
    typename std::vector<T>::iterator sit_before = stv.begin();

    testContainersEqual(myv, stv);

    myv.reserve(myv.capacity() / 2);
    stv.reserve(stv.capacity() / 2);

    testContainersEqual(myv, stv);
    EXPECT_EQ(fit_before == myv.begin(), sit_before == stv.begin());
}

template<typename T>
void reserveMoreTest() {
    printTestName<T>("Reserve bigger capacity");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    typename stl::vector<T>::iterator fit_before = myv.begin();
    typename std::vector<T>::iterator sit_before = stv.begin();

    testContainersEqual(myv, stv);

    myv.reserve(myv.capacity() * 2);
    stv.reserve(stv.capacity() * 2);

    testContainersEqual(myv, stv);
    EXPECT_EQ(fit_before == myv.begin(), sit_before == stv.begin());
}

template<typename T>
void reserveSameTest() {
    printTestName<T>("Reserve the same capacity");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    typename stl::vector<T>::iterator fit_before = myv.begin();
    typename std::vector<T>::iterator sit_before = stv.begin();

    testContainersEqual(myv, stv);

    myv.reserve(myv.capacity());
    stv.reserve(stv.capacity());

    testContainersEqual(myv, stv);
    EXPECT_EQ(fit_before == myv.begin(), sit_before == stv.begin());
}

template<typename T>
void reserveGreaterThanMaxTest() {
    printTestName<T>("Reserver to capacity bigger than max_size");

    stl::vector<T> myv(0);
    std::vector<T> stv(0);

    std::string ferr = "success";
    std::string serr = "success";
    try {
        myv.reserve(myv.max_size() + 1);
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

    testContainersEqual(myv, stv);
    EXPECT_EQ(ferr, serr);
}

template<typename T>
void OperatorBracketsAccessTest() {
    printTestName<T>("Testing operator[]");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(myv, stv);

    std::size_t i = 0;

    while (i < myv.size() && i < stv.size()) {
        EXPECT_EQ(myv[i], stv[i]);
        ++i;
    }
}

template<typename T>
void FunctionAtTest() {
    printTestName<T>("Testing function at");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(myv, stv);

    std::size_t i = 0;

    while (i < myv.size() && i < stv.size()) {
        EXPECT_EQ(myv.at(i), stv.at(i));
        ++i;
    }
    for (int j = 0; j < 5; ++j) {
        std::string ferr = "success";
        std::string serr = "success";
        try { myv.at(i); }
        catch (std::out_of_range &e) { ferr = e.what(); }
        try { stv.at(i); }
        catch (std::out_of_range &e) { serr = e.what(); }
        EXPECT_EQ(ferr, serr);
        ++i;
    }
    myv.clear();
    stv.clear();
    std::string ferr = "success";
    std::string serr = "success";
    try { myv.at(0); }
    catch (std::out_of_range &e) { ferr = e.what(); }
    try { stv.at(0); }
    catch (std::out_of_range &e) { serr = e.what(); }
    EXPECT_EQ(ferr, serr);
}

template<typename T>
void FunctionFrontTest() {
    printTestName<T>("Testing function front");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(myv, stv);
    EXPECT_EQ(myv.front(), stv.front());
}

template<typename T>
void FunctionBackTest() {
    printTestName<T>("Testing function back");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(myv, stv);
    EXPECT_EQ(myv.back(), stv.back());
}

template<typename T>
void AssignFillLessTest() {
    printTestName<T>("Testing assign with size lesser than cap");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(myv, stv);

    T value = getRandomValue<T>();
    myv.assign(myv.capacity() * .7, value);
    stv.assign(stv.capacity() * .7, value);

    testContainersEqual(myv, stv);
}

template<typename T>
void AssignFillBetweenSizeCapTest() {
    printTestName<T>("Testing assign with size between size and cap");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(myv, stv);

    myv.resize(myv.capacity() * 2);
    stv.resize(stv.capacity() * 2);
    T value = getRandomValue<T>();
    myv.assign(myv.capacity() * 1.5, value);
    stv.assign(stv.capacity() * 1.5, value);

    testContainersEqual(myv, stv);
}

template<typename T>
void AssignFillMoreTest() {
    printTestName<T>("Testing assign with size more than cap");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(myv, stv);

    T value = getRandomValue<T>();
    myv.assign(myv.capacity() * 1.6, value);
    stv.assign(stv.capacity() * 1.6, value);

    testContainersEqual(myv, stv);
}

template<typename T>
void AssignFillMaxSizeTest() {
    printTestName<T>("Testing assign with maximum size");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(myv, stv);

    bool serr = false, ferr = serr;
    std::string fmsg = "success";
    std::string smsg = "success";
    T value = getRandomValue<T>();
    try {
        myv.assign(myv.max_size(), value);
    } catch(std::exception& e) { fmsg = e.what(); ferr = true; }
    try {
        stv.assign(stv.max_size(), value);
    } catch(std::exception& e) { smsg = e.what(); serr = true; }
    EXPECT_EQ(ferr, serr);
    EXPECT_EQ(fmsg, smsg);
    testContainersEqual(myv, stv);
}

template<typename T>
void AssignFillMoreThanMaxTest() {
    printTestName<T>("Testing assign with size more than the maximum cap");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(myv, stv);

    bool err = false;
    std::string fmsg = "success";
    std::string smsg = "success";
    T value = getRandomValue<T>();
    try {
        myv.assign(myv.max_size() + 1, value);
    } catch(std::exception& e) { fmsg = e.what(); err = true; }
    try {
        stv.assign(stv.max_size() + 1, value);
    } catch(std::exception& e) { smsg = e.what(); err = true; }

    EXPECT_EQ(fmsg, smsg);
    testContainersEqual(myv, stv);

    value = getRandomValue<T>();
    myv.push_back(value);
    stv.push_back(value);

    testContainersEqual(myv, stv);
}

template<typename T>
void AssignFillSameTest() {
    printTestName<T>("Testing assign with same size as cap");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(myv, stv);

    T value = getRandomValue<T>();
    myv.assign(myv.capacity(), value);
    stv.assign(stv.capacity(), value);

    testContainersEqual(myv, stv);
}

template<typename T>
void PushBackTest() {
    printTestName<T>("Testing push back on empty container with few values");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    testContainersEqual(myv, stv);
}

template<typename T>
void PopBackTest() {
    printTestName<T>("Testing pop back on small container size with every delete state check (overkill?)");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }

    while (!(myv.empty() || stv.empty())) {
        myv.pop_back();
        stv.pop_back();
        testContainersEqual(myv, stv);
    }

    testContainersEqual(myv, stv);
}

template<typename T>
void SwapTest() {
    printTestName<T>("Testing swap for a slightly filled container");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(myv, stv);

    stl::vector<T> myv_sw;
    std::vector<T> stv_sw;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv_sw.push_back(value);
        stv_sw.push_back(value);
    }
    testContainersEqualNoprint(myv_sw, stv_sw);

    stl::swap(myv, myv_sw);
    std::swap(stv, stv_sw);

    testContainersEqualNoprint(myv_sw, stv_sw);
    testContainersEqual(myv, stv);
}

template<typename T>
void SwapOneEmptyTest() {
    printTestName<T>("Testing swap with one of containers initially empty");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(myv, stv);

    stl::vector<T> myv_sw;
    std::vector<T> stv_sw;
    testContainersEqualNoprint(myv_sw, stv_sw);

    stl::swap(myv, myv_sw);
    std::swap(stv, stv_sw);

    testContainersEqual(myv_sw, stv_sw);
    testContainersEqual(myv, stv);
}

template<typename T>
void SwapOneClearedTest() {
    printTestName<T>("Testing swap with one of containers cleared");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(myv, stv);

    stl::vector<T> myv_sw;
    std::vector<T> stv_sw;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv_sw.push_back(value);
        stv_sw.push_back(value);
    }
    myv_sw.clear();
    stv_sw.clear();
    testContainersEqualNoprint(myv_sw, stv_sw);

    stl::swap(myv, myv_sw);
    std::swap(stv, stv_sw);

    testContainersEqual(myv_sw, stv_sw);
    testContainersEqual(myv, stv);
}

template<typename T>
void SwapEmptyTest() {
    printTestName<T>("Testing swap with both containers initially empty");

    stl::vector<T> myv;
    std::vector<T> stv;
    testContainersEqualNoprint(myv, stv);

    stl::vector<T> myv_sw;
    std::vector<T> stv_sw;
    testContainersEqualNoprint(myv_sw, stv_sw);

    stl::swap(myv, myv_sw);
    std::swap(stv, stv_sw);

    testContainersEqual(myv_sw, stv_sw);
    testContainersEqual(myv, stv);
}

template<typename T>
void SwapClearedTest() {
    printTestName<T>("Testing swap with both containers cleared");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }
    myv.clear();
    stv.clear();
    testContainersEqualNoprint(myv, stv);

    stl::vector<T> myv_sw;
    std::vector<T> stv_sw;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv_sw.push_back(value);
        stv_sw.push_back(value);
    }
    myv_sw.clear();
    stv_sw.clear();
    testContainersEqualNoprint(myv_sw, stv_sw);

    stl::swap(myv, myv_sw);
    std::swap(stv, stv_sw);

    testContainersEqual(myv_sw, stv_sw);
    testContainersEqual(myv, stv);
}

template<typename T>
void ClearTest() {
    printTestName<T>("Testing clear on slightly filled container");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(myv, stv);

    myv.clear();
    stv.clear();
    testContainersEqual(myv, stv);
}

template<typename T>
void ClearEmptyTest() {
    printTestName<T>("Testing clear on initially empty container");

    stl::vector<T> myv;
    std::vector<T> stv;
    testContainersEqualNoprint(myv, stv);

    myv.clear();
    stv.clear();
    testContainersEqual(myv, stv);
}

template<typename T>
void ClearDoubleTest() {
    printTestName<T>("Testing clear on already cleared container");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(myv, stv);

    myv.clear();
    stv.clear();
    testContainersEqualNoprint(myv, stv);

    myv.clear();
    stv.clear();
    testContainersEqual(myv, stv);
}

template<typename T>
void InsertTest() {
    printTestName<T>("Testing insert single value into container");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(myv, stv);

    T value = getRandomValue<T>();
    myv.insert(++++++++myv.begin(), value);
    stv.insert(++++++++stv.begin(), value);
    value = getRandomValue<T>();
    myv.insert(----------------myv.end(), value);
    stv.insert(----------------stv.end(), value);
    testContainersEqual(myv, stv);
}

template<typename T>
void InsertMultipleTest() {
    printTestName<T>("Testing insert multiple copies of value into container");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(myv, stv);

    T value = getRandomValue<T>();
    myv.insert(++++++++myv.begin(), 12, value);
    stv.insert(++++++++stv.begin(), 12, value);
    value = getRandomValue<T>();
    myv.insert(--------------------myv.end(), 7, value);
    stv.insert(--------------------stv.end(), 7, value);
    testContainersEqual(myv, stv);
}

template<typename T>
void InsertRangeTest() {
    printTestName<T>("Testing insert iterators range into container");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    std::vector<T> range;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
        range.push_back(value);
    }
    testContainersEqualNoprint(myv, stv);

    myv.insert(++++++++myv.begin(), range.begin(), range.end());
    stv.insert(++++++++stv.begin(), range.begin(), range.end());
    myv.insert(----------------myv.end(), ++++++++range.begin(), ----range.end());
    stv.insert(----------------stv.end(), ++++++++range.begin(), ----range.end());
    testContainersEqual(myv, stv);
}

template<typename T>
void EraseTest() {
    printTestName<T>("Testing erase single value from container");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(myv, stv);

    auto ferend = myv.erase(++++++++myv.begin());
    auto serend = stv.erase(++++++++stv.begin());
    EXPECT_EQ(*ferend, *serend);
    ferend = myv.erase(----------------myv.end());
    serend = stv.erase(----------------stv.end());
    EXPECT_EQ(*ferend, *serend);
    testContainersEqual(myv, stv);
}

template<typename T>
void EraseRangeTest() {
    printTestName<T>("Testing erase range of values from container");

    std::size_t numOfItems = rand() % 20 + 20;
    stl::vector<T> myv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(myv, stv);

    auto ferend = myv.erase(++++++++++++++myv.begin(), ------myv.end());
    auto serend = stv.erase(++++++++++++++stv.begin(), ------stv.end());
    EXPECT_EQ(*ferend, *serend);
    ferend = myv.erase(----------------myv.end(), myv.end());
    serend = stv.erase(----------------stv.end(), stv.end());
    EXPECT_EQ(*--ferend, *--serend);
    testContainersEqual(myv, stv);
}

template<typename T>
void defaultListConstructorTest() {
    printTestName<T>("Default constructor");
    stl::list<T> myv;
    std::list<T> stv;
    testListContainersEqual(myv, stv);
}

template<typename T>
void zeroElementsListConstructorTest() {
    printTestName<T>("Constructor for 0 elements");
    stl::list<T> myv(0);
    std::list<T> stv(0);
    testListContainersEqual(myv, stv);

}

template<typename T>
void twentyElementsListConstructorTest() {
    printTestName<T>("Constructor for N elements");
    stl::list<T> myv(20);
    std::list<T> stv(20);
    testListContainersEqual(myv, stv);
}

template<typename T>
void twentyElementsWithDefaultValueListConstructorTest() {
    printTestName<T>("Constructor for N elements with value");
    T value = getRandomValue<T>();
    stl::list<T> myv(20, value);
    std::list<T> stv(20, value);
    testListContainersEqual(myv, stv);
}

template<typename T>
void iteratorListConstructorTest() {
    printTestName<T>("Constructor for iterators begin and end");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::list<T> fiter;
    std::list<T>   siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value      = getRandomValue<T>();
        fiter.push_back(value);
        siter.push_back(value);
    }

    typename stl::list<T>::iterator lit = fiter.begin();
    stl::advance(lit, 2);
    typename stl::list<T>::iterator rit = fiter.begin();
    stl::advance(rit, -3);
    stl::list<T> myv(lit, rit);
    typename std::list<T>::iterator lsit = siter.begin();
    stl::advance(lsit, 2);
    typename std::list<T>::iterator rsit = siter.begin();
    stl::advance(rsit, -3);
    std::list<T> stv(lsit, rsit);
    testListContainersEqual(myv, stv);
}

template<typename T>
void copyListConstructorTest() {
    {
        printTestName<T>("Copy constructor for default container");
        stl::list<T> myv_o;
        std::list<T> stv_o;
        stl::list<T> myv(myv_o);
        std::list<T> stv(stv_o);
        testListContainersEqual(myv, stv);
    }
    {
        printTestName<T>("Copy constructor for 0 elements");
        stl::list<T> myv_o(0);
        std::list<T> stv_o(0);
        stl::list<T> myv(myv_o);
        std::list<T> stv(stv_o);
        testListContainersEqual(myv, stv);
    }
    {
        printTestName<T>("Copy constructor for N elements");
        stl::list<T>  myv_o(20);
        std::list<T> stv_o(20);
        stl::list<T>  myv(myv_o);
        std::list<T> stv(stv_o);
        testListContainersEqual(myv, stv);
    }
    {
        printTestName<T>("Copy constructor for N elements with value");
        T value = getRandomValue<T>();
        stl::list<T> myv_o(20, value);
        std::list<T> stv_o(20, value);
        stl::list<T> myv(myv_o);
        std::list<T> stv(stv_o);
        testListContainersEqual(myv, stv);
    }
    {
        printTestName<T>("Copy constructor for iterators begin and end");

        std::size_t numOfItems = rand() % 20 + 10;
        stl::list<T>    fiter;
        std::list<T>   siter;
        for (std::size_t i = 0; i < numOfItems; ++i) {
            T value = getRandomValue<T>();
            fiter.push_back(value);
            siter.push_back(value);
        }

        typename stl::list<T>::iterator lit = fiter.begin();
        stl::advance(lit, 2);
        typename stl::list<T>::iterator rit = fiter.begin();
        stl::advance(rit, -3);
        stl::list<T> myv_o(lit, rit);
        typename std::list<T>::iterator lsit = siter.begin();
        stl::advance(lsit, 2);
        typename std::list<T>::iterator rsit = siter.begin();
        stl::advance(rsit, -3);
        std::list<T> stv_o(lsit, rsit);

        stl::list<T> myv(myv_o);
        std::list<T> stv(stv_o);

        testListContainersEqual(myv, stv);
    }
}

template<typename T>
void listAssignationBothEmptyTest() {
    printTestName<T>("List Assignation operator of empty lists");

    stl::list<T> myv_o;
    std::list<T> stv_o;
    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv, stv);

    myv = myv_o;
    stv = stv_o;

    testListContainersEqual(myv, stv);
}

template<typename T>
void listAssignationBothNotEmptyTest() {
    printTestName<T>("List Assignation operator of non empty lists");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> fiter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
    }

    stl::list<T> myv_o(fiter.begin() + 2, fiter.end() - 3);
    std::list<T> stv_o(fiter.begin() + 2, fiter.end() - 3);
    stl::list<T> myv(fiter.rbegin(), fiter.rend() - 9);
    std::list<T> stv(fiter.rbegin(), fiter.rend() - 9);

    testListContainersEqual(myv_o, stv_o);
    testListContainersEqual(myv, stv);

    myv = myv_o;
    stv = stv_o;

    testListContainersEqual(myv, stv);
}

template<typename T>
void listAssignationToEmptyTest() {
    printTestName<T>("List Assignation operator to empty lists");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> fiter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
    }

    stl::list<T> myv_o(fiter.begin() + 2, fiter.end() - 3);
    std::list<T> stv_o(fiter.begin() + 2, fiter.end() - 3);
    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv_o, stv_o);
    testListContainersEqual(myv, stv);

    myv = myv_o;
    stv = stv_o;

    testListContainersEqual(myv, stv);
}

template<typename T>
void listAssignationFromEmptyTest() {
    printTestName<T>("List Assignation operator From empty lists");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> fiter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
    }

    stl::list<T> myv_o;
    std::list<T> stv_o;
    stl::list<T> myv(fiter.rbegin(), fiter.rend() - 9);
    std::list<T> stv(fiter.rbegin(), fiter.rend() - 9);

    testListContainersEqual(myv_o, stv_o);
    testListContainersEqual(myv, stv);

    myv = myv_o;
    stv = stv_o;

    testListContainersEqual(myv, stv);
}

template<typename T>
void listAssignationFunctionBothEmptyTest() {
    printTestName<T>("List Assignation function of empty lists");

    stl::list<T> myv_o;
    std::list<T> stv_o;
    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv, stv);

    myv.assign(myv_o.begin(), myv_o.end());
    stv.assign(stv_o.begin(), stv_o.end());

    testListContainersEqual(myv, stv);
}

template<typename T>
void listAssignationFunctionBothNotEmptyTest() {
    printTestName<T>("List Assignation function of non empty lists");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> fiter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
    }

    stl::list<T> myv_o(fiter.begin() + 2, fiter.end() - 3);
    std::list<T> stv_o(fiter.begin() + 2, fiter.end() - 3);
    stl::list<T> myv(fiter.rbegin(), fiter.rend() - 9);
    std::list<T> stv(fiter.rbegin(), fiter.rend() - 9);

    testListContainersEqual(myv_o, stv_o);
    testListContainersEqual(myv, stv);

    myv.assign(myv_o.begin(), myv_o.end());
    stv.assign(stv_o.begin(), stv_o.end());

    testListContainersEqual(myv, stv);
}

template<typename T>
void listAssignationFunctionToEmptyTest() {
    printTestName<T>("List Assignation function to empty lists");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> fiter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
    }

    stl::list<T> myv_o(fiter.begin() + 2, fiter.end() - 3);
    std::list<T> stv_o(fiter.begin() + 2, fiter.end() - 3);
    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv_o, stv_o);
    testListContainersEqual(myv, stv);

    myv.assign(myv_o.begin(), myv_o.end());
    stv.assign(stv_o.begin(), stv_o.end());

    testListContainersEqual(myv, stv);
}

template<typename T>
void listAssignationFunctionFromEmptyTest() {
    printTestName<T>("List Assignation function From empty lists");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T> fiter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        fiter.push_back(value);
    }

    stl::list<T> myv_o;
    std::list<T> stv_o;
    stl::list<T> myv(fiter.rbegin(), fiter.rend() - 9);
    std::list<T> stv(fiter.rbegin(), fiter.rend() - 9);

    testListContainersEqual(myv_o, stv_o);
    testListContainersEqual(myv, stv);

    myv.assign(myv_o.begin(), myv_o.end());
    stv.assign(stv_o.begin(), stv_o.end());

    testListContainersEqual(myv, stv);
}

template<typename T>
void listAssignationFunctionSizeZeroTest() {
    printTestName<T>("List Assignation function with size 0 and default value");

    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv, stv);

    myv.assign(0, T());
    stv.assign(0, T());

    testListContainersEqual(myv, stv);
}

template<typename T>
void listAssignationFunctionSizeZeroValTest() {
    printTestName<T>("List Assignation function with size 0 and random value");

    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv, stv);

    T val = getRandomValue<T>();
    myv.assign(0, val);
    stv.assign(0, val);

    testListContainersEqual(myv, stv);
}

template<typename T>
void listAssignationFunctionSizeNoValTest() {
    printTestName<T>("List Assignation function with random size and default value");

    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv, stv);

    int size = rand() % 20 + 10;
    myv.assign(size, T());
    stv.assign(size, T());

    testListContainersEqual(myv, stv);
}

template<typename T>
void listAssignationFunctionSizeValTest() {
    printTestName<T>("List Assignation function with random size and random value");

    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv, stv);

    int size = rand() % 20 + 10;
    T val = getRandomValue<T>();
    myv.assign(size, val);
    stv.assign(size, val);

    testListContainersEqual(myv, stv);
}

template<typename T>
void listPushPopFrontTest() {
    printTestName<T>("List push_front some values, then pop_front values until empty with middle checks");

    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv, stv);
    int size = rand() % 20 + 20;
    int i = 0;
    for (; i < size / 2; ++i) {
        T val = getRandomValue<T>();
        myv.push_front(val);
        stv.push_front(val);
    }
    testListContainersEqual(myv, stv);
    for (; i < size; ++i) {
        T val = getRandomValue<T>();
        myv.push_front(val);
        stv.push_front(val);
    }
    testListContainersEqual(myv, stv);
    for (i = 0; i < size / 3; ++i) {
        myv.pop_front();
        stv.pop_front();
    }
    testListContainersEqual(myv, stv);
    for (; i < size; ++i) {
        myv.pop_front();
        stv.pop_front();
    }
    testListContainersEqual(myv, stv);
}

template<typename T>
void listPushPopBackTest() {
    printTestName<T>("List push_back some values, then pop_back values until empty with middle checks");

    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv, stv);
    int size = rand() % 20 + 20;
    int i = 0;
    for (; i < size / 2; ++i) {
        T val = getRandomValue<T>();
        myv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(myv, stv);
    for (; i < size; ++i) {
        T val = getRandomValue<T>();
        myv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(myv, stv);
    for (i = 0; i < size / 3; ++i) {
        myv.pop_back();
        stv.pop_back();
    }
    testListContainersEqual(myv, stv);
    for (; i < size; ++i) {
        myv.pop_back();
        stv.pop_back();
    }
    testListContainersEqual(myv, stv);
}

template<typename T>
void listPushFrontPopBackTest() {
    printTestName<T>("List push_front some values, then pop_back values until empty with middle checks");

    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv, stv);
    int size = rand() % 20 + 20;
    int i = 0;
    for (; i < size / 2; ++i) {
        T val = getRandomValue<T>();
        myv.push_front(val);
        stv.push_front(val);
    }
    testListContainersEqual(myv, stv);
    for (; i < size; ++i) {
        T val = getRandomValue<T>();
        myv.push_front(val);
        stv.push_front(val);
    }
    testListContainersEqual(myv, stv);
    for (i = 0; i < size / 3; ++i) {
        myv.pop_back();
        stv.pop_back();
    }
    testListContainersEqual(myv, stv);
    for (; i < size; ++i) {
        myv.pop_back();
        stv.pop_back();
    }
    testListContainersEqual(myv, stv);
}

template<typename T>
void listPushBackPopFrontTest() {
    printTestName<T>("List push_back some values, then pop_front values until empty with middle checks");

    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv, stv);
    int size = rand() % 20 + 20;
    int i = 0;
    for (; i < size / 2; ++i) {
        T val = getRandomValue<T>();
        myv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(myv, stv);
    for (; i < size; ++i) {
        T val = getRandomValue<T>();
        myv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(myv, stv);
    for (i = 0; i < size / 3; ++i) {
        myv.pop_front();
        stv.pop_front();
    }
    testListContainersEqual(myv, stv);
    for (; i < size; ++i) {
        myv.pop_front();
        stv.pop_front();
    }
    testListContainersEqual(myv, stv);
}

template<typename T>
void listInsertSingleValuesTest() {
    printTestName<T>("List inset single values into different positions");

    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv, stv);

    int size = rand() % 10 + 10;
    myv.insert(myv.end(), T());
    stv.insert(stv.end(), T());
    myv.insert(myv.begin(), T());
    stv.insert(stv.begin(), T());
    for (int i = 2; i < size; ++i) {
        T val = getRandomValue<T>();
        myv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(myv, stv);

    typename stl::list<T>::iterator fit;
    typename std::list<T>::iterator sit;
    for (int i = 0; i < 8; ++i) {
        int position = rand() % (size + i + 1);
        T value = getRandomValue<T>();
        fit = myv.begin();
        stl::advance(fit, position);
        typename stl::list<T>::iterator fret = myv.insert(fit, value);
        EXPECT_EQ(--fit, fret);
        sit = stv.begin();
        while (position--)
            ++sit;
        typename std::list<T>::iterator sret = stv.insert(sit, value);
        EXPECT_EQ(--sit, sret);
    }
    testListContainersEqual(myv, stv);
}

template<typename T>
void listInsertSeveralValuesTest() {
    printTestName<T>("List inset multiple values into different positions");

    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv, stv);

    int size = rand() % 10 + 10;
    for (int i = 0; i < size; ++i) {
        T val = getRandomValue<T>();
        myv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(myv, stv);

    typename stl::list<T>::iterator fit;
    typename std::list<T>::iterator sit;
    for (int i = 0; i < 8; ++i) {
        int position = rand() % (size + i + 1);
        int amount = rand() % 5 + 1;
        T value = getRandomValue<T>();
        fit = myv.begin();
        stl::advance(fit, position);
        myv.insert(fit, amount, value);
        sit = stv.begin();
        while (position--)
            ++sit;
        stv.insert(sit, amount, value);
    }
    testListContainersEqual(myv, stv);
}

template<typename T>
void listInsertIteratorPointedValuesTest() {
    printTestName<T>("List inset iterated data into different positions");

    const int data_len = 20;
    T data[data_len];
    for (int i = 0; i < data_len; ++i) {
        data[i] = getRandomValue<T>();
    }

    stl::list<T> myv;
    std::list<T> stv;

    testListContainersEqual(myv, stv);

    int size = rand() % 10 + 10;
    for (int i = 0; i < size; ++i) {
        T val = getRandomValue<T>();
        myv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(myv, stv);

    typename stl::list<T>::iterator fit;
    typename std::list<T>::iterator sit;
    for (int i = 0; i < 8; ++i) {
        int position = rand() % (size + i + 1);
        int iter_start = rand() % data_len;
        int iter_end = rand() % data_len;
        if (iter_start > iter_end)
            stl::swap(iter_start, iter_end);
        fit = myv.begin();
        stl::advance(fit, position);
        myv.insert(fit, stl::input_iterator<T>(data + iter_start), stl::input_iterator<T>(data + iter_end));
        sit = stv.begin();
        while (position--)
            ++sit;
        stv.insert(sit, stl::input_iterator<T>(data + iter_start), stl::input_iterator<T>(data + iter_end));
    }
    testListContainersEqual(myv, stv);
}

template<typename T>
void listEraseSingleValuesTest() {
    printTestName<T>("List erase single values from different positions");

    stl::list<T> myv;
    std::list<T> stv;

    int size = rand() % 50 + 50;
    for (int i = 0; i < size; ++i) {
        T val = getRandomValue<T>();
        myv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(myv, stv);

    typename stl::list<T>::iterator fit;
    typename std::list<T>::iterator sit;
    for (int i = 0; i < 25; ++i) {
        int position = rand() % (myv.size() - 10);
        fit = myv.begin();
        stl::advance(fit, position);
        sit = stv.begin();
        while (position--)
            ++sit;
        typename stl::list<T>::iterator ffin;
        typename std::list<T>::iterator sfin;
        typename stl::list<T>::iterator ffinpre = fit;
        --ffinpre;
        typename std::list<T>::iterator sfinpre = sit;
        --sfinpre;
        ffin = myv.erase(fit);
        sfin = stv.erase(sit);
        EXPECT_EQ(ffin, ++ffinpre);
        EXPECT_EQ(sfin, ++sfinpre);
    }
    testListContainersEqual(myv, stv);
}

template<typename T>
void listEraseIteratorPointedValuesTest() {
    printTestName<T>("List erase iterated data from different positions");

    stl::list<T> myv;
    std::list<T> stv;

    int size = rand() % 50 + 50;
    for (int i = 0; i < size; ++i) {
        T val = getRandomValue<T>();
        myv.push_back(val);
        stv.push_back(val);
    }
    testListContainersEqual(myv, stv);

    typename stl::list<T>::iterator fitst;
    typename stl::list<T>::iterator fiten;
    typename std::list<T>::iterator sitst;
    typename std::list<T>::iterator siten;
    for (int i = 0; i < 4; ++i) {
        int iter_start = rand() % (myv.size() - 10);
        int iter_end = rand() % 10;
        fitst = myv.begin();
        stl::advance(fitst, iter_start);
        fiten = fitst;
        stl::advance(fiten, iter_end);
        sitst = stv.begin();
        while (iter_start--)
            ++sitst;
        siten = sitst;
        while (iter_end--)
            ++siten;
        typename stl::list<T>::iterator ffin;
        typename std::list<T>::iterator sfin;
        typename stl::list<T>::iterator ffinpre = fitst;
        ffinpre--;
        typename std::list<T>::iterator sfinpre = sitst;
        sfinpre--;
        ffin = myv.erase(fitst, fiten);
        sfin = stv.erase(sitst, siten);
        EXPECT_EQ(ffin, ++ffinpre);
        EXPECT_EQ(sfin, ++sfinpre);
    }
    testListContainersEqual(myv, stv);
}

template<typename T>
void listSwapTest() {
    printTestName<T>("Testing list swap");
    stl::list<T> mylist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    stl::list<T> mylist2;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        mylist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
    mylist.swap(mylist2);
    stdlist.swap(stdlist2);
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
}

template<typename T>
void listSwapLEmptyTest() {
    printTestName<T>("Testing list swap");
    stl::list<T> mylist;
    std::list<T> stdlist(mylist.begin(), mylist.end());
    stl::list<T> mylist2;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        mylist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
    mylist.swap(mylist2);
    stdlist.swap(stdlist2);
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
}

template<typename T>
void listSwapREmptyTest() {
    printTestName<T>("Testing list swap");
    stl::list<T> mylist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    stl::list<T> mylist2;
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
    mylist.swap(mylist2);
    stdlist.swap(stdlist2);
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
}

template<typename T>
void listSwapBothEmptyTest() {
    printTestName<T>("Testing list swap");
    stl::list<T> mylist;
    std::list<T> stdlist(mylist.begin(), mylist.end());
    stl::list<T> mylist2;
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
    mylist.swap(mylist2);
    stdlist.swap(stdlist2);
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
}

template<typename T>
void listNonMemberSwapTest() {
    printTestName<T>("Testing list non-member swap");
    stl::list<T> mylist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    stl::list<T> mylist2;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        mylist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
    stl::swap(mylist, mylist2);
    std::swap(stdlist, stdlist2);
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
}

template<typename T>
void listNonMemberSwapLEmptyTest() {
    printTestName<T>("Testing list non-member swap");
    stl::list<T> mylist;
    std::list<T> stdlist(mylist.begin(), mylist.end());
    stl::list<T> mylist2;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        mylist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
    stl::swap(mylist, mylist2);
    std::swap(stdlist, stdlist2);
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
}

template<typename T>
void listNonMemberSwapREmptyTest() {
    printTestName<T>("Testing list non-member swap");
    stl::list<T> mylist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    stl::list<T> mylist2;
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
    stl::swap(mylist, mylist2);
    std::swap(stdlist, stdlist2);
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
}

template<typename T>
void listNonMemberSwapBothEmptyTest() {
    printTestName<T>("Testing list non-member swap");
    stl::list<T> mylist;
    std::list<T> stdlist(mylist.begin(), mylist.end());
    stl::list<T> mylist2;
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
    stl::swap(mylist, mylist2);
    std::swap(stdlist, stdlist2);
    testListContainersEqual(mylist, stdlist);
    testListContainersEqual(mylist2, stdlist2);
}

template<typename T>
void listResizeWithoutDefaultTest() {
    printTestName<T>("Testing list resize without default value");
    stl::list<T> mylist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    testListContainersEqual(mylist, stdlist);
    mylist.resize(50);
    stdlist.resize(50);
    testListContainersEqual(mylist, stdlist);
    mylist.resize(12);
    stdlist.resize(12);
    testListContainersEqual(mylist, stdlist);
    mylist.resize(27);
    stdlist.resize(27);
    testListContainersEqual(mylist, stdlist);
    mylist.resize(0);
    stdlist.resize(0);
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listResizeWithDefaultTest() {
    printTestName<T>("Testing list resize with default value");
    stl::list<T> mylist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    testListContainersEqual(mylist, stdlist);
    T value = getRandomValue<T>();
    mylist.resize(50, value);
    stdlist.resize(50, value);
    testListContainersEqual(mylist, stdlist);
    value = getRandomValue<T>();
    mylist.resize(12, value);
    stdlist.resize(12, value);
    testListContainersEqual(mylist, stdlist);
    value = getRandomValue<T>();
    mylist.resize(0, value);
    stdlist.resize(0, value);
    testListContainersEqual(mylist, stdlist);
    value = getRandomValue<T>();
    mylist.resize(27, value);
    stdlist.resize(27, value);
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listClearTest() {
    printTestName<T>("Testing clear on empty and not empty list");
    stl::list<T> mylist;
    for (std::size_t i = 0; i < rand() % 30; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    testListContainersEqual(mylist, stdlist);
    mylist.clear();
    stdlist.clear();
    testListContainersEqual(mylist, stdlist);
    mylist.clear();
    stdlist.clear();
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listSpliceBeginTest() {
    printTestName<T>("Testing list splice full list into begin");
    stl::list<T> mylist;
    stl::list<T> mylist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    typename stl::list<T>::iterator fit = mylist.begin();
    typename std::list<T>::iterator sit = stdlist.begin();
    mylist.splice(fit, mylist2);
    stdlist.splice(sit, stdlist2);
    testListContainersEqual(mylist, stdlist);
    mylist.splice(fit, mylist2);
    stdlist.splice(sit, stdlist2);
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listSpliceEndTest() {
    printTestName<T>("Testing list splice full list into end");
    stl::list<T> mylist;
    stl::list<T> mylist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    typename stl::list<T>::iterator fit = mylist.end();
    typename std::list<T>::iterator sit = stdlist.end();
    mylist.splice(fit, mylist2);
    stdlist.splice(sit, stdlist2);
    testListContainersEqual(mylist, stdlist);
    mylist.splice(fit, mylist2);
    stdlist.splice(sit, stdlist2);
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listSpliceRandomTest() {
    printTestName<T>("Testing list splice full list into random position");
    stl::list<T> mylist;
    stl::list<T> mylist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    int position = rand() % (mylist.size() - 1) + 1;
    typename stl::list<T>::iterator fit = mylist.begin();
    stl::advance(fit, position);
    typename std::list<T>::iterator sit = stdlist.begin();
    for (int i = position; i--;)
        ++sit;
    mylist.splice(fit, mylist2);
    stdlist.splice(sit, stdlist2);
    testListContainersEqual(mylist, stdlist);
    mylist.splice(fit, mylist2);
    stdlist.splice(sit, stdlist2);
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listSpliceOneBeginTest() {
    printTestName<T>("Testing list splice one iterator of list into begin");
    stl::list<T> mylist;
    stl::list<T> mylist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    // position where to place
    typename stl::list<T>::iterator fit = mylist.begin();
    typename std::list<T>::iterator sit = stdlist.begin();
    // position what to place
    int x_pos = rand() % (mylist2.size() - 1);
    typename stl::list<T>::iterator xfit = mylist2.begin();
    stl::advance(xfit, x_pos);
    typename std::list<T>::iterator xsit = stdlist2.begin();
    for (int i = x_pos; i--;)
        ++xsit;
    mylist.splice(fit, mylist2, xfit);
    stdlist.splice(sit, stdlist2, xsit);
    testListContainersEqual(mylist, stdlist);
    // position what to place
    x_pos = rand() % (mylist2.size() - 1);
    xfit = mylist2.begin();
    stl::advance(xfit, x_pos);
    xsit = stdlist2.begin();
    for (int i = x_pos; i--;)
        ++xsit;
    mylist.splice(fit, mylist2, xfit);
    stdlist.splice(sit, stdlist2, xsit);
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listSpliceOneEndTest() {
    printTestName<T>("Testing list splice one iterator of list into end");
    stl::list<T> mylist;
    stl::list<T> mylist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    // position where to place
    typename stl::list<T>::iterator fit = mylist.end();
    typename std::list<T>::iterator sit = stdlist.end();
    // position what to place
    int x_pos = rand() % (mylist2.size() - 1);
    typename stl::list<T>::iterator xfit = mylist2.begin();
    stl::advance(xfit, x_pos);
    typename std::list<T>::iterator xsit = stdlist2.begin();
    for (int i = x_pos; i--;)
        ++xsit;
    mylist.splice(fit, mylist2, xfit);
    stdlist.splice(sit, stdlist2, xsit);
    testListContainersEqual(mylist, stdlist);
    // position what to place
    x_pos = rand() % (mylist2.size() - 1);
    xfit = mylist2.begin();
    stl::advance(xfit, x_pos);
    xsit = stdlist2.begin();
    for (int i = x_pos; i--;)
        ++xsit;
    mylist.splice(fit, mylist2, xfit);
    stdlist.splice(sit, stdlist2, xsit);
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listSpliceOneRandomTest() {
    printTestName<T>("Testing list splice one iterator of list into random position");
    stl::list<T> mylist;
    stl::list<T> mylist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    // position where to place
    int position = rand() % (mylist.size() - 1) + 1;
    typename stl::list<T>::iterator fit = mylist.begin();
    stl::advance(fit, position);
    typename std::list<T>::iterator sit = stdlist.begin();
    for (int i = position; i--;)
        ++sit;
    // position what to place
    int x_pos = rand() % (mylist2.size() - 1);
    typename stl::list<T>::iterator xfit = mylist2.begin();
    stl::advance(xfit, x_pos);
    typename std::list<T>::iterator xsit = stdlist2.begin();
    for (int i = x_pos; i--;)
        ++xsit;
    mylist.splice(fit, mylist2, xfit);
    stdlist.splice(sit, stdlist2, xsit);
    testListContainersEqual(mylist, stdlist);
    // position what to place
    x_pos = rand() % (mylist2.size() - 1);
    xfit = mylist2.begin();
    stl::advance(xfit, x_pos);
    xsit = stdlist2.begin();
    for (int i = x_pos; i--;)
        ++xsit;
    mylist.splice(fit, mylist2, xfit);
    stdlist.splice(sit, stdlist2, xsit);
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listSpliceIterBeginTest() {
    printTestName<T>("Testing list splice iterator range of list into begin");
    stl::list<T> mylist;
    stl::list<T> mylist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    // position where to place
    typename stl::list<T>::iterator fit = mylist.begin();
    typename std::list<T>::iterator sit = stdlist.begin();
    // position what to place (left end)
    int x_pos_left = rand() % (mylist2.size() - 9) + 1;
    typename stl::list<T>::iterator xfitlft = mylist2.begin();
    stl::advance(xfitlft, x_pos_left);
    typename std::list<T>::iterator xsitlft = stdlist2.begin();
    for (int i = x_pos_left; i--;)
        ++xsitlft;
    // position what to place (right end)
    int x_pos_right = rand() % (mylist2.size() - x_pos_left - 3) + 1;
    typename stl::list<T>::iterator xfitrht = xfitlft;
    stl::advance(xfitrht, x_pos_right);
    typename std::list<T>::iterator xsitrht = xsitlft;
    for (int i = x_pos_right; i--;)
        ++xsitrht;
    mylist.splice(fit, mylist2, xfitlft, xfitrht);
    stdlist.splice(sit, stdlist2, xsitlft, xsitrht);
    testListContainersEqual(mylist, stdlist);
    // position what to place (left end)
    x_pos_left = rand() % (mylist2.size() - 2) + 1;
    xfitlft = mylist2.begin();
    stl::advance(xfitlft, x_pos_left);
    xsitlft = stdlist2.begin();
    for (int i = x_pos_left; i--;)
        ++xsitlft;
    // position what to place (right end)
    x_pos_right = rand() % (mylist2.size() - x_pos_left - 1) + 1;
    xfitrht = xfitlft;
    stl::advance(xfitrht, x_pos_right);
    xsitrht = xsitlft;
    for (int i = x_pos_right; i--;)
        ++xsitrht;
    mylist.splice(fit, mylist2, xfitlft, xfitrht);
    stdlist.splice(sit, stdlist2, xsitlft, xsitrht);
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listSpliceIterEndTest() {
    printTestName<T>("Testing list splice iterator range of list into end");
    stl::list<T> mylist;
    stl::list<T> mylist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    // position where to place
    typename stl::list<T>::iterator fit = mylist.end();
    typename std::list<T>::iterator sit = stdlist.end();
    // position what to place (left end)
    int x_pos_left = rand() % (mylist2.size() - 2) + 1;
    typename stl::list<T>::iterator xfitlft = mylist2.begin();
    stl::advance(xfitlft, x_pos_left);
    typename std::list<T>::iterator xsitlft = stdlist2.begin();
    for (int i = x_pos_left; i--;)
        ++xsitlft;
    // position what to place (right end)
    int x_pos_right = rand() % (mylist2.size() - x_pos_left - 1) + 1;
    typename stl::list<T>::iterator xfitrht = xfitlft;
    stl::advance(xfitrht, x_pos_right);
    typename std::list<T>::iterator xsitrht = xsitlft;
    for (int i = x_pos_right; i--;)
        ++xsitrht;
    mylist.splice(fit, mylist2, xfitlft, xfitrht);
    stdlist.splice(sit, stdlist2, xsitlft, xsitrht);
    testListContainersEqual(mylist, stdlist);
    // position what to place (left end)
    x_pos_left = rand() % (mylist2.size() - 2) + 1;
    xfitlft = mylist2.begin();
    stl::advance(xfitlft, x_pos_left);
    xsitlft = stdlist2.begin();
    for (int i = x_pos_left; i--;)
        ++xsitlft;
    // position what to place (right end)
    x_pos_right = rand() % (mylist2.size() - x_pos_left - 1) + 1;
    xfitrht = xfitlft;
    stl::advance(xfitrht, x_pos_right);
    xsitrht = xsitlft;
    for (int i = x_pos_right; i--;)
        ++xsitrht;
    mylist.splice(fit, mylist2, xfitlft, xfitrht);
    stdlist.splice(sit, stdlist2, xsitlft, xsitrht);
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listSpliceIterRandomTest() {
    printTestName<T>("Testing list splice iterator range of list into random position");
    stl::list<T> mylist;
    stl::list<T> mylist2;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist2.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    std::list<T> stdlist2(mylist2.begin(), mylist2.end());
    // position where to place
    int position = rand() % (mylist.size() - 1) + 1;
    typename stl::list<T>::iterator fit = mylist.begin();
    stl::advance(fit, position);
    typename std::list<T>::iterator sit = stdlist.begin();
    for (int i = position; i--;)
        ++sit;
    // position what to place (left end)
    int x_pos_left = rand() % (mylist2.size() - 2) + 1;
    typename stl::list<T>::iterator xfitlft = mylist2.begin();
    stl::advance(xfitlft, x_pos_left);
    typename std::list<T>::iterator xsitlft = stdlist2.begin();
    for (int i = x_pos_left; i--;)
        ++xsitlft;
    // position what to place (right end)
    int x_pos_right = rand() % (mylist2.size() - x_pos_left - 1) + 1;
    typename stl::list<T>::iterator xfitrht = xfitlft;
    stl::advance(xfitrht, x_pos_right);
    typename std::list<T>::iterator xsitrht = xsitlft;
    for (int i = x_pos_right; i--;)
        ++xsitrht;
    mylist.splice(fit, mylist2, xfitlft, xfitrht);
    stdlist.splice(sit, stdlist2, xsitlft, xsitrht);
    testListContainersEqual(mylist, stdlist);
    // position what to place (left end)
    x_pos_left = rand() % (mylist2.size() - 2) + 1;
    xfitlft = mylist2.begin();
    stl::advance(xfitlft, x_pos_left);
    xsitlft = stdlist2.begin();
    for (int i = x_pos_left; i--;)
        ++xsitlft;
    // position what to place (right end)
    x_pos_right = rand() % (mylist2.size() - x_pos_left - 1) + 1;
    xfitrht = xfitlft;
    stl::advance(xfitrht, x_pos_right);
    xsitrht = xsitlft;
    for (int i = x_pos_right; i--;)
        ++xsitrht;
    mylist.splice(fit, mylist2, xfitlft, xfitrht);
    stdlist.splice(sit, stdlist2, xsitlft, xsitrht);
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listRemoveNotRandomTest() {
    printTestName<T>("Testing list remove with not random lists");
    stl::list<T> mylist;
    T values[] = {10, 12, 12, 12, 12, 12, 10, 12, 12, 12, 4, 12};
    for (std::size_t i = 0; i < sizeof(values) / sizeof(*values); ++i) {
        mylist.push_back(values[i]);
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    typename std::list<T>::iterator it;
    for (int i = 0; i < 3; ++i) {
        for (it = stdlist.begin(); it != stdlist.end(); ++it) {
            if (rand() % 10 == 0 || *it == stdlist.back())
                break;
        }
        mylist.remove(*it);
        stdlist.remove(*it);
        testListContainersEqual(mylist, stdlist);
    }
}

template<>
void listRemoveNotRandomTest<std::string>() {
    typedef std::string T;
    printTestName<T>("Testing list remove with not random lists");
    stl::list<T> mylist;
    T values[] = {"", "a", "", "", "", "b", "b", "", "a"};
    for (std::size_t i = 0; i < sizeof(values) / sizeof(*values); ++i) {
        mylist.push_back(values[i]);
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    typename std::list<T>::iterator it;
    for (int i = 0; i < 3; ++i) {
        for (it = stdlist.begin(); it != stdlist.end(); ++it) {
            if (rand() % 10 == 0 || *it == stdlist.back())
                break;
        }
        mylist.remove(*it);
        stdlist.remove(*it);
        testListContainersEqual(mylist, stdlist);
    }
}

template<>
void listRemoveNotRandomTest<SomeStruct>() {
    typedef SomeStruct T;
    printTestName<T>("Testing list remove with not random lists");
    stl::list<T> mylist;
    T values[] = {
        SomeStruct("a", 0), SomeStruct("a", 1),
        SomeStruct("a", 1), SomeStruct("b", 0),
        SomeStruct("b", 0), SomeStruct("a", 0)
    };
    for (std::size_t i = 0; i < sizeof(values) / sizeof(*values); ++i) {
        mylist.push_back(values[i]);
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    typename std::list<T>::iterator it;
    for (int i = 0; i < 3; ++i) {
        for (it = stdlist.begin(); it != stdlist.end(); ++it) {
            if (rand() % 10 == 0 || *it == stdlist.back())
                break;
        }
        mylist.remove(*it);
        stdlist.remove(*it);
        testListContainersEqual(mylist, stdlist);
    }
}

template<typename T>
void listRemoveTest() {
    printTestName<T>("Testing list remove");
    stl::list<T> mylist;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    typename std::list<T>::iterator it;
    for (int i = 0; i < 3; ++i) {
        for (it = stdlist.begin(); it != stdlist.end(); ++it) {
            if (rand() % 10 == 0 || *it == stdlist.back())
                break;
        }
        mylist.remove(*it);
        stdlist.remove(*it);
        testListContainersEqual(mylist, stdlist);
    }
}

template<typename T>
void listRemoveAllTest() {
    printTestName<T>("Testing list remove all elements by one");
    stl::list<T> mylist;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    typename std::list<T>::iterator tmp;
    for (typename std::list<T>::iterator it = stdlist.begin(); it != stdlist.end(); ++it) {
        tmp = it;
        --tmp;
        mylist.remove(*it);
        stdlist.remove(*it);
        it = tmp;
        testListContainersEqual(mylist, stdlist);
    }
}

template<typename T>
void listRemoveAllSameTest() {
    printTestName<T>("Testing list remove all when all list is the same");
    stl::list<T> mylist(40, getRandomValue<T>());
    std::list<T> stdlist(mylist.begin(), mylist.end());
    mylist.remove(mylist.front());
    stdlist.remove(stdlist.front());
    testListContainersEqual(mylist, stdlist);
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
    stl::list<T> mylist;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    mylist.remove(mylist.front());
    stdlist.remove(stdlist.front());
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listUniqueTest() {
    printTestName<T>("Testing list unique");
    stl::list<T> mylist;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    mylist.unique();
    stdlist.unique();
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listUniqueSortedTest() {
    printTestName<T>("Testing list unique when sorted");
    stl::list<T> mylist;
    for (std::size_t i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    mylist.sort();
    std::list<T> stdlist(mylist.begin(), mylist.end());
    mylist.unique();
    stdlist.unique();
    testListContainersEqual(mylist, stdlist);
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
    stl::list<T> mylist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> backup(mylist.begin(), mylist.end());
    std::list<T> stdlist(mylist.begin(), mylist.end());
    mylist.unique(unique_compare<T>);
    stdlist.unique(unique_compare<T>);
    std::list<T> ftstd(mylist.begin(), mylist.end());
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listUniqueSortedCompareTest() {
    printTestName<T>("Testing list unique when sorted");
    stl::list<T> mylist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    mylist.sort();
    std::list<T> stdlist(mylist.begin(), mylist.end());
    mylist.unique(unique_compare<T>);
    stdlist.unique(unique_compare<T>);
    testListContainersEqual(mylist, stdlist);
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
    stl::list<T> flst, flst2;

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
    stl::list<T> mylist;
    for (std::size_t i = 0; i < 12; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    testListContainersEqual(mylist, stdlist);
    mylist.reverse();
    mylist.sort();
    stdlist.sort();
    testListContainersEqual(mylist, stdlist);
    mylist.sort(compare_nocase<T>);
    stdlist.sort(compare_nocase<T>);
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listReverseTest() {
    printTestName<T>("Testing list reverse (empty and not empty)");
    stl::list<T> mylist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    testListContainersEqual(mylist, stdlist);
    mylist.reverse();
    stdlist.reverse();
    testListContainersEqual(mylist, stdlist);
    mylist.reverse();
    stdlist.reverse();
    testListContainersEqual(mylist, stdlist);
    mylist.clear();
    stdlist.clear();
    mylist.reverse();
    stdlist.reverse();
    testListContainersEqual(mylist, stdlist);
}

template<typename T>
void listCompareEqualsTest() {
    printTestName<T>("Testing compare operator ==");
    stl::list<T> mylist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    // equal
    stl::list<T> mylisteq = mylist;
    std::list<T> stdlisteq = stdlist;
    // less in size
    stl::list<T> mylistlt = mylist;
    mylistlt.pop_back();
    std::list<T> stdlistlt = stdlist;
    stdlistlt.pop_back();
    // less in element
    T tmp;
    do { tmp = getRandomValue<T>(); } while (tmp >= mylist.back());
    stl::list<T> mylistlt2 = mylist;
    mylistlt2.back() = tmp;
    std::list<T> stdlistlt2 = stdlist;
    stdlistlt2.back() = tmp;
    // greater in size
    stl::list<T> mylistgt = mylist;
    mylistgt.push_back(getRandomValue<T>());
    std::list<T> stdlistgt = stdlist;
    stdlistgt.push_back(getRandomValue<T>());
    // greater in element
    do { tmp = getRandomValue<T>(); } while (tmp <= mylist.back());
    stl::list<T> mylistgt2 = mylist;
    mylistgt2.back() = tmp;
    std::list<T> stdlistgt2 = stdlist;
    stdlistgt2.back() = tmp;
    EXPECT_EQ(mylist == mylisteq, stdlist == stdlisteq);
    EXPECT_EQ(mylist == mylistlt, stdlist == stdlistlt);
    EXPECT_EQ(mylist == mylistlt2, stdlist == stdlistlt2);
    EXPECT_EQ(mylist == mylistgt, stdlist == stdlistgt);
    EXPECT_EQ(mylist == mylistgt2, stdlist == stdlistgt2);
}

template<typename T>
void listCompareNotEqualsTest() {
    printTestName<T>("Testing compare operator !=");
    stl::list<T> mylist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    // equal
    stl::list<T> mylisteq = mylist;
    std::list<T> stdlisteq = stdlist;
    // less in size
    stl::list<T> mylistlt = mylist;
    mylistlt.pop_back();
    std::list<T> stdlistlt = stdlist;
    stdlistlt.pop_back();
    // less in element
    T tmp;
    do { tmp = getRandomValue<T>(); } while (tmp >= mylist.back());
    stl::list<T> mylistlt2 = mylist;
    mylistlt2.back() = tmp;
    std::list<T> stdlistlt2 = stdlist;
    stdlistlt2.back() = tmp;
    // greater in size
    stl::list<T> mylistgt = mylist;
    mylistgt.push_back(getRandomValue<T>());
    std::list<T> stdlistgt = stdlist;
    stdlistgt.push_back(getRandomValue<T>());
    // greater in element
    do { tmp = getRandomValue<T>(); } while (tmp <= mylist.back());
    stl::list<T> mylistgt2 = mylist;
    mylistgt2.back() = tmp;
    std::list<T> stdlistgt2 = stdlist;
    stdlistgt2.back() = tmp;
    EXPECT_EQ(mylist != mylisteq, stdlist != stdlisteq);
    EXPECT_EQ(mylist != mylistlt, stdlist != stdlistlt);
    EXPECT_EQ(mylist != mylistlt2, stdlist != stdlistlt2);
    EXPECT_EQ(mylist != mylistgt, stdlist != stdlistgt);
    EXPECT_EQ(mylist != mylistgt2, stdlist != stdlistgt2);
}

template<typename T>
void listCompareLessThanTest() {
    printTestName<T>("Testing compare operator <");
    stl::list<T> mylist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    // equal
    stl::list<T> mylisteq = mylist;
    std::list<T> stdlisteq = stdlist;
    // less in size
    stl::list<T> mylistlt = mylist;
    mylistlt.pop_back();
    std::list<T> stdlistlt = stdlist;
    stdlistlt.pop_back();
    // less in element
    T tmp;
    do { tmp = getRandomValue<T>(); } while (tmp >= mylist.back());
    stl::list<T> mylistlt2 = mylist;
    mylistlt2.back() = tmp;
    std::list<T> stdlistlt2 = stdlist;
    stdlistlt2.back() = tmp;
    // greater in size
    stl::list<T> mylistgt = mylist;
    mylistgt.push_back(getRandomValue<T>());
    std::list<T> stdlistgt = stdlist;
    stdlistgt.push_back(getRandomValue<T>());
    // greater in element
    do { tmp = getRandomValue<T>(); } while (tmp <= mylist.back());
    stl::list<T> mylistgt2 = mylist;
    mylistgt2.back() = tmp;
    std::list<T> stdlistgt2 = stdlist;
    stdlistgt2.back() = tmp;
    EXPECT_EQ(mylist < mylisteq, stdlist < stdlisteq);
    EXPECT_EQ(mylist < mylistlt, stdlist < stdlistlt);
    EXPECT_EQ(mylist < mylistlt2, stdlist < stdlistlt2);
    EXPECT_EQ(mylist < mylistgt, stdlist < stdlistgt);
    EXPECT_EQ(mylist < mylistgt2, stdlist < stdlistgt2);
}

template<typename T>
void listCompareGreaterThanTest() {
    printTestName<T>("Testing compare operator >");
    stl::list<T> mylist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    // equal
    stl::list<T> mylisteq = mylist;
    std::list<T> stdlisteq = stdlist;
    // less in size
    stl::list<T> mylistlt = mylist;
    mylistlt.pop_back();
    std::list<T> stdlistlt = stdlist;
    stdlistlt.pop_back();
    // less in element
    T tmp;
    do { tmp = getRandomValue<T>(); } while (tmp >= mylist.back());
    stl::list<T> mylistlt2 = mylist;
    mylistlt2.back() = tmp;
    std::list<T> stdlistlt2 = stdlist;
    stdlistlt2.back() = tmp;
    // greater in size
    stl::list<T> mylistgt = mylist;
    mylistgt.push_back(getRandomValue<T>());
    std::list<T> stdlistgt = stdlist;
    stdlistgt.push_back(getRandomValue<T>());
    // greater in element
    do { tmp = getRandomValue<T>(); } while (tmp <= mylist.back());
    stl::list<T> mylistgt2 = mylist;
    mylistgt2.back() = tmp;
    std::list<T> stdlistgt2 = stdlist;
    stdlistgt2.back() = tmp;
    EXPECT_EQ(mylist > mylisteq, stdlist > stdlisteq);
    EXPECT_EQ(mylist > mylistlt, stdlist > stdlistlt);
    EXPECT_EQ(mylist > mylistlt2, stdlist > stdlistlt2);
    EXPECT_EQ(mylist > mylistgt, stdlist > stdlistgt);
    EXPECT_EQ(mylist > mylistgt2, stdlist > stdlistgt2);
}

template<typename T>
void listCompareLTETest() {
    printTestName<T>("Testing compare operator <=");
    stl::list<T> mylist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    // equal
    stl::list<T> mylisteq = mylist;
    std::list<T> stdlisteq = stdlist;
    // less in size
    stl::list<T> mylistlt = mylist;
    mylistlt.pop_back();
    std::list<T> stdlistlt = stdlist;
    stdlistlt.pop_back();
    // less in element
    T tmp;
    do { tmp = getRandomValue<T>(); } while (tmp >= mylist.back());
    stl::list<T> mylistlt2 = mylist;
    mylistlt2.back() = tmp;
    std::list<T> stdlistlt2 = stdlist;
    stdlistlt2.back() = tmp;
    // greater in size
    stl::list<T> mylistgt = mylist;
    mylistgt.push_back(getRandomValue<T>());
    std::list<T> stdlistgt = stdlist;
    stdlistgt.push_back(getRandomValue<T>());
    // greater in element
    do { tmp = getRandomValue<T>(); } while (tmp <= mylist.back());
    stl::list<T> mylistgt2 = mylist;
    mylistgt2.back() = tmp;
    std::list<T> stdlistgt2 = stdlist;
    stdlistgt2.back() = tmp;
    EXPECT_EQ(mylist <= mylisteq, stdlist <= stdlisteq);
    EXPECT_EQ(mylist <= mylistlt, stdlist <= stdlistlt);
    EXPECT_EQ(mylist <= mylistlt2, stdlist <= stdlistlt2);
    EXPECT_EQ(mylist <= mylistgt, stdlist <= stdlistgt);
    EXPECT_EQ(mylist <= mylistgt2, stdlist <= stdlistgt2);
}

template<typename T>
void listCompareGTETest() {
    printTestName<T>("Testing compare operator >=");
    stl::list<T> mylist;
    for (int i = 0; i < rand() % 20 + 10; ++i) {
        mylist.push_front(getRandomValue<T>());
    }
    std::list<T> stdlist(mylist.begin(), mylist.end());
    // equal
    stl::list<T> mylisteq = mylist;
    std::list<T> stdlisteq = stdlist;
    // less in size
    stl::list<T> mylistlt = mylist;
    mylistlt.pop_back();
    std::list<T> stdlistlt = stdlist;
    stdlistlt.pop_back();
    // less in element
    T tmp;
    do { tmp = getRandomValue<T>(); } while (tmp >= mylist.back());
    stl::list<T> mylistlt2 = mylist;
    mylistlt2.back() = tmp;
    std::list<T> stdlistlt2 = stdlist;
    stdlistlt2.back() = tmp;
    // greater in size
    stl::list<T> mylistgt = mylist;
    mylistgt.push_back(getRandomValue<T>());
    std::list<T> stdlistgt = stdlist;
    stdlistgt.push_back(getRandomValue<T>());
    // greater in element
    do { tmp = getRandomValue<T>(); } while (tmp <= mylist.back());
    stl::list<T> mylistgt2 = mylist;
    mylistgt2.back() = tmp;
    std::list<T> stdlistgt2 = stdlist;
    stdlistgt2.back() = tmp;
    EXPECT_EQ(mylist >= mylisteq, stdlist >= stdlisteq);
    EXPECT_EQ(mylist >= mylistlt, stdlist >= stdlistlt);
    EXPECT_EQ(mylist >= mylistlt2, stdlist >= stdlistlt2);
    EXPECT_EQ(mylist >= mylistgt, stdlist >= stdlistgt);
    EXPECT_EQ(mylist >= mylistgt2, stdlist >= stdlistgt2);
}

template<typename T>
void defaultMapConstructorTest() {
    printTestName<T>("Default constructor");
    stl::map<T, T> myv;
    std::map<T, T> stv;
    testMapContainersEqual(myv, stv);
}

template<typename T>
void iteratorMapConstructorTest() {
    printTestName<T>("Constructor for iterators begin and end");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> fiter;
    std::map<T, T>   siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        fiter.insert(stl::make_pair(key, value));
        siter.insert(std::make_pair(key, value));
    }

    typename stl::map<T, T>::iterator lit = fiter.begin();
    stl::advance(lit, 2);
    typename stl::map<T, T>::iterator rit = fiter.end();
    stl::advance(rit, -3);
    stl::map<T, T> myv(lit, rit);
    typename std::map<T, T>::iterator lsit = siter.begin();
    stl::advance(lsit, 2);
    typename std::map<T, T>::iterator rsit = siter.end();
    stl::advance(rsit, -3);
    std::map<T, T> stv(lsit, rsit);
    testMapContainersEqual(myv, stv);
}

template<class T>
bool map_constructor_greater_compare(T a, T b) {
    return a > b;
}

template<typename T>
void defaultMapWithCompareTest() {
    printTestName<T>("Default constructor with compare function");
    stl::map<T, T, bool (*)(T a, T b)> myv(map_constructor_greater_compare<T>);
    std::map<T, T, bool (*)(T a, T b)> stv(map_constructor_greater_compare<T>);
    testMapContainersEqual(myv, stv);
}

template<typename T>
void iteratorMapWithCompareTest() {
    printTestName<T>("Constructor for iterators begin and end");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T, bool (*)(T a, T b)> fiter(map_constructor_greater_compare<T>);
    std::map<T, T, bool (*)(T a, T b)>   siter(map_constructor_greater_compare<T>);
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        fiter.insert(stl::make_pair(key, value));
        siter.insert(std::make_pair(key, value));
    }

    typename stl::map<T, T, bool (*)(T a, T b)>::iterator lit = fiter.begin();
    stl::advance(lit, 2);
    typename stl::map<T, T, bool (*)(T a, T b)>::iterator rit = fiter.end();
    stl::advance(rit, -3);
    stl::map<T, T, bool (*)(T a, T b)> myv(lit, rit, map_constructor_greater_compare<T>);

    typename std::map<T, T, bool (*)(T a, T b)>::iterator lsit = siter.begin();
    stl::advance(lsit, 2);
    typename std::map<T, T, bool (*)(T a, T b)>::iterator rsit = siter.end();
    stl::advance(rsit, -3);
    std::map<T, T, bool (*)(T a, T b)> stv(lsit, rsit, map_constructor_greater_compare<T>);

    testMapContainersEqual(myv, stv);
}

template<typename T>
void copyMapConstructorTest() {
    {
        printTestName<T>("Copy constructor for default container");
        stl::map<T, T> myv_o;
        std::map<T, T> stv_o;
        stl::map<T, T> myv(myv_o);
        std::map<T, T> stv(stv_o);
        testMapContainersEqual(myv, stv);
    }
    {
        printTestName<T>("Copy constructor for iterators begin and end");

        std::size_t numOfItems = rand() % 20 + 10;
        stl::map<T, T>    fiter;
        std::map<T, T>   siter;
        for (std::size_t i = 0; i < numOfItems; ++i) {
            T key = getRandomValue<T>();
            T value = getRandomValue<T>();
            fiter.insert(stl::make_pair(key, value));
            siter.insert(std::make_pair(key, value));
        }

        typename stl::map<T, T>::iterator lit = fiter.begin();
        stl::advance(lit, 2);
        typename stl::map<T, T>::iterator rit = fiter.end();
        stl::advance(rit, -3);
        stl::map<T, T> myv_o(lit, rit);
        typename std::map<T, T>::iterator lsit = siter.begin();
        stl::advance(lsit, 2);
        typename std::map<T, T>::iterator rsit = siter.end();
        stl::advance(rsit, -3);
        std::map<T, T> stv_o(lsit, rsit);

        stl::map<T, T> myv(myv_o);
        std::map<T, T> stv(stv_o);

        testMapContainersEqual(myv, stv);
    }
}

template<typename T>
void assignOperatorEmptyTest() {
    printTestName<T>("Assignation operator of empty container");
    stl::pair<T, T> farr[5] = {
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
    stl::map<T, T> myv_o;
    std::map<T, T> stv_o;
    testMapContainersEqual(myv_o, stv_o);
    stl::map<T, T> myv(farr, farr + 5);
    std::map<T, T> stv(sarr, sarr + 5);
    myv = myv_o;
    stv = stv_o;
    testMapContainersEqual(myv_o, stv_o);
}

template<typename T>
void assignOperatorNotEmptyTest() {
    printTestName<T>("Assignation operator of a container");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> fiter;
    std::map<T, T>   siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        fiter.insert(stl::make_pair(key, value));
        siter.insert(std::make_pair(key, value));
    }

    stl::map<T, T> myv;
    std::map<T, T> stv;
    myv = fiter;
    stv = siter;
    testMapContainersEqual(myv, stv);
}

template<typename T>
void assignOperatorEmptyWithCmpTest() {
    printTestName<T>("Assignation operator of empty container with cmp fucntion");
    stl::pair<T, T> farr[5] = {
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
    stl::map<T, T, bool (*)(T a, T b)> myv_o(map_constructor_greater_compare<T>);
    std::map<T, T, bool (*)(T a, T b)> stv_o(map_constructor_greater_compare<T>);
    testMapContainersEqual(myv_o, stv_o);
    stl::map<T, T, bool (*)(T a, T b)> myv(farr, farr + 5, map_constructor_greater_compare<T>);
    std::map<T, T, bool (*)(T a, T b)> stv(sarr, sarr + 5, map_constructor_greater_compare<T>);
    myv = myv_o;
    stv = stv_o;
    testMapContainersEqual(myv, stv);
}

template<typename T>
void assignOperatorNotEmptyWithCmpTest() {
    printTestName<T>("Assignation operator of a container with cmp fucntion");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T, bool (*)(T a, T b)> fiter(map_constructor_greater_compare<T>);
    std::map<T, T, bool (*)(T a, T b)>   siter(map_constructor_greater_compare<T>);
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        fiter.insert(stl::make_pair(key, value));
        siter.insert(std::make_pair(key, value));
    }

    stl::map<T, T, bool (*)(T a, T b)> myv;
    std::map<T, T, bool (*)(T a, T b)> stv;
    myv = fiter;
    stv = siter;
    testMapContainersEqual(myv, stv);
}

template<typename T>
void mapInsertHintTest() {
    printTestName<T>("Testing map insert hint");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(myv.begin(),stl::make_pair(key, value));
        stv.insert(stv.begin(),std::make_pair(key, value));
    }

    testMapContainersEqual(myv, stv);
}

template<typename T>
void mapInsertIteratorsTest() {
    printTestName<T>("Testing map insert iterators");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> fiter;
    std::map<T, T>   siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        fiter.insert(stl::make_pair(key, value));
        siter.insert(std::make_pair(key, value));
    }

    stl::map<T,T> myv;
    std::map<T,T> stv;
    myv.insert(fiter.rbegin(), fiter.rend());
    stv.insert(siter.rbegin(), siter.rend());
    testMapContainersEqual(myv, stv);
}

template<typename T>
void mapEraseSingleTest() {
    printTestName<T>("Testing map erase single iterator");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    myv.erase(myv.begin());
    stv.erase(stv.begin());

    typename stl::map<T,T>::iterator fit;
    typename std::map<T,T>::iterator sit;
    for (int i = 0; i < 5; ++i) {
        int pos = rand() % stv.size();
        fit = myv.begin();
        stl::advance(fit, pos);
        sit = stv.begin();
        std::advance(sit, pos);
        std::cout << "erase pos " << pos << " (" << sit->first << ")" << std::endl;
        myv.erase(fit);
        stv.erase(sit);
    }
    testMapContainersEqual(myv, stv);
    while (!myv.empty())
        myv.erase(myv.begin());
    while (!stv.empty())
        stv.erase(stv.begin());
    testMapContainersEqual(myv, stv);
}

template<typename T>
void mapEraseKeyTest() {
    printTestName<T>("Testing map erase by key");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        std::cout << key << std::endl;
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    std::cout << "erase start: " << myv.begin()->first << std::endl;
    myv.erase(myv.begin());
    stv.erase(stv.begin());
    testMapContainersEqual(myv, stv);

    typename stl::map<T,T>::iterator fit;
    typename std::map<T,T>::iterator sit;
    for (int i = 0; i < 5; ++i) {
        int pos = rand() % stv.size();
        sit = stv.begin();
        std::advance(sit, pos);
        std::cout << "erase " << sit->first << std::endl;
        myv.erase(sit->first);
        stv.erase(sit->first);
    }
    testMapContainersEqual(myv, stv);
}

template<typename T>
void mapEraseIteratorsTest() {
    printTestName<T>("Testing map erase iterators range");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    myv.erase(myv.begin());
    stv.erase(stv.begin());

    typename stl::map<T,T>::iterator fit = myv.begin();
    typename std::map<T,T>::iterator sit = stv.begin();
    int pos = rand() % stv.size();
    stl::advance(fit, pos);
    std::advance(sit, pos);
    typename stl::map<T,T>::iterator fen = fit;
    typename std::map<T,T>::iterator sen = sit;
    int pos1 = rand() % (myv.size() - pos);
    stl::advance(fen, pos1);
    std::advance(sen, pos1);

    std::cout << "delete range " << pos << '-' << pos1 << std::endl;
    myv.erase(fit, fen);
    stv.erase(sit, sen);
    testMapContainersEqual(myv, stv);
}

template<typename T>
void mapSwapEmptyTest() {
    printTestName<T>("Testing map swap when both empty");

    stl::map<T, T> myv1;
    std::map<T, T>   stv1;
    stl::map<T, T> myv2;
    std::map<T, T>   stv2;

    myv1.swap(myv2);
    stv1.swap(stv2);
    testMapContainersEqual(myv1, stv1);
    testMapContainersEqual(myv2, stv2);
}

template<typename T>
void mapSwapOneEmptyTest() {
    printTestName<T>("Testing map swap when one empty");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv1;
    std::map<T, T>   stv1;
    stl::map<T, T> myv2;
    std::map<T, T>   stv2;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv2.insert(stl::make_pair(key, value));
        stv2.insert(std::make_pair(key, value));
    }

    myv1.swap(myv2);
    stv1.swap(stv2);
    testMapContainersEqual(myv1, stv1);
    testMapContainersEqual(myv2, stv2);
}

template<typename T>
void mapSwapNotEmptyTest() {
    printTestName<T>("Testing map swap when filled");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv1;
    std::map<T, T>   stv1;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv1.insert(stl::make_pair(key, value));
        stv1.insert(std::make_pair(key, value));
    }
    numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv2;
    std::map<T, T>   stv2;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv2.insert(stl::make_pair(key, value));
        stv2.insert(std::make_pair(key, value));
    }

    myv1.swap(myv2);
    stv1.swap(stv2);
    testMapContainersEqual(myv1, stv1);
    testMapContainersEqual(myv2, stv2);
}

template<typename T>
void mapClearTest() {
    printTestName<T>("Testing map clear");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    myv.clear();
    stv.clear();
    testMapContainersEqual(myv, stv);
    myv.clear();
    stv.clear();
    testMapContainersEqual(myv, stv);
    for (std::size_t i = 9; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }
    testMapContainersEqual(myv, stv);
}

template<typename T>
void mapKeyCompTest() {
    printTestName<T>("Testing map key compare function");

    bool(*function)(T,T) = map_constructor_greater_compare<T>;
    stl::map<T,T,bool(*)(T,T)>  myv(function);
    std::map<T,T,bool(*)(T,T)> stv(function);

    EXPECT_EQ(myv.key_comp(), function);
    EXPECT_EQ(stv.key_comp(), function);
    EXPECT_EQ(myv.key_comp(), stv.key_comp());
}

template<typename T>
void mapValCompTest() {
    printTestName<T>("Testing map value compare function");

    bool(*function)(T,T) = map_constructor_greater_compare<T>;
    stl::map<T,T,bool(*)(T,T)>  myv(function);
    std::map<T,T,bool(*)(T,T)> stv(function);

    typename stl::map<T,T,bool(*)(T,T)>::value_compare mycmp = myv.value_comp();
    typename std::map<T,T,bool(*)(T,T)>::value_compare stcmp = stv.value_comp();

    stl::pair<T,T> fp1 = stl::make_pair(getRandomValue<T>(), getRandomValue<T>());
    std::pair<T,T> sp1 = std::make_pair(fp1.first, fp1.second);

    stl::pair<T,T> fp2 = stl::make_pair(getRandomValue<T>(), getRandomValue<T>());
    std::pair<T,T> sp2 = std::make_pair(fp2.first, fp2.second);

    EXPECT_EQ(mycmp(fp1, fp2), stcmp(sp1, sp2));
    EXPECT_EQ(mycmp(fp1, fp1), stcmp(sp1, sp1));
}

template<typename T>
void mapFindExistTest() {
    printTestName<T>("Testing map find when keys exist");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    for (typename std::map<T,T>::iterator it = stv.begin(); it != stv.end(); ++it) {
        typename stl::map<T,T>::iterator fit = myv.find(it->first);
        typename std::map<T,T>::iterator sit = stv.find(it->first);
        EXPECT_EQ(fit == myv.end(), sit == stv.end());
        EXPECT_EQ(fit->first, sit->first);
        EXPECT_EQ(fit->second, sit->second);
    }
    testMapContainersEqual(myv, stv);
}

template<typename T>
void mapFindNotExistTest() {
    printTestName<T>("Testing map find when keys not exist");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    for (int i = 0; i < 100; ++i) {
        T key = getRandomValue<T>();
        typename stl::map<T,T>::iterator fit = myv.find(key);
        typename std::map<T,T>::iterator sit = stv.find(key);
        EXPECT_EQ(fit == myv.end(), sit == stv.end());
    }
}

template<typename T>
void mapCountEmptyTest() {
    printTestName<T>("Testing map count on empty containers");

    stl::map<T, T> myv;
    std::map<T, T>   stv;

    for (int i = 0; i < 100; ++i) {
        T key = getRandomValue<T>();
        EXPECT_EQ(myv.count(key), stv.count(key));
    }
}

template<typename T>
void mapCountExistTest() {
    printTestName<T>("Testing map count when keys exist");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    for (typename std::map<T,T>::iterator it = stv.begin(); it != stv.end(); ++it) {
        EXPECT_EQ(myv.count(it->first), stv.count(it->first));
    }
    testMapContainersEqual(myv, stv);
}

template<typename T>
void mapCountNotExistTest() {
    printTestName<T>("Testing map count when keys not exist");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    for (int i = 0; i < 100; ++i) {
        T key = getRandomValue<T>();
        EXPECT_EQ(myv.count(key), stv.count(key));
    }
}

template<typename T>
void mapLowerBoundBelowMinTest() {
    printTestName<T>("Testing map lower bound below minimum key");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    T lower = T();
    while (!(lower < myv.begin()->first)) {
        lower = getRandomValue<T>();
    }
    typename stl::map<T,T>::iterator fit = myv.lower_bound(lower);
    typename std::map<T,T>::iterator sit = stv.lower_bound(lower);
    EXPECT_EQ(fit == myv.end(), sit == stv.end());
    if (fit != myv.end() && sit != stv.end()) {
        EXPECT_EQ(fit->first, sit->first);
        EXPECT_EQ(fit->second, sit->second);
    }
}

template<typename T>
void mapLowerBoundAboveMaxTest() {
    printTestName<T>("Testing map lower bound above maximum key");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    T greater = T();
    T max_ = (--myv.end())->first;
    while (!(greater > max_)) {
        greater = getRandomValue<T>();
    }
    typename stl::map<T,T>::iterator fit = myv.lower_bound(greater);
    typename std::map<T,T>::iterator sit = stv.lower_bound(greater);
    EXPECT_EQ(fit == myv.end(), sit == stv.end());
    if (fit != myv.end() && sit != stv.end()) {
        EXPECT_EQ(fit->first, sit->first);
        EXPECT_EQ(fit->second, sit->second);
    }
}

template<typename T>
void mapLowerBoundExistantTest() {
    printTestName<T>("Testing map lower bound with existing key");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    std::size_t pos = rand() % stv.size();
    typename stl::map<T,T>::iterator fpos = myv.begin();
    stl::advance(fpos, pos);
    typename stl::map<T,T>::iterator fit = myv.lower_bound(fpos->first);
    typename std::map<T,T>::iterator sit = stv.lower_bound(fpos->first);
    EXPECT_EQ(fit == myv.end(), sit == stv.end());
    if (fit != myv.end() && sit != stv.end()) {
        EXPECT_EQ(fit->first, sit->first);
        EXPECT_EQ(fit->second, sit->second);
    }
}

template<typename T>
void mapLowerBoundRandomTest() {
    printTestName<T>("Testing map lower bound with random key");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    T key = getRandomValue<T>();
    typename stl::map<T,T>::iterator fit = myv.lower_bound(key);
    typename std::map<T,T>::iterator sit = stv.lower_bound(key);
    EXPECT_EQ(fit == myv.end(), sit == stv.end());
    if (fit != myv.end() && sit != stv.end()) {
        EXPECT_EQ(fit->first, sit->first);
        EXPECT_EQ(fit->second, sit->second);
    }
}

template<typename T>
void mapUpperBoundBelowMinTest() {
    printTestName<T>("Testing map upper bound below minimum key");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    T lower = T();
    while (!(lower < myv.begin()->first)) {
        lower = getRandomValue<T>();
    }
    typename stl::map<T,T>::iterator fit = myv.upper_bound(lower);
    typename std::map<T,T>::iterator sit = stv.upper_bound(lower);
    EXPECT_EQ(fit == myv.end(), sit == stv.end());
    if (fit != myv.end() && sit != stv.end()) {
        EXPECT_EQ(fit->first, sit->first);
        EXPECT_EQ(fit->second, sit->second);
    }
}

template<typename T>
void mapUpperBoundAboveMaxTest() {
    printTestName<T>("Testing map upper bound above maximum key");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    T greater = T();
    while (!(greater > myv.begin()->first)) {
        greater = getRandomValue<T>();
    }
    typename stl::map<T,T>::iterator fit = myv.upper_bound(greater);
    typename std::map<T,T>::iterator sit = stv.upper_bound(greater);
    EXPECT_EQ(fit == myv.end(), sit == stv.end());
    if (fit != myv.end() && sit != stv.end()) {
        EXPECT_EQ(fit->first, sit->first);
        EXPECT_EQ(fit->second, sit->second);
    }
}

template<typename T>
void mapUpperBoundExistantTest() {
    printTestName<T>("Testing map upper bound with existing key");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    std::size_t pos = rand() % stv.size();
    typename stl::map<T,T>::iterator fpos = myv.begin();
    stl::advance(fpos, pos);
    typename stl::map<T,T>::iterator fit = myv.upper_bound(fpos->first);
    typename std::map<T,T>::iterator sit = stv.upper_bound(fpos->first);
    EXPECT_EQ(fit == myv.end(), sit == stv.end());
    if (fit != myv.end() && sit != stv.end()) {
        EXPECT_EQ(fit->first, sit->first);
        EXPECT_EQ(fit->second, sit->second);
    }
}

template<typename T>
void mapUpperBoundRandomTest() {
    printTestName<T>("Testing map upper bound with random key");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    T key = getRandomValue<T>();
    typename stl::map<T,T>::iterator fit = myv.upper_bound(key);
    typename std::map<T,T>::iterator sit = stv.upper_bound(key);
    EXPECT_EQ(fit == myv.end(), sit == stv.end());
    if (fit != myv.end() && sit != stv.end()) {
        EXPECT_EQ(fit->first, sit->first);
        EXPECT_EQ(fit->second, sit->second);
    }
}

template<typename T>
void mapEqualRangeBelowMinTest() {
    printTestName<T>("Testing map equal range below minimum key");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    T lower = T();
    while (!(lower < myv.begin()->first)) {
        lower = getRandomValue<T>();
    }
    stl::pair<typename stl::map<T,T>::iterator,typename stl::map<T,T>::iterator> fit = myv.equal_range(lower);
    std::pair<typename std::map<T,T>::iterator,typename std::map<T,T>::iterator> sit = stv.equal_range(lower);
    EXPECT_EQ(fit.first == myv.end(), sit.first == stv.end());
    if (fit.first != myv.end() && sit.first != stv.end()) {
        EXPECT_EQ(fit.first->first, sit.first->first);
        EXPECT_EQ(fit.first->second, sit.first->second);
    }
    EXPECT_EQ(fit.second == myv.end(), sit.second == stv.end());
    if (fit.second != myv.end() && sit.second != stv.end()) {
        EXPECT_EQ(fit.second->first, sit.second->first);
        EXPECT_EQ(fit.second->second, sit.second->second);
    }
}

template<typename T>
void mapEqualRangeAboveMaxTest() {
    printTestName<T>("Testing map equal range above maximum key");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    T greater = T();
    while (!(greater > myv.begin()->first)) {
        greater = getRandomValue<T>();
    }
    stl::pair<typename stl::map<T,T>::iterator,typename stl::map<T,T>::iterator> fit = myv.equal_range(greater);
    std::pair<typename std::map<T,T>::iterator,typename std::map<T,T>::iterator> sit = stv.equal_range(greater);
    EXPECT_EQ(fit.first == myv.end(), sit.first == stv.end());
    if (fit.first != myv.end() && sit.first != stv.end()) {
        EXPECT_EQ(fit.first->first, sit.first->first);
        EXPECT_EQ(fit.first->second, sit.first->second);
    }
    EXPECT_EQ(fit.second == myv.end(), sit.second == stv.end());
    if (fit.second != myv.end() && sit.second != stv.end()) {
        EXPECT_EQ(fit.second->first, sit.second->first);
        EXPECT_EQ(fit.second->second, sit.second->second);
    }
}

template<typename T>
void mapEqualRangeExistantTest() {
    printTestName<T>("Testing map equal range with existing key");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    std::size_t pos = rand() % stv.size();
    typename stl::map<T,T>::iterator fpos = myv.begin();
    stl::advance(fpos, pos);
    stl::pair<typename stl::map<T,T>::iterator,typename stl::map<T,T>::iterator> fit = myv.equal_range(fpos->first);
    std::pair<typename std::map<T,T>::iterator,typename std::map<T,T>::iterator> sit = stv.equal_range(fpos->first);
    EXPECT_EQ(fit.first == myv.end(), sit.first == stv.end());
    if (fit.first != myv.end() && sit.first != stv.end()) {
        EXPECT_EQ(fit.first->first, sit.first->first);
        EXPECT_EQ(fit.first->second, sit.first->second);
    }
    EXPECT_EQ(fit.second == myv.end(), sit.second == stv.end());
    if (fit.second != myv.end() && sit.second != stv.end()) {
        EXPECT_EQ(fit.second->first, sit.second->first);
        EXPECT_EQ(fit.second->second, sit.second->second);
    }
}

template<typename T>
void mapEqualRangeRandomTest() {
    printTestName<T>("Testing map equal range with random key");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::map<T, T> myv;
    std::map<T, T>   stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T key = getRandomValue<T>();
        T value      = getRandomValue<T>();
        myv.insert(stl::make_pair(key, value));
        stv.insert(std::make_pair(key, value));
    }

    T key = getRandomValue<T>();
    stl::pair<typename stl::map<T,T>::iterator,typename stl::map<T,T>::iterator> fit = myv.equal_range(key);
    std::pair<typename std::map<T,T>::iterator,typename std::map<T,T>::iterator> sit = stv.equal_range(key);
    EXPECT_EQ(fit.first == myv.end(), sit.first == stv.end());
    if (fit.first != myv.end() && sit.first != stv.end()) {
        EXPECT_EQ(fit.first->first, sit.first->first);
        EXPECT_EQ(fit.first->second, sit.first->second);
    }
    EXPECT_EQ(fit.second == myv.end(), sit.second == stv.end());
    if (fit.second != myv.end() && sit.second != stv.end()) {
        EXPECT_EQ(fit.second->first, sit.second->first);
        EXPECT_EQ(fit.second->second, sit.second->second);
    }
}

template<typename T>
void stackEmptyConstructorTest() {
    printTestName<T>("Stack empty constructor");

    stl::stack<T> myv;
    std::stack<T> stv;
    testStackContainersEqual(myv, stv);
}

template<typename T>
void stackListConstructorTest() {
    printTestName<T>("Stack constructor from list");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::list<T>  flst;
    std::list<T> slst;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value      = getRandomValue<T>();
        flst.push_back(value);
        slst.push_back(value);
    }

    stl::stack<T,stl::list<T>> myv(flst);
    std::stack<T,std::list<T>> stv(slst);
    testStackContainersEqual(myv, stv);
}

template<typename T>
void stackVectorConstructorTest() {
    printTestName<T>("Stack constructor from vector");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::vector<T>  fvec;
    std::vector<T> svec;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value      = getRandomValue<T>();
        fvec.push_back(value);
        svec.push_back(value);
    }

    stl::stack<T,stl::vector<T> > myv(fvec);
    std::stack<T,std::vector<T> > stv(svec);
    testStackContainersEqual(myv, stv);
}

template<typename T>
void stackEmptyTest() {
    printTestName<T>("Stack test empty");

    stl::stack<T> myv;
    std::stack<T> stv;
    EXPECT_EQ(myv.empty(), stv.empty());
    T value = getRandomValue<T>();
    myv.push(value);
    stv.push(value);
    EXPECT_EQ(myv.empty(), stv.empty());
    myv.push(value);
    stv.push(value);
    EXPECT_EQ(myv.empty(), stv.empty());
    myv.pop();
    stv.pop();
    EXPECT_EQ(myv.empty(), stv.empty());
    myv.pop();
    stv.pop();
    EXPECT_EQ(myv.empty(), stv.empty());
}

template<typename T>
void stackEmptyListTest() {
    printTestName<T>("Stack test empty when list");

    stl::stack<T,stl::list<T>> myv;
    std::stack<T,std::list<T>> stv;
    EXPECT_EQ(myv.empty(), stv.empty());
    T value = getRandomValue<T>();
    myv.push(value);
    stv.push(value);
    EXPECT_EQ(myv.empty(), stv.empty());
    myv.push(value);
    stv.push(value);
    EXPECT_EQ(myv.empty(), stv.empty());
    myv.pop();
    stv.pop();
    EXPECT_EQ(myv.empty(), stv.empty());
    myv.pop();
    stv.pop();
    EXPECT_EQ(myv.empty(), stv.empty());
}

template<typename T>
void stackEmptyVectorTest() {
    printTestName<T>("Stack test empty when vector");

    stl::stack<T,stl::vector<T> > myv;
    std::stack<T,std::vector<T> > stv;
    EXPECT_EQ(myv.empty(), stv.empty());
    T value = getRandomValue<T>();
    myv.push(value);
    stv.push(value);
    EXPECT_EQ(myv.empty(), stv.empty());
    myv.push(value);
    stv.push(value);
    EXPECT_EQ(myv.empty(), stv.empty());
    myv.pop();
    stv.pop();
    EXPECT_EQ(myv.empty(), stv.empty());
    myv.pop();
    stv.pop();
    EXPECT_EQ(myv.empty(), stv.empty());
}

template<typename T>
void stackSizeTest() {
    printTestName<T>("Stack test size");

    int num;
    stl::stack<T> myv;
    std::stack<T> stv;
    EXPECT_EQ(myv.size(), stv.size());
    T value = getRandomValue<T>();
    num = rand() % 10 + 4;
    for (int i = 0; i < num; ++i) {
        myv.push(value);
        stv.push(value);
    }
    EXPECT_EQ(myv.size(), stv.size());
    num = rand() % 10 + 4;
    for (int i = 0; i < num; ++i) {
        myv.push(value);
        stv.push(value);
    }
    EXPECT_EQ(myv.size(), stv.size());
    num = rand() % (myv.size() - 5) + 1;
    for (int i = 0; i < num; ++i) {
        myv.pop();
        stv.pop();
    }
    EXPECT_EQ(myv.size(), stv.size());
    while (!myv.empty() || !stv.empty()) {
        myv.pop();
        stv.pop();
    }
    EXPECT_EQ(myv.size(), stv.size());
}

template<typename T>
void stackSizeListTest() {
    printTestName<T>("Stack test size when list");

    int num;
    stl::stack<T,stl::list<T>> myv;
    std::stack<T,std::list<T>> stv;
    EXPECT_EQ(myv.size(), stv.size());
    T value = getRandomValue<T>();
    num = rand() % 10 + 4;
    for (int i = 0; i < num; ++i) {
        myv.push(value);
        stv.push(value);
    }
    EXPECT_EQ(myv.size(), stv.size());
    num = rand() % 10 + 4;
    for (int i = 0; i < num; ++i) {
        myv.push(value);
        stv.push(value);
    }
    EXPECT_EQ(myv.size(), stv.size());
    num = rand() % 10 % (myv.size() - 5) + 1;
    for (int i = 0; i < num; ++i) {
        myv.pop();
        stv.pop();
    }
    EXPECT_EQ(myv.size(), stv.size());
    while (!myv.empty() || !stv.empty()) {
        myv.pop();
        stv.pop();
    }
    EXPECT_EQ(myv.size(), stv.size());
}

template<typename T>
void stackSizeVectorTest() {
    printTestName<T>("Stack size when vector");

    int num;
    stl::stack<T,stl::vector<T> > myv;
    std::stack<T,std::vector<T> > stv;
    EXPECT_EQ(myv.size(), stv.size());
    T value = getRandomValue<T>();
    num = rand() % 10 + 4;
    for (int i = 0; i < num; ++i) {
        myv.push(value);
        stv.push(value);
    }
    EXPECT_EQ(myv.size(), stv.size());
    num = rand() % 10 + 4;
    for (int i = 0; i < num; ++i) {
        myv.push(value);
        stv.push(value);
    }
    EXPECT_EQ(myv.size(), stv.size());
    num = rand() % 10 % (myv.size() - 5) + 1;
    for (int i = 0; i < num; ++i) {
        myv.pop();
        stv.pop();
    }
    EXPECT_EQ(myv.size(), stv.size());
    while (!myv.empty() || !stv.empty()) {
        myv.pop();
        stv.pop();
    }
    EXPECT_EQ(myv.size(), stv.size());
}

template<typename T>
void stackPushPopListTest() {
    printTestName<T>("Stack test push and pop when list");

    std::size_t numOfItems = rand() % 50 + 50;
    stl::stack<T,stl::list<T>> myv;
    std::stack<T,std::list<T>> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push(value);
        stv.push(value);
        EXPECT_EQ(myv.size(), stv.size());
    }

    while (!myv.empty() && !stv.empty()) {
        T a = myv.top();
        T b = stv.top();
        myv.pop();
        stv.pop();
        EXPECT_EQ(myv.size(), stv.size());
        EXPECT_EQ(a, b);
    }
    EXPECT_EQ(myv.empty(), stv.empty());
}

template<typename T>
void stackPushPopVectorTest() {
    printTestName<T>("Stack test push and pop when vector");

    std::size_t numOfItems = rand() % 50 + 50;
    stl::stack<T,stl::vector<T> > myv;
    std::stack<T,std::vector<T> > stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push(value);
        stv.push(value);
        EXPECT_EQ(myv.size(), stv.size());
    }

    while (!myv.empty() && !stv.empty()) {
        T a = myv.top();
        T b = stv.top();
        myv.pop();
        stv.pop();
        EXPECT_EQ(myv.size(), stv.size());
        EXPECT_EQ(a, b);
    }
    EXPECT_EQ(myv.empty(), stv.empty());
}

template<typename T>
std::pair<T*,int> getStackCompareData() {
    T *data = new T[5];
    data[0] = 5;
    data[1] = 32;
    data[2] = 15;
    data[3] = 420;
    data[4] = 32;
    return std::pair<T*, int>(data, 5);
}

template<>
std::pair<std::string*,int> getStackCompareData<std::string>() {
    std::string *data = new std::string[4];
    data[0] = "a";
    data[2] = "asf";
    data[3] = "vas";
    return std::pair<std::string*, int>(data, 3);
}

template<>
std::pair<SomeStruct*,int> getStackCompareData<SomeStruct>() {
    SomeStruct *data = new SomeStruct[3];
    data[0] = {"a", 4};
    data[1] = {"asf", 17};
    data[2] = {"vas", 22};
    return std::pair<SomeStruct*, int>(data, 3);
}

template<typename T>
std::pair<T*,int> getStackCompareLess() {
    T *data = new T[4];
    data[0] = 5;
    data[1] = 32;
    data[2] = 15;
    data[3] = 420;
    return std::pair<T*, int>(data, 4);
}

template<>
std::pair<std::string*,int> getStackCompareLess<std::string>() {
    std::string *data = new std::string[4];
    data[0] = "a";
    data[1] = "asd";
    data[2] = "vas";
    return std::pair<std::string*, int>(data, 3);
}

template<>
std::pair<SomeStruct*,int> getStackCompareLess<SomeStruct>() {
    SomeStruct *data = new SomeStruct[3];
    data[0] = {"a", 4};
    data[1] = {"as", 13};
    data[2] = {"vas", 22};
    return std::pair<SomeStruct*, int>(data, 3);
}

template<typename T>
std::pair<T*,int> getStackCompareMore() {
    T *data = new T[5];
    data[0] = 5;
    data[1] = 32;
    data[2] = 15;
    data[3] = 421;
    data[4] = 32;
    return std::pair<T*, int>(data, 5);
}

template<>
std::pair<std::string*,int> getStackCompareMore<std::string>() {
    std::string *data = new std::string[5];
    data[0] = "a";
    data[1] = "asf";
    data[2] = "vas";
    data[3] = "ff";
    return std::pair<std::string*, int>(data, 4);
}

template<>
std::pair<SomeStruct*,int> getStackCompareMore<SomeStruct>() {
    SomeStruct *data = new SomeStruct[3];
    data[0] = {"b", 5};
    data[1] = {"asf", 17};
    data[2] = {"vas", 22};
    return std::pair<SomeStruct*, int>(data, 3);
}

template<typename T>
void stackCompareOperatorsTest() {
    printTestName<T>("Testing stack compare operators");

    std::pair<T*,int> data = getStackCompareData<T>();
    std::pair<T*,int> less = getStackCompareLess<T>();
    std::pair<T*,int> more = getStackCompareMore<T>();

    stl::stack<T,stl::vector<T> > mydata;
    std::stack<T,stl::vector<T> > stdata;
    for (int i = 0; i < data.second; ++i) {
        mydata.push(data.first[i]);
        stdata.push(data.first[i]);
    }
    delete [] data.first;

    stl::stack<T,stl::vector<T> > myless;
    std::stack<T,stl::vector<T> > stless;
    for (int i = 0; i < less.second; ++i) {
        myless.push(less.first[i]);
        stless.push(less.first[i]);
    }
    delete [] less.first;

    stl::stack<T,stl::vector<T> > mymore;
    std::stack<T,stl::vector<T> > stmore;
    for (int i = 0; i < more.second; ++i) {
        mymore.push(more.first[i]);
        stmore.push(more.first[i]);
    }
    delete [] more.first;

    EXPECT_EQ(mydata == mydata, stdata == stdata);
    EXPECT_EQ(mydata != myless, stdata != stless);
    EXPECT_EQ(mydata > myless, stdata > stless);
    EXPECT_EQ(mydata < mymore, stdata < stmore);
    EXPECT_EQ(mydata <= mydata, stdata <= stdata);
    EXPECT_EQ(mydata >= mydata, stdata >= stdata);
    EXPECT_EQ(mydata >= myless, stdata >= stless);
    EXPECT_EQ(mydata <= mymore, stdata <= stmore);
}

template<typename T>
void queueEmptyConstructorTest() {
    printTestName<T>("Queue empty constructor");

    stl::queue<T> myv;
    std::queue<T> stv;
    testQueueContainersEqual(myv, stv);
}

template<typename T>
void queueListConstructorTest() {
    printTestName<T>("Queue constructor from list");

    std::size_t numOfItems = rand() % 20 + 10;
    stl::list<T>  flst;
    std::list<T> slst;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value      = getRandomValue<T>();
        flst.push_back(value);
        slst.push_back(value);
    }

    stl::queue<T,stl::list<T>> myv(flst);
    std::queue<T,std::list<T>> stv(slst);
    testQueueContainersEqual(myv, stv);
}

template<typename T>
void queueEmptyListTest() {
    printTestName<T>("Queue test empty when list");

    stl::queue<T,stl::list<T>> myv;
    std::queue<T,std::list<T>> stv;
    EXPECT_EQ(myv.empty(), stv.empty());
    T value = getRandomValue<T>();
    myv.push(value);
    stv.push(value);
    EXPECT_EQ(myv.empty(), stv.empty());
    myv.push(value);
    stv.push(value);
    EXPECT_EQ(myv.empty(), stv.empty());
    myv.pop();
    stv.pop();
    EXPECT_EQ(myv.empty(), stv.empty());
    myv.pop();
    stv.pop();
    EXPECT_EQ(myv.empty(), stv.empty());
}

template<typename T>
void queueSizeListTest() {
    printTestName<T>("Queue test size when list");

    int num;
    stl::queue<T,stl::list<T>> myv;
    std::queue<T,std::list<T>> stv;
    EXPECT_EQ(myv.size(), stv.size());
    T value = getRandomValue<T>();
    num = rand() % 10 + 4;
    for (int i = 0; i < num; ++i) {
        myv.push(value);
        stv.push(value);
    }
    EXPECT_EQ(myv.size(), stv.size());
    num = rand() % 10 + 4;
    for (int i = 0; i < num; ++i) {
        myv.push(value);
        stv.push(value);
    }
    EXPECT_EQ(myv.size(), stv.size());
    num = rand() % 10 % (myv.size() - 5) + 1;
    for (int i = 0; i < num; ++i) {
        myv.pop();
        stv.pop();
    }
    EXPECT_EQ(myv.size(), stv.size());
    while (!myv.empty() || !stv.empty()) {
        myv.pop();
        stv.pop();
    }
    EXPECT_EQ(myv.size(), stv.size());
}

template<typename T>
void queuePushPopListTest() {
    printTestName<T>("Queue test push and pop when list");

    std::size_t numOfItems = rand() % 50 + 50;
    stl::queue<T,stl::list<T>> myv;
    std::queue<T,std::list<T>> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        myv.push(value);
        stv.push(value);
        EXPECT_EQ(myv.size(), stv.size());
    }

    while (!myv.empty() && !stv.empty()) {
        T a = myv.back();
        T b = stv.back();
        myv.pop();
        stv.pop();
        EXPECT_EQ(myv.size(), stv.size());
        EXPECT_EQ(a, b);
    }
    EXPECT_EQ(myv.empty(), stv.empty());
}

template<typename T>
std::pair<T*,int> getQueueCompareData() {
    T *data = new T[5];
    data[0] = 5;
    data[1] = 32;
    data[2] = 15;
    data[3] = 420;
    data[4] = 32;
    return std::pair<T*, int>(data, 5);
}

template<>
std::pair<std::string*,int> getQueueCompareData<std::string>() {
    std::string *data = new std::string[4];
    data[0] = "a";
    data[2] = "asf";
    data[3] = "vas";
    return std::pair<std::string*, int>(data, 3);
}

template<>
std::pair<SomeStruct*,int> getQueueCompareData<SomeStruct>() {
    SomeStruct *data = new SomeStruct[3];
    data[0] = {"a", 4};
    data[1] = {"asf", 17};
    data[2] = {"vas", 22};
    return std::pair<SomeStruct*, int>(data, 3);
}

template<typename T>
std::pair<T*,int> getQueueCompareLess() {
    T *data = new T[4];
    data[0] = 5;
    data[1] = 32;
    data[2] = 15;
    data[3] = 420;
    return std::pair<T*, int>(data, 4);
}

template<>
std::pair<std::string*,int> getQueueCompareLess<std::string>() {
    std::string *data = new std::string[4];
    data[0] = "a";
    data[1] = "asd";
    data[2] = "vas";
    return std::pair<std::string*, int>(data, 3);
}

template<>
std::pair<SomeStruct*,int> getQueueCompareLess<SomeStruct>() {
    SomeStruct *data = new SomeStruct[3];
    data[0] = {"a", 4};
    data[1] = {"as", 13};
    data[2] = {"vas", 22};
    return std::pair<SomeStruct*, int>(data, 3);
}

template<typename T>
std::pair<T*,int> getQueueCompareMore() {
    T *data = new T[5];
    data[0] = 5;
    data[1] = 32;
    data[2] = 15;
    data[3] = 421;
    data[4] = 32;
    return std::pair<T*, int>(data, 5);
}

template<>
std::pair<std::string*,int> getQueueCompareMore<std::string>() {
    std::string *data = new std::string[5];
    data[0] = "a";
    data[1] = "asf";
    data[2] = "vas";
    data[3] = "ff";
    return std::pair<std::string*, int>(data, 4);
}

template<>
std::pair<SomeStruct*,int> getQueueCompareMore<SomeStruct>() {
    SomeStruct *data = new SomeStruct[3];
    data[0] = {"b", 5};
    data[1] = {"asf", 17};
    data[2] = {"vas", 22};
    return std::pair<SomeStruct*, int>(data, 3);
}

template<typename T>
void queueCompareOperatorsTest() {
    printTestName<T>("Testing queue compare operators");

    std::pair<T*,int> data = getQueueCompareData<T>();
    std::pair<T*,int> less = getQueueCompareLess<T>();
    std::pair<T*,int> more = getQueueCompareMore<T>();

    stl::queue<T,stl::list<T> > mydata;
    std::queue<T,stl::list<T> > stdata;
    for (int i = 0; i < data.second; ++i) {
        mydata.push(data.first[i]);
        stdata.push(data.first[i]);
    }
    delete [] data.first;

    stl::queue<T,stl::list<T> > myless;
    std::queue<T,stl::list<T> > stless;
    for (int i = 0; i < less.second; ++i) {
        myless.push(less.first[i]);
        stless.push(less.first[i]);
    }
    delete [] less.first;

    stl::queue<T,stl::list<T> > mymore;
    std::queue<T,stl::list<T> > stmore;
    for (int i = 0; i < more.second; ++i) {
        mymore.push(more.first[i]);
        stmore.push(more.first[i]);
    }
    delete [] more.first;

    EXPECT_EQ(mydata == mydata, stdata == stdata);
    EXPECT_EQ(mydata != myless, stdata != stless);
    EXPECT_EQ(mydata > myless, stdata > stless);
    EXPECT_EQ(mydata < mymore, stdata < stmore);
    EXPECT_EQ(mydata <= mydata, stdata <= stdata);
    EXPECT_EQ(mydata >= mydata, stdata >= stdata);
    EXPECT_EQ(mydata >= myless, stdata >= stless);
    EXPECT_EQ(mydata <= mymore, stdata <= stmore);
}

/*** VECTOR TESTS ***/

TEST(VectorConstructors, DefaultConstructor) STL_DO_TEST(defaultConstructorTest)
TEST(VectorConstructors, ZeroElementsConstructor) STL_DO_TEST(zeroElementsConstructorTest)
TEST(VectorConstructors, TwentyElementsConstructor) STL_DO_TEST(twentyElementsConstructorTest)
TEST(VectorConstructors, TwentyElementsWithDefaultValueConstructor) STL_DO_TEST(twentyElementsWithDefaultValueConstructorTest)
TEST(VectorConstructors, IteratorConstructor)  STL_DO_TEST(iteratorConstructorTest)
TEST(VectorConstructors, CopyConstructor)  STL_DO_TEST(copyConstructorTest)

TEST(VectorAssignation, AssignationOperatorToMoreCap) STL_DO_TEST(assignationOperatorToMoreCapTest)
TEST(VectorAssignation, AssignationOperatorToMoreSize) STL_DO_TEST(assignationOperatorToMoreSizeTest)
TEST(VectorAssignation, AssignationOperatorToLess) STL_DO_TEST(assignationOperatorToLessTest)
TEST(VectorAssignation, AssignationOperatorToSame) STL_DO_TEST(assignationOperatorToSameTest)

TEST(VectorCapacity, ResizeLess) STL_DO_TEST(resizeLessTest)
TEST(VectorCapacity, ResizeMore) STL_DO_TEST(resizeMoreTest)
TEST(VectorCapacity, ResizeSame) STL_DO_TEST(resizeSameTest)

TEST(VectorCapacity, ReserveLess) STL_DO_TEST(reserveLessTest)
TEST(VectorCapacity, ReserveMore) STL_DO_TEST(reserveMoreTest)
TEST(VectorCapacity, ReserveSame) STL_DO_TEST(reserveSameTest)
TEST(VectorCapacity, ReserveGreaterThanMax) STL_DO_TEST(reserveGreaterThanMaxTest)

TEST(VectorElementAccess, operatorBracketsAccess) STL_DO_TEST(OperatorBracketsAccessTest)
TEST(VectorElementAccess, functionAt) STL_DO_TEST(FunctionAtTest)
TEST(VectorElementAccess, functionFront) STL_DO_TEST(FunctionFrontTest)
TEST(VectorElementAccess, functionBack) STL_DO_TEST(FunctionBackTest)

TEST(VectorAssign, assignFillLess) STL_DO_TEST(AssignFillLessTest)
TEST(VectorAssign, assignFillBetweenSizeCap) STL_DO_TEST(AssignFillBetweenSizeCapTest)
TEST(VectorAssign, assignFillMore) STL_DO_TEST(AssignFillMoreTest)
TEST(VectorAssign, assignFillMaxSize) STL_DO_TEST(AssignFillMaxSizeTest)
TEST(VectorAssign, assignFillMoreThanMax) STL_DO_TEST(AssignFillMoreThanMaxTest)
TEST(VectorAssign, assignFillSame) STL_DO_TEST(AssignFillSameTest)

TEST(VectorPushBack, pushBack) STL_DO_TEST(PushBackTest)
TEST(VectorPopBack, popBack) STL_DO_TEST(PopBackTest)

TEST(VectorSwap, swap) STL_DO_TEST(SwapTest)
TEST(VectorSwap, swapOneEmpty) STL_DO_TEST(SwapOneEmptyTest)
TEST(VectorSwap, swapOneCleared) STL_DO_TEST(SwapOneClearedTest)
TEST(VectorSwap, swapEmpty) STL_DO_TEST(SwapEmptyTest)
TEST(VectorSwap, swapCleared) STL_DO_TEST(SwapClearedTest)

TEST(VectorClear, clear) STL_DO_TEST(ClearTest)
TEST(VectorClear, clearEmpty) STL_DO_TEST(ClearEmptyTest)
TEST(VectorClear, clearDouble) STL_DO_TEST(ClearDoubleTest)

TEST(VectorInsert, insert) STL_DO_TEST(InsertTest)
TEST(VectorInsert, insertMultiple) STL_DO_TEST(InsertMultipleTest)
TEST(VectorInsert, insertRange) STL_DO_TEST(InsertRangeTest)
TEST(VectorErase, erase) STL_DO_TEST(EraseTest)
TEST(VectorErase, eraseRange) STL_DO_TEST(EraseRangeTest)

/*** LIST TESTS ***/

TEST(ListConstructors, DefaultConstructor) STL_DO_TEST(defaultListConstructorTest)
TEST(ListConstructors, ZeroElementsConstructor) STL_DO_TEST(zeroElementsListConstructorTest)
TEST(ListConstructors, TwentyElementsConstructor) STL_DO_TEST(twentyElementsListConstructorTest)
TEST(ListConstructors, TwentyElementsWithDefaultValueConstructor) STL_DO_TEST(twentyElementsWithDefaultValueListConstructorTest)
TEST(ListConstructors, IteratorConstructor)  STL_DO_TEST(iteratorListConstructorTest)
TEST(ListConstructors, CopyConstructor)  STL_DO_TEST(copyListConstructorTest)

TEST(ListAssignation, ListAssignationBothEmpty) STL_DO_TEST(listAssignationBothEmptyTest)
TEST(ListAssignation, ListAssignationBothNotEmpty) STL_DO_TEST(listAssignationBothNotEmptyTest)
TEST(ListAssignation, ListAssignationToEmpty) STL_DO_TEST(listAssignationToEmptyTest)
TEST(ListAssignation, ListAssignationFromEmpty) STL_DO_TEST(listAssignationFromEmptyTest)

TEST(ListAssignationFunction, ListAssignationFunctionBothEmpty) STL_DO_TEST(listAssignationFunctionBothEmptyTest)
TEST(ListAssignationFunction, ListAssignationFunctionBothNotEmpty) STL_DO_TEST(listAssignationFunctionBothNotEmptyTest)
TEST(ListAssignationFunction, ListAssignationFunctionToEmpty) STL_DO_TEST(listAssignationFunctionToEmptyTest)
TEST(ListAssignationFunction, ListAssignationFunctionFromEmpty) STL_DO_TEST(listAssignationFunctionFromEmptyTest)
TEST(ListAssignationFunction, ListAssignationFunctionSizeZero) STL_DO_TEST(listAssignationFunctionSizeZeroTest)
TEST(ListAssignationFunction, ListAssignationFunctionSizeZeroVal) STL_DO_TEST(listAssignationFunctionSizeZeroValTest)
TEST(ListAssignationFunction, ListAssignationFunctionSizeNoVal) STL_DO_TEST(listAssignationFunctionSizeNoValTest)
TEST(ListAssignationFunction, ListAssignationFunctionSizeVal) STL_DO_TEST(listAssignationFunctionSizeValTest)

TEST(ListPushPop, ListPushPopFront) STL_DO_TEST(listPushPopFrontTest)
TEST(ListPushPop, ListPushPopBack) STL_DO_TEST(listPushPopBackTest)
TEST(ListPushPop, ListPushFrontPopBack) STL_DO_TEST(listPushFrontPopBackTest)
TEST(ListPushPop, ListPushBackPopFront) STL_DO_TEST(listPushBackPopFrontTest)

TEST(ListInsert, ListInsertSingleValues) STL_DO_TEST(listInsertSingleValuesTest)
TEST(ListInsert, ListInsertSeveralValues) STL_DO_TEST(listInsertSeveralValuesTest)
TEST(ListInsert, ListInsertIteratorPointedValues) STL_DO_TEST(listInsertIteratorPointedValuesTest)

TEST(ListErase, ListEraseSingleValues) STL_DO_TEST(listEraseSingleValuesTest)
TEST(ListErase, ListEraseIteratorPointedValues) STL_DO_TEST(listEraseIteratorPointedValuesTest)

TEST(ListSwap, ListSwap) STL_DO_TEST(listSwapTest)
TEST(ListSwap, ListSwapLEmpty) STL_DO_TEST(listSwapLEmptyTest)
TEST(ListSwap, ListSwapREmpty) STL_DO_TEST(listSwapREmptyTest)
TEST(ListSwap, ListSwapEmpty) STL_DO_TEST(listSwapBothEmptyTest)
TEST(ListSwap, ListNonMemberSwap) STL_DO_TEST(listNonMemberSwapTest)
TEST(ListSwap, ListNonMemberSwapLEmpty) STL_DO_TEST(listNonMemberSwapLEmptyTest)
TEST(ListSwap, ListNonMemberSwapREmpty) STL_DO_TEST(listNonMemberSwapREmptyTest)
TEST(ListSwap, ListNonMemberSwapEmpty) STL_DO_TEST(listNonMemberSwapBothEmptyTest)

TEST(ListResize, ListResizeWithoutDefault) STL_DO_TEST(listResizeWithoutDefaultTest)
TEST(ListResize, ListResizeWithDefault) STL_DO_TEST(listResizeWithDefaultTest)

TEST(ListClear, ListClear) STL_DO_TEST(listClearTest)

TEST(ListSplice, ListSpliceBegin) STL_DO_TEST(listSpliceBeginTest)
TEST(ListSplice, ListSpliceEnd) STL_DO_TEST(listSpliceEndTest)
TEST(ListSplice, ListSpliceRandom) STL_DO_TEST(listSpliceRandomTest)
TEST(ListSplice, ListSpliceOneBegin) STL_DO_TEST(listSpliceOneBeginTest)
TEST(ListSplice, ListSpliceOneEnd) STL_DO_TEST(listSpliceOneEndTest)
TEST(ListSplice, ListSpliceOneRandom) STL_DO_TEST(listSpliceOneRandomTest)
TEST(ListSplice, ListSpliceIterBegin) STL_DO_TEST(listSpliceIterBeginTest)
TEST(ListSplice, ListSpliceIterEnd) STL_DO_TEST(listSpliceIterEndTest)
TEST(ListSplice, ListSpliceIterRandom) STL_DO_TEST(listSpliceIterRandomTest)

TEST(ListRemove, ListRemoveNotRandom) STL_DO_TEST(listRemoveNotRandomTest)
TEST(ListRemove, ListRemove) STL_DO_TEST(listRemoveTest)
TEST(ListRemove, ListRemoveAll) STL_DO_TEST(listRemoveAllTest)
TEST(ListRemove, ListRemoveAllSame) STL_DO_TEST(listRemoveAllSameTest)
TEST(ListRemove, ListRemoveIf) STL_DO_TEST(listRemoveIfTest)

TEST(ListUnique, ListUnique) STL_DO_TEST(listUniqueTest)
TEST(ListUnique, ListUniqueSorted) STL_DO_TEST(listUniqueSortedTest)
TEST(ListUnique, ListUniqueCompare) STL_DO_TEST(listUniqueCompareTest)
TEST(ListUnique, ListUniqueSortedCompare) STL_DO_TEST(listUniqueSortedCompareTest)

TEST(ListMerge, ListMerge)  STL_DO_TEST(listMergeTest)

TEST(ListSort, ListSortExample)  STL_DO_TEST(listSortExampleTest)

TEST(ListReverse, ListReverse) STL_DO_TEST(listReverseTest)

TEST(ListCompare, ListCompareEquals) STL_DO_TEST(listCompareEqualsTest)
TEST(ListCompare, ListCompareNotEquals) STL_DO_TEST(listCompareNotEqualsTest)
TEST(ListCompare, ListCompareLessThan) STL_DO_TEST(listCompareLessThanTest)
TEST(ListCompare, ListCompareGreaterThan) STL_DO_TEST(listCompareGreaterThanTest)
TEST(ListCompare, ListCompareLTE) STL_DO_TEST(listCompareLTETest)
TEST(ListCompare, ListCompareGTE) STL_DO_TEST(listCompareGTETest)

/*** MAP TESTS ***/

TEST(MapConstructors, DefaultConstructor) STL_DO_TEST(defaultMapConstructorTest)
TEST(MapConstructors, IteratorConstructor)  STL_DO_TEST(iteratorMapConstructorTest)
TEST(MapConstructors, DefaultWithCompare) STL_DO_TEST(defaultMapWithCompareTest)
TEST(MapConstructors, IteratorWithCompare)  STL_DO_TEST(iteratorMapWithCompareTest)
TEST(MapConstructors, CopyConstructor)  STL_DO_TEST(copyMapConstructorTest)
TEST(MapConstructors, AssignOperatorEmpty) STL_DO_TEST(assignOperatorEmptyTest)
TEST(MapConstructors, AssignOperatorNotEmpty)  STL_DO_TEST(assignOperatorNotEmptyTest)
TEST(MapConstructors, AssignOperatorEmptyWithCmp) STL_DO_TEST(assignOperatorEmptyWithCmpTest)
TEST(MapConstructors, AssignOperatorNotEmptyWithCmp)  STL_DO_TEST(assignOperatorNotEmptyWithCmpTest)

TEST(MapOperatorSquare, OperSqtest) {
    std::map<char, std::string> myv;
    std::map<char, std::string> stv;

    std::string keys = getRandomValue<std::string>();

    int i = 0;
    char k[4];

    for (std::string::size_type s = 0; s < keys.length() && s < 23; ++s) {
        std::string val = getRandomValue<std::string>();
        myv[keys[s]] = val;
        stv[keys[s]] = val;
        if (s % 5 == 0)
            k[i++] = keys[s];
    }

    myv[k[0]] = myv[k[1]];
    myv[k[2]] = myv[k[3]];
    stv[k[0]] = stv[k[1]];
    stv[k[2]] = stv[k[3]];

    testMapContainersEqual(myv, stv);
}

TEST(MapOperatorSquare, OperSqtestCmp) {
    std::map<char, std::string, bool (*)(char, char)> myv(map_constructor_greater_compare<char>);
    std::map<char, std::string, bool (*)(char, char)> stv(map_constructor_greater_compare<char>);

    std::string keys = getRandomValue<std::string>();

    int i = 0;
    char k[4];

    for (std::string::size_type s = 0; s < keys.length() && s < 23; ++s) {
        std::string val = getRandomValue<std::string>();
        myv[keys[s]] = val;
        stv[keys[s]] = val;
        if (s % 5 == 0)
            k[i++] = keys[s];
    }

    myv[k[0]] = myv[k[1]];
    myv[k[2]] = myv[k[3]];
    stv[k[0]] = stv[k[1]];
    stv[k[2]] = stv[k[3]];

    testMapContainersEqual(myv, stv);
}

TEST(MapInsert, InsertHint)  STL_DO_TEST(mapInsertHintTest)
TEST(MapInsert, InsertIterators)  STL_DO_TEST(mapInsertIteratorsTest)

TEST(MapErase, EraseSingle)  STL_DO_TEST(mapEraseSingleTest)
TEST(MapErase, EraseKey)  STL_DO_TEST(mapEraseKeyTest)
TEST(MapErase, EraseIterators)  STL_DO_TEST(mapEraseIteratorsTest)

TEST(MapSwap, SwapEmpty)  STL_DO_TEST(mapSwapEmptyTest)
TEST(MapSwap, SwapOneEmpty)  STL_DO_TEST(mapSwapOneEmptyTest)
TEST(MapSwap, SwapNotEmpty)  STL_DO_TEST(mapSwapNotEmptyTest)

TEST(MapClear, Clear)  STL_DO_TEST(mapClearTest)
TEST(MapKeyComp, KeyComp)  STL_DO_TEST(mapKeyCompTest)
TEST(MapValComp, KeyComp)  STL_DO_TEST(mapValCompTest)

TEST(MapFind, FindExist)  STL_DO_TEST(mapFindExistTest)
TEST(MapFind, FindNotExist)  STL_DO_TEST(mapFindNotExistTest)

TEST(MapCount, CountEmpty)  STL_DO_TEST(mapCountEmptyTest)
TEST(MapCount, CountExist)  STL_DO_TEST(mapCountExistTest)
TEST(MapCount, CountNotExist)  STL_DO_TEST(mapCountNotExistTest)

TEST(MapLowerBound, BelowMin)  STL_DO_TEST(mapLowerBoundBelowMinTest)
TEST(MapLowerBound, AboveMax)  STL_DO_TEST(mapLowerBoundAboveMaxTest)
TEST(MapLowerBound, Existant)  STL_DO_TEST(mapLowerBoundExistantTest)
TEST(MapLowerBound, Random)    STL_DO_TEST(mapLowerBoundRandomTest)

TEST(MapUpperBound, BelowMin)  STL_DO_TEST(mapUpperBoundBelowMinTest)
TEST(MapUpperBound, AboveMax)  STL_DO_TEST(mapUpperBoundAboveMaxTest)
TEST(MapUpperBound, Existant)  STL_DO_TEST(mapUpperBoundExistantTest)
TEST(MapUpperBound, Random)    STL_DO_TEST(mapUpperBoundRandomTest)

TEST(MapEqualRange, BelowMin)  STL_DO_TEST(mapEqualRangeBelowMinTest)
TEST(MapEqualRange, AboveMax)  STL_DO_TEST(mapEqualRangeAboveMaxTest)
TEST(MapEqualRange, Existant)  STL_DO_TEST(mapEqualRangeExistantTest)
TEST(MapEqualRange, Random)    STL_DO_TEST(mapEqualRangeRandomTest)

/*** STACK TESTS ***/

TEST(StackConstructor, StackEmptyConstructor) STL_DO_TEST(stackEmptyConstructorTest)
TEST(StackConstructor, StackListConstructor) STL_DO_TEST(stackListConstructorTest)
TEST(StackConstructor, StackVectorConstructor) STL_DO_TEST(stackVectorConstructorTest)

TEST(StackEmpty, StackEmpty) STL_DO_TEST(stackEmptyTest)
TEST(StackEmpty, StackEmptyList) STL_DO_TEST(stackEmptyListTest)
TEST(StackEmpty, StackEmptyVector) STL_DO_TEST(stackEmptyVectorTest)

TEST(StackSize, StackSize) STL_DO_TEST(stackSizeTest)
TEST(StackSize, StackSizeList) STL_DO_TEST(stackSizeListTest)
TEST(StackSize, StackSizeVector) STL_DO_TEST(stackSizeVectorTest)

TEST(StackPush, StackPushPopList) STL_DO_TEST(stackPushPopListTest)
TEST(StackPush, StackPushPopVector) STL_DO_TEST(stackPushPopVectorTest)

TEST(StackCompare, StackCompareEquals) STL_DO_TEST(stackCompareOperatorsTest)

/*** QUEUE TESTS ***/

TEST(QueueConstructor, QueueEmptyConstructor) STL_DO_TEST(queueEmptyConstructorTest)
TEST(QueueConstructor, QueueListConstructor) STL_DO_TEST(queueListConstructorTest)

TEST(QueueEmpty, QueueEmptyList) STL_DO_TEST(queueEmptyListTest)

TEST(QueueSize, QueueSizeList) STL_DO_TEST(queueSizeListTest)

TEST(QueuePushPop, QueuePushPopList) STL_DO_TEST(queuePushPopListTest)

TEST(QueueCompare, QueueCompareOperators) STL_DO_TEST(queueCompareOperatorsTest)

int main(int argc, char **argv) {
    srand(time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
