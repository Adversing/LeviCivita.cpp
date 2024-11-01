#ifndef LEVI_CIVITA_HPP
#define LEVI_CIVITA_HPP

#include <vector>
#include <cstdint>
#include <array>
#include <map>
#include <cstddef>

namespace tensor {

class LeviCivita {
public:
    explicit LeviCivita(const size_t dimension);
    int8_t get(const std::vector<size_t>& indices) const;
    [[nodiscard]] size_t getDimension() const noexcept;
    static constexpr size_t MAX_DIMENSION = 32;

private:
    size_t dimension;
    
    static const std::map<std::vector<size_t>, int8_t> PARITY_3D_MAP;
    static const std::map<std::vector<size_t>, int8_t> PARITY_2D_MAP;
    
    [[nodiscard]] bool validateIndices(const std::vector<size_t>& indices) const noexcept;
    [[nodiscard]] bool isEvenPermutation(const std::vector<size_t>& indices) const;
    [[nodiscard]] int countInversionsMergeSort(std::vector<size_t>& arr, std::vector<size_t>& temp, size_t left, size_t right) const;
    [[nodiscard]] int mergeAndCount(std::vector<size_t>& arr, std::vector<size_t>& temp, size_t left, size_t mid, size_t right) const;
};

}

#endif
