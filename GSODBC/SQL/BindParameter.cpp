#include "stdafx.h"

SQLRETURN SQL_API SQLBindParameter(
	SQLHSTMT     StatementHandle,
	SQLUSMALLINT	ParameterNumber,	//	Parameter number, ordered sequentially in increasing parameter order, starting at 1.
	SQLSMALLINT		InputOutputType,	//	The type of the parameter.
	SQLSMALLINT		ValueType,			//	The C data type of the parameter.
	SQLSMALLINT		ParameterType,		//	The SQL data type of the parameter.
	SQLUINTEGER		ColumnSize,			//	The size of the column or expression of the corresponding parameter marker.
	SQLSMALLINT		DecimalDigits,		//	The decimal digits of the column or expression of the corresponding parameter marker.
	SQLPOINTER		ParameterValuePtr,	//	A pointer to a buffer for the parameter's data.
	SQLINTEGER		BufferLength,		//	Length of the ParameterValuePtr buffer in bytes.
	SQLINTEGER		*StrLen_or_IndPtr)	//	A pointer to a buffer for the parameter's length.
{
	GS_STMT		hStmt = (GS_STMT) StatementHandle;
	GS_DBC		hDBC = hStmt->hDBC;

	WriteToLog("SQLBindParameter()");
	return Success(hDBC);
}
