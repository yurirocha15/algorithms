#include "sorting.hpp"
#include "gtest/gtest.h"

class SortingTester : public ::testing::Test {
protected:
    SortingTester() {
        quick_sorter.chooseSorter("quick");
        merge_sorter.chooseSorter("merge");
    }
    virtual ~SortingTester() {}
    Sorted quick_sorter;
    Sorted merge_sorter;
};

TEST_F(SortingTester, testQuickSort) {
    std::vector<int>tint({4,6565,65,43,7,44,6,76,5,4,334,3});
    std::vector<float>tfloat({2,23.2,33.2,454.3,23.2000211,3433.3432,1.23, 0.2});
    std::vector<std::string>tstring({"asdfsd", "tregid", "dsfjlg", "dsfhuthr", "sdgiofhwer", "gtheivnew00", "asdfsdq"});

    quick_sorter.sort<int>(tint);
    quick_sorter.sort<float>(tfloat);
    quick_sorter.sort<std::string>(tstring);

    EXPECT_EQ(*(tint.begin()), 3);
    EXPECT_EQ(*(tint.rbegin()), 6565);

    EXPECT_FLOAT_EQ(*(tfloat.begin()), 0.2);
    EXPECT_FLOAT_EQ(*(tfloat.rbegin()), 3433.3432);

    EXPECT_EQ(*(tstring.begin()), "asdfsd");
    EXPECT_EQ(*(tstring.rbegin()), "tregid");
}

TEST_F(SortingTester, testMergeSort) {
    std::vector<int>tint({4,6565,65,43,7,44,6,76,5,4,334,3});
    std::vector<float>tfloat({2,23.2,33.2,454.3,23.2000211,3433.3432,1.23, 0.2});
    std::vector<std::string>tstring({"asdfsd", "tregid", "dsfjlg", "dsfhuthr", "sdgiofhwer", "gtheivnew00", "asdfsdq"});

    merge_sorter.sort<int>(tint);
    merge_sorter.sort<float>(tfloat);
    merge_sorter.sort<std::string>(tstring);

    EXPECT_EQ(*(tint.begin()), 3);
    EXPECT_EQ(*(tint.rbegin()), 6565);

    EXPECT_FLOAT_EQ(*(tfloat.begin()), 0.2);
    EXPECT_FLOAT_EQ(*(tfloat.rbegin()), 3433.3432);

    EXPECT_EQ(*(tstring.begin()), "asdfsd");
    EXPECT_EQ(*(tstring.rbegin()), "tregid");
}

TEST_F(SortingTester, testEmpty) {
    std::vector<int> empty_vector;
    ASSERT_EXIT((quick_sorter.sort<int>(empty_vector), exit(0)), ::testing::ExitedWithCode(0), ".*");
    ASSERT_EXIT((merge_sorter.sort<int>(empty_vector), exit(0)), ::testing::ExitedWithCode(0), ".*");
}

