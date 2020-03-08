#include "stdafx.h"

SQLRETURN  SQL_API SQLFreeStmt(
     SQLHSTMT		StatementHandle,
     SQLUSMALLINT	Option)
{
	GS_STMT			hStmt = (GS_STMT) StatementHandle;

	switch (Option) 
	{
		case SQL_CLOSE:			//	Closes the cursor associated with StatementHandle (if one was defined) 
								//	and discards all pending results. The application can reopen this cursor 
								//	later by executing a SELECT statement again with the same or different 
								//	parameter values. If no cursor is open, this option has no effect for 
								//	the application. SQLCloseCursor can also be called to close a cursor. 
								//	For more information, see Closing the Cursor. 
			WriteToLog("SQLFreeStmt(0x%p, SQL_CLOSE)", StatementHandle);
			return Success(hStmt);
			break;
		case SQL_DROP:			//	This option is deprecated. 
								//	A call to SQLFreeStmt with an Option of SQL_DROP is mapped in the Driver Manager to SQLFreeHandle. 
			WriteToLog("SQLFreeStmt(0x%p, SQL_DROP)", StatementHandle);
			break;
		case SQL_UNBIND:		//	Sets the SQL_DESC_COUNT field of the ARD to 0, 
								//	releasing all column buffers bound by SQLBindCol for the given StatementHandle. 
								//	This does not unbind the bookmark column; to do that, 
								//	the SQL_DESC_DATA_PTR field of the ARD for the bookmark column is set to NULL. 
								//	Note that if this operation is performed on an explicitly allocated descriptor 
								//	that is shared by more than one statement, the operation will affect the bindings 
								//	of all statements that share the descriptor. 
								//	For more information, see Overview of Retrieving Results (Basic). 
			WriteToLog("SQLFreeStmt(0x%p, SQL_UNBIND)", StatementHandle);
			ClearColumnData(hStmt);
			return Success(hStmt);
		case SQL_RESET_PARAMS:	//	Sets the SQL_DESC_COUNT field of the APD to 0, 
								//	releasing all parameter buffers set by SQLBindParameter for the given StatementHandle. 
								//	If this operation is performed on an explicitly allocated descriptor that is shared 
								//	by more than one statement, this operation will affect the bindings of all the statements 
								//	that share the descriptor. For more information, see Binding Parameters. 
			WriteToLog("SQLFreeStmt(0x%p, SQL_RESET_PARAMS)", StatementHandle);
			break;
	}
	return Error(StatementHandle, 0, "errorState", "errorMessage");
};
