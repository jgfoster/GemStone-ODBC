#include "stdafx.h"

SQLRETURN SQL_API SQLDescribeCol(
	SQLHSTMT       StatementHandle,
	SQLUSMALLINT   ColumnNumber,
	SQLCHAR *      ColumnName,
	SQLSMALLINT    BufferLength,
	SQLSMALLINT *  NameLengthPtr,
	SQLSMALLINT *  DataTypePtr,
	SQLULEN *      ColumnSizePtr,
	SQLSMALLINT *  DecimalDigitsPtr,
	SQLSMALLINT *  NullablePtr )
{
	WriteToLog("SQLDescribeCol(0x%p, %i, 0x%p, %i, 0x%p, 0x%p, 0x%p, 0x%p, 0x%p)", 
		StatementHandle, ColumnNumber, ColumnName, BufferLength, NameLengthPtr, DataTypePtr, ColumnSizePtr, DecimalDigitsPtr, NullablePtr);

	GS_STMT				hStmt = (GS_STMT) StatementHandle;
	GS_DBC				hDBC = hStmt->hDBC;
	BOOL				successFlag;			
	GciTravBufType		*travBuffer = Gci_AllocTravBuf(GCI_MIN_TRAV_BUFF_SIZE);
	GciObjRepSType		*objectReports[2], *primaryObject;
	OopType				args[2], *resultArray = NULL;
	int					bufferSize;

	args[0] = Gci_I32ToOop((int32) ColumnNumber);
	successFlag = Gci_PerformTraverse(
		hStmt->odbcStatement, 
		"sqlDescribeColumn:", 
		args, 
		1, 
		travBuffer, 
		2);
	if (!successFlag) { 
		Gci_Free(travBuffer);
		Gci_Err(&(hDBC->gciError));
		return Error(hStmt, 0, "state", "#'sqlDescribeColumn:' error");
	}
/*
	Answer an Array
		1:	column name
		2:	data type
		3:	column size (in characters)
		4:	decimal digits
		5:	nullable 
	Traversal structure should send element 1 (a String) before the Array.
*/
	int count = ParseTraversalBuffer(travBuffer, objectReports, sizeof(objectReports));
	primaryObject = objectReports[count - 1];
	if (count != 2) 
		return Error(hStmt, 0, "state", "#'sqlDescribeCol' returned %i objects instead of 2", count);
	args[0]	= objectReports[0]->hdr.objId;
	if (objectReports[0]->hdr.oclass != OOP_CLASS_STRING) {
		Gci_ReleaseOops(args, 1);
		Gci_Free(travBuffer);
		return Error(hStmt, 0, "state", "#'sqlDescribeCol:' did not return a String");
	}
	*NameLengthPtr = objectReports[0]->hdr.valueBuffSize;
	if (ColumnName != NULL) {
		int	length = min(*NameLengthPtr, BufferLength - 1);
		memcpy(ColumnName, objectReports[0]->u.bytes, length);
		ColumnName[length] = '\0';
	}

	args[1]	= objectReports[1]->hdr.objId;
	if (objectReports[1]->hdr.oclass != OOP_CLASS_ARRAY) {
		Gci_ReleaseOops(args, 2);
		Gci_Free(travBuffer);
		return Error(hStmt, 0, "state", "#'sqlDescribeColumn:' did not return a String");
	}
	bufferSize = objectReports[1]->hdr.valueBuffSize;
	int	arraySize = (int) objectReports[1]->hdr._idxSizeBits >> 24;
	resultArray = objectReports[1]->u.oops;
	if (arraySize != 5 || bufferSize != 5 * 8) {
		Gci_ReleaseOops(args, 2);
		Gci_ReleaseOops(resultArray, arraySize);
		Gci_Free(travBuffer);
		return Error(hStmt, 0, "state", "#'sqlDescribeColumn:' did not return five objects in Array");
	}
	SQLSMALLINT dataType		= (SQLSMALLINT) Gci_OopToI32(resultArray[1]);
	SQLULEN		columnSize		= (SQLULEN)		Gci_OopToI32(resultArray[2]);
	SQLSMALLINT	decimalDigits	= (SQLSMALLINT) Gci_OopToI32(resultArray[3]);
	SQLSMALLINT nullable		= (SQLSMALLINT) Gci_OopToI32(resultArray[4]);
	if (DataTypePtr)		*DataTypePtr		= dataType;
	if (ColumnSizePtr)		*ColumnSizePtr		= columnSize;
	if (DecimalDigitsPtr)	*DecimalDigitsPtr	= decimalDigits;
	if (NullablePtr)		*NullablePtr		= nullable;
	Gci_ReleaseOops(args, 2);
	Gci_Free(travBuffer);
	WriteToLog("\t\"%s\", %i, %u, %i, %i", ColumnName, dataType, columnSize, decimalDigits, nullable);
	return Success(hStmt);
}
