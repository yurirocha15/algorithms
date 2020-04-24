#include "sorting.hpp"

template<class T>
void print(std::vector<T> vec) {
    for(auto& i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int>tint({3,4,65,43,7,44,6,76,5,4,334,6565});
    std::vector<float>tfloat({2,23.2,33.2,454.3,23.2000211,3433.3432,1.23, 0.2});
    std::vector<std::string>tstring({"asdfsd", "tregid", "dsfjlg", "dsfhuthr", "sdgiofhwer", "gtheivnew00", "asdfsdq"});

    Sorted sorter;
    try {
        sorter.chooseSorter("quick");
    } catch (std::string e) {
        std::cout << e << std::endl;
    }
    sorter.sort<int>(tint);
    sorter.sort<float>(tfloat);
    sorter.sort<std::string>(tstring);

    print<int>(tint);
    print<float>(tfloat);
    print<std::string>(tstring);

    return 0;
}