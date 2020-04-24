#include "sorting.hpp"
#include <algorithm>

Sorted::Sorted() {
    this->type = "quick";
    sorters.push_back("quick");
    sorters.push_back("merge");
}

Sorted::Sorted(std::string type) {
    sorters.push_back("quick");
    sorters.push_back("merge");
    std::transform(type.begin(), type.end(), std::back_inserter(this->type), ::tolower);
    auto found = std::find(sorters.begin(), sorters.end(), this->type);
    if(found == sorters.end()) throw "Sorting algorithm implementation not found. Required: " + this->type;
}

void Sorted::chooseSorter(std::string type) {
    this->type.clear();
    std::transform(type.begin(), type.end(), std::back_inserter(this->type), ::tolower);
    auto found = std::find(sorters.begin(), sorters.end(), this->type);
    if(found == sorters.end()) throw "Sorting algorithm implementation not found. Required: " + this->type;
}

std::vector<std::string> Sorted::getImplementedSorts() {
    return sorters;
}