#include "stdafx.h"

SQLRETURN  SQL_API SQLDisconnect(
	SQLHDBC		ConnectionHandle)
{
	GS_DBC		hDBC = (GS_DBC) ConnectionHandle;

	WriteToLog("SQLDisconnect(0x%p)", ConnectionHandle);
	Gci_SetSessionId(hDBC->sessionID);
	Gci_Logout();
	return Success(hDBC);
}
