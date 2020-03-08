#include "stdafx.h"

typedef GciTravBufType*		(__cdecl *GciAllocTravBuf_t)(size_t);
typedef BoolType			(__cdecl *GciDbgEstablishToFile_t)(const char *);
typedef BoolType			(__cdecl *GciErr_t)(GciErrSType *);
typedef OopType				(__cdecl *GciExecuteStr_t)(const char *, OopType);
typedef void				(__cdecl *GciFree_t)(void*);
typedef GciSessionIdType	(__cdecl *GciGetSessionId_t)(void);
typedef OopType				(__cdecl *GciI32ToOop_t)(int);
typedef OopType				(__cdecl *GciI64ToOop_t)(int64);
typedef BoolType			(__cdecl *GciInit_t)(void);
typedef BoolType			(__cdecl *GciLogin_t)(const char *, const char *);
typedef void				(__cdecl *GciLogout_t)(void);
typedef OopType				(__cdecl *GciNewString_t)(const char *cString);
typedef int					(__cdecl *GciOopToI32_t)(OopType arg);
typedef int64				(__cdecl *GciOopToI64_t)(OopType arg);
typedef OopType				(__cdecl *GciPerform_t)(OopType, const char [], const OopType [], int);
typedef BoolType			(__cdecl *GciPerformTraverse_t)(OopType, const char [], const OopType [], int, GciTravBufType *, int);
typedef void				(__cdecl *GciReleaseOops_t)(const OopType [], int);
typedef void				(__cdecl *GciSetNet_t)(const char *, const char *, const char *, const char *);
typedef void				(__cdecl *GciSetSessionId_t)(GciSessionIdType sessionId);
typedef void				(__cdecl *GciShutdown_t)(void);

GciAllocTravBuf_t		pGciAllocTravBuf;
GciDbgEstablishToFile_t	pGciDbgEstablishToFile;
GciErr_t				pGciErr;
GciExecuteStr_t			pGciExecuteStr;
GciFree_t				pGciFree;
GciGetSessionId_t		pGciGetSessionId;
GciI32ToOop_t			pGciI32ToOop;
GciI64ToOop_t			pGciI64ToOop;
GciInit_t				pGciInit;
GciLogin_t				pGciLogin;
GciLogout_t				pGciLogout;
GciNewString_t			pGciNewString;
GciOopToI32_t			pGciOopToI32;
GciOopToI64_t			pGciOopToI64;
GciPerform_t			pGciPerform;
GciPerformTraverse_t	pGciPerformTraverse;
GciReleaseOops_t		pGciReleaseOops;
GciSetNet_t				pGciSetNet;
GciSetSessionId_t		pGciSetSessionId;
GciShutdown_t			pGciShutdown;

HINSTANCE	hGciLibrary = NULL;
CHAR		loadedVersion[DSN_STRING_SIZE];

extern HMODULE hDLL;

#define GetGci(name)	\
	p ## name = (name ## _t) GetProcAddress(hGciLibrary, #name); \
	if (!p ## name) { FreeLibrary(hGciLibrary); \
		Error(hDBC, 0, CONNECTION_ERROR, "GetProcAddress(name) returned %lu", GetLastError()); }

void UnloadGciLibrary()
{
	if (hGciLibrary) {
		Gci_Shutdown();
		BOOL flag = FreeLibrary(hGciLibrary);
		hGciLibrary = NULL;
	}
}

SQLRETURN LoadGciLibrary(
	GS_DBC		hDBC,
	const char *gsVersion)
{
	char	filename[MAX_PATH];
	char	pathToDLL[MAX_PATH];
	int		count;
	int		lastSlash = 0;
	DWORD	lastError;
	
	if (hGciLibrary) {
		if (0 == strcmp(gsVersion, loadedVersion))
			return SQL_SUCCESS;
		else
			return Error(hDBC, 0, CONNECTION_ERROR, "Unable to load %s library because we have already loaded %s", 
				gsVersion, loadedVersion);
	}
	count = GetModuleFileName(hDLL, pathToDLL, sizeof(pathToDLL));
	if (lastError = GetLastError()) 
		return Error(hDBC, 0, CONNECTION_ERROR, "GetModuleFileName() returned %ul", lastError);
	for (int i = 0; i < count; ++i) {
		if (pathToDLL[i] == '\\') lastSlash = i;
	}
	pathToDLL[lastSlash] = '\0';
	count = sprintf_s(filename, sizeof(filename), "%s\\libgcirpc-%s-32.dll", pathToDLL, gsVersion);
	if (count <= 0)
		return Error(hDBC, 0, CONNECTION_ERROR, "Error %ul creating path to GCI library", GetLastError());
	if (!(hGciLibrary = LoadLibrary(filename))) 
		return Error(hDBC, 0, CONNECTION_ERROR, "LoadLibrary(\"%s\") returned %ul", filename);
	if (lastError = strcpy_s(loadedVersion, sizeof(loadedVersion), gsVersion))
		return Error(hDBC, 0, CONNECTION_ERROR, "strcpy_s() returned %ul", lastError);

	GetGci(GciAllocTravBuf);
	GetGci(GciDbgEstablishToFile);
	GetGci(GciErr);
	GetGci(GciExecuteStr);
	GetGci(GciFree);
	GetGci(GciGetSessionId);
	GetGci(GciI32ToOop);
	GetGci(GciI64ToOop);
	GetGci(GciInit);
	GetGci(GciLogin);
	GetGci(GciLogout);
	GetGci(GciNewString);
	GetGci(GciOopToI32);
	GetGci(GciOopToI64);
	GetGci(GciPerform);
	GetGci(GciPerformTraverse);
	GetGci(GciReleaseOops);
	GetGci(GciSetNet);
	GetGci(GciSetSessionId);
	GetGci(GciShutdown);

	if (!(pGciInit)()) { 
		FreeLibrary(hGciLibrary); 
		hGciLibrary = NULL;
		return Error(hDBC, 0, CONNECTION_ERROR, "GciInit() failed!");
	}
	return SQL_SUCCESS;
}
GciTravBufType * Gci_AllocTravBuf(size_t allocationSize)
{
	return (pGciAllocTravBuf)(allocationSize);
}

BoolType Gci_DbgEstablishToFile(const char *fileName)
{
	return (pGciDbgEstablishToFile)(NULL);
}

BoolType Gci_Err(GciErrSType *errorReport) 
{
	return (pGciErr)(errorReport);
}

OopType Gci_ExecuteStr(const char source[], OopType symbolList)
{
	return (pGciExecuteStr)(source, symbolList);
}

void Gci_Free(void* ptr)
{
	return (pGciFree)(ptr);
}

GciSessionIdType Gci_GetSessionId(void)
{
	return (pGciGetSessionId)();
}

OopType Gci_I32ToOop(int arg)
{
	return (pGciI32ToOop)(arg);
}

OopType Gci_I64ToOop(int64 arg)
{
	return (pGciI64ToOop)(arg);
}

BoolType Gci_Login(const char gemstoneUsername[], const char gemstonePassword[])
{
	return (pGciLogin)(gemstoneUsername, gemstonePassword);
}

void Gci_Logout(void)
{
	return (pGciLogout)();
}

OopType Gci_NewString(const char *cString)
{
	return (pGciNewString)(cString);
}

int Gci_OopToI32(OopType arg)
{
	return (pGciOopToI32)(arg);
}

int64 Gci_OopToI64(OopType arg)
{
	return (pGciOopToI64)(arg);
}

OopType Gci_Perform(OopType receiver, const char selector[], const OopType args[], int numArgs)
{
	return (pGciPerform)(receiver, selector, args, numArgs);
}

BoolType Gci_PerformTraverse(OopType receiver, const char selector[], const OopType args[], int numArgs, GciTravBufType *travBuff, int level)
{
	return (pGciPerformTraverse)(receiver, selector, args, numArgs, travBuff, level);
}

void Gci_ReleaseOops(const OopType theOops[], int numOops)
{
	return (pGciReleaseOops)(theOops, numOops);
}

void Gci_SetNet(const char StoneName[], const char HostUserId[], const char HostPassword[], const char GemService[])
{
	(pGciSetNet)(StoneName, HostUserId, HostPassword, GemService);
}

void Gci_SetSessionId(GciSessionIdType sessionId)
{
	return (pGciSetSessionId)(sessionId);
}

void Gci_Shutdown(void)
{
	return (pGciShutdown)();
}
