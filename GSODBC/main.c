#include "setup.h"
#include "ReadDSN.h"

HINSTANCE	hinst;
DataDSN		data;

BOOL APIENTRY DllMain( 
	IN HINSTANCE	hDllHandle, 
	IN DWORD		ul_reason_for_call, 
	IN LPVOID		lpReserved)
{
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:	// 1
			DisableThreadLibraryCalls( hDllHandle );
			hinst = hDllHandle;
			return TRUE;
		case DLL_PROCESS_DETACH:	// 0
			hinst = NULL;
			return TRUE;
		case DLL_THREAD_ATTACH:		// 2
		case DLL_THREAD_DETACH:		// 3
		default:
			return TRUE;
	}
}

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
			return TRUE;
		case ODBC_REMOVE_DRIVER:
			return TRUE;
		case ODBC_CONFIG_DRIVER:
			return TRUE;
		default:
			SQLPostInstallerError(
				(DWORD) ODBC_ERROR_INVALID_REQUEST_TYPE,
				_T("Unknown request"));
			return FALSE;
	}
}

void SaveDialogInfo(
	HWND		hwndDlg)
{
	GetDlgItemText(hwndDlg, IDC_NAME,			data.dataSourceName,	sizeof(data.dataSourceName)	);
	GetDlgItemText(hwndDlg, IDC_STONE_HOST,		data.stoneHost,			sizeof(data.stoneHost)		);
	GetDlgItemText(hwndDlg, IDC_STONE_NAME,		data.stoneName,			sizeof(data.stoneName)		);
	GetDlgItemText(hwndDlg, IDC_GEM_HOST,		data.gemHost,			sizeof(data.gemHost)		);
	GetDlgItemText(hwndDlg, IDC_GEM_NETLDI,		data.gemNetLDI,			sizeof(data.gemNetLDI)		);
	GetDlgItemText(hwndDlg, IDC_GEM_TASK,		data.gemTask,			sizeof(data.gemTask)		);
	GetDlgItemText(hwndDlg, IDC_HOST_USER,		data.hostUserID,		sizeof(data.hostUserID)		);
	GetDlgItemText(hwndDlg, IDC_HOST_PASSWORD,	data.hostPassword,		sizeof(data.hostPassword)	);
	GetDlgItemText(hwndDlg, IDC_GS_USER,		data.gsUserID,			sizeof(data.gsUserID)		);
	GetDlgItemText(hwndDlg, IDC_GS_PASSWORD,	data.gsPassword,		sizeof(data.gsPassword)		);
	GetDlgItemText(hwndDlg, IDC_CATALOG,		data.catalog,			sizeof(data.catalog)		);
	GetDlgItemText(hwndDlg, IDC_SCHEMA,			data.schema,			sizeof(data.schema)			);
	GetDlgItemText(hwndDlg, IDC_LOG_FILE,		data.logFilePath,		sizeof(data.logFilePath)	);
}

BOOL InitDialog(
	HWND		hwndDlg)
{
	SetDlgItemText(hwndDlg, IDC_NAME,			data.dataSourceName	);
	SetDlgItemText(hwndDlg, IDC_STONE_HOST,		data.stoneHost		);
	SetDlgItemText(hwndDlg, IDC_STONE_NAME,		data.stoneName		);
	SetDlgItemText(hwndDlg, IDC_GEM_HOST,		data.gemHost		);
	SetDlgItemText(hwndDlg, IDC_GEM_NETLDI,		data.gemNetLDI		);
	SetDlgItemText(hwndDlg, IDC_GEM_TASK,		data.gemTask		);
	SetDlgItemText(hwndDlg, IDC_HOST_USER,		data.hostUserID		);
	SetDlgItemText(hwndDlg, IDC_HOST_PASSWORD,	data.hostPassword	);
	SetDlgItemText(hwndDlg, IDC_GS_USER,		data.gsUserID		);
	SetDlgItemText(hwndDlg, IDC_GS_PASSWORD,	data.gsPassword		);
	SetDlgItemText(hwndDlg, IDC_CATALOG,		data.catalog		);
	SetDlgItemText(hwndDlg, IDC_SCHEMA,			data.schema			);
	SetDlgItemText(hwndDlg, IDC_LOG_FILE,		data.logFilePath	);
	CheckRadioButton(hwndDlg, IDC_LINKED, IDC_REMOTE, IDC_REMOTE);
	if ('\0' != data.dataSourceName[0]) EnableWindow(GetDlgItem(hwndDlg, IDC_NAME),   FALSE);
	return TRUE;
}

/* 
BOOL PopupHelp(
	HWND		hwndDlg,
	LPHELPINFO	helpInfo)
{
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
	return TRUE;
}
*/

BOOL EnableGemFields(
	HWND		hwndDlg,
	BOOL		bFlag)
{
	EnableWindow(GetDlgItem(hwndDlg, IDC_GEM_HOST),   bFlag);
	EnableWindow(GetDlgItem(hwndDlg, IDC_GEM_NETLDI), bFlag);
	EnableWindow(GetDlgItem(hwndDlg, IDC_GEM_TASK),   bFlag);
	return TRUE;
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
	ofn.lpstrFile			= data.logFilePath;
	ofn.nMaxFile			= sizeof(data.logFilePath);
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
		SetDlgItemText(hwndDlg, IDC_LOG_FILE, data.logFilePath);
	}
	return TRUE;
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
		case IDC_LINKED:
			return EnableGemFields(hwndDlg, FALSE);
		case IDC_REMOTE:
			return EnableGemFields(hwndDlg, TRUE);
		case IDC_HELP_BUTTON:
			//	HtmlHelp(hwndDlg, PATH_TO_HELP, HH_DISPLAY_TOPIC, (DWORD_PTR) NULL);
			return FALSE;	//	TRUE;
		case IDC_LOOKUP_LOG_FILE:
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
			return FALSE; // PopupHelp(hwndDlg, (LPHELPINFO) lParam);
		default:
			return FALSE;
	} 
	return FALSE; 
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

#define SetValue(field, key) MySetValue(data.field, sizeof(data.field), association, key)
void ParseAttributes(
	LPCSTR lpszAttributes)
{
	LPCSTR		association = lpszAttributes;

	data.dataSourceName	[0] = '\0';
	data.stoneHost		[0] = '\0';
	data.stoneName		[0] = '\0';
	data.gemHost		[0] = '\0';
	data.gemNetLDI		[0] = '\0';
	data.gemTask		[0] = '\0';
	data.hostUserID		[0] = '\0';
	data.hostPassword	[0] = '\0';
	data.gsUserID		[0] = '\0';
	data.gsPassword		[0] = '\0';
	data.catalog		[0] = '\0';
	data.schema			[0] = '\0';
	data.logFilePath	[0] = '\0';

	while (0 < association[0]) {
		SetValue(dataSourceName,	KEY_DSN				);
		SetValue(stoneHost,			KEY_StoneHost		);
		SetValue(stoneName,			KEY_StoneName		);
		SetValue(gemHost,			KEY_GemHost			);
		SetValue(gemNetLDI,			KEY_NetLDI			);
		SetValue(gemTask,			KEY_GemTask			);
		SetValue(hostUserID,		KEY_HostUser		);
		SetValue(hostPassword,		KEY_HostPassword	);
		SetValue(gsUserID,			KEY_StoneUser		);
		SetValue(gsPassword,		KEY_StonePassword	);
		SetValue(catalog,			KEY_Catalog			);
		SetValue(schema,			KEY_Schema			);
		SetValue(logFilePath,		KEY_LogPath			);
		association = association + strlen(association) + 1;
	}
}

#define WriteFieldDSN(key, value) if (!SQLWritePrivateProfileString(data.dataSourceName, key, data.value, _T("ODBC.INI"))) return FALSE
BOOL WriteDSN()
{
	WriteFieldDSN(KEY_StoneHost		, stoneHost		);
	WriteFieldDSN(KEY_StoneName		, stoneName		);
	WriteFieldDSN(KEY_GemHost		, gemHost		);
	WriteFieldDSN(KEY_NetLDI		, gemNetLDI		);
	WriteFieldDSN(KEY_GemTask		, gemTask		);
	WriteFieldDSN(KEY_HostUser		, hostUserID	);
	WriteFieldDSN(KEY_HostPassword	, hostPassword	);
	WriteFieldDSN(KEY_StoneUser		, gsUserID		);
	WriteFieldDSN(KEY_StonePassword	, gsPassword	);
	WriteFieldDSN(KEY_Catalog		, catalog		);
	WriteFieldDSN(KEY_Schema		, schema		);
	WriteFieldDSN(KEY_LogPath		, logFilePath	);
	return TRUE;
}

BOOL SQL_API ConfigDSN(
	HWND	hwndParent,
	WORD	fRequest,
	LPCSTR	lpszDriver,
	LPCSTR	lpszAttributes)
{
	INT_PTR		result;

	ParseAttributes(lpszAttributes);
	switch (fRequest) {
		case ODBC_ADD_DSN:
		case ODBC_ADD_SYS_DSN:
			result = DialogBox(
				hinst, 
				MAKEINTRESOURCE(IDD_CONFIGURE_DSN), 
				hwndParent,
				(DLGPROC)DialogProc);
			if (IDCANCEL == result) return FALSE;
			if (!SQLWriteDSNToIni(data.dataSourceName, DRIVER_NAME)) return FALSE;
			return WriteDSN();

		case ODBC_CONFIG_DSN:
		case ODBC_CONFIG_SYS_DSN:
			ReadDSN();
			result = DialogBox(
				hinst, 
				MAKEINTRESOURCE(IDD_CONFIGURE_DSN), 
				hwndParent,
				(DLGPROC)DialogProc);
			if (IDCANCEL == result) return FALSE;
			return WriteDSN();

		case ODBC_REMOVE_DSN:
		case ODBC_REMOVE_SYS_DSN:
			return SQLRemoveDSNFromIni(data.dataSourceName);

		case ODBC_REMOVE_DEFAULT_DSN:
		default:
			return FALSE;
	}
}
