#include "stdafx.h"

#define ReturnString(x) ReturnString_(hDBC, x, InfoValuePtr, BufferLength, StringLengthPtr)

SQLRETURN  SQL_API ReturnString_(
	GS_DBC			hDBC, 
	PCSTR			string,
	SQLPOINTER		InfoValuePtr,
	SQLSMALLINT		BufferLength, 
	SQLSMALLINT		*StringLengthPtr)
{
	SQLSMALLINT		size = (SQLSMALLINT) strlen(string);

	if (!InfoValuePtr) {
		return Error(hDBC, 0, "HYC00", "\tInfoValuePtr is NULL");
	}
	if (BufferLength < size) {
		return Error(hDBC, 0, "HYC00", "\tBufferLength (%hi) < size (%hi)", BufferLength, size);
	}
	strcpy_s((char *) InfoValuePtr, BufferLength, string);
	if (StringLengthPtr) {
		*StringLengthPtr = size;
	}
	WriteToLog("\t\"%s\" (%hi)", string, size);
	return Success(hDBC);
}

#define ReturnSmallInt(x) ReturnSmallInt_(hDBC, x, InfoValuePtr)

SQLRETURN  SQL_API ReturnSmallInt_(
	GS_DBC			hDBC,
	SQLSMALLINT		Data, 
	SQLPOINTER		InfoValuePtr)
{
	if (InfoValuePtr) {
		*((SQLSMALLINT *) InfoValuePtr) = Data;
	}
	WriteToLog("\t%hi", Data);
	return Success(hDBC);
}

#define ReturnUInteger(x) ReturnUInteger_(hDBC, x, InfoValuePtr)

SQLRETURN  SQL_API ReturnUInteger_(
	GS_DBC			hDBC,
	SQLUINTEGER		Data, 
	SQLPOINTER		InfoValuePtr
)
{
	if (InfoValuePtr) {
		*((SQLUINTEGER *) InfoValuePtr) = Data;
	}
	WriteToLog("\t%u", Data);
	return Success(hDBC);
}

SQLRETURN  SQL_API SQLGetInfo(
	SQLHDBC			ConnectionHandle,
	SQLUSMALLINT	InfoType, 
	SQLPOINTER		InfoValuePtr,
	SQLSMALLINT		BufferLength, 
	SQLSMALLINT	*	StringLengthPtr)
{
	GS_DBC			hDBC = (GS_DBC) ConnectionHandle;
	switch (InfoType)
	{
//	Driver Information
	case SQL_ACTIVE_ENVIRONMENTS:
		WriteToLog("SQLGetInfo(0x%p, SQL_ACTIVE_ENVIRONMENTS)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_ASYNC_MODE:
		WriteToLog("SQLGetInfo(0x%p, SQL_ASYNC_MODE) ==> SQL_AM_NONE", ConnectionHandle);
		return ReturnUInteger(SQL_AM_NONE);

	case SQL_BATCH_ROW_COUNT:
		WriteToLog("SQLGetInfo(0x%p, SQL_BATCH_ROW_COUNT)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_BATCH_SUPPORT:
		WriteToLog("SQLGetInfo(0x%p, SQL_BATCH_SUPPORT)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_DATA_SOURCE_NAME: {
		/*	A character string with the data source name that was used during connection. If the application called SQLConnect, this is the value of the szDSN argument. If the application called SQLDriverConnect or SQLBrowseConnect, this is the value of the DSN keyword in the connection string passed to the driver. If the connection string did not contain the DSN keyword (such as when it contains the DRIVER keyword), this is an empty string. */
		WriteToLog("SQLGetInfo(0x%p, SQL_DATA_SOURCE_NAME)", ConnectionHandle);
		return ReturnString(hDBC->dataSourceName);
	}
	case SQL_DRIVER_HDBC:
		WriteToLog("SQLGetInfo(0x%p, SQL_DRIVER_HDBC)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_DRIVER_HDESC:
		WriteToLog("SQLGetInfo(0x%p, SQL_DRIVER_HDESC)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_DRIVER_HENV:
		WriteToLog("SQLGetInfo(0x%p, SQL_DRIVER_HENV)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_DRIVER_HLIB:
		WriteToLog("SQLGetInfo(0x%p, SQL_DRIVER_HLIB)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_DRIVER_HSTMT:
		WriteToLog("SQLGetInfo(0x%p, SQL_DRIVER_HSTMT)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_DRIVER_NAME:
		WriteToLog("SQLGetInfo(0x%p, SQL_DRIVER_NAME)", ConnectionHandle);
		return ReturnString("GemStone/S");

	case SQL_DRIVER_ODBC_VER:
		WriteToLog("SQLGetInfo(0x%p, SQL_DRIVER_ODBC_VER, 0x%p, %lu, 0x%p)", ConnectionHandle);
		return ReturnString(GS_DRIVER_ODBC_VER);

	case SQL_DRIVER_VER:
		/* A character string with the version of the driver and optionally, a description of the driver. 
			At a minimum, the version is of the form ##.##.####, where the first two digits are the major version, 
			the next two digits are the minor version, and the last four digits are the release version. */
		WriteToLog("SQLGetInfo(0x%p, SQL_DRIVER_VER)", ConnectionHandle);
		return ReturnString(GS_DRIVER_VER);

	case SQL_DYNAMIC_CURSOR_ATTRIBUTES1:
		WriteToLog("SQLGetInfo(0x%p, SQL_DYNAMIC_CURSOR_ATTRIBUTES1)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_DYNAMIC_CURSOR_ATTRIBUTES2:
		WriteToLog("SQLGetInfo(0x%p, SQL_DYNAMIC_CURSOR_ATTRIBUTES2)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1:
		WriteToLog("SQLGetInfo(0x%p, SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES2:
		WriteToLog("SQLGetInfo(0x%p, SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES2)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_FILE_USAGE:
		WriteToLog("SQLGetInfo(0x%p, SQL_FILE_USAGE)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_GETDATA_EXTENSIONS: {
		/*	An SQLUINTEGER bitmask enumerating extensions to SQLGetData.
			The following bitmasks are used together with the flag to determine what common extensions the driver supports for SQLGetData:
			SQL_GD_ANY_COLUMN = SQLGetData can be called for any unbound column, including those before the last bound column. Note that the columns must be called in order of ascending column number unless SQL_GD_ANY_ORDER is also returned.
			SQL_GD_ANY_ORDER = SQLGetData can be called for unbound columns in any order. Note that SQLGetData can be called only for columns after the last bound column unless SQL_GD_ANY_COLUMN is also returned.
			SQL_GD_BLOCK = SQLGetData can be called for an unbound column in any row in a block (where the rowset size is greater than 1) of data after positioning to that row with SQLSetPos.
			SQL_GD_BOUND = SQLGetData can be called for bound columns in addition to unbound columns. A driver cannot return this value unless it also returns SQL_GD_ANY_COLUMN.
			SQL_GD_OUTPUT_PARAMS = SQLGetData can be called to return output parameter values. For more information, see Retrieving Output Parameters Using SQLGetData.
			SQLGetData is required to return data only from unbound columns that occur after the last bound column, are called in order of increasing column number, and are not in a row in a block of rows.
			If a driver supports bookmarks (either fixed-length or variable-length), it must support calling SQLGetData on column 0. This support is required regardless of what the driver returns for a call to SQLGetInfo with the SQL_GETDATA_EXTENSIONS InfoType. */ 
		WriteToLog("SQLGetInfo(0x%p, SQL_GETDATA_EXTENSIONS) ==> none", ConnectionHandle);
		return ReturnSmallInt(0);
	}
	case SQL_INFO_SCHEMA_VIEWS:
		WriteToLog("SQLGetInfo(0x%p, SQL_INFO_SCHEMA_VIEWS)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_KEYSET_CURSOR_ATTRIBUTES1:
		WriteToLog("SQLGetInfo(0x%p, SQL_KEYSET_CURSOR_ATTRIBUTES1)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_KEYSET_CURSOR_ATTRIBUTES2:
		WriteToLog("SQLGetInfo(0x%p, SQL_KEYSET_CURSOR_ATTRIBUTES2)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_MAX_ASYNC_CONCURRENT_STATEMENTS:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_ASYNC_CONCURRENT_STATEMENTS)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_MAX_CONCURRENT_ACTIVITIES:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_CONCURRENT_ACTIVITIES)", ConnectionHandle);
		return ReturnSmallInt(1);

	case SQL_MAX_DRIVER_CONNECTIONS:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_DRIVER_CONNECTIONS)", ConnectionHandle);
		return ReturnSmallInt(1);

	case SQL_ODBC_INTERFACE_CONFORMANCE:
		WriteToLog("SQLGetInfo(0x%p, SQL_ODBC_INTERFACE_CONFORMANCE)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_ODBC_VER:
		WriteToLog("SQLGetInfo(0x%p, SQL_ODBC_VER)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_PARAM_ARRAY_ROW_COUNTS:
		WriteToLog("SQLGetInfo(0x%p, SQL_PARAM_ARRAY_ROW_COUNTS)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_PARAM_ARRAY_SELECTS:
		WriteToLog("SQLGetInfo(0x%p, SQL_PARAM_ARRAY_SELECTS)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_ROW_UPDATES:
		WriteToLog("SQLGetInfo(0x%p, SQL_ROW_UPDATES)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_SEARCH_PATTERN_ESCAPE:
		WriteToLog("SQLGetInfo(0x%p, SQL_SEARCH_PATTERN_ESCAPE)", ConnectionHandle);
		// If this string is empty, the driver does not support a search-pattern escape character. 
		return ReturnString("");

	case SQL_SERVER_NAME:
		WriteToLog("SQLGetInfo(0x%p, SQL_SERVER_NAME)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_STATIC_CURSOR_ATTRIBUTES1:
			/*
				SQL_CA1_ABSOLUTE
				SQL_CA1_RELATIVE
				SQL_CA1_BOOKMARK
				SQL_CA1_LOCK_NO_CHANGE
				SQL_CA1_LOCK_EXCLUSIVE
				SQL_CA1_LOCK_UNLOCK
				SQL_CA1_POS_POSITION
				SQL_CA1_POS_UPDATE
				SQL_CA1_POS_DELETE
				SQL_CA1_POS_REFRESH
				SQL_CA1_POSITIONED_UPDATE
				SQL_CA1_POSITIONED_DELETE
				SQL_CA1_SELECT_FOR_UPDATE
				SQL_CA1_BULK_ADD
				SQL_CA1_BULK_UPDATE_BY_BOOKMARK
				SQL_CA1_BULK_DELETE_BY_BOOKMARK
				SQL_CA1_BULK_FETCH_BY_BOOKMARK
			*/
		WriteToLog("SQLGetInfo(0x%p, SQL_STATIC_CURSOR_ATTRIBUTES1)", ConnectionHandle);
		return ReturnSmallInt(SQL_CA1_NEXT);

	case SQL_STATIC_CURSOR_ATTRIBUTES2:
		WriteToLog("SQLGetInfo(,XXX)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

//	DBMS Product Information

	case SQL_DATABASE_NAME:
		WriteToLog("SQLGetInfo(0x%p, SQL_DATABASE_NAME)", ConnectionHandle);
		return ReturnString(hDBC->stoneName);

	case SQL_DBMS_NAME:
		WriteToLog("SQLGetInfo(0x%p, SQL_DBMS_NAME)", ConnectionHandle);
		return ReturnString("GemStone/S 64 Bit");

	case SQL_DBMS_VER:
		/* A character string that indicates the version of the DBMS product accessed by the driver. 
		The version is of the form ##.##.####, where the first two digits are the major version, 
		the next two digits are the minor version, and the last four digits are the release version. 
		The driver must render the DBMS product version in this form but can also append the DBMS 
		product-specific version. For example, "04.01.0000 Rdb 4.1". */
		WriteToLog("SQLGetInfo(0x%p, SQL_DBMS_VER)", ConnectionHandle);
		return ReturnString(hDBC->gsVersion);

//	Data Source Information

	case SQL_ACCESSIBLE_PROCEDURES:
		WriteToLog("SQLGetInfo(0x%p, SQL_ACCESSIBLE_PROCEDURES)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_ACCESSIBLE_TABLES:
		WriteToLog("SQLGetInfo(0x%p, SQL_ACCESSIBLE_TABLES)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_BOOKMARK_PERSISTENCE:
		WriteToLog("SQLGetInfo(0x%p, SQL_BOOKMARK_PERSISTENCE)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CATALOG_TERM:
		WriteToLog("SQLGetInfo(0x%p, SQL_CATALOG_TERM)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_COLLATION_SEQ:
		WriteToLog("SQLGetInfo(0x%p, SQL_COLLATION_SEQ)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONCAT_NULL_BEHAVIOR:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONCAT_NULL_BEHAVIOR)", ConnectionHandle);
		return ReturnSmallInt(SQL_CB_NULL);

	case SQL_CURSOR_COMMIT_BEHAVIOR: {
		/*	An SQLUSMALLINT value that indicates how a COMMIT operation affects cursors and prepared statements in the data source (the behavior of the data source when you commit a transaction).
			The value of this attribute will reflect the current state of the next setting: SQL_COPT_SS_PRESERVE_CURSORS.
			SQL_CB_DELETE = Close cursors and delete prepared statements. To use the cursor again, the application must reprepare and reexecute the statement.
			SQL_CB_CLOSE = Close cursors. For prepared statements, the application can call SQLExecute on the statement without calling SQLPrepare again. The default for the SQL ODBC driver is SQL_CB_CLOSE. This means that the SQL ODBC driver will close your cursor(s) when you commit a transaction.
			SQL_CB_PRESERVE = Preserve cursors in the same position as before the COMMIT operation. The application can continue to fetch data, or it can close the cursor and re-execute the statement without re-preparing it. */
		WriteToLog("SQLGetInfo(0x%p, SQL_CURSOR_COMMIT_BEHAVIOR) ==> SQL_CB_CLOSE", ConnectionHandle);
		return ReturnSmallInt(SQL_CB_CLOSE);
	}
	case SQL_CURSOR_ROLLBACK_BEHAVIOR: {
		/*	An SQLUSMALLINT value that indicates how a ROLLBACK operation affects cursors and prepared statements in the data source:
			SQL_CB_DELETE = Close cursors and delete prepared statements. To use the cursor again, the application must reprepare and reexecute the statement.
			SQL_CB_CLOSE = Close cursors. For prepared statements, the application can call SQLExecute on the statement without calling SQLPrepare again.
			SQL_CB_PRESERVE = Preserve cursors in the same position as before the ROLLBACK operation. The application can continue to fetch data, or it can close the cursor and reexecute the statement without repreparing it. */
		WriteToLog("SQLGetInfo(0x%p, SQL_CURSOR_ROLLBACK_BEHAVIOR) ==> SQL_CB_CLOSE", ConnectionHandle);
		return ReturnSmallInt(SQL_CB_CLOSE);
	}
	case SQL_CURSOR_SENSITIVITY:
		WriteToLog("SQLGetInfo(0x%p, SQL_CURSOR_SENSITIVITY)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_DATA_SOURCE_READ_ONLY:
		WriteToLog("SQLGetInfo(0x%p, SQL_DATA_SOURCE_READ_ONLY)", ConnectionHandle);
		return ReturnString("Y");

	case SQL_DEFAULT_TXN_ISOLATION:
		WriteToLog("SQLGetInfo(0x%p, SQL_DEFAULT_TXN_ISOLATION)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_DESCRIBE_PARAMETER:
		WriteToLog("SQLGetInfo(0x%p, SQL_DESCRIBE_PARAMETER)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_MULT_RESULT_SETS:
		WriteToLog("SQLGetInfo(0x%p, SQL_MULT_RESULT_SETS)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_MULTIPLE_ACTIVE_TXN:
		WriteToLog("SQLGetInfo(0x%p, SQL_MULTIPLE_ACTIVE_TXN)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_NEED_LONG_DATA_LEN:
		WriteToLog("SQLGetInfo(0x%p, SQL_NEED_LONG_DATA_LEN)", ConnectionHandle);
		return ReturnString("Y");

	case SQL_NULL_COLLATION:
		WriteToLog("SQLGetInfo(0x%p, SQL_NULL_COLLATION)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_PROCEDURE_TERM:
		WriteToLog("SQLGetInfo(0x%p, SQL_PROCEDURE_TERM)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_SCHEMA_TERM:
		WriteToLog("SQLGetInfo(0x%p, SQL_SCHEMA_TERM)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_SCROLL_OPTIONS:
		WriteToLog("SQLGetInfo(0x%p, SQL_SCROLL_OPTIONS)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_TABLE_TERM:
		WriteToLog("SQLGetInfo(0x%p, SQL_TABLE_TERM)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_TXN_CAPABLE:
		/*
			#define SQL_TC_NONE                         0
			#define SQL_TC_DML                          1
			#define SQL_TC_ALL                          2
			#define SQL_TC_DDL_COMMIT                   3
			#define SQL_TC_DDL_IGNORE                   4
		*/
		WriteToLog("SQLGetInfo(0x%p, SQL_TXN_CAPABLE) ==> SQL_TC_ALL", ConnectionHandle);
		return ReturnSmallInt(SQL_TC_ALL);

	case SQL_TXN_ISOLATION_OPTION:
		WriteToLog("SQLGetInfo(0x%p, SQL_TXN_ISOLATION_OPTION)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_USER_NAME:
		WriteToLog("SQLGetInfo(0x%p, SQL_USER_NAME)", ConnectionHandle);
		return ReturnString(hDBC->gsUserName);

//	Supported SQL
		
	case SQL_AGGREGATE_FUNCTIONS:
		/*	An SQLUINTEGER bitmask enumerating support for aggregation functions:
			SQL_AF_ALL SQL_AF_AVG SQL_AF_COUNT SQL_AF_DISTINCT SQL_AF_MAX SQL_AF_MIN SQL_AF_SUM
			An SQL-92 Entry level–conformant driver will always return all of these options as supported. */
		WriteToLog("SQLGetInfo(0x%p, SQL_AGGREGATE_FUNCTIONS)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_ALTER_DOMAIN:
		WriteToLog("SQLGetInfo(0x%p, SQL_ALTER_DOMAIN)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_ALTER_TABLE:	
		WriteToLog("SQLGetInfo(0x%p, SQL_ALTER_TABLE)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_CATALOG_LOCATION:
		WriteToLog("SQLGetInfo(0x%p, SQL_CATALOG_LOCATION) ==> SQL_CL_START", ConnectionHandle);
		return ReturnUInteger(SQL_CL_START);

	case SQL_CATALOG_NAME:
		WriteToLog("SQLGetInfo(0x%p, SQL_CATALOG_NAME)", ConnectionHandle);
		return ReturnString("Y");

	case SQL_CATALOG_NAME_SEPARATOR:
		WriteToLog("SQLGetInfo(0x%p, SQL_CATALOG_NAME_SEPARATOR)", ConnectionHandle);
		return ReturnString(".");

	case SQL_CATALOG_USAGE:
		WriteToLog("SQLGetInfo(0x%p, SQL_CATALOG_USAGE)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_COLUMN_ALIAS:
		WriteToLog("SQLGetInfo(0x%p, SQL_COLUMN_ALIAS)", ConnectionHandle);
		return ReturnString("N");

	case SQL_CORRELATION_NAME:
		WriteToLog("SQLGetInfo(0x%p, SQL_CORRELATION_NAME) ==> SQL_CN_NONE", ConnectionHandle);
		return ReturnSmallInt(SQL_CN_NONE);

	case SQL_CREATE_ASSERTION:
		WriteToLog("SQLGetInfo(0x%p, SQL_CREATE_ASSERTION)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_CREATE_CHARACTER_SET:
		WriteToLog("SQLGetInfo(0x%p, SQL_CREATE_CHARACTER_SET)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_CREATE_COLLATION:
		WriteToLog("SQLGetInfo(0x%p, SQL_CREATE_COLLATION)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_CREATE_DOMAIN:
		WriteToLog("SQLGetInfo(0x%p, SQL_CREATE_DOMAIN)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_CREATE_SCHEMA:
		WriteToLog("SQLGetInfo(0x%p, SQL_CREATE_SCHEMA)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_CREATE_TABLE:
		WriteToLog("SQLGetInfo(0x%p, SQL_CREATE_TABLE)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_CREATE_TRANSLATION:
		WriteToLog("SQLGetInfo(0x%p, SQL_CREATE_TRANSLATION)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_DDL_INDEX:
		WriteToLog("SQLGetInfo(0x%p, SQL_DDL_INDEX)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_DROP_ASSERTION:
		WriteToLog("SQLGetInfo(0x%p, SQL_DROP_ASSERTION)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_DROP_CHARACTER_SET:
		WriteToLog("SQLGetInfo(0x%p, SQL_DROP_CHARACTER_SET)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_DROP_COLLATION:
		WriteToLog("SQLGetInfo(0x%p, SQL_DROP_COLLATION)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_DROP_DOMAIN:
		WriteToLog("SQLGetInfo(0x%p, SQL_DROP_DOMAIN)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_DROP_SCHEMA:
		WriteToLog("SQLGetInfo(0x%p, SQL_DROP_SCHEMA)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_DROP_TABLE:
		WriteToLog("SQLGetInfo(0x%p, SQL_DROP_TABLE)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_DROP_TRANSLATION:
		WriteToLog("SQLGetInfo(0x%p, SQL_DROP_TRANSLATION)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_DROP_VIEW:
		WriteToLog("SQLGetInfo(0x%p, SQL_DROP_VIEW)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_EXPRESSIONS_IN_ORDERBY:
		WriteToLog("SQLGetInfo(0x%p, SQL_EXPRESSIONS_IN_ORDERBY)", ConnectionHandle);
		return ReturnString("N");

	case SQL_GROUP_BY:
		WriteToLog("SQLGetInfo(0x%p, SQL_GROUP_BY) ==> SQL_GB_NOT_SUPPORTED", ConnectionHandle);
		return ReturnSmallInt(SQL_GB_NOT_SUPPORTED);

	case SQL_IDENTIFIER_CASE:
		WriteToLog("SQLGetInfo(0x%p, SQL_IDENTIFIER_CASE) ==> SQL_IC_UPPER", ConnectionHandle);
		return ReturnSmallInt(SQL_IC_UPPER);

	case SQL_IDENTIFIER_QUOTE_CHAR:
		WriteToLog("SQLGetInfo(0x%p, SQL_IDENTIFIER_QUOTE_CHAR)", ConnectionHandle);
		return ReturnString("\"");

	case SQL_INDEX_KEYWORDS:
		WriteToLog("SQLGetInfo(0x%p, SQL_INDEX_KEYWORDS) ==> SQL_IK_NONE", ConnectionHandle);
		return ReturnUInteger(SQL_IK_NONE);

	case SQL_INSERT_STATEMENT:
		WriteToLog("SQLGetInfo(0x%p, SQL_INSERT_STATEMENT)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_INTEGRITY:
		WriteToLog("SQLGetInfo(0x%p, SQL_INTEGRITY)", ConnectionHandle);
		return ReturnString("N");

	case SQL_KEYWORDS:
		WriteToLog("SQLGetInfo(0x%p, SQL_KEYWORDS)", ConnectionHandle);
		return ReturnString("");

	case SQL_LIKE_ESCAPE_CLAUSE:
		WriteToLog("SQLGetInfo(0x%p, SQL_LIKE_ESCAPE_CLAUSE)", ConnectionHandle);
		return ReturnString("N");

	case SQL_NON_NULLABLE_COLUMNS:
		WriteToLog("SQLGetInfo(0x%p, SQL_NON_NULLABLE_COLUMNS)", ConnectionHandle);
		return ReturnSmallInt(SQL_NNC_NULL);

	case SQL_SQL_CONFORMANCE:
		WriteToLog("SQLGetInfo(0x%p, SQL_SQL_CONFORMANCE) ==> SQL_SC_SQL92_ENTRY", ConnectionHandle);
		return ReturnUInteger(SQL_SC_SQL92_ENTRY);

	case SQL_OJ_CAPABILITIES:
		WriteToLog("SQLGetInfo(0x%p, SQL_OJ_CAPABILITIES)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_ORDER_BY_COLUMNS_IN_SELECT:
		WriteToLog("SQLGetInfo(0x%p, SQL_ORDER_BY_COLUMNS_IN_SELECT)", ConnectionHandle);
		return ReturnString("N");

	case SQL_OUTER_JOINS:
		WriteToLog("SQLGetInfo(0x%p, SQL_OUTER_JOINS)", ConnectionHandle);
		return ReturnString("N");

	case SQL_PROCEDURES:
		WriteToLog("SQLGetInfo(0x%p, SQL_PROCEDURES)", ConnectionHandle);
		return ReturnString("N");

	case SQL_QUOTED_IDENTIFIER_CASE:
		WriteToLog("SQLGetInfo(0x%p, SQL_QUOTED_IDENTIFIER_CASE)", ConnectionHandle);
		return ReturnUInteger(SQL_IC_SENSITIVE);

	case SQL_SCHEMA_USAGE:
		WriteToLog("SQLGetInfo(0x%p, SQL_SCHEMA_USAGE)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_SPECIAL_CHARACTERS:
		WriteToLog("SQLGetInfo(0x%p, SQL_SPECIAL_CHARACTERS)", ConnectionHandle);
		return ReturnString("");

	case SQL_SUBQUERIES:
		WriteToLog("SQLGetInfo(0x%p, SQL_SUBQUERIES)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_UNION:
		WriteToLog("SQLGetInfo(0x%p, SQL_UNION)", ConnectionHandle);
		return ReturnUInteger(0);

//	SQL Limits

	case SQL_MAX_BINARY_LITERAL_LEN:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_BINARY_LITERAL_LEN)", ConnectionHandle);
		return ReturnSmallInt(MAX_BINARY_LITERAL_LEN);

	case SQL_MAX_CATALOG_NAME_LEN:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_CATALOG_NAME_LEN)", ConnectionHandle);
		return ReturnSmallInt(MAX_CATALOG_NAME_LEN);

	case SQL_MAX_CHAR_LITERAL_LEN:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_CHAR_LITERAL_LEN)", ConnectionHandle);
		return ReturnSmallInt(MAX_CHAR_LITERAL_LEN);

	case SQL_MAX_COLUMN_NAME_LEN:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_COLUMN_NAME_LEN)", ConnectionHandle);
		return ReturnSmallInt(MAX_COLUMN_NAME_LEN);

	case SQL_MAX_COLUMNS_IN_GROUP_BY:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_COLUMNS_IN_GROUP_BY)", ConnectionHandle);
		return ReturnSmallInt(MAX_COLUMNS_IN_GROUP_BY);

	case SQL_MAX_COLUMNS_IN_INDEX:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_COLUMNS_IN_INDEX)", ConnectionHandle);
		return ReturnSmallInt(MAX_COLUMNS_IN_INDEX);

	case SQL_MAX_COLUMNS_IN_ORDER_BY:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_COLUMNS_IN_ORDER_BY)", ConnectionHandle);
		return ReturnSmallInt(MAX_COLUMNS_IN_ORDER_BY);

	case SQL_MAX_COLUMNS_IN_SELECT:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_COLUMNS_IN_SELECT)", ConnectionHandle);
		return ReturnSmallInt(MAX_COLUMNS_IN_SELECT);

	case SQL_MAX_COLUMNS_IN_TABLE:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_COLUMNS_IN_TABLE)", ConnectionHandle);
		return ReturnSmallInt(MAX_COLUMNS_IN_TABLE);

	case SQL_MAX_CURSOR_NAME_LEN:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_CURSOR_NAME_LEN)", ConnectionHandle);
		return ReturnSmallInt(MAX_CURSOR_NAME_LEN);

	case SQL_MAX_USER_NAME_LEN:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_USER_NAME_LEN)", ConnectionHandle);
		return ReturnSmallInt(MAX_USER_NAME_LEN);

	case SQL_MAX_IDENTIFIER_LEN:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_IDENTIFIER_LEN)", ConnectionHandle);
		return ReturnSmallInt(MAX_IDENTIFIER_LEN);

	case SQL_MAX_INDEX_SIZE:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_INDEX_SIZE)", ConnectionHandle);
		return ReturnSmallInt(MAX_INDEX_SIZE);

	case SQL_MAX_PROCEDURE_NAME_LEN:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_PROCEDURE_NAME_LEN)", ConnectionHandle);
		return ReturnSmallInt(MAX_PROCEDURE_NAME_LEN);

	case SQL_MAX_ROW_SIZE:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_ROW_SIZE)", ConnectionHandle);
		return ReturnSmallInt(MAX_ROW_SIZE);

	case SQL_MAX_ROW_SIZE_INCLUDES_LONG:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_ROW_SIZE_INCLUDES_LONG)", ConnectionHandle);
		return ReturnSmallInt(MAX_ROW_SIZE_INCLUDES_LONG);

	case SQL_MAX_SCHEMA_NAME_LEN:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_SCHEMA_NAME_LEN)", ConnectionHandle);
		return ReturnSmallInt(MAX_SCHEMA_NAME_LEN);

	case SQL_MAX_STATEMENT_LEN:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_STATEMENT_LEN)", ConnectionHandle);
		return ReturnSmallInt(MAX_STATEMENT_LEN);

	case SQL_MAX_TABLE_NAME_LEN:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_TABLE_NAME_LEN)", ConnectionHandle);
		return ReturnSmallInt(MAX_TABLE_NAME_LEN);

	case SQL_MAX_TABLES_IN_SELECT:
		WriteToLog("SQLGetInfo(0x%p, SQL_MAX_TABLES_IN_SELECT)", ConnectionHandle);
		return ReturnSmallInt(MAX_TABLES_IN_SELECT);

//	Scalar Function Information

	case SQL_CONVERT_FUNCTIONS:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_FUNCTIONS)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_NUMERIC_FUNCTIONS:
		WriteToLog("SQLGetInfo(0x%p, SQL_NUMERIC_FUNCTIONS)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_STRING_FUNCTIONS:
		WriteToLog("SQLGetInfo(0x%p, SQL_STRING_FUNCTIONS)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_SYSTEM_FUNCTIONS:
		WriteToLog("SQLGetInfo(0x%p, SQL_SYSTEM_FUNCTIONS)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_TIMEDATE_ADD_INTERVALS:
		WriteToLog("SQLGetInfo(0x%p, SQL_TIMEDATE_ADD_INTERVALS)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_TIMEDATE_DIFF_INTERVALS:
		WriteToLog("SQLGetInfo(0x%p, SQL_TIMEDATE_DIFF_INTERVALS)", ConnectionHandle);
		return ReturnUInteger(0);

	case SQL_TIMEDATE_FUNCTIONS:
		WriteToLog("SQLGetInfo(0x%p, SQL_TIMEDATE_FUNCTIONS)", ConnectionHandle);
		return ReturnUInteger(0);

//	Conversion Information

	case SQL_CONVERT_BIGINT:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_BIGINT)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_BINARY:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_BINARY)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_BIT:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_BIT)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_CHAR:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_CHAR)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_DATE:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_DATE)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_DECIMAL:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_DECIMAL)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_DOUBLE:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_DOUBLE)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_FLOAT:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_FLOAT)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_INTEGER:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_INTEGER)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_INTERVAL_YEAR_MONTH:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_INTERVAL_YEAR_MONTH)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_INTERVAL_DAY_TIME:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_INTERVAL_DAY_TIME)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_LONGVARBINARY:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_LONGVARBINARY)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_LONGVARCHAR:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_LONGVARCHAR)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_NUMERIC:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_NUMERIC)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_REAL:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_REAL)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_SMALLINT:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_SMALLINT)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_TIME:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_TIME)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_TIMESTAMP:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_TIMESTAMP)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_TINYINT:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_TINYINT)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_VARBINARY:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_VARBINARY)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_CONVERT_VARCHAR:
		WriteToLog("SQLGetInfo(0x%p, SQL_CONVERT_VARCHAR)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

//	Information Types Deprecated in ODBC 3.x

	case SQL_FETCH_DIRECTION:
			/*
				SQL_FD_FETCH_FIRST
				SQL_FD_FETCH_LAST
				SQL_FD_FETCH_PRIOR
				SQL_FD_FETCH_ABSOLUTE
				SQL_FD_FETCH_RELATIVE
				SQL_FD_FETCH_BOOKMARK
			*/
		WriteToLog("SQLGetInfo(0x%p, SQL_FETCH_DIRECTION)", ConnectionHandle);
		return ReturnSmallInt(SQL_FD_FETCH_NEXT);

	case SQL_LOCK_TYPES:
		WriteToLog("SQLGetInfo(0x%p, SQL_LOCK_TYPES)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_ODBC_API_CONFORMANCE:
		WriteToLog("SQLGetInfo(0x%p, SQL_ODBC_API_CONFORMANCE)", ConnectionHandle);
		return ReturnSmallInt(SQL_OAC_LEVEL2);

	case SQL_ODBC_SQL_CONFORMANCE:
		WriteToLog("SQLGetInfo(0x%p, SQL_ODBC_SQL_CONFORMANCE)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_POS_OPERATIONS:
		WriteToLog("SQLGetInfo(0x%p, SQL_POS_OPERATIONS)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_POSITIONED_STATEMENTS:
		WriteToLog("SQLGetInfo(0x%p, SQL_POSITIONED_STATEMENTS)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_SCROLL_CONCURRENCY:
		WriteToLog("SQLGetInfo(0x%p, SQL_SCROLL_CONCURRENCY)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_STATIC_SENSITIVITY:
		WriteToLog("SQLGetInfo(0x%p, SQL_STATIC_SENSITIVITY)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

//	Other

	case SQL_CREATE_VIEW:
		WriteToLog("SQLGetInfo(0x%p, SQL_CREATE_VIEW)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_DATETIME_LITERALS:
		WriteToLog("SQLGetInfo(0x%p, SQL_DATETIME_LITERALS)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_SQL92_FOREIGN_KEY_DELETE_RULE:
		WriteToLog("SQLGetInfo(0x%p, SQL_SQL92_FOREIGN_KEY_DELETE_RULE)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_SQL92_FOREIGN_KEY_UPDATE_RULE:
		WriteToLog("SQLGetInfo(0x%p, SQL_SQL92_FOREIGN_KEY_UPDATE_RULE)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_SQL92_GRANT:
		WriteToLog("SQLGetInfo(0x%p, SQL_SQL92_GRANT)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_SQL92_PREDICATES:
		WriteToLog("SQLGetInfo(0x%p, SQL_SQL92_PREDICATES)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_SQL92_RELATIONAL_JOIN_OPERATORS:
		WriteToLog("SQLGetInfo(0x%p, SQL_SQL92_RELATIONAL_JOIN_OPERATORS)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_SQL92_ROW_VALUE_CONSTRUCTOR:
		WriteToLog("SQLGetInfo(0x%p, SQL_SQL92_ROW_VALUE_CONSTRUCTOR)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_SQL92_STRING_FUNCTIONS:
		WriteToLog("SQLGetInfo(0x%p, SQL_SQL92_STRING_FUNCTIONS)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_SQL92_REVOKE:
		WriteToLog("SQLGetInfo(0x%p, SQL_SQL92_REVOKE)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_SQL92_VALUE_EXPRESSIONS:
		WriteToLog("SQLGetInfo(0x%p, SQL_SQL92_VALUE_EXPRESSIONS)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

	case SQL_STANDARD_CLI_CONFORMANCE:
		WriteToLog("SQLGetInfo(0x%p, SQL_STANDARD_CLI_CONFORMANCE)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");

/*
	case XXX:
		WriteToLog("SQLGetInfo(0x%p, XXX)", ConnectionHandle);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");
*/
	default:
		WriteToLog("SQLGetInfo(0x%p, %hi)", ConnectionHandle, InfoType);
		return Error(hDBC, 0, "HYC00", "\tUnknown Info request");
	}
}
