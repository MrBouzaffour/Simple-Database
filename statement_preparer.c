#include "statement_struct.h"
#include "statement_preparer.h"

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    /*
    * This function analyzes user input to determine the type of SQL statement it represents and initializes
    * the `Statement` structure accordingly. It currently supports preparing "insert" and "select" statements.
    *
    * @param input_buffer A pointer to an InputBuffer structure containing the user's input string.
    * @param statement A pointer to a Statement structure where the type of the statement will be set based on the input.
    *
    *@return A PrepareResult indicating the outcome of the operation:
    *         - PREPARE_SUCCESS if the statement is recognized and prepared successfully.
    *         - PREPARE_UNRECOGNIZED_STATEMENT if the input does not correspond to a recognized statement type.
    */
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;

        // args_assigned: stores the count of successfully assigned inputs from sscanf.
        // using sscanf the data will be taken from 'input_buffer->buffer' following this format "insert %d %s %s"
        // &(statement->row_to_insert.id)
        // statement->row_to_insert.username
        // statement->row_to_insert.email
        int args_assigned = sscanf(input_buffer->buffer,"insert %d %s %s",&(statement->row_to_insert.id),statement->row_to_insert.username,statement->row_to_insert.email);
        
        if(args_assigned < 3)
        {
            return PREPARE_SYNTAX_ERROR;
        }
        
        return PREPARE_SUCCESS;
        }
  
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}