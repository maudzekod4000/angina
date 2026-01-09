#include "Debug.h"
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <SDL.h>

Debug DebugLog;

void Debug::showDebugInfo()
{
	TCHAR buffer[256];
	DWORD returnCode = GetCurrentDirectory(256, buffer);
	if (returnCode == 0) {
		std::cout << buffer << std::endl;
	}
}

void Debug::showErrorInfo(const std::string& action)
{
	printf("An SDL error occured while %s: %s\n", action.c_str(), SDL_GetError());
}
