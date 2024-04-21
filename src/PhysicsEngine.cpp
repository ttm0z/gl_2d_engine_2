#include "PhysicsEngine.hpp"
#include <iostream>

PhysicsEngine::PhysicsEngine(){
    std::cout << "Physics Engine Initialization" << std::endl;
    // init object list
    objects = {};
}

void PhysicsEngine::addPhysicsObject(PhysicsObject* object){
    objects.push_back(object);
}

void PhysicsEngine::update(int deltaTime){
    // for object in objects
    // object.update();
}