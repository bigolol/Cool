//
// Created by holger on 22.07.17.
//


#ifndef COOL_COOTENSORELEMENT_H
#define COOL_COOTENSORELEMENT_H

#include "typedefs.h"

template <size_t size>
class CooTensorElement {
public:

    CooTensorElement() = delete ;
    CooTensorElement(CooTensorElement&& other) {
        e_ = other.e_;
        for(size_t i = 0; i < size; ++i) {
            coords_[i] = other.coords_[i];
        }
    }

    CooTensorElement(const CooTensorElement& other) {
        e_ = other.e_;
        for(size_t i = 0; i < size; ++i) {
            coords_[i] = other.coords_[i];
        }
    }

    CooTensorElement(uint32_t coords[size], numericVal e) {
        e_ = e;
        for(size_t i = 0; i < size; ++i) {
            coords_[i] = coords[i];
        }
    }

    CooTensorElement<size>& operator=(const CooTensorElement &rhs) {
        e_ = rhs.e_;
        for(size_t i = 0; i < size; ++i) {
            coords_[i] = rhs.coords_[i];
        }
        return *this;
    }

    void replaceValue(numericVal newValue) {
        e_ = newValue;
    }

    numericVal getValue() const {
        return e_;
    }

    bool operator==(const CooTensorElement &rhs) const {
        for(size_t i = 0; i < size; ++i) {
            if(coords_[i] != rhs.coords_[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const CooTensorElement &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const CooTensorElement &rhs) const {
        auto i1 = coords_[0];
        auto i2 = coords_[1];
        auto i3 = coords_[2];
        auto i4 = coords_[3];
        auto i5 = coords_[4];
        auto i6 = coords_[5];
        for(size_t i = 0; i < size; ++i) {
            if(coords_[i] < rhs.coords_[i]) {
                return true;
            }
        }
        return false;
    }

    bool operator>(const CooTensorElement &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const CooTensorElement &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const CooTensorElement &rhs) const {
        return !(*this < rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const CooTensorElement &element) {
        for(size_t i = 0; i < size; ++i) {
            os << element.coords_[i] << ' ';
        }
        os << element.e_;
    }

    const uint32_t *getCoords() const {
        return coords_;
    }

private:
    numericVal e_;
    uint32_t coords_[size];
};

#endif //COOL_COOTENSORELEMENT_H
