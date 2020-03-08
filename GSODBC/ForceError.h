#pragma once

typedef enum {
	FORCE_ERROR_UNKNOWN = -1,
	FORCE_ERROR_NONE = 0,
	FORCE_ERROR_ALLOC_HANDLE_ENV = 1,
	FORCE_ERROR_ALLOC_HANDLE_DBC = 2,
	FORCE_ERROR_SERVER_NAME_SIZE = 3,
	FORCE_ERROR_NO_DATA_SOURCE = 4,
	FORCE_ERROR_MISSING_PROCEDURE = 5,
	FORCE_ERROR_GCI_INIT = 6,
	FORCE_ERROR_VERSION = 7,
} ForceErrorEnum;

//	Globals
extern LONG	forceError;
