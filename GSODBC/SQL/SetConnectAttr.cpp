#include "stdafx.h"

SQLRETURN  SQL_API SQLSetConnectAttr(
	SQLHDBC			ConnectionHandle,
	SQLINTEGER		Attribute, 
	SQLPOINTER		Value,
	SQLINTEGER		StringLength)
{
	GS_DBC	hDBC = (GS_DBC) ConnectionHandle;
	GS_ENV	hENV = hDBC->hEnv;

	switch (Attribute) {
		case SQL_ATTR_ACCESS_MODE: 
			/* An SQLUINTEGER value. SQL_MODE_READ_ONLY is used by the driver or data source as an indicator that the connection 
				is not required to support SQL statements that cause updates to occur. SQL_MODE_READ_WRITE is the default.	*/
			switch ((SQLUINTEGER) Value) {
				case SQL_MODE_READ_WRITE:
					WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_ACCESS_MODE, SQL_MODE_READ_WRITE, %i)", ConnectionHandle, StringLength);
					hDBC->accessMode = (SQLUINTEGER) Value;
					return Success(ConnectionHandle);
				case SQL_MODE_READ_ONLY:
					WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_ACCESS_MODE, SQL_MODE_READ_ONLY, %i)", ConnectionHandle, StringLength);
					hDBC->accessMode = (SQLUINTEGER) Value;
					return Success(ConnectionHandle);
				default:
					WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_ACCESS_MODE, %i, %i)", ConnectionHandle, Value, StringLength);
					return Error(
						ConnectionHandle, 
						0, // ErrorCode
						"IM001", // Driver does not support this function
						"Unsupported Value");
			}
//		case SQL_ATTR_ASYNC_DBC_EVENT:				//	ODBC 3.8
//		case SQL_ATTR_ASYNC_DBC_FUNCTIONS_ENABLE:	//	ODBC 3.8
//		case SQL_ATTR_ASYNC_DBC_PCALLBACK:			//	ODBC 3.8
//		case SQL_ATTR_ASYNC_DBC_PCONTEXT:			//	ODBC 3.8
//		case SQL_ATTR_ASYNC_DBC_FUNCTIONS_ENABLE:	//	ODBC 3.8
//		case SQL_ATTR_ASYNC_DBC_FUNCTIONS_ENABLE:	//	ODBC 3.8
		case SQL_ATTR_ASYNC_ENABLE:					//	ODBC 3.0
			switch ((SQLULEN) Value) {
				case SQL_ASYNC_ENABLE_OFF:
					WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_ASYNC_ENABLE, SQL_ASYNC_ENABLE_OFF, %i)", ConnectionHandle, StringLength);
					hDBC->asyncEnabled = (SQLULEN) Value;
					return Success(ConnectionHandle);
				case SQL_ASYNC_ENABLE_ON:
					WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_ASYNC_ENABLE, SQL_ASYNC_ENABLE_ON, %i)", ConnectionHandle, StringLength);
					hDBC->asyncEnabled = (SQLULEN) Value;
					return Success(ConnectionHandle);
				default:
					WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_ASYNC_ENABLE, %i, %i)", ConnectionHandle, Value, StringLength);
					return Error(
						ConnectionHandle, 
						0, // ErrorCode
						"IM001", // Driver does not support this function
						"Unsupported Value");
			}
		case SQL_ATTR_AUTO_IPD:
			if ((SQLPOINTER) SQL_TRUE == Value) {
				WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_AUTO_IPD, SQL_TRUE,)", ConnectionHandle);
			}
			if (SQL_FALSE == Value) {
				WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_AUTO_IPD, SQL_FALSE,)", ConnectionHandle);
			}
			break;

		case SQL_ATTR_AUTOCOMMIT:
			if ((SQLPOINTER) SQL_AUTOCOMMIT_ON == Value) {
				WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_ON,)", ConnectionHandle);
			}
			if (SQL_AUTOCOMMIT_OFF == Value) {
				WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF,)", ConnectionHandle);
			}
			break;

		case SQL_ATTR_CONNECTION_DEAD:
			if ((SQLPOINTER) SQL_CD_TRUE == Value) {
				WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_CONNECTION_DEAD, SQL_CD_TRUE,)", ConnectionHandle);
			}
			if (SQL_CD_FALSE == Value) {
				WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_CONNECTION_DEAD, SQL_CD_FALSE,)", ConnectionHandle);
			}
			break;

		case SQL_ATTR_CONNECTION_TIMEOUT:
			WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_CONNECTION_TIMEOUT,,)", ConnectionHandle);
			break;

		case SQL_ATTR_CURRENT_CATALOG:
			WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_CURRENT_CATALOG,,)", ConnectionHandle);
			break;

		case SQL_ATTR_LOGIN_TIMEOUT:
			/*	An SQLUINTEGER value corresponding to the number of seconds to wait for a login request to complete 
				before returning to the application. The default is driver-dependent. If ValuePtr is 0, the timeout 
				is disabled and a connection attempt will wait indefinitely.
				If the specified timeout exceeds the maximum login timeout in the data source, the driver substitutes 
				that value and returns SQLSTATE 01S02 (Option value changed).	*/
			hDBC->loginTimeout = (SQLUINTEGER) Value;
			WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_LOGIN_TIMEOUT, %lu, %lu)", ConnectionHandle, hDBC->loginTimeout, StringLength);
			return Success(hDBC);
		case SQL_ATTR_METADATA_ID:
			if ((SQLPOINTER) SQL_TRUE == Value) {
				WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_METADATA_ID, SQL_TRUE,)", ConnectionHandle);
			}
			if (SQL_FALSE == Value) {
				WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_METADATA_ID, SQL_FALSE,)", ConnectionHandle);
			}
			break;

		case SQL_ATTR_PACKET_SIZE:
			WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_PACKET_SIZE,,)", ConnectionHandle);
			break;

		case SQL_ATTR_QUIET_MODE:
			/*	A window handle (HWND).
				If the window handle is a null pointer, the driver does not display any dialog boxes.
				If the window handle is not a null pointer, it should be the parent window handle of 
				the application. This is the default. The driver uses this handle to display dialog boxes. */
			hDBC->hParentWindow = (HWND) Value;
			WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_QUIET_MODE, 0x%p, %lu)", ConnectionHandle, hDBC->hParentWindow, StringLength);
			return Success(hDBC);
		case SQL_ATTR_TRACE:
			if (SQL_OPT_TRACE_OFF == Value) {
				WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_TRACE, SQL_OPT_TRACE_OFF,)", ConnectionHandle);
			}
			if ((SQLPOINTER) SQL_OPT_TRACE_ON == Value) {
				WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_TRACE, SQL_OPT_TRACE_OFF,)", ConnectionHandle);
			}
			break;

		case SQL_ATTR_TRACEFILE:
			WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_TRACEFILE,,)", ConnectionHandle);
			break;

		case SQL_ATTR_TRANSLATE_LIB:
			WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_TRANSLATE_LIB,,)", ConnectionHandle);
			break;

		case SQL_ATTR_TRANSLATE_OPTION:
			WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_TRANSLATE_OPTION,,)", ConnectionHandle);
			break;

		case SQL_ATTR_TXN_ISOLATION:
			WriteToLog("SQLSetConnectAttr(0x%p, SQL_ATTR_TXN_ISOLATION,,)", ConnectionHandle);
			break;

		case 30002:		// Microsoft Access sends in this value just before crashing
			WriteToLog("SQLSetConnectAttr(,30002,,)", ConnectionHandle);
			break;

		default:
			WriteToLog("SQLSetConnectAttr(,???,,)", ConnectionHandle);
			return Error(
				ConnectionHandle, 
				0, // ErrorCode
				"IM001", // Driver does not support this function
				"Unsupported Attribute");
	}

	return Success(hDBC);
}
