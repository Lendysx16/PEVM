#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <iostream>

template<typename T>
size_t partition(T *nums, size_t l, size_t r) {
    T pivot = nums[(l + r) / 2];
    size_t i = l, j = r;
    while (i <= j) {
        while (nums[i] < pivot) {
            i += 1;
        }
        while (nums[j] > pivot) {
            j -= 1;
        }

        if (i >= j) {
            break;
        }
        std::swap(nums[i], nums[j]);
        i += 1;
        j -= 1;
    }
    return j;
}

template<typename T>
void quicksort(T *nums, size_t l, size_t r) {
    if (l < r) {
        size_t q = partition<T>(nums, l, r);
        quicksort<T>(nums, l, q);
        quicksort<T>(nums, q + 1, r);
    }
}
#endif
