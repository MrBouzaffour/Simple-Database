#ifndef STATEMENT_PREPARER_H
#define STATEMENT_PREPARER_H

#include <string.h>
#include <stdio.h>
#include "inputbuffer_structure.h"

typedef enum { 
    PREPARE_SUCCESS,    // Statement recognized and prepared successfully.
    PREPARE_UNRECOGNIZED_STATEMENT,  //  Statement is unrecognized and cannot be prepared.
    PREPARE_SYNTAX_ERROR,    // There is a syntax errorr
    PREPARE_FAILED
} PrepareResult;

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement, Database* db); // analyzes user input and initializes the `Statement` structure accordingly

#endif // STATEMENT_PREPARER_H