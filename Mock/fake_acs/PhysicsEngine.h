#pragma once

#include <memory>
#include "Car.h"

class PhysicsEngine {
    int m_porsche_checked_times = 0; // just an additional field to make finding m_ego_car "harder".
    std::unique_ptr<Car> m_ego_car;

public:
    PhysicsEngine();
    void run();

    Car* get_ego_car();
    bool is_ego_car_porsche();
};