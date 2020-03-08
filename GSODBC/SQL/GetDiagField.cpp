#include "stdafx.h"

SQLRETURN  SQL_API SQLGetDiagField(
	SQLSMALLINT		HandleType, 
	SQLHANDLE		Handle,
	SQLSMALLINT		RecNumber, 
	SQLSMALLINT		DiagIdentifier,
	SQLPOINTER		DiagInfo, 
	SQLSMALLINT		BufferLength,
	SQLSMALLINT		*StringLength)
{
	SQLRETURN	sqlReturn = SQL_ERROR;

	switch (HandleType) {
		case SQL_HANDLE_ENV: {
			GS_ENV hEnv = (GS_ENV) Handle;
			WriteToLog("SQLGetDiagField(SQL_HANDLE_ENV,,,,,,)");
			break;
		}
		case SQL_HANDLE_DBC: {
			GS_DBC hDBC = (GS_DBC) Handle;
			if (!RecNumber) {
				WriteToLog("SQLGetDiagField(SQL_HANDLE_DBC,,0,,,,)");
				switch (DiagIdentifier) {
					case SQL_DIAG_CURSOR_ROW_COUNT:
						break;
					case SQL_DIAG_DYNAMIC_FUNCTION:
						break;
					case SQL_DIAG_DYNAMIC_FUNCTION_CODE:
						break;
					case SQL_DIAG_NUMBER:
						break;
					case SQL_DIAG_RETURNCODE:
						break;
					case SQL_DIAG_ROW_COUNT:
						break;
					default:
						break;
				}
			} else {
				switch (DiagIdentifier) {
					case SQL_DIAG_CLASS_ORIGIN:
						WriteToLog("SQLGetDiagField(SQL_HANDLE_DBC,,n,SQL_DIAG_CLASS_ORIGIN,,,)");
						if (BufferLength > 8) {
							strcpy_s((char *) DiagInfo, BufferLength, "ISO 9075");
						}
						*StringLength = 8;
						sqlReturn = SQL_SUCCESS;
						break;
					case SQL_DIAG_SUBCLASS_ORIGIN:
						WriteToLog("SQLGetDiagField(SQL_HANDLE_DBC,,n,SQL_DIAG_SUBCLASS_ORIGIN,,,)");
						if (BufferLength > 8) {
							strcpy_s((char *) DiagInfo, BufferLength, "ISO 9075");
						}
						*StringLength = 8;
						sqlReturn = SQL_SUCCESS;
						break;
					case SQL_DIAG_CONNECTION_NAME:
						WriteToLog("SQLGetDiagField(SQL_HANDLE_DBC,,n,SQL_DIAG_CONNECTION_NAME,,,)");
						if (BufferLength > 8) {
							strcpy_s((char *) DiagInfo, BufferLength, "GemStone");
						}
						*StringLength = 8;
						sqlReturn = SQL_SUCCESS;
						break;
					case SQL_DIAG_SERVER_NAME:
						WriteToLog("SQLGetDiagField(SQL_HANDLE_DBC,,n,SQL_DIAG_SERVER_NAME,,,)");
						if (BufferLength > 8) {
							strcpy_s((char *) DiagInfo, BufferLength, "GemStone");
						}
						*StringLength = 8;
						sqlReturn = SQL_SUCCESS;
						break;
					case SQL_DIAG_MESSAGE_TEXT:
					case SQL_DIAG_COLUMN_NUMBER:
					case SQL_DIAG_NATIVE:
					case SQL_DIAG_ROW_NUMBER:
					case SQL_DIAG_SQLSTATE:
					default:
						WriteToLog("SQLGetDiagField(SQL_HANDLE_DBC,,n,,,,,)");
						break;
				}
				break;
			}
		}
		case SQL_HANDLE_DESC: {
			WriteToLog("SQLGetDiagField(SQL_HANDLE_DESC, 0x%p, %i, %i, 0x%p, %i, 0x%p)", 
				Handle, RecNumber, DiagIdentifier, DiagInfo, BufferLength, StringLength);
			break;
		}
		case SQL_HANDLE_STMT: {
			GS_STMT hStmt = (GS_STMT) Handle;
			GS_DBC  hDBC  = hStmt->hDBC;
			GS_ENV  hEnv  = hDBC->hEnv;

			switch (DiagIdentifier) {
				case SQL_DIAG_CURSOR_ROW_COUNT:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_CURSOR_ROW_COUNT, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_ERROR;
					break;
				case SQL_DIAG_DYNAMIC_FUNCTION:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_DYNAMIC_FUNCTION, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_ERROR;
					break;
				case SQL_DIAG_DYNAMIC_FUNCTION_CODE:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_DYNAMIC_FUNCTION_CODE, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_ERROR;
					break;
				case SQL_DIAG_NUMBER:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_NUMBER, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_ERROR;
					break;
				case SQL_DIAG_RETURNCODE:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_RETURNCODE, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_ERROR;
					break;
				case SQL_DIAG_ROW_COUNT:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_ROW_COUNT, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_ERROR;
					break;
					
				case SQL_DIAG_CLASS_ORIGIN:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_CLASS_ORIGIN, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_ERROR;
					break;
				case SQL_DIAG_COLUMN_NUMBER:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_COLUMN_NUMBER, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_ERROR;
					break;
				case SQL_DIAG_CONNECTION_NAME:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_CONNECTION_NAME, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_ERROR;
					break;
				case SQL_DIAG_MESSAGE_TEXT:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_MESSAGE_TEXT, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_ERROR;
					break;
				case SQL_DIAG_ROW_NUMBER:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_ROW_NUMBER, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_NO_ROW_NUMBER;	//	currently no diagnostic records for statement
					break;
				case SQL_DIAG_SERVER_NAME:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_SERVER_NAME, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_ERROR;
					break;
				case SQL_DIAG_SQLSTATE:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_SQLSTATE, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					if (StringLength) *StringLength = 5;
					if (DiagInfo && 5 <= BufferLength) {
						strcpy_s((char *) DiagInfo, BufferLength, "00000");
						WriteToLog("\tSQL_DIAG_SQLSTATE = \"%s\"", DiagInfo);
					}
					sqlReturn = SQL_SUCCESS;
					break;
				case SQL_DIAG_SUBCLASS_ORIGIN:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, SQL_DIAG_SUBCLASS_ORIGIN, 0x%p, %i, 0x%p)", 
						Handle, RecNumber, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_ERROR;
					break;
				default:
					WriteToLog("SQLGetDiagField(SQL_HANDLE_STMT, 0x%p, %i, %i, 0x%p, %i, 0x%p) (unrecognized DiagIdentifier)", 
						Handle, RecNumber, DiagIdentifier, DiagIdentifier, BufferLength, StringLength);
					sqlReturn = SQL_ERROR;
					break;
			}
			break;
		}
		default:
			break;
	}
	WriteToLog("\t%i", sqlReturn);
	return sqlReturn;
}
