#ifndef STATEMENT_EXECUTOR_H
#define STATEMENT_EXECUTOR_H

#include <stdio.h>
#include "statement_struct.h"
#include "row.h"
#include "table.h"
#include "row_serialization.h"
// Enum to define possible results of statement execution
typedef enum {
    EXECUTE_SUCCESS,    // Execution was successful
    EXECUTE_TABLE_FULL  // The table has no free space for more rows
} ExecuteResult;

ExecuteResult execute_insert(Statement* statement, Table* table);   // execute an insert statement
ExecuteResult execute_select(Statement* statement, Table* table);   // execute a select statement
ExecuteResult execute_statement(Statement* statement, Table* table);    // execute any given statement based on its type


#endif // STATEMENT_EXECUTOR_H