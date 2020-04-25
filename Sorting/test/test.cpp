#include "sorting.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class SortingTester : public ::testing::Test {
protected:
    SortingTester() {
        //TODO: Add better examples and some more corner cases
        tint = {4,6565,65,43,7,44,6,76,5,4,334,3};
        tfloat = {2,23.2,33.2,454.3,23.2000211,3433.3432,1.23, 0.2};
        tstring = {"asdfsd", "tregid", "dsfjlg", "dsfhuthr", "sdgiofhwer", "gtheivnew00", "asdfsdq"};
        tint_sorted = {3, 4, 4, 5, 6, 7, 43, 44, 65, 76, 334, 6565};
        tfloat_sorted = {0.2, 1.23, 2, 23.2, 23.2000211, 33.2, 454.3, 3433.3432};
        tstring_sorted = {"asdfsd", "asdfsdq", "dsfhuthr", "dsfjlg", "gtheivnew00", "sdgiofhwer", "tregid"};
    }
    virtual ~SortingTester() {}
    Sorted sorter;
    std::vector<int>tint;
    std::vector<float>tfloat;
    std::vector<std::string>tstring;
    std::vector<int>tint_sorted;
    std::vector<float>tfloat_sorted;
    std::vector<std::string>tstring_sorted;
    std::vector<int>empty_vector;
};

//This checks if the vector is sorted after running quick_sort. 
TEST_F(SortingTester, testQuickSort) {
    sorter.sort<int>(tint, Sorted::quick_sort);
    sorter.sort<float>(tfloat, Sorted::quick_sort);
    sorter.sort<std::string>(tstring, Sorted::quick_sort);

    EXPECT_THAT(tint, ::testing::ElementsAreArray(tint_sorted));
    EXPECT_THAT(tfloat, ::testing::ElementsAreArray(tfloat_sorted));
    EXPECT_THAT(tstring, ::testing::ElementsAreArray(tstring_sorted));
}

//This checks if the vector is sorted after running merge_sort.
TEST_F(SortingTester, testMergeSort) {
    sorter.sort<int>(tint, Sorted::merge_sort);
    sorter.sort<float>(tfloat, Sorted::merge_sort);
    sorter.sort<std::string>(tstring, Sorted::merge_sort);

    EXPECT_THAT(tint, ::testing::ElementsAreArray(tint_sorted));
    EXPECT_THAT(tfloat, ::testing::ElementsAreArray(tfloat_sorted));
    EXPECT_THAT(tstring, ::testing::ElementsAreArray(tstring_sorted));
}

//This checks if the vector is sorted after running insertion_sort. 
TEST_F(SortingTester, testInsertionSort) {
    sorter.sort<int>(tint, Sorted::insertion_sort);
    sorter.sort<float>(tfloat, Sorted::insertion_sort);
    sorter.sort<std::string>(tstring, Sorted::insertion_sort);

    EXPECT_THAT(tint, ::testing::ElementsAreArray(tint_sorted));
    EXPECT_THAT(tfloat, ::testing::ElementsAreArray(tfloat_sorted));
    EXPECT_THAT(tstring, ::testing::ElementsAreArray(tstring_sorted));
}

//This asserts that the sorting algorithm can handle empty vectors without segmentation fault
TEST_F(SortingTester, testEmpty) {
    ASSERT_EXIT((sorter.sort<int>(empty_vector, Sorted::quick_sort), exit(0)), ::testing::ExitedWithCode(0), ".*");
    ASSERT_EXIT((sorter.sort<int>(empty_vector, Sorted::merge_sort), exit(0)), ::testing::ExitedWithCode(0), ".*");
    ASSERT_EXIT((sorter.sort<int>(empty_vector, Sorted::insertion_sort), exit(0)), ::testing::ExitedWithCode(0), ".*");
}

