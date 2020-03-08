#include "stdafx.h"

#define  PATH_TO_GEMSTONE  "SOFTWARE\\ODBC\\ODBCINST.INI\\GemStone/S"

CHAR		logFilePath[FILENAME_MAX + 1];
LONG		forceError;

SQLRETURN Error(
	PVOID	handle,
	DWORD	errorCode,
	PCSTR	errorState,
	PCSTR	format, 
	...)
{
	GS_ERROR_P	error = (GS_ERROR_P) handle;

	error->code		= errorCode;		// see NativeErrorPtr in SQLGetDiagRec()
	error->state	= errorState;
	error->message	= format;
	va_list args;
	va_start(args, format);
	WriteToLog(format, args);
	va_end(args);
	return SQL_ERROR;
}

SQLRETURN Success(
	PVOID	handle)
{
	GS_ERROR_P	error = (GS_ERROR_P) handle;

	error->code = 0;
	error->state = NULL;
	error->message = NULL;
	WriteToLog("\tSQL_SUCCESS");
	return SQL_SUCCESS;
}

VOID FindLogFile()
{
	LONG	returnCode;
	HKEY	hKeyDriver;
	DWORD	type;
	DWORD	logFilePathSize = sizeof(logFilePath);
	CHAR	logFlag[6];
	DWORD	logFlagSize = sizeof(logFlag);
	DWORD	forceErrorSize = sizeof(forceError);

	forceError = 0;
	memset(logFilePath, 0, sizeof(logFilePath));

	returnCode = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PATH_TO_GEMSTONE, 0, KEY_QUERY_VALUE, &hKeyDriver);
	if (ERROR_SUCCESS == returnCode ) {
		returnCode = RegQueryValueEx(hKeyDriver, "GSForceError", 0, &type, (LPBYTE) &forceError, &forceErrorSize);
		returnCode = RegQueryValueEx(hKeyDriver, "LogFilePath", 0, &type, (LPBYTE) logFilePath, &logFilePathSize);
		returnCode = RegCloseKey(hKeyDriver);
	}
}

VOID WriteToLog(
	PCSTR	format,
	...)
{
	HANDLE	fileHandle;
	DWORD	offset;
	BOOL	writeSuccess;
	DWORD	bytesWritten;
	char	string[1024];

	if (!logFilePath[0]) return;

	va_list args;
	va_start(args, format);
	vsprintf_s(string, sizeof(string), format, args);
	va_end(args);

	fileHandle = CreateFile(
		logFilePath,			//	IN LPCSTR lpFileName
		FILE_WRITE_DATA,		//	IN DWORD dwDesiredAccess
		0,						//	IN DWORD dwShareMode
		NULL,					//	IN LPSECURITY_ATTRIBUTES lpSecurityAttributes
		OPEN_ALWAYS,			//	IN DWORD dwCreationDisposition
		FILE_ATTRIBUTE_NORMAL,	//	IN DWORD dwFlagsAndAttributes
		NULL);					//	IN HANDLE hTemplateFile
    if (!fileHandle) return;

	offset = SetFilePointer(
		fileHandle,				//	IN HANDLE hFile,
		0,						//	IN LONG lDistanceToMove,
		0,						//	IN PLONG lpDistanceToMoveHigh,
		FILE_END);				//	IN DWORD dwMoveMethod
	if (INVALID_SET_FILE_POINTER == offset) {
		CloseHandle(fileHandle);
		return;
	}

	writeSuccess = WriteFile(
		fileHandle,				//	IN HANDLE hFile,
		string,					//	IN LPCVOID lpBuffer,
		(DWORD) strlen(string),	//	IN DWORD nNumberOfBytesToWrite,
		&bytesWritten,			//	OUT LPDWORD lpNumberOfBytesWritten,
		NULL);					//	IN LPOVERLAPPED lpOverlapped
	writeSuccess = WriteFile(
		fileHandle,				//	IN HANDLE hFile,
		"\n",					//	IN LPCVOID lpBuffer,
		(DWORD) 1,				//	IN DWORD nNumberOfBytesToWrite,
		&bytesWritten,			//	OUT LPDWORD lpNumberOfBytesWritten,
		NULL);					//	IN LPOVERLAPPED lpOverlapped
	CloseHandle(fileHandle);
	return;
}

BOOL CopySqlString(
	CHAR		*destination,
	size_t		destinationSize,
	SQLCHAR		*source,
	size_t		sourceSize)
{
	size_t	actualSize = (source ? ((SQL_NTS == sourceSize) ? strlen((const char *) source) : sourceSize) : 0);
	if (destinationSize < actualSize + 1) return FALSE;
	if (actualSize) {
		memcpy(destination, source, actualSize);
	}
	destination[actualSize] = 0;
	return TRUE;
}

VOID CopyGciError(
  GS_DBC	hDBC)
{
	size_t			stringSize;

	Gci_Err(&(hDBC->gciError));
	stringSize = min(strlen(hDBC->gciError.message), sizeof(hDBC->errorString) - 1);
	memcpy(hDBC->errorString, hDBC->gciError.message, stringSize);
	hDBC->errorString[stringSize] = 0;
}

int ParseTraversalBuffer(
	GciTravBufType	*travBuffer,
	GciObjRepSType	*objectReports[],
	int				objectReportsSize)
{
	GciObjRepSType	*readLimit		= (GciObjRepSType*)(travBuffer->body + travBuffer->usedBytes);
	GciObjRepSType	*objectReport	= (GciObjRepSType *) travBuffer->body;
	int i = -1;
	for (; i < objectReportsSize;) {
		objectReports[++i] = objectReport;
		objectReport = (GciObjRepSType *) ((char *) objectReport + sizeof(GciObjRepHdrSType) + GCI_ALIGN(objectReport->hdr.valueBuffSize));
		if (readLimit <= objectReport) break;
	}
	return i + 1;
}
