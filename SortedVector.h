//
// Created by holger on 22.07.17.
//

#ifndef COOL_SORTEDVECTOR_H
#define COOL_SORTEDVECTOR_H

#include <vector>
#include <algorithm>
#include <ostream>
#include "CooTensorElement.h"

template <size_t dims>
class SortedVector {
public:
    SortedVector(){}

    SortedVector(const std::initializer_list<CooTensorElement<dims>>& es) {
        for(CooTensorElement<dims> t : es) {
            vec_.push_back(t);
        }
        std::sort(vec_.begin(), vec_.end());
    }

    auto begin() {
        return vec_.begin();
    }

    auto end() {
        return vec_.end();
    }

    void addElement(CooTensorElement<dims> e) {
        vec_.push_back(e);
        std::sort(vec_.begin(), vec_.end());
    }

    void addElements(const std::vector<CooTensorElement<dims>>& es) {
        for(CooTensorElement<dims> t : es) {
            vec_.push_back(t);
        }
        std::sort(vec_.begin(), vec_.end());
    }

    auto find(const CooTensorElement<dims>& e) {
        return std::lower_bound(vec_.begin(), vec_.end(), e);
    }

    size_t getIndexFor(const CooTensorElement<dims>& e) const {
        return std::lower_bound(vec_.begin(), vec_.end(), e) - vec_.begin();
    }


    CooTensorElement<dims>& operator[](size_t i) {
        return vec_[i];
    }

    size_t size() const {
        return vec_.size();
    }

    void reserve(size_t amt) {
        vec_.reserve(amt);
    }

    bool contains(const CooTensorElement<dims>& e) const {
        auto iter = std::lower_bound(vec_.begin(), vec_.end(), e);
        return  iter != vec_.end() && !(e < *iter);
    }

    friend std::ostream &operator<<(std::ostream &os, const SortedVector &vector) {
        for(const CooTensorElement<dims>& t : vector.vec_) {
            os << t << '\n';
        }
        return os;
    }

private:
std::vector<CooTensorElement<dims>> vec_;
};

#endif //COOL_SORTEDVECTOR_H
