#include "stdafx.h"

SQLRETURN  SQL_API SQLRowCount(
	SQLHSTMT		StatementHandle, 
	SQLLEN			*RowCount)
{
	GS_STMT				hStmt	= (GS_STMT) StatementHandle;
	GS_DBC				hDBC	= hStmt->hDBC;
	P_RELATION_SCHEMA	schema	= hStmt->RelationSchema;
	OopType				resultOop;

	WriteToLog("SQLRowCount(0x%p, 0x%p)", StatementHandle, RowCount);
	resultOop = Gci_Perform(hStmt->odbcStatement, "sqlRowCount", NULL, 0);
	Gci_Err(&(hDBC->gciError));
	if (resultOop == OOP_NIL) {
		return Error(hDBC, 0, "state", "error in #'sqlRowCount'");
	}
	if (!GCI_OOP_IS_SMALL_INT(resultOop)) {
		OopType	array[1];
		array[0] = resultOop;
		Gci_ReleaseOops(array, 1);
		return Error(hDBC, 0, "HY000", "sqlRowCount() did not return a SmallInteger");
	}
	*RowCount = (SQLSMALLINT) Gci_OopToI32(resultOop);
	WriteToLog("\t%i", *RowCount);
	return Success(StatementHandle);
}
