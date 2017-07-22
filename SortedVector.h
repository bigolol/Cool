//
// Created by holger on 22.07.17.
//

#ifndef COOL_SORTEDVECTOR_H
#define COOL_SORTEDVECTOR_H

#include <vector>
#include <algorithm>
#include <ostream>

template <typename T>
class SortedVector {
public:
    SortedVector(){}

    SortedVector(const std::initializer_list<T>& es) {
        for(T t : es) {
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

    void addElement(T e) {
        vec_.push_back(e);
        std::sort(vec_.begin(), vec_.end());
    }

    void addElements(const std::vector<T>& es) {
        for(T t : es) {
            vec_.push_back(t);
        }
        std::sort(vec_.begin(), vec_.end());
    }

    auto find(const T& e) {
        return std::lower_bound(vec_.begin(), vec_.end(), e);
    }

    size_t getIndexFor(const T& e) const {
        return std::lower_bound(vec_.begin(), vec_.end(), e) - vec_.begin();
    }


    T& operator[](size_t i) {
        return vec_[i];
    }

    size_t size() const {
        return vec_.size();
    }

    bool contains(const T& e) const {
        auto iter = std::lower_bound(vec_.begin(), vec_.end(), e);
        return  iter != vec_.end() && !(e < *iter);
    }

    friend std::ostream &operator<<(std::ostream &os, const SortedVector &vector) {
        for(const T& t : vector.vec_) {
            os << t << '\n';
        }
        return os;
    }

private:
std::vector<T> vec_;
};

#endif //COOL_SORTEDVECTOR_H
