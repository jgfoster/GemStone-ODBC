#include "stdafx.h"

SQLRETURN  SQL_API SQLPrepare(
	SQLHSTMT		StatementHandle,
	SQLCHAR			*StatementText, 
	SQLINTEGER		TextLength)
{
	GS_STMT				hStmt = (GS_STMT) StatementHandle;
	GS_DBC				hDBC = hStmt->hDBC;
	OopType				stringOop, args[1];
	CHAR				string[1024];
	OopType				oopType;
	SQLRETURN			sqlReturn;

	WriteToLog("SQLPrepare()");
	if (SQL_NTS == TextLength) {
		stringOop = Gci_NewString((PCSTR) StatementText);
		WriteToLog((PCSTR) StatementText);
	} else {
		if (TextLength < sizeof(string)) {
			memcpy(string, StatementText, TextLength);
			string[TextLength] = 0;
			WriteToLog((PCSTR) string);
			stringOop = Gci_NewString((PCSTR) string);
			memset(string, 0, TextLength);
		} else {
			return Error(StatementHandle, 0, "HY000", "String length is not SQL_NTS");
		}
	}

	args[0] = stringOop;
	oopType = Gci_Perform(hStmt->odbcStatement, "sqlPrepare:", args, 1);
	Gci_Err(&(hDBC->gciError));
	Gci_ReleaseOops(args, 1);
	sqlReturn = Gci_OopToI32(oopType);
	return sqlReturn;
}
