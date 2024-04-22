#pragma once
#include <vector>
#include "PhysicsObject.hpp"
class PhysicsEngine {

public:
    PhysicsEngine();

    void addPhysicsObject(PhysicsObject object);
    void update(int deltaTime);

private:
    std::vector<PhysicsObject> objects;
};