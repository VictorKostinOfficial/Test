#include <algorithm>
#include <vector>

template <typename V>
void mergeSort(std::vector<V>& array, const size_t begin, const size_t end) {
    if (array.size() < 2) {
        return;
    }

    if (begin >= end) {
        return;
    }

    const size_t mid = 1 + begin + (end - begin) / 2;
    mergeSort(array, begin, mid - 1);
    mergeSort(array, mid, end);

    const std::vector<V> leftArray(array.begin() + begin, array.begin() + mid);
    const std::vector<V> rightArray(array.begin() + mid, array.begin() + end + 1);

    std::merge(leftArray.begin(), leftArray.end(), rightArray.begin(), rightArray.end(), array.begin() + begin);
}