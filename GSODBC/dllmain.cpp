// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

HMODULE hDLL = NULL;

VOID InitSupportedFunctions();
VOID UnloadGciLibrary();

BOOL APIENTRY DllMain( 
	HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hDLL = hModule;
		FindLogFile();
		InitSupportedFunctions();
		break;
	case DLL_PROCESS_DETACH:
//		UnloadGciLibrary();		//	Unable to reload (Kermit #45424)
		hDLL = NULL;
		break;
	default:
		break;
	}
	return TRUE;
}

