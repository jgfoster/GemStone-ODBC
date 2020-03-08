#include "stdafx.h"

SQLRETURN  SQL_API SQLNumResultCols(
	SQLHSTMT			StatementHandle,
	SQLSMALLINT			*ColumnCount)
{
	GS_STMT				hStmt = (GS_STMT) StatementHandle;
	GS_DBC				hDBC = hStmt->hDBC;
	SQLSMALLINT			numResultCols;
	OopType				resultOop;

	WriteToLog("SQLNumResultCols(0x%p, 0x%p)", StatementHandle, ColumnCount);

	resultOop = Gci_Perform(hStmt->odbcStatement, "sqlNumResultCols", NULL, 0);
	Gci_Err(&(hDBC->gciError));
	if (resultOop == OOP_NIL) {
		return Error(hDBC, 0, "state", "error in #'sqlNumResultCols'");
	}
	if (!GCI_OOP_IS_SMALL_INT(resultOop)) {
		OopType	array[1];

		array[0] = resultOop;
		Gci_ReleaseOops(array, 1);
		return Error(hDBC, 0, "HY000", "SQLNumResultCols() did not return a SmallInteger");
	}
	numResultCols = (SQLSMALLINT) Gci_OopToI32(resultOop);
	*ColumnCount = numResultCols;
	WriteToLog("\t%i", numResultCols);
	return Success(hStmt);
}
