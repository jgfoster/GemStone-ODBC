#include "stdafx.h"

SQLRETURN  SQL_API SQLFreeHandle(
	SQLSMALLINT		HandleType, 
	SQLHANDLE		Handle)
{
	switch (HandleType)
	{
		case SQL_HANDLE_ENV:
			WriteToLog("SQLFreeHandle(SQL_HANDLE_ENV, 0x%p)", Handle);
			break;
		case SQL_HANDLE_DBC:
			WriteToLog("SQLFreeHandle(SQL_HANDLE_DBC, 0x%p)", Handle);
			break;
		case SQL_HANDLE_DESC:
			WriteToLog("SQLFreeHandle(SQL_HANDLE_DESC, 0x%p)", Handle);
			break;
		case SQL_HANDLE_STMT: 
			{
				WriteToLog("SQLFreeHandle(SQL_HANDLE_STMT, 0x%p)", Handle);
				GS_STMT hStmt = (GS_STMT) Handle;
				if (hStmt->appParamDesc	!= NULL && hStmt->appParamDesc	!= hStmt->impParamDesc)	free(hStmt->appParamDesc	);
				if (hStmt->appRowDesc	!= NULL && hStmt->appRowDesc	!= hStmt->impRowDesc  )	free(hStmt->appRowDesc		);
				if (hStmt->impParamDesc	 )	free(hStmt->impParamDesc	);
				if (hStmt->impRowDesc	 )	free(hStmt->impRowDesc		);
				if (hStmt->RelationSchema)	free(hStmt->RelationSchema	);
				break;
			}
		default:
			WriteToLog("SQLFreeHandle(%hi, 0x%p) type not recognized", HandleType, Handle);
			break;
	}
	free(Handle);
	WriteToLog("\tSQL_SUCCESS");
	return SQL_INVALID_HANDLE;
}
