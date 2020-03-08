#include "stdafx.h"

SQLRETURN  SQL_API SQLGetDiagRec(
	SQLSMALLINT		HandleType, 
	SQLHANDLE		Handle,
	SQLSMALLINT		RecNumber, 
	SQLCHAR			*Sqlstate,
	SQLINTEGER		*NativeError, 
	SQLCHAR			*MessageText,
	SQLSMALLINT		BufferLength, 
	SQLSMALLINT		*TextLength)
{
	SQLRETURN		sqlReturn = SQL_NO_DATA;
	GS_DBC			hDBC;
	SQLCHAR			*messagePrefix = (SQLCHAR *) "[GemStone][ODBC Driver]";
	size_t			stringSize;
	size_t			spaceLeft = BufferLength;
	size_t			offset = 0;

	switch (HandleType)
	{
		case SQL_HANDLE_ENV:
			WriteToLog("SQLGetDiagRec(SQL_HANDLE_ENV, 0x%p, %hi, 0x%p, 0x%p, 0x%p, %hi, 0x%p)",
				Handle, RecNumber, Sqlstate, NativeError, MessageText, BufferLength, TextLength);
			break;
		case SQL_HANDLE_DBC:
			WriteToLog("SQLGetDiagRec(SQL_HANDLE_DBC, 0x%p, %hi, 0x%p, 0x%p, 0x%p, %hi, 0x%p)",
				Handle, RecNumber, Sqlstate, NativeError, MessageText, BufferLength, TextLength);
			hDBC = (GS_DBC) Handle;
			if (1 == RecNumber && hDBC->error.state) {
				if (Sqlstate && hDBC->error.state) {
					strcpy_s((char *) Sqlstate, 6, hDBC->error.state);
				}
				if (NativeError) {
					*NativeError = hDBC->error.code;
				}
				if (MessageText) {
					stringSize = strlen((char *) messagePrefix);
					if (stringSize < spaceLeft) {
						strcpy_s((char *) MessageText, BufferLength, (const char *) messagePrefix);
						spaceLeft = spaceLeft - stringSize;
						offset = offset + stringSize;
					}
					stringSize = strlen(hDBC->dataSourceName) + 2;
					if (2 < stringSize && stringSize < spaceLeft) {
						MessageText[offset] = '[';
						strcpy_s((char *) MessageText + offset + 1, BufferLength - offset - 1, hDBC->dataSourceName);
						MessageText[offset + stringSize - 1] = ']';
						MessageText[offset + stringSize] = 0;
						spaceLeft = spaceLeft - stringSize;
						offset = offset + stringSize;
					}
					stringSize = strlen(hDBC->error.message) + 1;
					if (1 < stringSize && stringSize < spaceLeft) {
						MessageText[offset] = ' ';
						strcpy_s((char *) MessageText + offset + 1, BufferLength - offset - 1, hDBC->error.message);
						spaceLeft = spaceLeft - stringSize;
						offset = offset + stringSize;
					}
				}
				if (TextLength && hDBC->error.message) {
					if (!offset) {
						offset = (SQLSMALLINT) strlen((char *) messagePrefix);
						if (hDBC->dataSourceName[0]) {
							offset = offset + strlen(hDBC->dataSourceName) + 2;
						}
						offset = offset + 1 + strlen(hDBC->error.message);
					}
					*TextLength = (SQLSMALLINT) offset;
				}
				sqlReturn = SQL_SUCCESS;
			}
			break;
		case SQL_HANDLE_DESC:
			WriteToLog("SQLGetDiagRec(SQL_HANDLE_DESC, 0x%p, %hi, 0x%p, 0x%p, 0x%p, %hi, 0x%p)",
				Handle, RecNumber, Sqlstate, NativeError, MessageText, BufferLength, TextLength);
			break;
		case SQL_HANDLE_STMT:
			WriteToLog("SQLGetDiagRec(SQL_HANDLE_STMT, 0x%p, %hi, 0x%p, 0x%p, 0x%p, %hi, 0x%p)",
				Handle, RecNumber, Sqlstate, NativeError, MessageText, BufferLength, TextLength);
			break;
		default:
			WriteToLog("SQLGetDiagRec(%hi, 0x%p, %hi, 0x%p, 0x%p, 0x%p, %hi, 0x%p)",
				HandleType, Handle, RecNumber, Sqlstate, NativeError, MessageText, BufferLength, TextLength);
			break;
	}
	WriteToLog("\tSQL_NO_DATA");
	return sqlReturn;
}
