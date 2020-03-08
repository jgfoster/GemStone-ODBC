#pragma once

#include "GCI.h"

#define int32 long
#define	BASIC_STRING_MAX			100
#define DSN_STRING_SIZE				 32

#define MAX_BINARY_LITERAL_LEN		128
#define	MAX_CATALOG_NAME_LEN		128
#define	MAX_CHAR_LITERAL_LEN		128
#define	MAX_COLUMN_COUNT			128
#define MAX_COLUMN_NAME_LEN			 64
#define MAX_COLUMNS_IN_GROUP_BY		  8
#define MAX_COLUMNS_IN_INDEX		  8
#define MAX_COLUMNS_IN_ORDER_BY		  8
#define MAX_COLUMNS_IN_SELECT		 64
#define MAX_COLUMNS_IN_TABLE		 64
#define MAX_CURSOR_NAME_LEN			 64
#define MAX_USER_NAME_LEN			 64
#define MAX_IDENTIFIER_LEN			 64
#define MAX_INDEX_SIZE				  8
#define MAX_PROCEDURE_NAME_LEN		 64
#define MAX_ROW_SIZE				 64
#define MAX_ROW_SIZE_INCLUDES_LONG	  0
#define MAX_SCHEMA_NAME_LEN			 64
#define MAX_STATEMENT_LEN		   1024
#define MAX_TABLE_NAME_LEN			 64
#define MAX_TABLES_IN_SELECT		 16

#define BUFFER_SIZE_ERROR		"HY090"
#define CONNECTION_ERROR		"08001"
#define AUTHORIZATION_ERROR		"28000"
#define GS_DRIVER_ODBC_VER		"03.00"
#define GS_DRIVER_VER			"00.01.0000"

#define	ClearColumnData(hStmt)	memset(hStmt->Columns, 0, sizeof(COLUMN_DATA) * MAX_COLUMN_COUNT)
#define	ForceError(errorCode)	(errorCode == forceError)

typedef struct {							//	used as the first element of several structures
	DWORD code; 
	PCSTR state; 
	PCSTR message;
} GS_ERROR, *GS_ERROR_P; 

typedef struct {
	GS_ERROR	error;						// must be first (see Error() in utilities.cpp)
	DWORD		ODBC_Version;
} GS_ENVIRONMENT, *GS_ENV;

typedef struct {
	GS_ERROR	error;						// must be first (see Error() in utilities.cpp)
	GS_ENV		hEnv;
	CHAR		errorString		[512];
	CHAR		dataSourceName	[SQL_MAX_DSN_LENGTH];
	CHAR		gsUserName		[DSN_STRING_SIZE];
	CHAR		gsPassword		[DSN_STRING_SIZE];
	CHAR		gsVersion		[DSN_STRING_SIZE];
	CHAR		stoneHost		[DSN_STRING_SIZE];
	CHAR		stoneName		[DSN_STRING_SIZE];
	CHAR		gemHost			[DSN_STRING_SIZE];
	CHAR		gemNetLDI		[DSN_STRING_SIZE];
	CHAR		gemTask			[DSN_STRING_SIZE];
	CHAR		catalog			[DSN_STRING_SIZE];
	CHAR		schema			[DSN_STRING_SIZE];
	CHAR		logFilePath		[FILENAME_MAX + 1];
	WORD		sessionID;
	OopType		odbcServer;
	GciErrSType	gciError;
	//	Attributes set by SQLSetConnectAttr()
	SQLUINTEGER	accessMode;		//	SQL_MODE_READ_ONLY or SQL_MODE_READ_ONLY
	SQLULEN		asyncEnabled;	//	SQL_ASYNC_ENABLE_OFF or SQL_ASYNC_ENABLE_ON

	SQLUINTEGER loginTimeout;
	HWND		hParentWindow;
} GS_CONNECTION, *GS_DBC;

typedef struct {
	SQLUSMALLINT	ColumnNumber;
	SQLSMALLINT		TargetType;
	SQLPOINTER		TargetValuePtr;
	SQLLEN			BufferLength;
	SQLLEN			*StrLen_or_Ind;
} COLUMN_DATA, *P_COLUMN_DATA;

typedef struct {
	SDWORD	Type;
	DWORD	Size;
	CHAR	Name[1];
} ATTRIBUTE_DATA, *P_ATTRIBUTE_DATA;

typedef struct {
	DWORD				Version;
	DWORD				ColumnCount;
	DWORD				RowCount;
	P_ATTRIBUTE_DATA	Attributes[1];
} RELATION_SCHEMA, *P_RELATION_SCHEMA;

typedef struct {
	GS_ERROR			error;				// must be first (see Error() in utilities.cpp)
	GS_DBC				hDBC;
	PVOID				impRowDesc;
	PVOID				impParamDesc;
	PVOID				appRowDesc;
	PVOID				appParamDesc;

	OopType				odbcStatement;
	COLUMN_DATA			Columns[MAX_COLUMN_COUNT];
	P_RELATION_SCHEMA	RelationSchema;
	SQLUSMALLINT *		pRowStatus;
	SQLUINTEGER			cursorType;
} GS_STATEMENT, *GS_STMT;

typedef struct {
	GS_ERROR		error;					// must be first (see Error() in utilities.cpp)
	GS_STMT			hStmt;
	DWORD			data;
} GS_DESCRIPTOR, *GS_DESC;



//	utilities.c
VOID		CopyGciError	(GS_DBC	hDBC);
BOOL		CopySqlString	(CHAR *destination, size_t destinationSize, SQLCHAR *source, size_t sourceSize);
SQLRETURN	Error			(PVOID handle, DWORD ErrorCode, PCSTR errorState, PCSTR errorMessage, ...);
VOID		FindLogFile		(VOID);
SQLRETURN	Success			(PVOID handle);
VOID		WriteToLog		(PCSTR string, ...);
VOID		SaveHinstance	(HINSTANCE myInstance);
HINSTANCE	GetHinstance	(VOID);
int			ParseTraversalBuffer(GciTravBufType	*, GciObjRepSType *[], int);

SQLRETURN	LoadGciLibrary	(GS_DBC	hDBC, const char *);

//	Freehandle.c
SQLRETURN FreeStatement		(GS_STMT hStmt);
