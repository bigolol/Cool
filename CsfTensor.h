//
// Created by holger on 22.07.17.
//

#ifndef COOL_CSFTENSOR_H
#define COOL_CSFTENSOR_H

#include <vector>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include "typedefs.h"

template <size_t dims>
class CsfTensor {
public:
    std::vector<numericVal> vals_;
    std::vector<uint32_t> modes[dims];
    std::vector<uint32_t> indices[dims - 1];

    numericVal getValueAt(uint32_t coords[dims]) {
        size_t posInArr = 0;
        for(size_t i = 0; i < dims - 1; ++i) {
            while(posInArr < modes[i].size() && modes[i][posInArr] < coords[i]) {
                ++posInArr;
            }
            if(posInArr == modes[i].size() ||
                    modes[i][posInArr] != coords[i]) {
                return 0;
            }
            posInArr = indices[i][posInArr];
        }
        while(posInArr < modes[dims - 1].size() && modes[dims - 1][posInArr] < coords[dims - 1]) {
            ++posInArr;
        }
        if(posInArr == modes[dims - 1].size() ||
                modes[dims - 1][posInArr] != coords[dims - 1]) {
            return 0;
        }
        return vals_[posInArr];
    }

private:
};
#endif //COOL_CSFTENSOR_H
