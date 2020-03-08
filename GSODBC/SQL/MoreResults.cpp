#include "stdafx.h"

SQLRETURN  SQL_API SQLMoreResults(
     SQLHSTMT     StatementHandle)
{
	WriteToLog("SQLMoreResults()");
	Success(StatementHandle);
	return SQL_NO_DATA;
}
