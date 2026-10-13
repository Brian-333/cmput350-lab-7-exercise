#include <iostream>

#include "entity_manager.h"

int main() {
    // test here...
    EntityManager<int, float, bool> entityManager;
    EntityID entity = entityManager.createEntity();
    entityManager.addComponent(entity, 1);
    entityManager.addComponent(entity, 2.0f);
    entityManager.addComponent(entity, true);
    std::cout << "entityManager.getComponent<int>(entity): " << entityManager.getComponent<int>(entity) << std::endl;
    std::cout << "entityManager.getComponent<float>(entity): " << entityManager.getComponent<float>(entity) << std::endl;
    std::cout << "entityManager.hasComponent<int>(entity): " << entityManager.hasComponent<int>(entity) << std::endl;
    std::cout << "entityManager.hasComponent<float>(entity): " << entityManager.hasComponent<float>(entity) << std::endl;
    std::cout << "entityManager.hasComponent<bool>(entity): " << entityManager.hasComponent<bool>(entity) << std::endl;


    EntityID entity2 = entityManager.createEntity();
    entityManager.addComponent(entity2, 15);
    std::cout << "entityManager.getComponent<int>(entity2): " << entityManager.getComponent<int>(entity2) << std::endl;
    std::cout << "entityManager.hasComponent<int>(entity2): " << entityManager.hasComponent<int>(entity2) << std::endl;
    std::cout << "entityManager.hasComponent<float>(entity2): " << entityManager.hasComponent<float>(entity2) << std::endl;


    EntityID entity3 = entityManager.createEntity();
    int value = 17;
    entityManager.addComponent(entity3, std::move(value));
    std::cout << "value: " << value << std::endl;
    std::cout << "entityManager.getComponent<int>(entity3): " << entityManager.getComponent<int>(entity3) << std::endl;
    std::cout << "entityManager.hasComponent<int>(entity3): " << entityManager.hasComponent<int>(entity3) << std::endl;
    std::cout << "entityManager.hasComponent<float>(entity3): " << entityManager.hasComponent<float>(entity3) << std::endl;
    return 0;
}
