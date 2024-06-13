#include "input_management.h"
#include "command_processor.h"
#include "statement_executor.h"
#include "statement_preparer.h"
#include "statement_struct.h"
#include "inputbuffer_structure.h"
#include "table.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>




int main(int argc, char* argv[]) {
    // Create an empty table
    Table* table = new_table();

    //creating an InputBuffer strucure
    InputBuffer* input_buffer = new_input_buffer();
    
    while (true) {
    
        /* -- Interface -- 
        *   input_management.c
        *   input_management.h   
        */
        print_prompt(); // 'db > '
        read_input(input_buffer); 

       /* -- Command Peocessor -- */

        // Here we handel the Non-SQL statements like '.exit'
        if (input_buffer->buffer[0] == '.')
        {
            switch( do_meta_command(input_buffer))
            {
                case(META_COMMAND_SUCCESS):
                    continue;

                case(META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }
        }

        // Converting the line of input into our internal representation of a statement
        Statement statement;
        switch ( prepare_statement(input_buffer, &statement))
        {
            case(PREPARE_SUCCESS):
                break;

            case (PREPARE_SYNTAX_ERROR):
                printf("Syntax error. Could not parse statement.\n");
                continue;

            case(PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n",input_buffer->buffer);
                continue;
        }

        switch (execute_statement(&statement, table)) {
            case (EXECUTE_SUCCESS):
	            printf("Executed.\n");
	            break;
	        case (EXECUTE_TABLE_FULL):
	            printf("Error: Table full.\n");
	            break;
        }
    }
}
