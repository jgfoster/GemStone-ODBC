#include "stdafx.h"

SQLRETURN	SQL_API SQLAllocHandle(
	SQLSMALLINT		HandleType,
	SQLHANDLE		InputHandle, 
	SQLHANDLE		*OutputHandle)
{
	PCSTR			outOfMemory = "Out of memory";
	OopType			odbcResult;

	if (!OutputHandle) {
		WriteToLog("NULL == OutputHandle");
		return SQL_INVALID_HANDLE;
	}
	switch (HandleType)
	{
		case SQL_HANDLE_ENV:
			{
				GS_ENV		hEnv;

				WriteToLog("SQLAllocHandle(SQL_HANDLE_ENV, 0x%p, 0x%p)", InputHandle, OutputHandle);
				if (SQL_NULL_HANDLE != InputHandle) {
					WriteToLog("InputHandle should be NULL");
					return SQL_INVALID_HANDLE;
				}
				if (ForceError(FORCE_ERROR_ALLOC_HANDLE_ENV) || !(hEnv = (GS_ENV) calloc(sizeof(GS_ENVIRONMENT), 1))) {
					WriteToLog("calloc() failed for ENV handle");
					return SQL_ERROR;
				}
				*OutputHandle = hEnv;
				WriteToLog("\t0x%p", hEnv);
				return Success(hEnv);
			}
		case SQL_HANDLE_DBC:
			{
				GS_ENV		hEnv = (GS_ENV) InputHandle;
				GS_DBC		hDBC;

				WriteToLog("SQLAllocHandle(SQL_HANDLE_DBC, 0x%p, 0x%p)", InputHandle, OutputHandle);
				if (!hEnv) {
					WriteToLog("!hEnv");
					return SQL_INVALID_HANDLE;
				}
				;
				if (ForceError(FORCE_ERROR_ALLOC_HANDLE_DBC) || !(hDBC = (GS_DBC) calloc(sizeof(GS_CONNECTION),1))) {
					return Error(hEnv, 0, "HY001", outOfMemory);
				}
				hDBC->hEnv = hEnv;
				//	set default attributes (see SetConnectAttr() for details)
				hDBC->accessMode = SQL_MODE_READ_WRITE;
				hDBC->asyncEnabled = SQL_ASYNC_ENABLE_OFF;

				*OutputHandle = hDBC;
				WriteToLog("\t0x%p", hDBC);
				return Success(hEnv);
			}
		case SQL_HANDLE_STMT:
			{
				GS_DBC		hDBC = (GS_DBC) InputHandle;
				GS_STMT		hStmt;

				WriteToLog("SQLAllocHandle(SQL_HANDLE_STMT, 0x%p, 0x%p)", InputHandle, OutputHandle);
				if (!InputHandle) {
					WriteToLog("!InputHandle");
					return SQL_INVALID_HANDLE;
				}
				if (ForceError(FORCE_ERROR_UNKNOWN) || !(hStmt = (GS_STMT) calloc(sizeof(GS_STATEMENT),1))) {
					return Error(hDBC, 0, "HY001", outOfMemory);
				}
				hStmt->hDBC = hDBC;
				hStmt->impParamDesc = (GS_DESC) calloc(sizeof(GS_DESCRIPTOR),1);
				hStmt->impRowDesc	= (GS_DESC) calloc(sizeof(GS_DESCRIPTOR),1);
				hStmt->appParamDesc = hStmt->impParamDesc;
				hStmt->appRowDesc	= hStmt->impRowDesc;
				if (!(hStmt->appParamDesc) || !(hStmt->appRowDesc) || ForceError(FORCE_ERROR_UNKNOWN)) {
					SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
					return Error(hDBC, 0, "HY001", outOfMemory);
				}
				odbcResult = Gci_Perform(hDBC->odbcServer, "allocateStatement", NULL, 0);
				if (odbcResult == OOP_NIL) {
					Gci_Err(&(hDBC->gciError));
					SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
					return Error(hDBC, 0, "state", "error when calling allocateStatement on server");
				}
				hStmt->odbcStatement = odbcResult;
				*OutputHandle = hStmt;
				WriteToLog("\t0x%p", hStmt);
				return Success(hDBC);
			}
		case SQL_HANDLE_DESC:
			WriteToLog("SQLAllocHandle(SQL_HANDLE_DESC, 0x%p, 0x%p)", InputHandle, OutputHandle);
			break;

		default:
			WriteToLog("SQLAllocHandle(unknownHandleType, 0x%p, 0x%p)", InputHandle, OutputHandle);
			break;
	}
	return Error(InputHandle, 0, "HYC00", "Unknown");
}
