#ifndef STATEMENT_PREPARER_H
#define STATEMENT_PREPARER_H

#include <string.h>
#include <stdio.h>
#include "inputbuffer_structure.h"

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);

#endif // STATEMENT_PREPARER_H