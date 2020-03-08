#include "stdafx.h"

SQLRETURN  SQL_API SQLSetEnvAttr(
	SQLHENV			EnvironmentHandle,
	SQLINTEGER		Attribute, 
	SQLPOINTER		pValue,
	SQLINTEGER		StringLength)
{
	GS_ENV	hEnv	= (GS_ENV) EnvironmentHandle;
	union {
		SQLPOINTER	sqlPointer;
		int			myInteger;
	} myUnion;

	myUnion.sqlPointer = pValue;

	switch (Attribute)
	{
		case SQL_ATTR_CONNECTION_POOLING:
			WriteToLog("SQLSetEnvAttr(0x%p, SQL_ATTR_CONNECTION_POOLING,,)", EnvironmentHandle);
			break;

		case SQL_ATTR_CP_MATCH:
			WriteToLog("SQLSetEnvAttr(0x%p, SQL_ATTR_CP_MATCH,,)", EnvironmentHandle);
			break;

		case SQL_ATTR_ODBC_VERSION:
			switch (myUnion.myInteger)
			{
				case SQL_OV_ODBC2:
					WriteToLog("SQLSetEnvAttr(0x%p, SQL_ATTR_ODBC_VERSION, SQL_OV_ODBC2, %lu)", EnvironmentHandle, StringLength);
					hEnv->ODBC_Version = SQL_OV_ODBC2;
					return Success(hEnv);
				case SQL_OV_ODBC3:
					WriteToLog("SQLSetEnvAttr(0x%p, SQL_ATTR_ODBC_VERSION, SQL_OV_ODBC3, %lu)", EnvironmentHandle, StringLength);
					hEnv->ODBC_Version = SQL_OV_ODBC3;
					return Success(hEnv);
			}
			return Error(hEnv, 0, "HYC00", "SQLSetEnvAttr not supported for SQL_ATTR_ODBC_VERSION");

		case SQL_ATTR_OUTPUT_NTS:
			WriteToLog("SQLSetEnvAttr(0x%p,SQL_ATTR_OUTPUT_NTS,,)", EnvironmentHandle);
			break;

		default:
			WriteToLog("SQLSetEnvAttr(0x%p,%i,,)", EnvironmentHandle, Attribute);
			break;
	}
	return Error(hEnv, 0, "HYC00", "\tSQLSetEnvAttr not supported");
}
