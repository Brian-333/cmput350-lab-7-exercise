#ifndef REGISTRY_H
#define REGISTRY_H

#include <cstddef>  // std::size_t
#include <vector>  // std::vector
#include <utility> // Required for std::forward
#include <cassert> // Required for assert
#include <iostream> // std::cout
template <typename T>
class Registry {
public:
    Registry() : mIsFree() {
    }
    std::size_t store(const T& item) {
        if (mFreeIndices.empty()) {
            mData.push_back(item);
            mIsFree.push_back(false);
            return mData.size() - 1;
        } else {
            std::size_t index = mFreeIndices.back();
            mData[index] = item;
            mFreeIndices.pop_back();
            mIsFree[index] = false;
            return index;
        }
    }

    std::size_t store(T&& item) {
        if (mFreeIndices.empty()) {
            mData.push_back(std::move(item));
            mIsFree.push_back(false);
            return mData.size() - 1;
        } else {
            std::size_t index = mFreeIndices.back();
            mData[index] = std::move(item);
            mFreeIndices.pop_back();
            mIsFree[index] = false;
            return index;
        }
    }

    bool valid(std::size_t index) const {
        return index < mData.size() && !mIsFree[index];
    }

    void remove(std::size_t index) {
        assert(valid(index));
        mFreeIndices.push_back(index);
        mIsFree[index] = true;
        mData[index] = T{};
    }

    T& operator[](std::size_t index) {
        assert(valid(index));
        return mData[index];
    }

    const T& operator[](std::size_t index) const {
        assert(valid(index));
        return mData[index];
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
