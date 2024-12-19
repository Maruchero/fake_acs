#pragma once
class Car {
    const char* m_model;

public:
    Car(const char* model);
    const char* get_model() const;
};