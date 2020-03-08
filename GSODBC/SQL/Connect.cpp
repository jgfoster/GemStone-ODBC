#include "stdafx.h"

#define  CORRUPT_DSN_ERROR	"IM015"

extern BOOL ReadDSN(GS_DBC);

SQLRETURN	Connect(GS_DBC);
BOOL		GetProcAddressGCI(GS_DBC);
SQLRETURN	SQLConnectError(GS_DBC, HKEY, PCSTR, PCSTR);


SQLRETURN  SQL_API SQLConnect(
	SQLHDBC			ConnectionHandle,
	SQLCHAR	*		ServerName, 
	SQLSMALLINT		NameLength1,
	SQLCHAR	*		UserName, 
	SQLSMALLINT		NameLength2,
	SQLCHAR	*		Authentication, 
	SQLSMALLINT		NameLength3)
{
	GS_DBC			hDBC = (GS_DBC) ConnectionHandle;

	// get DSN
	if (!CopySqlString(hDBC->dataSourceName, sizeof(hDBC->dataSourceName), ServerName, NameLength1)) {
		WriteToLog("SQLConnect(0x%p, \"%s\", %hi, \"%s\", %hi, \"%s\", %hi)", 
			ConnectionHandle, ServerName, NameLength1, UserName, NameLength2, Authentication, NameLength3);
		return Error(hDBC, 0, BUFFER_SIZE_ERROR, "ServerName string too long");
	}
	strcpy_s(hDBC->dataSourceName, sizeof(hDBC->dataSourceName), hDBC->dataSourceName);
	if (!CopySqlString(hDBC->gsUserName, sizeof(hDBC->gsUserName), UserName, NameLength2)) {
		WriteToLog("SQLConnect(0x%p, \"%s\", %hi, \"%s\", %hi, \"%s\", %hi)", 
			ConnectionHandle, ServerName, NameLength1, UserName, NameLength2, Authentication, NameLength3);
		return Error(hDBC, 0, BUFFER_SIZE_ERROR, "UserName string too long");
	}
	if (!CopySqlString(hDBC->gsPassword, sizeof(hDBC->gsPassword), Authentication, NameLength3)) {
		WriteToLog("SQLConnect(0x%p, \"%s\", %hi, \"%s\", %hi, \"%s\", %hi)", 
			ConnectionHandle, ServerName, NameLength1, UserName, NameLength2, Authentication, NameLength3);
		return Error(hDBC, 0, BUFFER_SIZE_ERROR, "Authentication string too long");
	}
	WriteToLog("SQLConnect(0x%p, \"%s\", %hi, \"%s\", %hi, \"%s\", %hi)", 
		ConnectionHandle, hDBC->dataSourceName, NameLength1, 
		hDBC->gsUserName, NameLength2, hDBC->gsPassword, NameLength3);
	return Connect(hDBC);
}

SQLRETURN Connect(
	GS_DBC		hDBC)
{
	CHAR		string[256];
	HKEY		hKeyDataSource = NULL;
	CHAR		stoneNRS[BASIC_STRING_MAX];
	CHAR		gemNRS[BASIC_STRING_MAX];
	SQLRETURN	result;

	stoneNRS[0] = '\0';
	gemNRS[0] = '\0';

	if (!ReadDSN(hDBC))
		return Error(hDBC, 0, BUFFER_SIZE_ERROR, "Data source name error");
	if (result = LoadGciLibrary(hDBC, hDBC->gsVersion))
		return result;
	if (!Gci_DbgEstablishToFile(hDBC->logFilePath))
		return Error(hDBC, 0, BUFFER_SIZE_ERROR, "Unable to establish debug log");
	strcpy_s(stoneNRS + strlen(stoneNRS), sizeof(stoneNRS) - strlen(stoneNRS), "!tcp@");
	if (hDBC->stoneHost[0]) {
		strcpy_s(stoneNRS + strlen(stoneNRS), sizeof(stoneNRS) - strlen(stoneNRS), hDBC->stoneHost);
	} else {
		strcpy_s(stoneNRS + strlen(stoneNRS), sizeof(stoneNRS) - strlen(stoneNRS), "localhost");
	}
	strcpy_s(stoneNRS + strlen(stoneNRS), sizeof(stoneNRS) - strlen(stoneNRS), "#server!");
	if (hDBC->stoneName[0]) {
		strcpy_s(stoneNRS + strlen(stoneNRS), sizeof(stoneNRS) - strlen(stoneNRS), hDBC->stoneName);
	} else {
		strcpy_s(stoneNRS + strlen(stoneNRS), sizeof(stoneNRS) - strlen(stoneNRS), "gs64stone");
	}
	strcpy_s(gemNRS + strlen(gemNRS), sizeof(gemNRS) - strlen(gemNRS), "!tcp@");
	if (hDBC->gemHost[0]) {
		strcpy_s(gemNRS + strlen(gemNRS), sizeof(gemNRS) - strlen(gemNRS), hDBC->gemHost);
	} else {
		strcpy_s(gemNRS + strlen(gemNRS), sizeof(gemNRS) - strlen(gemNRS), "localhost");
	}
	strcpy_s(gemNRS + strlen(gemNRS), sizeof(gemNRS) - strlen(gemNRS), "#netldi:");
	if (hDBC->gemNetLDI[0]) {
		strcpy_s(gemNRS + strlen(gemNRS), sizeof(gemNRS) - strlen(gemNRS), hDBC->gemNetLDI);
	} else {
		strcpy_s(gemNRS + strlen(gemNRS), sizeof(gemNRS) - strlen(gemNRS), "gs64ldi");
	}
	strcpy_s(gemNRS + strlen(gemNRS), sizeof(gemNRS) - strlen(gemNRS), "#task!");
	if (hDBC->gemTask[0]) {
		strcpy_s(gemNRS + strlen(gemNRS), sizeof(gemNRS) - strlen(gemNRS), hDBC->gemTask);
	} else {
		strcpy_s(gemNRS + strlen(gemNRS), sizeof(gemNRS) - strlen(gemNRS), "gemnetobject");
	}
	Gci_SetNet(stoneNRS, NULL, NULL, gemNRS);

	if (!(Gci_Login(hDBC->gsUserName, hDBC->gsPassword))) {
		CopyGciError(hDBC);
		return SQLConnectError(hDBC, hKeyDataSource, AUTHORIZATION_ERROR, hDBC->errorString);
	}

	hDBC->sessionID = Gci_GetSessionId();
	int count = sprintf_s(string, sizeof(string), "OdbcServer catalog: \'%s\' schema: \'%s\'", hDBC->catalog, hDBC->schema);
	hDBC->odbcServer = Gci_ExecuteStr(string, OOP_NIL);
	if ((OOP_NIL == hDBC->odbcServer) && Gci_Err(&(hDBC->gciError))) {
		CopyGciError(hDBC);
		return SQLConnectError(hDBC, hKeyDataSource, AUTHORIZATION_ERROR, hDBC->errorString);
	}
	return Success(hDBC);
}

SQLRETURN SQLConnectError(
	GS_DBC	hDBC,
	HKEY	hKeyDataSource,
	PCSTR	errorState,
	PCSTR	errorMessage)
{
	if (hKeyDataSource) {
		RegCloseKey(hKeyDataSource);
	}
	return Error(hDBC, 0, errorState, errorMessage);
}
