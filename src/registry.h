#ifndef REGISTRY_H
#define REGISTRY_H

#include <cstddef>  // std::size_t
#include <vector>  // std::vector
#include <algorithm> // Required for std::find
#include <utility> // Required for std::forward

template <typename T>
class Registry {
public:
    Registry() : mIsFree() {
    }
    // std::size_t store(const T& item) {
    //     if (mFreeIndices.empty()) {
    //         mData.push_back(item);
    //         mIsFree.push_back(false);
    //         return mData.size() - 1;
    //     } else {
    //         std::size_t index = mFreeIndices.back();
    //         mData[index] = item;
    //         mFreeIndices.pop_back();
    //         mIsFree[index] = false;
    //         return index;
    //     }
    // }

    std::size_t store(T&& item) {
        if (mFreeIndices.empty()) {
            mData.push_back(std::forward<T>(item));
            mIsFree.push_back(false);
            return mData.size() - 1;
        } else {
            std::size_t index = mFreeIndices.back();
            mData[index] = std::forward<T>(item);
            mFreeIndices.pop_back();
            mIsFree[index] = false;
            return index;
        }
    }

    void remove(std::size_t index) {
        if (!valid(index)) {
            throw std::out_of_range("Index is not valid");
        }
        mFreeIndices.push_back(index);
        mIsFree[index] = true;
    }

    T& operator[](std::size_t index) {
        if (!valid(index)) {
            throw std::out_of_range("Index is not valid");
        }
        return mData[index];
    }

    const T& operator[](std::size_t index) const {
        if (!valid(index)) {
            throw std::out_of_range("Index is not valid");
        }
        return mData[index];
    }

    bool valid(std::size_t index) const {
        return index < mData.size() && !mIsFree[index];
    }

    std::size_t size() const {
        return mData.size() - mFreeIndices.size();
    }


private:
    std::vector<T> mData;
    std::vector<bool> mIsFree;
    std::vector<std::size_t> mFreeIndices;

};

#endif  // REGISTRY_H
