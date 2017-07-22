#include <iostream>
#include "CooTensor.h"

int main() {
    constexpr size_t dims = 6;
    constexpr size_t amt = 20;
    CooTensor<dims> tensor;
    tensor.reserve(amt);


    for(int i = 0; i < amt; ++i) {
        uint32_t coords[dims];
        for(int j = 0; j < dims; ++j) {
            coords[j] = static_cast<uint32_t >(0 + (rand() % static_cast<int>(20 - 0 + 1)));
        }
        tensor.add(coords, 2);
        std::cout << tensor << '\n';
    }


}