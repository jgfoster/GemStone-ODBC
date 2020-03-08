#include "stdafx.h"

SQLRETURN  SQL_API SQLBindCol(
	SQLHSTMT		StatementHandle, 
	SQLUSMALLINT	ColumnNumber, 
	SQLSMALLINT		TargetType, 
	SQLPOINTER		TargetValuePtr, 
	SQLLEN			BufferLength, 
	SQLLEN			*StrLen_or_Ind)
{
	GS_STMT			hStmt	= (GS_STMT) StatementHandle;
	GS_DBC			hDBC	= hStmt->hDBC;
	P_COLUMN_DATA	column	= &(hStmt->Columns[ColumnNumber - 1]);
	
	WriteToLog("SQLBindCol(0x%p, %u, %i, 0x%p, %u, 0x%p)",
		StatementHandle, ColumnNumber, TargetType, TargetValuePtr, BufferLength, StrLen_or_Ind);
	if (MAX_COLUMN_COUNT < ColumnNumber) {
		return Error(hStmt, 0, "state", "exceeded max column count");
	}
	column->ColumnNumber	= ColumnNumber;
	if (!TargetType) {
		return Error(hStmt, 0, "state", "TargetType not defined");
	}
	column->TargetType		= TargetType;
	column->TargetValuePtr	= TargetValuePtr;
	column->BufferLength	= BufferLength;
	if (!StrLen_or_Ind) {
		return Error(hStmt, 0, "state", "StrLen_or_Ind is NULL");
	}
	column->StrLen_or_Ind	= StrLen_or_Ind;
	return Success(hStmt);
}
