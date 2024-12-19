#include "Car.h"

#include <iostream>

Car::Car(const char* model) : m_model(model) { }

const char* Car::get_model() const {
    // The objective is to detour run() to your own custom code
    // Your code should then call engine.m_ego_car.get_model() instead, and print the returned model.

    std::cout << "You managed to execute get_model!" << std::endl;

    return m_model; // your code should print the model to screen.
}
