#include "stdafx.h"
/*	
	SQLTables returns the list of table, catalog, or schema names, and table types, stored in a specific data source. 
	The driver returns the information as a result set.
*/
SQLRETURN  SQL_API SQLTables(
	SQLHSTMT		 StatementHandle,
	SQLCHAR			*CatalogName, 
	SQLSMALLINT		 NameLength1,
	SQLCHAR			*SchemaName, 
	SQLSMALLINT		 NameLength2,
	SQLCHAR			*TableName, 
	SQLSMALLINT		 NameLength3,
	SQLCHAR			*TableType, 
	SQLSMALLINT		 NameLength4)
{
	WriteToLog("SQLTables(0x%p, \"%s\", %i, \"%s\", %i, \"%s\", %i, \"%s\", %i)", StatementHandle,
		CatalogName, NameLength1, SchemaName, NameLength2, TableName, NameLength3, TableType, NameLength4);
	GS_STMT				hStmt = (GS_STMT) StatementHandle;
	CHAR				catalogName	[BASIC_STRING_MAX + 1];
	CHAR				schemaName	[BASIC_STRING_MAX + 1];
	CHAR				tableName	[BASIC_STRING_MAX + 1];
	CHAR				tableType	[BASIC_STRING_MAX + 1];

	GS_DBC				hDBC = hStmt->hDBC;
	OopType				args[4];
	OopType				resultOop;


	if (!CopySqlString(catalogName, sizeof(catalogName), CatalogName, NameLength1)) {
		return Error(hStmt, 0, "state", "error copying catalog name");
	}
	if (!CopySqlString(schemaName, sizeof(schemaName), SchemaName, NameLength2)) {
		return Error(hStmt, 0, "state", "error copying schema name");
	}
	if (!CopySqlString(tableName, sizeof(tableName), TableName, NameLength3)) {
		return Error(hStmt, 0, "state", "error copying table name");
	}
	if (!CopySqlString(tableType, sizeof(tableType), TableType, NameLength4)) {
		return Error(hStmt, 0, "state", "error copying table type");
	}

	args[0] = Gci_NewString(catalogName);
	args[1] = Gci_NewString(schemaName);
	args[2] = Gci_NewString(tableName);
	args[3] = Gci_NewString(tableType);
	resultOop = Gci_Perform(hStmt->odbcStatement, "sqlTables:_:_:_:", args, 4);
	Gci_ReleaseOops(args, 4);
	Gci_Err(&(hDBC->gciError));
	if (resultOop == OOP_NIL) {
		return Error(hDBC, 0, "state", "error in sqlTables:_:_:_:");
	}
	return Success(hStmt);
}
