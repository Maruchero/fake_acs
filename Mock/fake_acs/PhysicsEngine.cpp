#include <iostream>

#include "PhysicsEngine.h"

Car* PhysicsEngine::get_ego_car() {
    return m_ego_car.get();
}

void PhysicsEngine::run() {
    std::cout << "The physics engine is running! (if you haven't printed the model yet, you've failed)" << std::endl;
}

bool PhysicsEngine::is_ego_car_porsche() {
    // Other functions like this are useful for:
    // 1) as a quick check that you got the PhysicsEngine address right (just execute this - does it blow up? - do you see the expected no. of times being printed?)
    // 2) finding the offset of the m_ego_car by inspection

    ++m_porsche_checked_times; // just writing somewhere to make it more likely that it blows up if you got the PhysicsEngine address wrong.
    std::cout << "Called is_ego_car_porsche " << m_porsche_checked_times << " times." << std::endl;

    constexpr const char* pattern = "Porsche";
    return strncmp(m_ego_car->get_model(), pattern, sizeof(pattern) - 1) == 0;
}

constexpr const char* THE_SECRET = "Mazda Mx5";
PhysicsEngine::PhysicsEngine() : m_ego_car(std::make_unique<Car>(THE_SECRET)) {}