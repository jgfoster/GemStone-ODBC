#include "stdafx.h"

SQLRETURN  SQL_API SQLExecute(
	SQLHSTMT	StatementHandle)
{
	GS_STMT		hStmt = (GS_STMT) StatementHandle;
	GS_DBC		hDBC = hStmt->hDBC;
	OopType		oopType;
	SQLRETURN	sqlReturn;

	WriteToLog("SQLExecute()");
	oopType	= Gci_Perform(hStmt->odbcStatement, "sqlExecute", NULL, 0);
	Gci_Err(&(hDBC->gciError));
	if (!GCI_OOP_IS_SMALL_INT(oopType)) {
		return Error(hStmt, 0, "state", "#'sqlExecute' did not return a SmallInteger");
	}
	sqlReturn = (SQLRETURN) Gci_OopToI32(oopType);
	return sqlReturn;
}
