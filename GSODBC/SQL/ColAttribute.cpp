#include "stdafx.h"

SQLRETURN SQL_API SQLColAttribute(
     SQLHSTMT		StatementHandle,
     SQLUSMALLINT	ColumnNumber,
     SQLUSMALLINT	FieldIdentifier,
     SQLPOINTER		CharacterAttributePtr,
     SQLSMALLINT	BufferLength,
     SQLSMALLINT *	StringLengthPtr,
     SQLPOINTER		NumericAttributePtr)
{
	GS_STMT	hStmt	= (GS_STMT) StatementHandle;
	GS_DBC	hDBC	= hStmt->hDBC;
	char	*string = (char *) CharacterAttributePtr;
	SQLLEN	*numericAttributePtr = (SQLLEN *) NumericAttributePtr;

	switch (FieldIdentifier) {
		case SQL_COLUMN_LENGTH:
			{
				switch (BufferLength) {
					case 0:
					case SQL_IS_UINTEGER: {
						WriteToLog("SQLColAttribute(0x%p, %i, SQL_COLUMN_LENGTH, 0x%p, SQL_IS_UNINTEGER, 0x%p, 0x%p)",
							StatementHandle, ColumnNumber, CharacterAttributePtr, StringLengthPtr, NumericAttributePtr);
						OopType resultOop, args[1];
						args[0] = Gci_I32ToOop(ColumnNumber);
						resultOop = Gci_Perform(hStmt->odbcStatement, "sqlColAttribute_ColumnLength:", args, 1);
						Gci_Err(&(hDBC->gciError));
						if (resultOop == OOP_NIL) {
							return Error(hDBC, 0, "state", "error in #'sqlColAttribute_ColumnLength:'");
						}
						if (!GCI_OOP_IS_SMALL_INT(resultOop)) {
							OopType	array[1];
							array[0] = resultOop;
							Gci_ReleaseOops(array, 1);
							return Error(hDBC, 0, "HY000", "sqlColAttribute_ColumnLength() did not return a SmallInteger");
						}
						*numericAttributePtr = (SQLSMALLINT) Gci_OopToI32(resultOop);
						WriteToLog("\t%i", *numericAttributePtr);
						return Success(hStmt);
					}
					case SQL_IS_INTEGER:
						WriteToLog("SQLColAttribute(,,SQL_COLUMN_LENGTH,,SQL_IS_INTEGER,,)");
						break;
					case SQL_IS_SMALLINT:
						WriteToLog("SQLColAttribute(,,SQL_COLUMN_LENGTH,,SQL_SMALLINT,,)");
						break;
					case SQL_IS_USMALLINT:
						WriteToLog("SQLColAttribute(,,SQL_COLUMN_LENGTH,,SQL_USMALLINT,,)");
						break;
					default:
						WriteToLog("SQLColAttribute(,,SQL_COLUMN_LENGTH,,???,,)");
						break;
				}
				WriteToLog("SQLColAttribute(,,SQL_COLUMN_LENGTH,,,,)");
				break;
			}
		case SQL_COLUMN_PRECISION:
			WriteToLog("SQLColAttribute(,,SQL_COLUMN_PRECISION,,,,)");
			break;
		case SQL_COLUMN_SCALE:
			WriteToLog("SQLColAttribute(,,SQL_COLUMN_SCALE,,,,)");
			break;
		case SQL_DESC_AUTO_UNIQUE_VALUE:
			WriteToLog("SQLColAttribute(,,SQL_DESC_AUTO_UNIQUE_VALUE,,,,)");
			break;
		case SQL_DESC_BASE_COLUMN_NAME:
			WriteToLog("SQLColAttribute(0x%p, %i, SQL_DESC_BASE_COLUMN_NAME, 0x%p, %i, 0x%p, 0x%p)",
				StatementHandle, ColumnNumber, CharacterAttributePtr, BufferLength, StringLengthPtr, NumericAttributePtr);
			string[0] = 0;
			*StringLengthPtr = 0;
			WriteToLog("\t\"%s\"", string);
			return Success(hStmt);
		case SQL_DESC_BASE_TABLE_NAME:
			WriteToLog("SQLColAttribute(,,SQL_DESC_BASE_TABLE_NAME,,,,)");
			break;
		case SQL_DESC_CASE_SENSITIVE:
			WriteToLog("SQLColAttribute(,,SQL_DESC_CASE_SENSITIVE,,,,)");
			break;
		case SQL_DESC_CATALOG_NAME:
			WriteToLog("SQLColAttribute(,,SQL_DESC_CATALOG_NAME,,,,)");
			break;
		case SQL_DESC_CONCISE_TYPE:
			WriteToLog("SQLColAttribute(,,SQL_DESC_CONCISE_TYPE,,,,)");
			break;
		case SQL_DESC_COUNT:
			WriteToLog("SQLColAttribute(,,SQL_DESC_COUNT,,,,)");
			break;
		case SQL_DESC_DISPLAY_SIZE:
			WriteToLog("SQLColAttribute(,,SQL_DESC_DISPLAY_SIZE,,,,)");
			break;
		case SQL_DESC_FIXED_PREC_SCALE:
			WriteToLog("SQLColAttribute(,,SQL_DESC_FIXED_PREC_SCALE,,,,)");
			break;
		case SQL_DESC_LABEL:
			WriteToLog("SQLColAttribute(,,SQL_DESC_LABEL,,,,)");
			break;
		case SQL_DESC_LENGTH:
			WriteToLog("SQLColAttribute(,,SQL_DESC_LENGTH,,,,)");
			break;
		case SQL_DESC_LITERAL_PREFIX:
			WriteToLog("SQLColAttribute(,,SQL_DESC_LITERAL_PREFIX,,,,)");
			break;
		case SQL_DESC_LITERAL_SUFFIX:
			WriteToLog("SQLColAttribute(,,SQL_DESC_LITERAL_SUFFIX,,,,)");
			break;
		case SQL_DESC_LOCAL_TYPE_NAME:
			WriteToLog("SQLColAttribute(,,SQL_DESC_LOCAL_TYPE_NAME,,,,)");
			break;
		case SQL_DESC_NAME:
			WriteToLog("SQLColAttribute(,,SQL_DESC_NAME,,,,)");
			break;
		case SQL_DESC_NULLABLE:
			WriteToLog("SQLColAttribute(,,SQL_DESC_NULLABLE,,,,)");
			break;
		case SQL_DESC_NUM_PREC_RADIX:
			WriteToLog("SQLColAttribute(,,SQL_DESC_NUM_PREC_RADIX,,,,)");
			break;
		case SQL_DESC_OCTET_LENGTH:
			WriteToLog("SQLColAttribute(,,SQL_DESC_OCTET_LENGTH,,,,)");
			break;
		case SQL_DESC_PRECISION:
			WriteToLog("SQLColAttribute(,,SQL_DESC_PRECISION,,,,)");
			break;
		case SQL_DESC_SCALE:
			WriteToLog("SQLColAttribute(,,SQL_DESC_SCALE,,,,)");
			break;
		case SQL_DESC_SCHEMA_NAME:
			WriteToLog("SQLColAttribute(,,SQL_DESC_SCHEMA_NAME,,,,)");
			break;
		case SQL_DESC_SEARCHABLE:
			WriteToLog("SQLColAttribute(0x%p, %i, SQL_DESC_SEARCHABLE, 0x%p, %i, 0x%p, 0x%p)",
				StatementHandle, ColumnNumber, CharacterAttributePtr, BufferLength, StringLengthPtr, NumericAttributePtr);
			if (numericAttributePtr) {
				*numericAttributePtr = SQL_PRED_NONE;
				WriteToLog("\t%i", *numericAttributePtr);
				return SQL_SUCCESS;
			}
			break;
		case SQL_DESC_TABLE_NAME:
			WriteToLog("SQLColAttribute(,,SQL_DESC_TABLE_NAME,,,,)");
			break;
		case SQL_DESC_TYPE:
			WriteToLog("SQLColAttribute(,,SQL_DESC_TYPE,,,,)");
			break;
		case SQL_DESC_TYPE_NAME:
			WriteToLog("SQLColAttribute(,,SQL_DESC_TYPE_NAME,,,,)");
			break;
		case SQL_DESC_UNNAMED:
			WriteToLog("SQLColAttribute(,,SQL_DESC_UNNAMED,,,,)");
			break;
		case SQL_DESC_UNSIGNED:
			WriteToLog("SQLColAttribute(,,SQL_DESC_UNSIGNED,,,,)");
			break;
		case SQL_DESC_UPDATABLE:
			WriteToLog("SQLColAttribute(,,SQL_DESC_UPDATABLE,,,,)");
			break;
		default:
			WriteToLog("SQLColAttribute(,,???,,,,)");
			break;
	}
	return Error(StatementHandle, 0, "errorState", "errorMessage");
}
