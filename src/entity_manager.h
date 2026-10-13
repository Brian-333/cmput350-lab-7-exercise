#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <cstddef>  // size_t
#include <limits> // std::numeric_limits
#include <tuple> // std::tuple
#include <utility> // std::forward
#include <cassert> // assert
#include <type_traits> // std::remove_reference_t
#include <array> // std::array
#include <vector> // std::vector

#include "pack.h"  // Pack from prep
#include "registry.h" // Registry for components

using EntityID = size_t;

template <typename... ComponentTypes>
class EntityManager {
public:
    EntityManager() : mComponentIndices(), mComponents() {
    }

    EntityID createEntity() {
        if (mFreeIndices.empty()) {
            mIsFree.push_back(false);
            mComponentIndices.push_back(std::array<size_t, numComponents>());
            for (size_t i = 0; i < numComponents; ++i) {
                mComponentIndices.back()[i] = mMaxSizeT;
            }
            return mIsFree.size() - 1;
        } else {
            EntityID index = mFreeIndices.back();
            mIsFree[index] = false;
            mFreeIndices.pop_back();
            for (size_t i = 0; i < numComponents; ++i) {
                mComponentIndices[index][i] = mMaxSizeT;
            }
            return index;
        }
    }

    bool validEntity(EntityID id) const {
        return id < mIsFree.size() && !mIsFree[id];
    }

    template <typename ComponentType>
    bool hasComponent(EntityID id) const {
        assert(validEntity(id));
        static_assert(Pack<ComponentTypes...>::template contains<ComponentType>);
        static constexpr auto COMPONENT_TYPE_INDEX = Pack<ComponentTypes...>::template index<ComponentType>;
        return mComponentIndices[id][COMPONENT_TYPE_INDEX] != mMaxSizeT;
    }

    template <typename ComponentType>
    ComponentType& getComponent(EntityID id) {
        assert(validEntity(id));
        assert(hasComponent<ComponentType>(id));
        static constexpr auto COMPONENT_TYPE_INDEX = Pack<ComponentTypes...>::template index<ComponentType>;
        return std::get<COMPONENT_TYPE_INDEX>(mComponents)[mComponentIndices[id][COMPONENT_TYPE_INDEX]];
    }

    template <typename ComponentType>
    void addComponent(EntityID id, ComponentType&& component) {
        using OriginalComponentType = std::remove_reference_t<ComponentType>;
        assert(validEntity(id));
        assert(!hasComponent<OriginalComponentType>(id));

        static constexpr auto COMPONENT_TYPE_INDEX = Pack<ComponentTypes...>::template index<OriginalComponentType>;
        mComponentIndices[id][COMPONENT_TYPE_INDEX] =
            std::get<COMPONENT_TYPE_INDEX>(mComponents).store(std::forward<ComponentType>(component));
    }

private:
    static constexpr size_t numComponents = sizeof...(ComponentTypes);
    static constexpr size_t mMaxSizeT = std::numeric_limits<size_t>::max();

    std::vector<bool> mIsFree;
    std::vector<EntityID> mFreeIndices;

    std::vector<std::array<size_t, numComponents>> mComponentIndices;
    std::tuple<Registry<ComponentTypes>...> mComponents;

};

#endif  // ENTITY_MANAGER_H
