#pragma once

#include "gci.hf"

GciTravBufType * Gci_AllocTravBuf(
	size_t allocationSize);

BoolType Gci_DbgEstablishToFile(
	const char *fileName);

BoolType Gci_Err(
	GciErrSType *errorReport) ;

OopType Gci_ExecuteStr(
	const char source[], 
	OopType symbolList);

void Gci_Free(
	void* ptr);

GciSessionIdType Gci_GetSessionId(void);

OopType Gci_I32ToOop(
	int arg);

OopType Gci_I64ToOop(
	int64 arg);

BoolType Gci_Login(
	const char gemstoneUsername[], 
	const char gemstonePassword[]);

void Gci_Logout(void);

OopType Gci_NewString(
	const char *cString);

int Gci_OopToI32(
	OopType arg);

int64 Gci_OopToI64(
	OopType arg);

OopType Gci_Perform(
	OopType receiver, 
	const char selector[],
	const OopType args[], 
	int numArgs ) ;

BoolType Gci_PerformTraverse(
	OopType receiver, 
	const char selector[],
  	const OopType args[], 
	int numArgs, 
	GciTravBufType *travBuff,
  	int level);

void Gci_ReleaseOops(
	const OopType theOops[], 
	int numOops);

void Gci_SetNet(
  const char StoneName[],
  const char HostUserId[],
  const char HostPassword[],
  const char GemService[]);

void Gci_SetSessionId(
GciSessionIdType sessionId);

void Gci_Shutdown(void);
