#include <vector>
#include "vector.hpp"
#include "gtest/gtest.h"

TEST(CompareVectors, DefaultConstructor) {
    ft::vector<int> ftv;
    std::vector<int> stv;
    EXPECT_EQ(ftv.empty(), stv.empty());
    EXPECT_EQ(ftv.size(), stv.size());
    EXPECT_EQ(ftv.max_size(), stv.max_size());
    EXPECT_EQ(ftv.capacity(), stv.capacity());
    EXPECT_EQ(&(ftv[0]), &(stv[0]));
    EXPECT_EQ(ftv.begin() == ftv.end(), stv.begin() == stv.end());
    EXPECT_EQ(ftv.rbegin() == ftv.rend(), stv.rbegin() == stv.rend());
}

TEST(CompareVectors, ZeroElementsConstructor) {
    ft::vector<int> ftv(0);
    std::vector<int> stv(0);
    EXPECT_EQ(ftv.empty(), stv.empty());
    EXPECT_EQ(ftv.size(), stv.size());
    EXPECT_EQ(ftv.max_size(), stv.max_size());
    EXPECT_EQ(ftv.capacity(), stv.capacity());
    EXPECT_EQ(&(ftv[0]), &(stv[0]));
    EXPECT_EQ(ftv.begin() == ftv.end(), stv.begin() == stv.end());
    EXPECT_EQ(ftv.rbegin() == ftv.rend(), stv.rbegin() == stv.rend());
}

TEST(CompareVectors, TwentyElementsConstructor) {
    ft::vector<int> ftv(20);
    std::vector<int> stv(20);
    EXPECT_EQ(ftv.empty(), stv.empty());
    EXPECT_EQ(ftv.size(), stv.size());
    EXPECT_EQ(ftv.max_size(), stv.max_size());
    EXPECT_EQ(ftv.capacity(), stv.capacity());
    EXPECT_EQ(ftv.begin() == ftv.end(), stv.begin() == stv.end());
    EXPECT_EQ(ftv.rbegin() == ftv.rend(), stv.rbegin() == stv.rend());
}

TEST(CompareVectors, TwentyElementsWithDefaultValueConstructor) {
    ft::vector<int> ftv(20, 17);
    std::vector<int> stv(20, 17);
    EXPECT_EQ(ftv.empty(), stv.empty());
    EXPECT_EQ(ftv.size(), stv.size());
    EXPECT_EQ(ftv.max_size(), stv.max_size());
    EXPECT_EQ(ftv.capacity(), stv.capacity());
    EXPECT_EQ(ftv.begin() == ftv.end(), stv.begin() == stv.end());
    EXPECT_EQ(ftv.rbegin() == ftv.rend(), stv.rbegin() == stv.rend());
}

TEST(CompareVectors, CopyConstructor) {
    ft::vector<int> ftv_o(20, 17);
    std::vector<int> stv_o(20, 17);
    ft::vector<int> ftv(ftv_o);
    std::vector<int> stv(stv_o);
    EXPECT_EQ(ftv.empty(), stv.empty());
    EXPECT_EQ(ftv.size(), stv.size());
    EXPECT_EQ(ftv.max_size(), stv.max_size());
    EXPECT_EQ(ftv.capacity(), stv.capacity());
    EXPECT_EQ(ftv.begin() == ftv.end(), stv.begin() == stv.end());
    EXPECT_EQ(ftv.rbegin() == ftv.rend(), stv.rbegin() == stv.rend());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
