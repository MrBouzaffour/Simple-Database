#ifndef STATEMENT_STRUCT_H
#define STATEMENT_STRUCT_H

#include "table.h"

typedef enum {
    STATEMENT_INSERT,   // SQL INSERT operation.
    STATEMENT_SELECT    // SQL SELECT operation.
} StatementType;

typedef struct {
    StatementType type; // type of the SQL statement, defined by StatementType enum.
    Row row_to_insert;  // only used by insert statement

} Statement;

#endif // STATEMENT_STRUCT_H