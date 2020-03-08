#include "stdafx.h"

SQLRETURN  SQL_API SQLSetStmtAttr(
	SQLHSTMT		StatementHandle,
	SQLINTEGER		Attribute, 
	SQLPOINTER		Value,
	SQLINTEGER		StringLength)
{
	GS_STMT			hStmt		= (GS_STMT) StatementHandle;
	union {
		SQLPOINTER	pointer;
		SQLUINTEGER	value;
	}	data;
	data.pointer = Value;
	
	switch (Attribute) {
		case SQL_ATTR_APP_PARAM_DESC:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_APP_PARAM_DESC, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_APP_ROW_DESC:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_APP_ROW_DESC, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_ASYNC_ENABLE:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_ASYNC_ENABLE, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_CONCURRENCY:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_CONCURRENCY, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_CURSOR_SCROLLABLE:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_CURSOR_SCROLLABLE, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_CURSOR_SENSITIVITY:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_CURSOR_SENSITIVITY, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_CURSOR_TYPE:
			switch (data.value) {
				case SQL_CURSOR_FORWARD_ONLY:	// The cursor only scrolls forward.
					WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_CURSOR_TYPE, SQL_CURSOR_FORWARD_ONLY, %i)", StatementHandle, StringLength);
					hStmt->cursorType = SQL_CURSOR_FORWARD_ONLY;
					return Success(hStmt);
				case SQL_CURSOR_STATIC:			//The data in the result set is static.
					WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_CURSOR_TYPE, SQL_CURSOR_STATIC, %i)", StatementHandle, StringLength);
					break;
				case SQL_CURSOR_KEYSET_DRIVEN:	// The driver saves and uses the keys for the number of rows specified in the SQL_ATTR_KEYSET_SIZE statement attribute.
					WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_CURSOR_TYPE, SQL_CURSOR_KEYSET_DRIVEN, %i)", StatementHandle, StringLength);
					break;
				case SQL_CURSOR_DYNAMIC: 
					WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_CURSOR_TYPE, SQL_CURSOR_DYNAMIC, %i)", StatementHandle, StringLength);
					break;
				default:
					WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_CURSOR_TYPE,%i, %i)", StatementHandle, data.value, StringLength);
					break;
			}
			break;
		case SQL_ATTR_ENABLE_AUTO_IPD:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_ENABLE_AUTO_IPD, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_FETCH_BOOKMARK_PTR:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_FETCH_BOOKMARK_PTR, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_IMP_PARAM_DESC:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_IMP_PARAM_DESC, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_IMP_ROW_DESC:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_IMP_ROW_DESC, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_KEYSET_SIZE:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_KEYSET_SIZE, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_MAX_LENGTH:
			switch ((int) Value) {
				case 0:
					WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_MAX_LENGTH,0,)", StatementHandle);
					return Success(hStmt);
				case 0x7fffffff:
					WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_MAX_LENGTH,0x7fffffff,)", StatementHandle);
					return Success(hStmt);
				default:
					WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_MAX_LENGTH,???,)", StatementHandle);
					break;
			}
			break;
		case SQL_ATTR_MAX_ROWS:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_MAX_ROWS, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_METADATA_ID:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_METADATA_ID, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_NOSCAN:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_NOSCAN, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_PARAM_BIND_OFFSET_PTR:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_PARAM_BIND_OFFSET_PTR, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_PARAM_BIND_TYPE:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_PARAM_BIND_TYPE, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_PARAM_OPERATION_PTR:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_PARAM_OPERATION_PTR, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_PARAM_STATUS_PTR:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_PARAM_STATUS_PTR, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_PARAMS_PROCESSED_PTR:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_PARAMS_PROCESSED_PTR, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_PARAMSET_SIZE:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_PARAMSET_SIZE, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_QUERY_TIMEOUT:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_QUERY_TIMEOUT, 0x%p, %i)", StatementHandle, Value, StringLength);
			return Success(hStmt);
		case SQL_ATTR_RETRIEVE_DATA:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_RETRIEVE_DATA, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_ROW_ARRAY_SIZE:
			if ((SQLPOINTER) 1 == Value) {
				WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_ROW_ARRAY_SIZE, 1,)", StatementHandle);
				return Success(hStmt);
			} else {
				WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_ROW_ARRAY_SIZE, ???,)", StatementHandle);
			}
			break;
		case SQL_ATTR_ROW_BIND_OFFSET_PTR:
			if (!Value) {
				WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_ROW_BIND_OFFSET_PTR,0,)", StatementHandle);
				return Success(hStmt);
			} else {
				WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_ROW_BIND_OFFSET_PTR,???,)", StatementHandle);
			}
			break;
		case SQL_ATTR_ROW_BIND_TYPE:
			if (!Value) {
				WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_ROW_BIND_TYPE, SQL_BIND_BY_COLUMN, %i, StatementHandle)", StatementHandle, StringLength);
				return Success(hStmt);
			} else {
				WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_ROW_BIND_TYPE, ???,)", StatementHandle);
			}
			break;
		case SQL_ATTR_ROW_NUMBER:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_ROW_NUMBER, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_ROW_OPERATION_PTR:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_ROW_OPERATION_PTR, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_ROW_STATUS_PTR:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_ROW_STATUS_PTR, 0x%p, %i)", StatementHandle, Value, StringLength);
			hStmt->pRowStatus = (SQLUSMALLINT *) Value;
			return Success(hStmt);
		case SQL_ATTR_ROWS_FETCHED_PTR:
			if (!Value) {
				WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_ROWS_FETCHED_PTR, 0,)", StatementHandle);
				return Success(hStmt);
			} else {
				WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_ROWS_FETCHED_PTR, %i,)", StatementHandle, Value);
			}
			break;
		case SQL_ATTR_SIMULATE_CURSOR:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_SIMULATE_CURSOR, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		case SQL_ATTR_USE_BOOKMARKS:
			WriteToLog("SQLSetStmtAttr(0x%p, SQL_ATTR_USE_BOOKMARKS, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
		default:
			WriteToLog("SQLSetStmtAttr(,???, 0x%p, %i)", StatementHandle, Value, StringLength);
			break;
	}
	return Error(hStmt, 0, "errorState", "\terrorMessage");
}
