//
// Created by holger on 22.07.17.
//

#ifndef COOL_COOTENSOR_H
#define COOL_COOTENSOR_H

#include <ostream>
#include <cassert>
#include "SortedVector.h"
#include "CooTensorElement.h"
#include "typedefs.h"
#include "CsfTensor.h"

template <size_t dims>
class CooTensor {
public:
    void add(uint32_t coords[dims], numericVal val) {
        CooTensorElement<dims, numericVal> elem{coords, val};
        if(tensorElements_.contains(elem)) {
            tensorElements_.find(elem)->replaceValue(val);
        } else {
            tensorElements_.addElement(elem);
        }
    }

    bool contains(uint32_t coords[dims]) {
        CooTensorElement<dims, numericVal> elem{coords, 0};
        return tensorElements_.contains(elem);
    }

    size_t getAmtVals() const {
        return tensorElements_.size();
    }

    numericVal getValueAt(uint32_t coords[dims]) {
        CooTensorElement<dims, numericVal> elem{coords, 0};
        if(!tensorElements_.contains(elem)) return 0;
        else return tensorElements_.find(elem)->getValue();
    }

    friend std::ostream &operator<<(std::ostream &os, const CooTensor &tensor) {
        os << tensor.tensorElements_;
        return os;
    }

    CsfTensor<dims> createCsfTensor() {
        CsfTensor<dims> created;
        if(getAmtVals() == 0)
            return created;
        created.vals_.reserve(tensorElements_.size());

        uint32_t addedPerLevel[dims - 1];
        for(size_t i = 0; i < dims - 1; ++i) {
            addedPerLevel[i] = 1;
        }

        auto prevCooTensorElem = tensorElements_[0];
        for(size_t i = 0; i < dims - 1; ++i) {
            created.modes[i].push_back(prevCooTensorElem.getCoords_()[i]);
            created.indices[i].push_back(0);
        }
        created.modes[dims - 1].push_back(prevCooTensorElem.getCoords_()[dims - 1]);


        created.vals_.push_back(prevCooTensorElem.getValue());

        for(size_t i = 1; i < tensorElements_.size(); ++i) {
            auto newCooTensorElem = tensorElements_[i];
            //find lowest indices where the mode changes.
            size_t lowestModeChanged;
            for(lowestModeChanged = 0; lowestModeChanged < dims - 1; ++lowestModeChanged) {
                if(prevCooTensorElem.getCoords_()[lowestModeChanged] !=
                   newCooTensorElem.getCoords_()[lowestModeChanged]) {
                    break;
                }
            }

            ++addedPerLevel[lowestModeChanged - 1];

            //for this and all lower modes, add the new mode to the modes array
            //for this and all lower modes, add the new indices to the indices arrays
            //it is how many got added since the mode last changed (addedperlevel array) plus the last indices
            //afterwards, set entries for lower modes in addedperlevel array to 1 again
            for(size_t currentMode = lowestModeChanged; currentMode < dims - 1; ++currentMode) {
                created.modes[currentMode].push_back(newCooTensorElem.getCoords_()[currentMode]);
                auto indexToAdd = addedPerLevel[currentMode] +
                                  *(created.indices[currentMode].end() - 1);
                created.indices[currentMode].push_back(indexToAdd);
                addedPerLevel[currentMode] = 1;
            }

            //now simply add the new last mode, the indices is just its position in the vector
            created.modes[dims - 1].push_back(newCooTensorElem.getCoords_()[dims - 1]);

            created.vals_.push_back(newCooTensorElem.getValue());

            prevCooTensorElem = newCooTensorElem;
        }

        return created;
    }

private:
    SortedVector<CooTensorElement<dims, numericVal>> tensorElements_;
};



#endif //COOL_COOTENSOR_H
