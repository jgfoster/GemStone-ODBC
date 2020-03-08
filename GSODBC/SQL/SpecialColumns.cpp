#include "stdafx.h"

SQLRETURN  SQL_API SQLSpecialColumns(
	SQLHSTMT		StatementHandle,
	SQLUSMALLINT	IdentifierType, 
	SQLCHAR			*CatalogName,
	SQLSMALLINT		NameLength1, 
	SQLCHAR			*SchemaName,
	SQLSMALLINT		NameLength2, 
	SQLCHAR			*TableName,
	SQLSMALLINT		NameLength3, 
	SQLUSMALLINT	Scope,
	SQLUSMALLINT	Nullable)
{
	GS_STMT		hStmt = (GS_STMT) StatementHandle;
	GS_DBC		hDBC = hStmt->hDBC;
	CHAR		catalogName	[BASIC_STRING_MAX + 1];
	CHAR		schemaName	[BASIC_STRING_MAX + 1];
	CHAR		tableName	[BASIC_STRING_MAX + 1];
	OopType		oopType, oops[6];
	SQLRETURN	sqlReturn;

	if (SQL_ROWVER != IdentifierType) {
		return Error(hStmt, 0, "state", "SQLSpecialColumns() only supports SQL_ROWVER");
	}
	WriteToLog("SQLSpecialColumns(,SQL_ROWVER,,,,)");
	if (!CopySqlString(catalogName, sizeof(catalogName), CatalogName, NameLength1)) {
		return Error(hStmt, 0, "state", "error copying catalog name");
	}
	if (!CopySqlString(schemaName, sizeof(schemaName), SchemaName, NameLength2)) {
		return Error(hStmt, 0, "state", "error copying schema name");
	}
	if (!CopySqlString(tableName, sizeof(tableName), TableName, NameLength3)) {
		return Error(hStmt, 0, "state", "error copying table name");
	}
	oops[0] = Gci_NewString(catalogName);
	oops[1] = Gci_NewString(schemaName);
	oops[2] = Gci_NewString(tableName);
	oops[3] = Gci_I32ToOop(IdentifierType);
	oops[4] = Gci_I32ToOop(Scope);
	oops[5] = Gci_I32ToOop(Nullable);
	oopType	= Gci_Perform(hStmt->odbcStatement, "sqlSpecialColumns:_:_:_:_:_:", oops, 6);
	Gci_Err(&(hDBC->gciError));
	Gci_ReleaseOops(oops, 6);
	sqlReturn = Gci_OopToI32(oopType);
	return sqlReturn;
}
