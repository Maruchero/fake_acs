// Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <detours.h>

int main()
{
	std::cout << "Launching launcher" << std::endl;

	LPCWSTR targetExe = L"C:\\Users\\garon\\Files\\Unimore\\MMR_Driverless\\Fake_ACS\\Mock\\x64\\Debug\\fake_acs.exe";
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi = { 0 };
	LPCSTR dll = "C:\\Users\\garon\\Files\\Unimore\\MMR_Driverless\\Fake_ACS\\MyDll\\x64\\Debug\\MyDll.dll";

	// Inject DLL file into the process
	BOOL result = DetourCreateProcessWithDllEx(
		targetExe,
		NULL,
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS,
		NULL,
		NULL,
		&si,
		&pi,
		dll,
		NULL
	);

	// Wait for the process to exit.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Cleanup.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	if (result) {
		std::cout << L"Process created successfully" << std::endl;
	}
	else {
		std::cerr << L"Failed to create process. Error: " << GetLastError() << std::endl;
	}
}
