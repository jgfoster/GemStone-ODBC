#include "stdafx.h"

SQLRETURN  SQL_API SQLGetTypeInfo(
	SQLHSTMT		StatementHandle,
	SQLSMALLINT		DataType)
{
	GS_STMT			hStmt = (GS_STMT) StatementHandle;
	GS_DBC			hDBC = hStmt->hDBC;
	OopType			oops[1], oopType;
	SQLRETURN		sqlReturn;

	WriteToLog("SQLGetTypeInfo(0x%p, %hi)", StatementHandle, DataType);
	oops[0] = Gci_I32ToOop((int32) DataType);
	oopType	= Gci_Perform(hStmt->odbcStatement, "sqlGetTypeInfo:", oops, 1);
	Gci_Err(&(hDBC->gciError));
	if (!GCI_OOP_IS_SMALL_INT(oopType)) {
		return Error(hStmt, 0, "state", "#'sqlGetTypeInfo:' did not return a SmallInteger");
	}
	sqlReturn = (SQLRETURN) Gci_OopToI32(oopType);
	if (sqlReturn) {
		WriteToLog("\t%i", sqlReturn);
		return sqlReturn;
	} else {
		return Success(hStmt);
	}
}
