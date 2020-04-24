#include "sorting.hpp"
#include "gtest/gtest.h"

class SortingTester : public ::testing::Test {
protected:
    SortingTester() {}
    virtual ~SortingTester() {}
    Sorted sorter;
};

//This checks if the vector is sorted after running quick_sort. TODO: check the whole vector instead of first and last element 
TEST_F(SortingTester, testQuickSort) {
    std::vector<int>tint({4,6565,65,43,7,44,6,76,5,4,334,3});
    std::vector<float>tfloat({2,23.2,33.2,454.3,23.2000211,3433.3432,1.23, 0.2});
    std::vector<std::string>tstring({"asdfsd", "tregid", "dsfjlg", "dsfhuthr", "sdgiofhwer", "gtheivnew00", "asdfsdq"});

    sorter.sort<int>(tint, Sorted::quick_sort);
    sorter.sort<float>(tfloat, Sorted::quick_sort);
    sorter.sort<std::string>(tstring, Sorted::quick_sort);

    EXPECT_EQ(*(tint.begin()), 3);
    EXPECT_EQ(*(tint.rbegin()), 6565);

    EXPECT_FLOAT_EQ(*(tfloat.begin()), 0.2);
    EXPECT_FLOAT_EQ(*(tfloat.rbegin()), 3433.3432);

    EXPECT_EQ(*(tstring.begin()), "asdfsd");
    EXPECT_EQ(*(tstring.rbegin()), "tregid");
}

//This checks if the vector is sorted after running merge_sort. TODO: check the whole vector instead of first and last element 
TEST_F(SortingTester, testMergeSort) {
    std::vector<int>tint({4,6565,65,43,7,44,6,76,5,4,334,3});
    std::vector<float>tfloat({2,23.2,33.2,454.3,23.2000211,3433.3432,1.23, 0.2});
    std::vector<std::string>tstring({"asdfsd", "tregid", "dsfjlg", "dsfhuthr", "sdgiofhwer", "gtheivnew00", "asdfsdq"});

    sorter.sort<int>(tint, Sorted::merge_sort);
    sorter.sort<float>(tfloat, Sorted::merge_sort);
    sorter.sort<std::string>(tstring, Sorted::merge_sort);

    EXPECT_EQ(*(tint.begin()), 3);
    EXPECT_EQ(*(tint.rbegin()), 6565);

    EXPECT_FLOAT_EQ(*(tfloat.begin()), 0.2);
    EXPECT_FLOAT_EQ(*(tfloat.rbegin()), 3433.3432);

    EXPECT_EQ(*(tstring.begin()), "asdfsd");
    EXPECT_EQ(*(tstring.rbegin()), "tregid");
}

//This asserts that the sorting algorithm can handle empty vectors without segmentation fault
TEST_F(SortingTester, testEmpty) {
    std::vector<int> empty_vector;
    ASSERT_EXIT((sorter.sort<int>(empty_vector, Sorted::quick_sort), exit(0)), ::testing::ExitedWithCode(0), ".*");
    ASSERT_EXIT((sorter.sort<int>(empty_vector, Sorted::merge_sort), exit(0)), ::testing::ExitedWithCode(0), ".*");
}

