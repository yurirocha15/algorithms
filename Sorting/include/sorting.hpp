#pragma once
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

class Sorted {
public:

    //Tags used to choose the sorting algorithm
    static struct quick_sort_tag{} quick_sort;
    static struct merge_sort_tag{} merge_sort;
    static struct insertion_sort_tag{} insertion_sort;

    //Sorted Class
    Sorted();

    virtual ~Sorted(){};

    //Tag dispatching
    template<class T>
    void sort(std::vector<T>& A, quick_sort_tag);
    
    template<class T>
    void sort(std::vector<T>& A, merge_sort_tag);
    
    template<class T>
    void sort(std::vector<T>& A, insertion_sort_tag);

protected:
    template<class T>
    void merge(std::vector<T>& A, int iBegin, int iMiddle, int iEnd, std::vector<T>& B);

    template<class T>
    void mergeSort(std::vector<T>& A);

    template<class T>
    int partition(std::vector<T>& vec, int iBegin, int iEnd);

    template<class T>
    void quickSort(std::vector<T>& vec);

    template<class T>
    void insertionSort(std::vector<T>& vec);
};

#include "sorting.tcc"