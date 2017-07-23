//
// Created by holger on 22.07.17.
//

#include <cstddef>
#include <cstdint>
#include <ostream>

#ifndef COOL_COOTENSORELEMENT_H
#define COOL_COOTENSORELEMENT_H
template <size_t size, typename E>
class CooTensorElement {
public:
    CooTensorElement(uint32_t coords[size], E e) {
        e_ = e;
        for(size_t i = 0; i < size; ++i) {
            coords_[i] = coords[i];
        }
    }

    void replaceValue(E newValue) {
        e_ = newValue;
    }

    E getValue() const {
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
        for(size_t i = 0; i < size; ++i) {
            if(coords_[i] < rhs.coords_[i]) {
                return true;
            } else if(coords_[i] > rhs.coords_[i]) {
                return false;
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

    const uint32_t *getCoords_() const {
        return coords_;
    }

private:
    E e_;
    uint32_t coords_[size];
};

#endif //COOL_COOTENSORELEMENT_H
