# LeviCivita.cpp
A simple approach to the [Levi-Civita tensor](https://en.wikipedia.org/wiki/Levi-Civita_symbol).

## 📚 Example Usage:

```cpp
#include "levi_civita.hpp"
#include <iostream>
#include <iomanip>

void printTensorValue(const tensor::LeviCivita& tensor, const std::vector<size_t>& indices) {
    std::cout << "ε_";
    for (size_t idx : indices) {
        std::cout << (idx + 1);
    }
    std::cout << " = " << (int)tensor.get(indices) << std::endl;
}

int main() {
    try {
        // Test 2D tensor
        tensor::LeviCivita tensor2d(2);
        std::cout << "2D Levi-Civita tensor:\n";
        printTensorValue(tensor2d, {0, 1});
        printTensorValue(tensor2d, {1, 0});
        printTensorValue(tensor2d, {0, 0});
        
        std::cout << "\n3D Levi-Civita tensor:\n";
        // Test 3D tensor
        tensor::LeviCivita tensor3d(3);
        printTensorValue(tensor3d, {0, 1, 2});
        printTensorValue(tensor3d, {1, 2, 0});
        printTensorValue(tensor3d, {2, 0, 1});
        printTensorValue(tensor3d, {1, 0, 2});
        printTensorValue(tensor3d, {0, 2, 1});
        printTensorValue(tensor3d, {2, 1, 0});
        printTensorValue(tensor3d, {0, 0, 1});
        
        std::cout << "\n4D Levi-Civita tensor:\n";
        // Test 4D tensor
        tensor::LeviCivita tensor4d(4);
        printTensorValue(tensor4d, {0, 1, 2, 3});
        printTensorValue(tensor4d, {3, 2, 1, 0});
        printTensorValue(tensor4d, {0, 1, 1, 2});

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
```
