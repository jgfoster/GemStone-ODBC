#include "stdafx.h"

SQLRETURN  SQL_API SQLExecDirect(
	SQLHSTMT		StatementHandle,
	SQLCHAR			*StatementText, 
	SQLINTEGER		TextLength)
{
	WriteToLog("SQLExecDirect(0x%p, \"%s\", %i)", StatementHandle, StatementText, TextLength);

	GS_STMT				hStmt = (GS_STMT) StatementHandle;
	GS_DBC				hDBC = hStmt->hDBC;
	CHAR				text[1024];
	OopType				args[1];
	OopType				resultOop;

	if (!CopySqlString(text, sizeof(text), StatementText, TextLength))
		return Error(hStmt, 0, "state", "CopySqlString() failure!");
	args[0] = Gci_NewString(text);
	resultOop = Gci_Perform(hStmt->odbcStatement, "sqlExecDirect:", args, 1);
	Gci_ReleaseOops(args, 1);
	Gci_Err(&(hDBC->gciError));
	if (resultOop == OOP_NIL) {
		return Error(hDBC, 0, "state", "\tSQL_ERROR");
	}
	return Success(hStmt);
}

