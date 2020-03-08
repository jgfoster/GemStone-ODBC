#include "stdafx.h"

SQLRETURN  SQL_API SQLGetConnectAttr(
	SQLHDBC			ConnectionHandle,
	SQLINTEGER		Attribute, 
	SQLPOINTER		Value,
	SQLINTEGER		BufferLength, 
	SQLINTEGER		*StringLength)
{
	GS_DBC	hDBC = (GS_DBC) ConnectionHandle;
	GS_ENV	hENV = hDBC->hEnv;

	switch (Attribute) {
		case SQL_ATTR_ACCESS_MODE:	//	ODBC 1.0
			/* An SQLUINTEGER value. SQL_MODE_READ_ONLY is used by the driver or data source as an indicator that the connection 
				is not required to support SQL statements that cause updates to occur. SQL_MODE_READ_WRITE is the default.	*/
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_ACCESS_MODE, 0x%p, %i, 0x%p) ==> %i", 
				hDBC, Value, BufferLength, StringLength, hDBC->accessMode);
			*(SQLINTEGER *) Value = hDBC->accessMode;
			return Success(ConnectionHandle);
//		case SQL_ATTR_ASYNC_DBC_EVENT:				//	ODBC 3.8
//		case SQL_ATTR_ASYNC_DBC_FUNCTIONS_ENABLE:	//	ODBC 3.8
//		case SQL_ATTR_ASYNC_DBC_PCALLBACK:			//	ODBC 3.8
//		case SQL_ATTR_ASYNC_DBC_PCONTEXT:			//	ODBC 3.8
//		case SQL_ATTR_ASYNC_DBC_FUNCTIONS_ENABLE:	//	ODBC 3.8
//		case SQL_ATTR_ASYNC_DBC_FUNCTIONS_ENABLE:	//	ODBC 3.8
		case SQL_ATTR_ASYNC_ENABLE:					//	ODBC 3.0
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_ASYNC_ENABLE, 0x%p, %i, 0x%p) ==> %i", 
				hDBC, Value, BufferLength, StringLength, hDBC->asyncEnabled);
			break;
			
		case SQL_ATTR_AUTO_IPD:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_AUTO_IPD, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			*(SQLINTEGER *) Value = hDBC->accessMode;
			break;

		case SQL_ATTR_AUTOCOMMIT:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_AUTOCOMMIT, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			break;

		case SQL_ATTR_CONNECTION_DEAD:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_CONNECTION_DEAD, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			break;

		case SQL_ATTR_CONNECTION_TIMEOUT:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_CONNECTION_TIMEOUT, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			break;

		case SQL_ATTR_CURRENT_CATALOG:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_CURRENT_CATALOG, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			break;

		case SQL_ATTR_LOGIN_TIMEOUT:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_LOGIN_TIMEOUT, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			break;

		case SQL_ATTR_METADATA_ID:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_METADATA_ID, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			break;

		case SQL_ATTR_PACKET_SIZE:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_PACKET_SIZE, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			break;

		case SQL_ATTR_QUIET_MODE:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_QUIET_MODE, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			break;

		case SQL_ATTR_TRACE:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_TRACE, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			break;

		case SQL_ATTR_TRACEFILE:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_TRACEFILE, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			break;

		case SQL_ATTR_TRANSLATE_LIB:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_TRANSLATE_LIB, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			break;

		case SQL_ATTR_TRANSLATE_OPTION:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_TRANSLATE_OPTION, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			break;

		case SQL_ATTR_TXN_ISOLATION:
			WriteToLog("SQLGetConnectAttr(0x%p, SQL_ATTR_TXN_ISOLATION, 0x%p, %i, 0x%p)", hDBC, Value, BufferLength, StringLength);
			break;

		case 30002:		// Microsoft Access sends in this value
			return Error(
				ConnectionHandle, 
				0, // ErrorCode
				"IM001", // Driver does not support this function
				"SQLGetConnectAttr(,30002,,,) -> unrecognized Attribute");
			break;

		default:
			break;
	}

	return Error(
		ConnectionHandle, 
		0, // ErrorCode
		"IM001", // Driver does not support this function
		"Unsupported Attribute");
}
