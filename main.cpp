#include <iostream>
#include "SortedVector.h"
#include "CooTensorElement.h"
#include "CooTensor.h"

int main() {
    CooTensorElement<5, double > elem1{new uint32_t[5]{1,3,1,1,1},2};
    CooTensorElement<5, double > elem2{new uint32_t[5]{1,1,2,1,1},2};
    assert(elem2 < elem1);
    assert(!(elem2> elem1));
}