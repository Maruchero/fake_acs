#include <iostream>
#include <Windows.h>

#include "PhysicsEngine.h"

void the_actual_main() {
    PhysicsEngine engine;
    engine.run();
    std::cout << "Finished running! PhysicsEngine was @" << &engine << std::endl;
}

void my_main(int times) {
    // Pollute the stack with random stuff so that engine's address is guaranteed to be different every time
    if (times > 0) {
        if (times % 2000 == 679)
            std::cout << "Polluting the stack..." << std::endl;
        my_main(times - 1);
        if (times % 1234 == 123)
            std::cout << "Polluting the stack..." << std::endl;
    }

    if (times == 0) {
        the_actual_main();
    }
}

#include <random>

int main(int argc, const char* argv[])
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);

    // This call is only needed so that LoadLibraryA appears in the IAT (like in the case of the game).
    LoadLibraryW(L"kernel32.dll");
    my_main(dist(gen));
}