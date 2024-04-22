#pragma once
#include <glm.hpp>

class PhysicsObject {
public:
    PhysicsObject(float x, float y, float vx, float vy, float m, float rest)
        : position(x, y), velocity(vx, vy), mass(m), restitution(rest){};
    
    void setPosition(float x, float y) {position = glm::vec2(x, y);}
    void setVelocity(float vx, float vy) {velocity = glm::vec2(vx, vy);}
    void setMass(float m) {mass = m;}
    void setRestitution(float rest) {restitution = rest;}

    glm::vec2 getPosition() const {return position;}
    glm::vec2 getVelocity() const {return velocity;}
    
    float getMass() const {return mass;}
    float getRestitution() const {return restitution;}

    void applyForce(glm::vec2 force){
        glm::vec2 acc = force * mass;
        velocity += acc;
    }

    void updatePosition(float deltaTime){
        position += velocity * deltaTime;
    }

private:
    glm::vec2 position;
    glm::vec2 velocity;
    float mass;
    float restitution; //elasticity

};