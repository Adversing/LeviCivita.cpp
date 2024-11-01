#include "levi_civita.hpp"
#include <stdexcept>
#include <algorithm>

namespace tensor {

const std::map<std::vector<size_t>, int8_t> LeviCivita::PARITY_2D_MAP = {
    {{0, 1},  1},
    {{1, 0}, -1}
};

const std::map<std::vector<size_t>, int8_t> LeviCivita::PARITY_3D_MAP = {
    {{0, 1, 2},  1},
    {{1, 2, 0},  1},
    {{2, 0, 1},  1},
    {{1, 0, 2}, -1},
    {{2, 1, 0}, -1},
    {{0, 2, 1}, -1}
};

LeviCivita::LeviCivita(const size_t dim) : dimension(dim) {
    if (dim == 0) {
        throw std::invalid_argument("Dimension cannot be zero");
    }
    if (dim > MAX_DIMENSION) {
        throw std::invalid_argument("Dimension exceeds maximum supported size");
    }
}

int8_t LeviCivita::get(const std::vector<size_t>& indices) const {
    if (!validateIndices(indices)) {
        return 0;
    }

    if (dimension == 2) {
        auto it = PARITY_2D_MAP.find(indices);
        if (it != PARITY_2D_MAP.end()) {
            return it->second;
        }
    }
    else if (dimension == 3) {
        auto it = PARITY_3D_MAP.find(indices);
        if (it != PARITY_3D_MAP.end()) {
            return it->second;
        }
    }
    
    return isEvenPermutation(indices) ? 1 : -1;
}

size_t LeviCivita::getDimension() const noexcept {
    return dimension;
}

bool LeviCivita::validateIndices(const std::vector<size_t>& indices) const noexcept {
    if (indices.size() != dimension) {
        return false;
    }
    
    std::vector<bool> used(dimension, false);
    for (const size_t idx : indices) {
        if (idx >= dimension || used[idx]) {
            return false;
        }
        used[idx] = true;
    }
    
    return true;
}

bool LeviCivita::isEvenPermutation(const std::vector<size_t>& indices) const {
    std::vector<size_t> arr = indices;
    std::vector<size_t> temp(dimension);
    int inversions = countInversionsMergeSort(arr, temp, 0, dimension - 1);
    return (inversions % 2) == 0;
}

int LeviCivita::countInversionsMergeSort(std::vector<size_t>& arr, std::vector<size_t>& temp, 
                                        size_t left, size_t right) const {
    int inversions = 0;
    if (left < right) {
        size_t mid = (left + right) / 2;
        inversions += countInversionsMergeSort(arr, temp, left, mid);
        inversions += countInversionsMergeSort(arr, temp, mid + 1, right);
        inversions += mergeAndCount(arr, temp, left, mid + 1, right);
    }
    return inversions;
}

int LeviCivita::mergeAndCount(std::vector<size_t>& arr, std::vector<size_t>& temp,
                             size_t left, size_t mid, size_t right) const {
    size_t i = left;
    size_t j = mid;
    size_t k = left;
    int inversions = 0;

    while (i <= mid - 1 && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inversions += mid - i;
        }
    }

    while (i <= mid - 1) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inversions;
}

}
