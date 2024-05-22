#ifndef STATEMENT_EXECUTOR_H
#define STATEMENT_EXECUTOR_H

#include <stdio.h>
#include "statement_struct.h"

void execute_statement(Statement* statement);   // inspects the type of the statement, and executes the corresponding operation.

#endif // STATEMENT_EXECUTOR_H