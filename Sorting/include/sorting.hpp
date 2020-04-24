#pragma once
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <unordered_map>

class Sorted {
public:
    Sorted();
    Sorted(std::string str);
    virtual ~Sorted(){};

    template<class T>
    void sort(std::vector<T>& A);
    
    void chooseSorter(std::string type);

    std::vector<std::string> getImplementedSorts();
protected:
    std::string type;

    std::vector<std::string> sorters;

    template<class T>
    void merge(std::vector<T>& A, int iBegin, int iMiddle, int iEnd, std::vector<T>& B);

    template<class T>
    void mergeSort(std::vector<T>& A);

    template<class T>
    int partition(std::vector<T>& vec, int iBegin, int iEnd);

    template<class T>
    void quickSort(std::vector<T>& vec);
};

#include "sorting.tcc"