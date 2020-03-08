#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <odbcinst.h>
#include <htmlhelp.h>
#include <sqlext.h>
#include <tchar.h>
#include "../resource.h"

#define KEY_DSN				_T("DSN")
#define KEY_StoneHost		_T("StoneHost")
#define KEY_StoneName		_T("StoneName")
#define KEY_GemHost			_T("GemHost")
#define KEY_NetLDI			_T("NetLDI")
#define KEY_GemTask			_T("GemTask")
#define KEY_HostUser		_T("HostUser")
#define KEY_HostPassword	_T("HostPassword")
#define KEY_StoneUser		_T("StoneUser")
#define KEY_StonePassword	_T("StonePassword")
#define KEY_Catalog			_T("Catalog")
#define KEY_Schema			_T("Schema")
#define KEY_LogPath			_T("LogPath")

#define DRIVER_NAME  _T("GemStone/S")
#define PATH_TO_HELP _T("C:\\WINDOWS\\system32\\GemStone ODBC Setup.chm")
