// GSODBC.cpp : These are primarily the related to the install functions; the driver functions are separate
//

#include "stdafx.h"

PCSTR		errorState = "HYC00";
PCSTR		errorMessage = "Not implemented yet";

#define KEY_DSN				"DSN"
#define KEY_GsVersion		"GsVersion"
#define KEY_StoneHost		"StoneHost"
#define KEY_StoneName		"StoneName"
#define KEY_GemHost			"GemHost"
#define KEY_NetLDI			"NetLDI"
#define KEY_GemTask			"GemTask"
#define KEY_Catalog			"Catalog"
#define KEY_Schema			"Schema"
#define KEY_LogPath			"LogPath"

#define DRIVER_NAME			"GemStone/S"

extern	HMODULE		hDLL;
GS_CONNECTION		gsData;	//	we don't need all of it but the DSN portion

BOOL SQL_API		ConfigDriver(HWND, WORD, LPCSTR, LPCSTR, LPSTR, WORD, WORD *);
BOOL SQL_API		ConfigDSN(HWND, WORD, LPCSTR, LPCSTR);
BOOL				DialogCommand(HWND, WPARAM, LPARAM);
INT_PTR CALLBACK	DialogProc(HWND, UINT, WPARAM, LPARAM);
BOOL				InitDialog(HWND);
VOID				InitSupportedFunctions();
VOID				ParseAttributes(LPCSTR);
BOOL				PopupHelp(HWND, LPHELPINFO);
BOOL				ReadDSN(GS_DBC);
VOID				SaveDialogInfo(HWND);
BOOL				SaveLogFile(HWND);
BOOL				WriteDSN();

BOOL SQL_API ConfigDriver(
	HWND	hwndParent,
	WORD	fRequest,
	LPCSTR	lpszDriver,
	LPCSTR	lpszArgs,
	LPSTR	lpszMsg,
	WORD	cbMsgMax,
	WORD *	pcbMsgOut)
{
	switch (fRequest) {
		case ODBC_INSTALL_DRIVER:
			WriteToLog("ConfigDriver(,ODBC_INSTALL_DRIVER,,,,,)");
			return TRUE;
		case ODBC_REMOVE_DRIVER:
			WriteToLog("ConfigDriver(,ODBC_REMOVE_DRIVER,,,,,)");
			return TRUE;
		case ODBC_CONFIG_DRIVER:
			WriteToLog("ConfigDriver(,ODBC_CONFIG_DRIVER,,,,,)");
			return TRUE;
		default:
			WriteToLog("ConfigDriver(,???,,,,,)");
			SQLPostInstallerError(
				(DWORD) ODBC_ERROR_INVALID_REQUEST_TYPE,
				"Unknown request");
			return FALSE;
	}
}

BOOL SQL_API ConfigDSN(
	HWND	hwndParent,
	WORD	fRequest,
	LPCSTR	lpszDriver,
	LPCSTR	lpszAttributes)
{
	INT_PTR			result;

	ParseAttributes(lpszAttributes);
	switch (fRequest) {
		case ODBC_ADD_DSN:
		case ODBC_ADD_SYS_DSN:
			WriteToLog("ConfigDSN(0x%p, ODBC_ADD_*_DSN, 0x%p, 0x%p)", hwndParent, lpszDriver, lpszAttributes);
			result = DialogBox(
				hDLL, 
				MAKEINTRESOURCE(IDD_CONFIGURE_DSN), 
				hwndParent,
				(DLGPROC)DialogProc);
			if (IDCANCEL == result) return FALSE;
			if (!SQLWriteDSNToIni(gsData.dataSourceName, DRIVER_NAME)) return FALSE;
			return WriteDSN();

		case ODBC_CONFIG_DSN:
		case ODBC_CONFIG_SYS_DSN:
			WriteToLog("ConfigDSN(0x%p, ODBC_CONFIG_*_DSN, 0x%p, 0x%p)", hwndParent, lpszDriver, lpszAttributes);
			ReadDSN(&gsData);
			result = DialogBox(
				hDLL, 
				MAKEINTRESOURCE(IDD_CONFIGURE_DSN), 
				hwndParent,
				(DLGPROC)DialogProc);
			if (IDCANCEL == result) return FALSE;
			return WriteDSN();

		case ODBC_REMOVE_DSN:
		case ODBC_REMOVE_SYS_DSN:
			WriteToLog("ConfigDSN(0x%p, ODBC_REMOVE_*_DSN, 0x%p, 0x%p)", hwndParent, lpszDriver, lpszAttributes);
			return SQLRemoveDSNFromIni(gsData.dataSourceName);

		case ODBC_REMOVE_DEFAULT_DSN:
			WriteToLog("ConfigDSN(0x%p, ODBC_REMOVE_DEFAULT_DSN, 0x%p, 0x%p)", hwndParent, lpszDriver, lpszAttributes);
			WriteToLog("ConfigDSN(,,,)");
			return FALSE;

		default:
			WriteToLog("ConfigDSN(,???,,)");
			return FALSE;
	}
}

BOOL DialogCommand(
	HWND		hwndDlg,
	WPARAM		wParam,
	LPARAM		lParam)
{
	switch (LOWORD(wParam)) { 
		case IDOK: 
			SaveDialogInfo(hwndDlg);
			// Fall through; return ID of button that prompted close. 
		case IDCANCEL: 
			EndDialog(hwndDlg, wParam); 
			return TRUE;
		case IDC_LOG_FILE_LOOKUP:
			return SaveLogFile(hwndDlg);
		default:
			return FALSE;
	}
}

INT_PTR CALLBACK DialogProc(
	HWND		hwndDlg,
	UINT		uMsg,
	WPARAM		wParam,
	LPARAM		lParam)
{
	switch (uMsg) { 
		case WM_INITDIALOG:
			return InitDialog(hwndDlg);
		case WM_COMMAND:
			return DialogCommand(hwndDlg, wParam, lParam);
		case WM_HELP:
			return PopupHelp(hwndDlg, (LPHELPINFO) lParam);
		default:
			return FALSE;
	} 
	return FALSE; 
}

BOOL InitDialog(
	HWND		hwndDlg)
{
	WriteToLog("InitDialog(0x%p)", hwndDlg);
	HWND hVersion = GetDlgItem(hwndDlg, IDC_GS_VERSION);
	ComboBox_AddItemData(hVersion, "3.3.0");
	ComboBox_SelectString(hVersion, -1, gsData.gsVersion);

	SetDlgItemText(hwndDlg, IDC_NAME,			gsData.dataSourceName	);
	SetDlgItemText(hwndDlg, IDC_STONE_HOST,		gsData.stoneHost		);
	SetDlgItemText(hwndDlg, IDC_STONE_NAME,		gsData.stoneName		);
	SetDlgItemText(hwndDlg, IDC_GEM_HOST,		gsData.gemHost			);
	SetDlgItemText(hwndDlg, IDC_GEM_NETLDI,		gsData.gemNetLDI		);
	SetDlgItemText(hwndDlg, IDC_GEM_TASK,		gsData.gemTask			);
	SetDlgItemText(hwndDlg, IDC_CATALOG,		gsData.catalog			);
	SetDlgItemText(hwndDlg, IDC_SCHEMA,			gsData.schema			);
	SetDlgItemText(hwndDlg, IDC_LOG_FILE,		gsData.logFilePath		);
	if ('\0' != gsData.dataSourceName[0]) EnableWindow(GetDlgItem(hwndDlg, IDC_NAME),   FALSE);

	return TRUE;
}

void MySetValue(
	char *		field,
	size_t		fieldSize,
	LPCSTR		association, 
	LPCSTR		key)
{
	size_t	keySize = strlen(key);
	size_t	index = strchr(association, '=') - association;
	if (index == keySize && ! memcmp(association, key, keySize)) {
		strcpy_s(field, fieldSize, association + keySize + 1);
	}
}

#define SetValue(field, key) MySetValue(gsData.field, sizeof(gsData.field), association, key)
#define SetDefault(field, value) if (gsData.field[0] == '\0') strncpy_s(gsData.field, DSN_STRING_SIZE, value, _TRUNCATE);

VOID ParseAttributes(
	LPCSTR lpszAttributes)
{
	LPCSTR		association = lpszAttributes;

	gsData.dataSourceName	[0] = '\0';
	gsData.gsVersion		[0] = '\0';
	gsData.stoneHost		[0] = '\0';
	gsData.stoneName		[0] = '\0';
	gsData.gemHost			[0] = '\0';
	gsData.gemNetLDI		[0] = '\0';
	gsData.gemTask			[0] = '\0';
	gsData.catalog			[0] = '\0';
	gsData.schema			[0] = '\0';
	gsData.logFilePath		[0] = '\0';

	while (0 < association[0]) {
		SetValue(dataSourceName,	KEY_DSN				);
		SetValue(gsVersion,			KEY_GsVersion		);
		SetValue(stoneHost,			KEY_StoneHost		);
		SetValue(stoneName,			KEY_StoneName		);
		SetValue(gemHost,			KEY_GemHost			);
		SetValue(gemNetLDI,			KEY_NetLDI			);
		SetValue(gemTask,			KEY_GemTask			);
		SetValue(catalog,			KEY_Catalog			);
		SetValue(schema,			KEY_Schema			);
		SetValue(logFilePath,		KEY_LogPath			);
		association = association + strlen(association) + 1;
	}
	SetDefault(gsVersion	, "3.3"				);
	SetDefault(stoneHost	, "localhost"		);
	SetDefault(stoneName	, "gs64stone"		);
	SetDefault(gemTask		, "gemnetobject"	);
}

BOOL PopupHelp(
	HWND		hwndDlg,
	LPHELPINFO	helpInfo)
{
/*
	HH_POPUP	helpPopup;

	helpPopup.cbStruct			= sizeof(HH_POPUP);
	helpPopup.hinst				= NULL;
	helpPopup.idString			= (UINT) helpInfo->dwContextId;
	helpPopup.pszText			= NULL;
	helpPopup.pt				= helpInfo->MousePos;
	helpPopup.clrForeground		= -1;
	helpPopup.clrBackground		= -1;
	helpPopup.rcMargins.bottom	= -1;
	helpPopup.rcMargins.left	= -1;
	helpPopup.rcMargins.right	= -1;
	helpPopup.rcMargins.top		= -1;
	helpPopup.pszFont			= NULL;

	HtmlHelp(hwndDlg, PATH_TO_HELP _T("::/Popup.txt"), HH_DISPLAY_TEXT_POPUP, (DWORD_PTR) &helpPopup);
*/
	return TRUE;
}

#define ReadFieldDSN(key, value) SQLGetPrivateProfileString(hDBC->dataSourceName, key, "", hDBC->value, sizeof(hDBC->value), "ODBC.INI")

BOOL ReadDSN(
	GS_DBC hDBC)
{
	int count = 0;
	count = count + ReadFieldDSN(KEY_StoneHost		, stoneHost		);
	count = count + ReadFieldDSN(KEY_GsVersion		, gsVersion		);
	count = count + ReadFieldDSN(KEY_StoneName		, stoneName		);
	count = count + ReadFieldDSN(KEY_GemHost		, gemHost		);
	count = count + ReadFieldDSN(KEY_NetLDI			, gemNetLDI		);
	count = count + ReadFieldDSN(KEY_GemTask		, gemTask		);
	count = count + ReadFieldDSN(KEY_Catalog		, catalog		);
	count = count + ReadFieldDSN(KEY_Schema			, schema		);
	count = count + ReadFieldDSN(KEY_LogPath		, logFilePath	);
	return (0 < count);
}

VOID SaveDialogInfo(
	HWND		hwndDlg)
{
	WriteToLog("SaveDialogInfo(0x%p)", hwndDlg);
	GetDlgItemText(hwndDlg, IDC_NAME,			gsData.dataSourceName,	sizeof(gsData.dataSourceName)	);
	GetDlgItemText(hwndDlg, IDC_GS_VERSION,		gsData.gsVersion,		sizeof(gsData.gsVersion)		);
	GetDlgItemText(hwndDlg, IDC_STONE_HOST,		gsData.stoneHost,		sizeof(gsData.stoneHost)		);
	GetDlgItemText(hwndDlg, IDC_STONE_NAME,		gsData.stoneName,		sizeof(gsData.stoneName)		);
	GetDlgItemText(hwndDlg, IDC_GEM_HOST,		gsData.gemHost,			sizeof(gsData.gemHost)			);
	GetDlgItemText(hwndDlg, IDC_GEM_NETLDI,		gsData.gemNetLDI,		sizeof(gsData.gemNetLDI)		);
	GetDlgItemText(hwndDlg, IDC_GEM_TASK,		gsData.gemTask,			sizeof(gsData.gemTask)			);
	GetDlgItemText(hwndDlg, IDC_CATALOG,		gsData.catalog,			sizeof(gsData.catalog)			);
	GetDlgItemText(hwndDlg, IDC_SCHEMA,			gsData.schema,			sizeof(gsData.schema)			);
	GetDlgItemText(hwndDlg, IDC_LOG_FILE,		gsData.logFilePath,		sizeof(gsData.logFilePath)		);
}

BOOL SaveLogFile(
	HWND		hwndDlg)
{
	OPENFILENAMEA	ofn;

	ofn.lStructSize			= sizeof (OPENFILENAME);
	ofn.hwndOwner			= hwndDlg;
	ofn.hInstance			= NULL;
	ofn.lpstrFilter			= "Log Files (*.log)\0*.log\0All Files (*.*)\0*.*\0\0";
	ofn.lpstrCustomFilter	= NULL;
	ofn.nMaxCustFilter		= 0;
	ofn.nFilterIndex		= 1;
	ofn.lpstrFile			= gsData.logFilePath;
	ofn.nMaxFile			= sizeof(gsData.logFilePath);
	ofn.lpstrFileTitle		= NULL;
	ofn.nMaxFileTitle		= 0;
	ofn.lpstrInitialDir		= "";
	ofn.lpstrTitle			= "GemStone/S ODBC ";
	ofn.Flags				= 0;
	ofn.nFileOffset			= 0;
	ofn.nFileExtension		= 0;
	ofn.lpstrDefExt			= "log";
	ofn.lCustData			= 0;
	ofn.lpfnHook			= NULL;
	ofn.lpTemplateName		= "";

	if (GetSaveFileName(&ofn)) {
		SetDlgItemText(hwndDlg, IDC_LOG_FILE, gsData.logFilePath);
	}
	return TRUE;
}

#define WriteFieldDSN(key, value) if (!SQLWritePrivateProfileString(gsData.dataSourceName, key, gsData.value, "ODBC.INI")) return FALSE
BOOL WriteDSN()
{
	WriteToLog("WriteDSN()");
	WriteFieldDSN(KEY_StoneHost		, stoneHost		);
	WriteFieldDSN(KEY_GsVersion		, gsVersion		);
	WriteFieldDSN(KEY_StoneName		, stoneName		);
	WriteFieldDSN(KEY_GemHost		, gemHost		);
	WriteFieldDSN(KEY_NetLDI		, gemNetLDI		);
	WriteFieldDSN(KEY_GemTask		, gemTask		);
	WriteFieldDSN(KEY_Catalog		, catalog		);
	WriteFieldDSN(KEY_Schema		, schema		);
	WriteFieldDSN(KEY_LogPath		, logFilePath	);
	return TRUE;
}

