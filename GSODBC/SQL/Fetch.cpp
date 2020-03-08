#include "stdafx.h"

SQLRETURN  SQL_API SQLFetch(
	SQLHSTMT		StatementHandle)
{
	GS_STMT			hStmt = (GS_STMT) StatementHandle;
	GS_DBC			hDBC = hStmt->hDBC;
	GciTravBufType	*travBuffer = Gci_AllocTravBuf(GCI_MIN_TRAV_BUFF_SIZE);
	GciObjRepSType	*objectReports[MAX_COLUMN_COUNT + 1];	// allow for an array to hold the columns
	GciObjRepSType	*primaryObj;
	OopType			*resultArray;
	int				x;

	WriteToLog("SQLFetch(0x%p)", StatementHandle);
	BOOL successFlag = Gci_PerformTraverse(
		hStmt->odbcStatement, 
		"sqlFetch", 
		NULL, 
		0, 
		travBuffer, 
		2);
	Gci_Err(&(hDBC->gciError));
	if (!successFlag) 
		return Error(hDBC, 0, "state", "error in #'sqlFetch'");
	int objectCount = ParseTraversalBuffer(travBuffer, objectReports, sizeof(objectReports));
	primaryObj = objectReports[objectCount - 1];
	if (objectCount == 1 && primaryObj->hdr.objId == OOP_NIL) {
		WriteToLog("\tSQL_NO_DATA");
		return SQL_NO_DATA;
	}
	if (primaryObj->hdr.oclass != OOP_CLASS_ARRAY)
		Error(hStmt, SQL_ERROR, "state", "SQLFetch() didn\'t return an Array");
	int arraySize = (int) primaryObj->hdr._idxSizeBits >> 24;
	resultArray = primaryObj->u.oops;
	for (int i = 0; i < arraySize; ++i) {
		OopType oop = resultArray[i];
		COLUMN_DATA *column = &hStmt->Columns[i];
		switch (column->TargetType) {		//	https://msdn.microsoft.com/en-us/library/ms714556(v=vs.85).aspx
			case SQL_C_CHAR:		//	unsigned char *
				if (oop == OOP_NIL) {
					*(column->StrLen_or_Ind) = SQL_NULL_DATA;
					WriteToLog("\tcolumn %i set to SQL_NULL_DATA", i + 1);
				} else {
					for (int j = 0; j < arraySize; ++j) {
						if (objectReports[j]->hdr.objId == oop) {
							if (objectReports[j]->hdr.oclass != OOP_CLASS_STRING) {
								x = 0;	// cleanup and return error
							}
							int resultSize = objectReports[j]->hdr.valueBuffSize;
							int resultSpace = column->BufferLength;
							int copySize = min(resultSize, resultSpace);
							memcpy_s(column->TargetValuePtr, resultSpace, objectReports[j]->u.bytes, copySize);
							if (resultSize < resultSpace) 
								((char *)column->TargetValuePtr)[resultSize] = '\0';
							*(column->StrLen_or_Ind) = resultSize;
							break;
						}
					}
					WriteToLog("\tcolumn %i set to \'%s\'", i + 1, column->TargetValuePtr);
				}
				break;
			case SQL_C_WCHAR:		//	wchar_t *
				x = 0;
				break;
			case SQL_C_SSHORT:		//	short int
				x = 0;
				break;
			case SQL_C_USHORT:		//	unsigned short int
				x = 0;
				break;
			case SQL_C_SLONG:		//	long int
				x = 0;
				break;
			case SQL_C_ULONG:		//	unsigned long int	(also SQL_C_BOOKMARK)
				x = 0;
				break;
			case SQL_C_FLOAT:		//	float	
				x = 0;
				break;
			case SQL_C_DOUBLE:		//	double
				x = 0;
				break;
			case SQL_C_BIT:	{		//	unsigned char
				char flag = Gci_OopToI64(oop) == 0 ? 0 : 1;
				*((char *) column->TargetValuePtr) = flag;
				*(column->StrLen_or_Ind) = sizeof(char);
				WriteToLog("\tcolumn %i set to %i", i + 1, flag);
				break;
			}
			case SQL_C_STINYINT:	//	signed char
				x = 0;
				break;
			case SQL_C_UTINYINT:	//	unsigned char
				x = 0;
				break;
			case SQL_C_SBIGINT:		//	_int64
				if (GCI_OOP_IS_SMALL_INT(oop)) {
					int64 value = Gci_OopToI64(oop);
					*((int64 *) column->TargetValuePtr) = value;
					*(column->StrLen_or_Ind) = sizeof(value);
					WriteToLog("\tcolumn %i set to %lli", i + 1, value);
				} else {
					Error(hStmt, SQL_ERROR, "state", "SQLFetch() didn\'t return a SmallInteger for column %i", i);
				}
				break;
			case SQL_C_UBIGINT:		//	unsigned _int64
				x = 0;
				break;
			case SQL_C_BINARY:		//	unsigned char * (also SQL_C_VARBOOKMARK)
				x = 0;
				break;
			case SQL_C_TYPE_DATE:	//	struct tagDATE_STRUCT {
				x = 0;
				break;
			case SQL_C_TYPE_TIME:	//	struct tagTIME_STRUCT {
				x = 0;
				break;
			case SQL_C_TYPE_TIMESTAMP:	//	struct tagTIMESTAMP_STRUCT {
				x = 0;
				break;
			case SQL_C_NUMERIC:		//	struct tagSQL_NUMERIC_STRUCT {
				x = 0;
				break;
			case SQL_C_GUID:		//	struct tagSQLGUID {
				x = 0;
				break;
			default:
				x = column->TargetType;
				WriteToLog("\tcolumn %i has unrecognized TargetType of %i", i + 1, column->TargetType);
				break;
		}
	}
	WriteToLog("\tSQL_SUCCESS");
	return SQL_SUCCESS;
}
