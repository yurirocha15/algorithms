#include <vector>
#include <iostream>
#include <string>

template<class T>
void merge(std::vector<T>& A, int iBegin, int iMiddle, int iEnd, std::vector<T>& B) {
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
void mergeSort(std::vector<T>& A) {
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
void print(std::vector<T> vec) {
    for(auto& i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

template<class T>
int partition(std::vector<T>& vec, int iBegin, int iEnd) {
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
void quickSort(std::vector<T>& vec, int iBegin = 0, int iEnd = -1) {
    if(iEnd == -1) iEnd = vec.size() - 1;
    if(iBegin < iEnd) {
        int pi = partition(vec, iBegin, iEnd);
        quickSort(vec, iBegin, pi - 1);
        quickSort(vec, pi + 1, iEnd);
    }
    //TODO: remove recursion
}


int main() {
    std::vector<int>tint({3,4,65,43,7,44,6,76,5,4,334,6565});
    std::vector<float>tfloat({2,23.2,33.2,454.3,23.2000211,3433.3432,1.23, 0.2});
    std::vector<std::string>tstring({"asdfsd", "tregid", "dsfjlg", "dsfhuthr", "sdgiofhwer", "gtheivnew00", "asdfsdq"});

    // quickSort<int>(tint);
    // quickSort<float>(tfloat);
    // quickSort<std::string>(tstring);

    print<int>(tint);
    print<float>(tfloat);
    print<std::string>(tstring);

    return 0;
}