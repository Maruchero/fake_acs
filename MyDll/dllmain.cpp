// dllmain.cpp : Definisce il punto di ingresso per l'applicazione DLL.
#include "pch.h"
#include "MyDll.h"
#include <iostream>
#include <Windows.h>
#include "detours.h"

const char* moduleName = "C:\\Users\\garon\\Files\\Unimore\\MMR_Driverless\\Fake_ACS\\Mock\\x64\\Debug\\fake_acs.exe";

typedef void (*original_function_t)(void*);
typedef void* (*get_car_t)(void*);
typedef char* (*get_car_model_t)(void*);

original_function_t original_physics_engine_run = nullptr;

void __stdcall hooked_physics_engine_run(void* this_ptr) {
	std::cout << ">>> Engine address: " << this_ptr << std::endl;
	void* engine_address = this_ptr;

	void* physics_engine_get_ego_car_f = DetourFindFunction(moduleName, "PhysicsEngine::get_ego_car");

	if (physics_engine_get_ego_car_f) {
		// Get the pointer to the Car
		void* car = ((get_car_t) physics_engine_get_ego_car_f)(engine_address);
		std::cout << ">>> Ego car: " << car << std::endl;

		// Get the model of the car
		void* car_get_model_f = DetourFindFunction(moduleName, "Car::get_model");
		if (car_get_model_f) {
			char* model = ((get_car_model_t)car_get_model_f)(car);
			std::cout << ">>> Car model: " << model << std::endl;
		}
	}

	// Call the original function.
	if (original_physics_engine_run) {
		original_physics_engine_run(engine_address);
	}
}

void find_physics_engine() {
	// Find the address of the PhysicsEngine::run function
	const char* functionName = "PhysicsEngine::run";
	void* targetFunction = DetourFindFunction(moduleName, functionName);

	// Hook the function using Detours.
	if (targetFunction) {
		original_physics_engine_run = (original_function_t)targetFunction;

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)original_physics_engine_run, hooked_physics_engine_run);
		DetourTransactionCommit();

		std::cout << ">>> Successfully hooked " << functionName << std::endl;
	}
	else {
		std::cerr << ">>> Failed to find function " << functionName << " in module " << moduleName << std::endl;
	}
}

void dll_attached(HMODULE hModule) {
	std::cout << "=== Attached DLL ===" << std::endl;
	find_physics_engine();
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		dll_attached(hModule);
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

