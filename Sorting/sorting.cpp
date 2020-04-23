#include "sorting.hpp"
#include <algorithm>

template<class T>
void print(std::vector<T> vec) {
    for(auto& i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

Sorted::Sorted() {
    this->type = "quick";
}

Sorted::Sorted(std::string type) {
    std::transform(type.begin(), type.end(), std::back_inserter(this->type), ::tolower);
}

void Sorted::chooseSorter(std::string type) {
    this->type.clear();
    std::transform(type.begin(), type.end(), std::back_inserter(this->type), ::tolower);
}

// int main() {
//     std::vector<int>tint({3,4,65,43,7,44,6,76,5,4,334,6565});
//     std::vector<float>tfloat({2,23.2,33.2,454.3,23.2000211,3433.3432,1.23, 0.2});
//     std::vector<std::string>tstring({"asdfsd", "tregid", "dsfjlg", "dsfhuthr", "sdgiofhwer", "gtheivnew00", "asdfsdq"});

//     Sorted sorter("quick");
//     sorter.sort<int>(tint);
//     sorter.sort<float>(tfloat);
//     sorter.sort<std::string>(tstring);

//     print<int>(tint);
//     print<float>(tfloat);
//     print<std::string>(tstring);

//     return 0;
// }
