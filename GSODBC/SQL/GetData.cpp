#include "stdafx.h"

SQLRETURN  SQL_API SQLGetData(
	SQLHSTMT		StatementHandle,
	SQLUSMALLINT	ColumnNumber, 
	SQLSMALLINT		TargetType,
	SQLPOINTER		TargetValue, 
	SQLLEN			BufferLength,
	SQLLEN			*StrLen_or_Ind)
{
	GS_STMT				hStmt = (GS_STMT) StatementHandle;
return Error(hStmt, 0, "state", "SQLGetData() not yet implemented!");

#if 0
	GS_DBC				hDBC = hStmt->hDBC;
	OopType				oops[4], oopType;
	BOOL				successFlag;			
	GciTravBufType		*travBuffer = Gci_AllocTravBuf(GCI_MIN_TRAV_BUFF_SIZE);
	GciObjRepSType		*objects[4], *arrayObject, *readLimit, *nextObject, *stringObject;
	int					index = 0, toCopySize;
//	int					arraySize;
	SQLRETURN			sqlResult;
	SQLLEN				valueLength;
	ByteType			*bytes;
	
	WriteToLog("SQLGetData()");
	if (!TargetValue) {
		return Error(hStmt, 0, "state", "SQLGetData(,,,NULL,,)");
	}
	if (!StrLen_or_Ind) {
		return Error(hStmt, 0, "state", "SQLGetData(,,,,,NULL)");
	}
	oops[0] = Gci_I64ToOop((int64) ColumnNumber);
	oops[1] = Gci_I64ToOop((int64) TargetType);
	oops[2] = Gci_I64ToOop((int64) BufferLength);
	successFlag = Gci_PerformTraverse(
		hStmt->odbcStatement, 
		"sqlGetData:_:_:", 
		oops, 
		3, 
		travBuffer, 
		2);
	Gci_Err(&(hDBC->gciError));
	if (!successFlag) {
		Gci_Free(travBuffer);
		return Error(hStmt, 0, "state", "error in #'getData:_:_:'");
	}
	readLimit	= travBuffer->readLimit();
	nextObject	= travBuffer->firstReport();
	while (nextObject != readLimit) {

		oops[index]		= nextObject->hdr.objId;
		objects[index]	= nextObject;
		index			= index + 1;
		nextObject = nextObject->nextReport();
	}
	Gci_ReleaseOops(oops, index);
	arrayObject = objects[index - 1];
	if (OOP_CLASS_ARRAY != arrayObject->hdr.oclass) {
		Gci_Free(travBuffer);
		return Error(hStmt, 0, "state", "#'getData:_:_:' did not return Array");
	}
//	arraySize = arrayObject->hdr.idxSize();

	// (array at: 1) is sqlResult
	oopType = arrayObject->u.oops[0];
	if (!GCI_OOP_IS_SMALL_INT(oopType)) {
		Gci_Free(travBuffer);
		return Error(hStmt, 0, "state", "#'getData:_:_:' did not return a SmallInteger at #1");
	}
	sqlResult = (SQLRETURN) Gci_OopToI32(oopType);
	if (SQL_NO_DATA == sqlResult) {
		return SQL_NO_DATA;
	}
	if (SQL_SUCCESS != sqlResult) {
		return Error(hStmt, sqlResult, "state", "#'getData:_:_:' returned error");
	}

	// (array at: 2) is type (if we are given SQL_C_DEFAULT) otherwise size
	oopType = arrayObject->u.oops[1];
	if (!GCI_OOP_IS_SMALL_INT(oopType)) {
		Gci_Free(travBuffer);
		return Error(hStmt, 0, "state", "#'getData:_:_:' did not return a SmallInteger at #2");
	}
	valueLength = (SQLLEN) Gci_OopToI32(oopType);
	if (SQL_NULL_DATA == valueLength) {
		Gci_Free(travBuffer);
		*StrLen_or_Ind = SQL_NULL_DATA;
		return Success(hStmt);
	}

	// (array at: 3) is actual data
	oopType = arrayObject->u.oops[2];
	if (SQL_INTEGER == TargetType) {
		SQLSMALLINT	sqlType = (SQLSMALLINT) valueLength;
		if (SQL_INTEGER == sqlType) {
			SQLINTEGER data = (SQLINTEGER) Gci_OopToI64(oopType);
			Gci_Free(travBuffer);
			*StrLen_or_Ind = sizeof(SQLINTEGER);
			*( (SQLINTEGER *) TargetValue) = data;
			return Success(hStmt);
		}
		Gci_Free(travBuffer);
		return Error(hStmt, 0, "state", "SQLGetData(,,SQL_INTEGER,,,)");
	}
	if (SQL_C_DEFAULT == TargetType) {
		SQLSMALLINT	sqlType = (SQLSMALLINT) valueLength;
		if (SQL_SMALLINT == sqlType) {
			SQLSMALLINT data = (SQLSMALLINT) Gci_OopToI32(oopType);
			Gci_Free(travBuffer);
			*StrLen_or_Ind = sizeof(SQLSMALLINT);
			*( (SQLSMALLINT *) TargetValue) = data;
			return Success(hStmt);
		}
		if (SQL_INTEGER == sqlType) {
			SQLINTEGER data = (SQLINTEGER) Gci_OopToI64(oopType);
			Gci_Free(travBuffer);
			*StrLen_or_Ind = sizeof(SQLINTEGER);
			*( (SQLINTEGER *) TargetValue) = data;
			return Success(hStmt);
		}
		Gci_Free(travBuffer);
		return Error(hStmt, 0, "state", "SQLGetData(,,SQL_C_DEFAULT,,,)");
	}
	if (SQL_C_CHAR == TargetType) {
		index = 0;
		while (oops[index] != oopType) {
			index = index + 1;
		}
		stringObject = objects[index];
		if (OOP_CLASS_STRING != stringObject->hdr.oclass) {
			Gci_Free(travBuffer);
			return Error(hStmt, 0, "state", "#'getData:_:_:' did not return a String at #3");
		}
		bytes = stringObject->u.bytes;
		toCopySize = min(valueLength, BufferLength - 1);
		memcpy((char *) TargetValue, (const char *) bytes, toCopySize);
		((char *) TargetValue)[toCopySize] = 0;
		*StrLen_or_Ind = valueLength;
		Gci_Free(travBuffer);
		return Success(hStmt);
	}

	Gci_Free(travBuffer);
	return Error(hStmt, 0, "state", "SQLGetData(,,!SQL_C_CHAR,,,)");

#endif
}
