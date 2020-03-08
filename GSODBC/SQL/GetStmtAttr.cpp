#include "stdafx.h"

SQLRETURN  SQL_API SQLGetStmtAttr_uint(
	GS_STMT			hStmt,
	SQLUINTEGER 	Data, 
	SQLPOINTER		Value,
	SQLINTEGER		BufferLength, 
	SQLINTEGER		*StringLength)
{
	if (BufferLength < (SQLINTEGER) sizeof(SQLUINTEGER)) {
		return Error(hStmt, 0, "HYC00", "SQLGetStmtAttr(,,,<too small>,)");
	}
	if (!Value) {
		return Error(hStmt, 0, "HYC00", "SQLGetStmtAttr(,,NULL,,)");
	}
	*(SQLUINTEGER *) Value = Data;
	if (StringLength) {
		*StringLength = (SQLINTEGER) sizeof(SQLUINTEGER);
	}
	return Success(hStmt);
}

SQLRETURN  SQL_API SQLGetStmtAttr(
	SQLHSTMT		StatementHandle,
	SQLINTEGER		Attribute, 
	SQLPOINTER		Value,
	SQLINTEGER		BufferLength, 
	SQLINTEGER		*StringLength)
{
	GS_STMT	hStmt = (GS_STMT) StatementHandle;
	GS_DESC	*pValue = (GS_DESC *) Value;
	switch (Attribute) 
	{
		case SQL_ATTR_APP_PARAM_DESC:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_APP_PARAM_DESC, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			*pValue = (GS_DESC) hStmt->appParamDesc;
			WriteToLog("\t0x%p", *pValue);
			return Success(hStmt);
		case SQL_ATTR_APP_ROW_DESC:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_APP_ROW_DESC, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			*pValue = (GS_DESC) hStmt->appRowDesc;
			WriteToLog("\t0x%p", *pValue);
			return Success(hStmt);
		case SQL_ATTR_ASYNC_ENABLE:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_ASYNC_ENABLE, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_CONCURRENCY:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_CONCURRENCY, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_CURSOR_SCROLLABLE:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_CURSOR_SCROLLABLE, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_CURSOR_SENSITIVITY:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_CURSOR_SENSITIVITY, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_CURSOR_TYPE:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_CURSOR_TYPE, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_ENABLE_AUTO_IPD:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_ENABLE_AUTO_IPD, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_FETCH_BOOKMARK_PTR:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_FETCH_BOOKMARK_PTR, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_IMP_PARAM_DESC:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_IMP_PARAM_DESC, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			*pValue = (GS_DESC) hStmt->impParamDesc;
			WriteToLog("\t0x%p", *pValue);
			return Success(hStmt);
		case SQL_ATTR_IMP_ROW_DESC:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_IMP_ROW_DESC, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			*pValue = (GS_DESC) hStmt->impRowDesc;
			WriteToLog("\t0x%p", *pValue);
			return Success(hStmt);
		case SQL_ATTR_KEYSET_SIZE:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_KEYSET_SIZE, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_MAX_LENGTH:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_MAX_LENGTH, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			return SQLGetStmtAttr_uint(hStmt, 0, Value, BufferLength, StringLength);
		case SQL_ATTR_MAX_ROWS:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_MAX_ROWS, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_METADATA_ID:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_METADATA_ID, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_NOSCAN:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_NOSCAN, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_PARAM_BIND_OFFSET_PTR:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_PARAM_BIND_OFFSET_PTR, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_PARAM_BIND_TYPE:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_PARAM_BIND_TYPE, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_PARAM_OPERATION_PTR:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_PARAM_OPERATION_PTR, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_PARAM_STATUS_PTR:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_PARAM_STATUS_PTR, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_PARAMS_PROCESSED_PTR:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_PARAMS_PROCESSED_PTR, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_PARAMSET_SIZE:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_PARAMSET_SIZE, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_QUERY_TIMEOUT:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_QUERY_TIMEOUT, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			return SQLGetStmtAttr_uint(hStmt, 0, Value, BufferLength, StringLength);
		case SQL_ATTR_RETRIEVE_DATA:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_RETRIEVE_DATA, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_ROW_ARRAY_SIZE:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_ROW_ARRAY_SIZE, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_ROW_BIND_OFFSET_PTR:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_ROW_BIND_OFFSET_PTR, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_ROW_BIND_TYPE:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_ROW_BIND_TYPE, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_ROW_NUMBER:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_ROW_NUMBER, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_ROW_OPERATION_PTR:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_ROW_OPERATION_PTR, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_ROW_STATUS_PTR:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_ROW_STATUS_PTR, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_ROWS_FETCHED_PTR:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_ROWS_FETCHED_PTR, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_SIMULATE_CURSOR:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_SIMULATE_CURSOR, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		case SQL_ATTR_USE_BOOKMARKS:
			WriteToLog("SQLGetStmtAttr(0x%p, SQL_ATTR_USE_BOOKMARKS, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
		default:
			WriteToLog("SQLGetStmtAttr(,????, 0x%p, %i, %i)", StatementHandle, Value, BufferLength, StringLength);
			break;
	}
	return Error(hStmt, 0, "HYC00", "SQLGetStmtAttr attribute not supported");
}
