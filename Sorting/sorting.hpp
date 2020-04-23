#pragma once
#include <string>
#include <vector>
#include <stack>
#include <iostream>

class Sorted {
public:
    Sorted();
    Sorted(std::string str);
    virtual ~Sorted(){};

    template<class T>
    void sort(std::vector<T>& A);
    
    void chooseSorter(std::string type);
protected:
    std::string type;

    template<class T>
    void merge(std::vector<T>& A, int iBegin, int iMiddle, int iEnd, std::vector<T>& B);

    template<class T>
    void mergeSort(std::vector<T>& A);

    template<class T>
    int partition(std::vector<T>& vec, int iBegin, int iEnd);

    template<class T>
    void quickSort(std::vector<T>& vec);
};

template<class T>
void Sorted::sort(std::vector<T>& A){
    if(this->type == "quick") {
        this->quickSort(A);
    }
    else if (this->type == "merge") {
        this->mergeSort(A);
    }
    else {
        std::cerr << "Sorting algorithm not supported" << std::endl;
    }
}

template<class T>
void Sorted::merge(std::vector<T>& A, int iBegin, int iMiddle, int iEnd, std::vector<T>& B) {
    for(int k = iBegin, i = iBegin, j = iMiddle; k < iEnd; k++) {
        if(i < iMiddle && (j >= iEnd || A[i] < A[j])) {
            B[k] = A[i++];
        }
        else {
            B[k] = A[j++];
        }
    }
}


template<class T>
void Sorted::mergeSort(std::vector<T>& A) {
    if(A.empty()) return;
    unsigned int n = A.size();
    std::vector<T> B(A.begin(), A.end());
    bool swap = false;
    for(unsigned int width = 1; width < n; width *= 2) {
        for(unsigned int i = 0; i < n; i += 2*width) {
            merge(swap ? A : B, i, std::min(i + width, n), std::min(i + 2*width, n), swap ? B : A);
        }
        swap = !swap;
    }
    if(!swap) {
        try {
            std::copy(B.begin(), B.end(), A.begin());
        }
        catch(...) {
            std::cerr << "Error when copying." << std::endl;
        } 
    }
}


template<class T>
int Sorted::partition(std::vector<T>& vec, int iBegin, int iEnd) {
    T pivot = vec[iEnd ];
    int pos  = iBegin;
    for(int i = iBegin; i < iEnd; ++i) {
        if(vec[i] < pivot) {
            std::swap(vec[pos++], vec[i]);
        }
    }
    std::swap(vec[iEnd], vec[pos]);
    return pos;
}

template<class T>
void Sorted::quickSort(std::vector<T>& vec) {
    if(vec.empty()) return;
    int iBegin = 0;
    int iEnd = vec.size() - 1;

    std::stack<std::vector<int> > next_tuple;
    next_tuple.push(std::vector<int>{iBegin, iEnd});
    while(!next_tuple.empty()) {
        std::vector<int> nt = next_tuple.top();
        next_tuple.pop();

        if(nt.empty()) continue;

        iBegin = nt[0];
        iEnd = nt[1];

        if(iBegin < iEnd) {
            int pi = partition(vec, iBegin, iEnd);
            next_tuple.push(std::vector<int>{iBegin, pi - 1});
            next_tuple.push(std::vector<int>{pi + 1, iEnd});
        }
    }
}