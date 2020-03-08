#include "stdafx.h"

SQLRETURN  SQL_API SQLFetchScroll(
	SQLHSTMT		StatementHandle,
	SQLSMALLINT		FetchOrientation, 
	SQLLEN			FetchOffset)
{
	GS_STMT			hStmt = (GS_STMT) StatementHandle;

	switch (FetchOrientation) {
		case SQL_FETCH_NEXT:
			WriteToLog("SQLFetchScroll(,SQL_FETCH_NEXT,)");
			return SQLFetch(StatementHandle);
		case SQL_FETCH_PRIOR:
			WriteToLog("SQLFetchScroll(,SQL_FETCH_PRIOR,)");
			break;
		case SQL_FETCH_FIRST:
			WriteToLog("SQLFetchScroll(,SQL_FETCH_FIRST,)");
			break;
		case SQL_FETCH_LAST:
			WriteToLog("SQLFetchScroll(,SQL_FETCH_LAST,)");
			break;
		case SQL_FETCH_ABSOLUTE:
			WriteToLog("SQLFetchScroll(,SQL_FETCH_ABSOLUTE,)");
			break;
		case SQL_FETCH_RELATIVE:
			WriteToLog("SQLFetchScroll(,SQL_FETCH_RELATIVE,)");
			break;
		case SQL_FETCH_BOOKMARK:
			WriteToLog("SQLFetchScroll(,SQL_FETCH_BOOKMARK,)");
			break;
		default:
			WriteToLog("SQLFetchScroll(,SQL_FETCH_??,)");
			break;
	}
	return Error(StatementHandle, 0, "errorState", "errorMessage");
}
