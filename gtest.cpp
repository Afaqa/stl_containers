#include <vector>
#include "vector.hpp"
#include "gtest/gtest.h"

struct SomeStruct {
    std::string name;
    float       number;
    SomeStruct() : name("empty"), number(15.51) {}
    SomeStruct(std::string const& name, float number) : name(name), number(number) {}
    SomeStruct(SomeStruct const& other) : name(other.name), number(other.number) {}
    SomeStruct& operator=(SomeStruct const& other) { name = other.name; number = other.number; return *this; }
    ~SomeStruct() {}
    bool operator==(SomeStruct const& other) const { return name == other.name && number == other.number; }
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
    std::cout << id << ": " << v1 << " == " << v2 << std::endl;
}
template<>
void printValues(std::size_t id, std::string const& v1, std::string const& v2) {
    std::cout << id << ": \"" << v1 << "\" == \"" << v2 << '"' << std::endl;
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
    std::vector<T> siter;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
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
        ft::vector<T> ftv_o(20);
        std::vector<T> stv_o(20);
        ft::vector<T> ftv(ftv_o);
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
        ft::vector<T> fiter;
        std::vector<T> siter;
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

    bool err = false;
    std::string fmsg = "success";
    std::string smsg = "success";
    T value = getRandomValue<T>();
    try {
        ftv.assign(ftv.max_size(), value);
    } catch(std::exception& e) { fmsg = e.what(); err = true; }
    try {
        stv.assign(stv.max_size(), value);
    } catch(std::exception& e) { smsg = e.what(); err = true; }

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
    ftv.insert(----------------ftv.end(), 7, value);
    stv.insert(----------------stv.end(), 7, value);
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

    T value = getRandomValue<T>();
    ftv.insert(++++++++ftv.begin(), range.begin(), range.end());
    stv.insert(++++++++stv.begin(), range.begin(), range.end());
    value = getRandomValue<T>();
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

    ftv.erase(++++++++ftv.begin());
    stv.erase(++++++++stv.begin());
    ftv.erase(----------------ftv.end());
    stv.erase(----------------stv.end());
    testContainersEqual(ftv, stv);
}

template<typename T>
void EraseRangeTest() {
    printTestName<T>("Testing erase range of values from container");

    std::size_t numOfItems = rand() % 20 + 10;
    ft::vector<T> ftv;
    std::vector<T> stv;
    for (std::size_t i = 0; i < numOfItems; ++i) {
        T value = getRandomValue<T>();
        ftv.push_back(value);
        stv.push_back(value);
    }
    testContainersEqualNoprint(ftv, stv);

    ftv.erase(++++++++ftv.begin(), ------ftv.end());
    stv.erase(++++++++stv.begin(), ------stv.end());
    ftv.erase(----------------ftv.end(), ftv.end());
    stv.erase(----------------stv.end(), stv.end());
    testContainersEqual(ftv, stv);
}

TEST(VectorConstructors, DefaultConstructor) FT_DO_TEST(defaultConstructorTest)
TEST(VectorConstructors, ZeroElementsConstructor) FT_DO_TEST(zeroElementsConstructorTest)
TEST(VectorConstructors, TwentyElementsConstructor) FT_DO_TEST(twentyElementsConstructorTest)
TEST(VectorConstructors, TwentyElementsWithDefaultValueConstructor) FT_DO_TEST(twentyElementsWithDefaultValueConstructorTest)
TEST(VectorConstructors, IteratorConstructor)  FT_DO_TEST(iteratorConstructorTest)
TEST(VectorConstructors, CopyConstructor)  FT_DO_TEST(copyConstructorTest)

TEST(VectorAssignation, AssignationOperatorToMoreCap) FT_DO_TEST(assignationOperatorToMoreCapTest)
TEST(VectorAssignation, AssignationOperatorToMoreSize) FT_DO_TEST(assignationOperatorToMoreSizeTest)
TEST(VectorAssignation, AssignationOperatorToLess) FT_DO_TEST(assignationOperatorToLessTest)
TEST(VectorAssignation, AssignationOperatorToSame) FT_DO_TEST(assignationOperatorToSameTest)

TEST(VectorCapacity, ResizeLess) FT_DO_TEST(resizeLessTest)
TEST(VectorCapacity, ResizeMore) FT_DO_TEST(resizeMoreTest)
TEST(VectorCapacity, ResizeSame) FT_DO_TEST(resizeSameTest)

TEST(VectorCapacity, ReserveLess) FT_DO_TEST(reserveLessTest)
TEST(VectorCapacity, ReserveMore) FT_DO_TEST(reserveMoreTest)
TEST(VectorCapacity, ReserveSame) FT_DO_TEST(reserveSameTest)
TEST(VectorCapacity, ReserveGreaterThanMax) FT_DO_TEST(reserveGreaterThanMaxTest)

TEST(VectorElementAccess, operatorBracketsAccess) FT_DO_TEST(OperatorBracketsAccessTest)
TEST(VectorElementAccess, functionAt) FT_DO_TEST(FunctionAtTest)
TEST(VectorElementAccess, functionFront) FT_DO_TEST(FunctionFrontTest)
TEST(VectorElementAccess, functionBack) FT_DO_TEST(FunctionBackTest)

TEST(VectorAssign, assignFillLess) FT_DO_TEST(AssignFillLessTest)
TEST(VectorAssign, assignFillBetweenSizeCap) FT_DO_TEST(AssignFillBetweenSizeCapTest)
TEST(VectorAssign, assignFillMore) FT_DO_TEST(AssignFillMoreTest)
TEST(VectorAssign, assignFillMaxSize) FT_DO_TEST(AssignFillMaxSizeTest)
TEST(VectorAssign, assignFillMoreThanMax) FT_DO_TEST(AssignFillMoreThanMaxTest)
TEST(VectorAssign, assignFillSame) FT_DO_TEST(AssignFillSameTest)

TEST(VectorPushBack, pushBack) FT_DO_TEST(PushBackTest)
TEST(VectorPopBack, popBack) FT_DO_TEST(PopBackTest)

TEST(VectorSwap, swap) FT_DO_TEST(SwapTest)
TEST(VectorSwap, swapOneEmpty) FT_DO_TEST(SwapOneEmptyTest)
TEST(VectorSwap, swapOneCleared) FT_DO_TEST(SwapOneClearedTest)
TEST(VectorSwap, swapEmpty) FT_DO_TEST(SwapEmptyTest)
TEST(VectorSwap, swapCleared) FT_DO_TEST(SwapClearedTest)

TEST(VectorClear, clear) FT_DO_TEST(ClearTest)
TEST(VectorClear, clearEmpty) FT_DO_TEST(ClearEmptyTest)
TEST(VectorClear, clearDouble) FT_DO_TEST(ClearDoubleTest)

TEST(VectorInsert, insert) FT_DO_TEST(InsertTest)
TEST(VectorInsert, insertMultiple) FT_DO_TEST(InsertMultipleTest)
TEST(VectorInsert, insertRange) FT_DO_TEST(InsertRangeTest)
TEST(VectorErase, erase) FT_DO_TEST(EraseTest)
TEST(VectorErase, eraseRange) FT_DO_TEST(EraseRangeTest)

int main(int argc, char **argv) {
    srand(time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
