#pragma once
//tag dispatching
template<class T>
void Sorted::sort(std::vector<T>& A, Sorted::quick_sort_tag tag){
    this->quickSort<T>(A);
}

template<class T>
void Sorted::sort(std::vector<T>& A, Sorted::merge_sort_tag tag){
    this->mergeSort<T>(A);
}

template<class T>
void Sorted::sort(std::vector<T>& A, Sorted::insertion_sort_tag tag){
    this->insertionSort<T>(A);
}

//A is sorted from begin to middle and from middle to end. This function merge those two intervals into B.
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

//We use the bottom-up approach here to avoid recursions. Swapping B and A on each iteration avoids unnecessary copies.
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

//This function put the values smaller than the pivot to its left, and the bigger ones to its right
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

//We use a stack to store the next limits tuples. This perform the sorting in a depth first approach ensuring log(N) storage requirement.
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

template<class T>
void Sorted::insertionSort(std::vector<T>& vec) {
    if(vec.empty()) return;
    for(auto i = vec.begin(); i != vec.end(); ++i) {
        //find insertion point. Because the sequence from begin until i is sorted, we can use the upper_bound function.
        auto ip = std::upper_bound(vec.begin(), i, *i);
        //The rotate function is used to remove the value from its current position, shift the sequence from ip to i, and insert the value to the correct insertion point.
        std::rotate(ip, i, i + 1);
    }
}