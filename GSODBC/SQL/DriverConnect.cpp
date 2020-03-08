#include "stdafx.h"

SQLRETURN	Connect(GS_DBC);

SQLRETURN SQL_API SQLDriverConnect(
	SQLHDBC			ConnectionHandle,
	SQLHWND			hwnd,
	SQLCHAR			*szConnStrIn,
	SQLSMALLINT		cbConnStrIn,
	SQLCHAR			*szConnStrOut,
	SQLSMALLINT		cbConnStrOutMax,
	SQLSMALLINT		*pcbConnStrOut,
	SQLUSMALLINT	fDriverCompletion)
{
	GS_DBC			hDBC = (GS_DBC) ConnectionHandle;
	/*
		On successful connection to the data source, the driver also sets 
		*StringLength2Ptr to the length of the output connection string 
		that is available to return in *OutConnectionString.
	*/
	switch (fDriverCompletion) {
		case SQL_DRIVER_PROMPT:
			WriteToLog("SQLDriverConnect(0x%p, 0x%p, \"%s\", %hi, 0x%p, %hi, 0x%p, SQL_DRIVER_PROMPT)", 
				ConnectionHandle, hwnd, szConnStrIn, cbConnStrIn, szConnStrOut, cbConnStrOutMax, pcbConnStrOut, fDriverCompletion);
			/* 
				The driver displays a dialog box, using the values from the connection string 
				and system information (if any) as initial values. When the user exits the 
				dialog box, the driver connects to the data source. It also constructs a 
				connection string from the value of the DSN or DRIVER keyword in *InConnectionString 
				and the information returned from the dialog box. It places this connection 
				string in the *OutConnectionString buffer. 
			*/
			return Error(hDBC, 0, "HYC00", "Not implemented yet");
		case SQL_DRIVER_COMPLETE:
			WriteToLog("SQLDriverConnect(0x%p, 0x%p, \"%s\", %hi, 0x%p, %hi, 0x%p, SQL_DRIVER_COMPLETE)", 
				ConnectionHandle, hwnd, szConnStrIn, cbConnStrIn, szConnStrOut, cbConnStrOutMax, pcbConnStrOut, fDriverCompletion);
			/* 
				If the connection string contains enough information, and that information is correct, 
				the driver connects to the data source and copies *InConnectionString to *OutConnectionString. 
				If any information is missing or incorrect, the driver takes the same actions as it does 
				when DriverCompletion is SQL_DRIVER_PROMPT, except that if DriverCompletion is 
				SQL_DRIVER_COMPLETE_REQUIRED, the driver disables the controls for any information not 
				required to connect to the data source. 
			*/
			return Error(hDBC, 0, "HYC00", "Not implemented yet");
		case SQL_DRIVER_COMPLETE_REQUIRED:
			WriteToLog("SQLDriverConnect(0x%p, 0x%p, \"%s\", %hi, 0x%p, %hi, 0x%p, SQL_DRIVER_COMPLETE_REQUIRED)", 
				ConnectionHandle, hwnd, szConnStrIn, cbConnStrIn, szConnStrOut, cbConnStrOutMax, pcbConnStrOut, fDriverCompletion);
			/* 
				If the connection string contains enough information, and that information is correct, 
				the driver connects to the data source and copies *InConnectionString to *OutConnectionString. 
				If any information is missing or incorrect, the driver takes the same actions as it does 
				when DriverCompletion is SQL_DRIVER_PROMPT, except that if DriverCompletion is 
				SQL_DRIVER_COMPLETE_REQUIRED, the driver disables the controls for any information not 
				required to connect to the data source. 
			*/
			return Error(hDBC, 0, "HYC00", "Not implemented yet");
		case SQL_DRIVER_NOPROMPT:
			WriteToLog("SQLDriverConnect(0x%p, 0x%p, \"%s\", %hi, 0x%p, %hi, 0x%p, SQL_DRIVER_NOPROMPT)", 
				ConnectionHandle, hwnd, szConnStrIn, cbConnStrIn, szConnStrOut, cbConnStrOutMax, pcbConnStrOut, fDriverCompletion);
			/* 
				If the connection string contains enough information, the driver connects to the data 
				source and copies *InConnectionString to *OutConnectionString. Otherwise, the driver 
				returns SQL_ERROR for SQLDriverConnect.
			*/
			break;
		default:
			return Error(hDBC, 0, "HYC00", "Undefined value for fDriverCompletion");
	}
	// szConnStrIn "DSN=JamesTest;UID=DataCurator;PWD=swordfish;"
	char string[1024], *pString = string;
	if (!CopySqlString(pString, sizeof(string), szConnStrIn, cbConnStrIn)) {
			return Error(hDBC, 0, "HYC00", "Unable to copy connection string");
	}
	int length = strlen(pString);
	int end;
	
	if (length < 5 || memcmp(pString, "DSN=", 4)) {
		return Error(hDBC, 0, "HYC00", "Missing 'DSN=' from connection string");
	}
	pString = pString + 4;
	length = length - 4;
	end = 0;
	for (int i = 0; i < length; ++i) {
		if (pString[i] == ';') {
			end = i;
			break;
		}
	}
	if (!end) {
		return Error(hDBC, 0, "HYC00", "Missing ';' at end of DSN part of connection string");
	}
	pString[end] = '\0';
	strcpy_s(hDBC->dataSourceName, sizeof(hDBC->dataSourceName), pString);
	pString[end] = ';';

	pString = pString + end + 1;
	length = length - end - 1;
	if (length < 5 || memcmp(pString, "UID=", 4)) {
		return Error(hDBC, 0, "HYC00", "Missing 'UID=' from connection string");
	}
	pString = pString + 4;
	length = length - 4;
	end = 0;
	for (int i = 0; i < length; ++i) {
		if (pString[i] == ';') {
			end = i;
			break;
		}
	}
	if (!end) {
		return Error(hDBC, 0, "HYC00", "Missing ';=' at end of UID part of connection string");
	}
	pString[end] = '\0';
	strcpy_s(hDBC->gsUserName, sizeof(hDBC->gsUserName), pString);
	pString[end] = ';';

	pString = pString + end + 1;
	length = length - end - 1;
	if (length < 5 || memcmp(pString, "PWD=", 4)) {
		return Error(hDBC, 0, "HYC00", "Missing 'PWD=' from connection string");
	}
	pString = pString + 4;
	length = length - 4;
	end = 0;
	for (int i = 0; i < length; ++i) {
		if (pString[i] == ';') {
			end = i;
			break;
		}
	}
	if (!end) {
		return Error(hDBC, 0, "HYC00", "Missing ';=' at end of PWD part of connection string");
	}
	pString[end] = '\0';
	strcpy_s(hDBC->gsPassword, sizeof(hDBC->gsPassword), pString);
	pString[end] = ';';

	SQLRETURN result = Connect(hDBC);
	if (szConnStrOut) {
		strcpy_s((char *) szConnStrOut, cbConnStrOutMax, (const char *) string);
	}
	if (pcbConnStrOut) {
		*pcbConnStrOut = length;
	}
	return result;
}
