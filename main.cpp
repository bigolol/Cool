#include <iostream>
#include "SortedVector.h"
#include "CooTensorElement.h"
#include "CooTensor.h"

int main() {
    CooTensor<6> tensor{};
    for(size_t i = 0; i < 1000; ++i) {
        uint32_t coords[6];
        for(size_t j = 0; j < 6; ++j) {
            coords[j] = 0 + (rand() % static_cast<int>(20 - 0 + 1));
        }
        numericVal val = 2;
        tensor.add(coords, val);
    }
}