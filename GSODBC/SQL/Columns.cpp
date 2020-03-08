#include "stdafx.h"

SQLRETURN  SQL_API SQLColumns(
	SQLHSTMT		StatementHandle,
	SQLCHAR		*	CatalogName, 
	SQLSMALLINT		NameLength1,
	SQLCHAR		*	SchemaName, 
	SQLSMALLINT		NameLength2,
	SQLCHAR		*	TableName, 
	SQLSMALLINT		NameLength3,
	SQLCHAR		*	ColumnName, 
	SQLSMALLINT		NameLength4)
{
	GS_STMT		hStmt = (GS_STMT) StatementHandle;
	GS_DBC		hDBC = hStmt->hDBC;
	CHAR		catalogName	[BASIC_STRING_MAX + 1];
	CHAR		schemaName	[BASIC_STRING_MAX + 1];
	CHAR		tableName	[BASIC_STRING_MAX + 1];
	CHAR		columnName	[BASIC_STRING_MAX + 1];
	OopType		oopType, args[4];
	SQLRETURN	sqlReturn;

	WriteToLog("SQLColumns()");

	if (!CopySqlString(catalogName, sizeof(catalogName), CatalogName, NameLength1)) {
		return Error(hStmt, 0, "state", "error copying catalog name");
	}
	if (!CopySqlString(schemaName, sizeof(schemaName), SchemaName, NameLength2)) {
		return Error(hStmt, 0, "state", "error copying schema name");
	}
	if (!CopySqlString(tableName, sizeof(tableName), TableName, NameLength3)) {
		return Error(hStmt, 0, "state", "error copying table name");
	}
	if (!CopySqlString(columnName, sizeof(columnName), ColumnName, NameLength4)) {
		return Error(hStmt, 0, "state", "error copying sql string");
	}

	args[0] = Gci_NewString(catalogName);
	args[1] = Gci_NewString(schemaName);
	args[2] = Gci_NewString(tableName);
	args[3] = Gci_NewString(columnName);
	oopType = Gci_Perform(hStmt->odbcStatement, "sqlColumns:_:_:_:", args, 4);
	Gci_ReleaseOops(args, 4);
	if (!GCI_OOP_IS_SMALL_INT(oopType)) {
		return Error(hStmt, 0, "state", "#'fetch' did not return a SmallInteger");
	}
	sqlReturn = (SQLRETURN) Gci_OopToI32(oopType);
	return sqlReturn;
}
