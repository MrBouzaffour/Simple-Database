#include "statement_struct.h"
#include "statement_preparer.h"
#include "database.h"
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement, Database* db) {

    
    /**
    * This function analyzes user input to determine the type of SQL statement it represents and initializes the `Statement` structure accordingly
    *
    * @param input_buffer A pointer to an InputBuffer structure containing the user's input string
    * @param statement A pointer to a Statement structure where the type of the statement will be set based on the input
    *
    *@return A PrepareResult indicating the outcome of the operation:
    *       - PREPARE_SUCCESS if the statement is recognized and prepared successfully
    *       - PREPARE_SYNTAX_ERROR if there is a syntax error   
    *       - PREPARE_UNRECOGNIZED_STATEMENT if the input does not correspond to a recognized statement type
    */
    
    // Trim leading spaces
    char* buffer = input_buffer->buffer;
    while (isspace(*buffer)) buffer++;

    if (strncmp(buffer, "CREATE TABLE", 12) == 0) {
        
        buffer += 12; // Move past "CREATE TABLE"
        while (isspace(*buffer)) buffer++;  // Skip whitespace

        char table_name[256];
        int scanned = sscanf(buffer, "%s", table_name);
        if (scanned != 1) {
            return PREPARE_SYNTAX_ERROR;
        }

        // Find the opening parenthesis for columns definition
        char* columns_start = strchr(buffer, '(');
        if (!columns_start) {
            return PREPARE_SYNTAX_ERROR;
        }
        columns_start++; // Move past '('

        // Prepare to parse columns until the closing parenthesis ')'
        char* columns_end = strchr(columns_start, ')');
        if (!columns_end) {
            return PREPARE_SYNTAX_ERROR;
        }
        *columns_end = '\0'; // Temporarily null-terminate the columns string

        // Array to hold columns, assuming no more than 100 columns
        Column columns[100];
        int num_columns = 0;
        char* col_def = strtok(columns_start, ",");
        while (col_def && num_columns < 100) {
            char col_name[256], col_type[256];
            int col_size = 0; // Default size

            // Parse each column's details
            sscanf(col_def, "%s %s", col_name, col_type);
            if (strstr(col_type, "varchar") != NULL) {
                sscanf(col_type, "varchar(%d)", &col_size);
            }

            // Assign values to columns array
            columns[num_columns].name = strdup(col_name);
            columns[num_columns].type = strcmp(col_type, "int") == 0 ? INT : VARCHAR;
            columns[num_columns].size = col_size;
            columns[num_columns].not_null = 0; // Default, enhance to detect NOT NULL
            num_columns++;

            // Move to the next column definition
            col_def = strtok(NULL, ",");
        }

        // Now create the table with the parsed columns
        Table* new_table = create_table(db, table_name, columns, num_columns);
        if (!new_table) {
            // Cleanup if table creation fails
            for (int i = 0; i < num_columns; i++) {
                free(columns[i].name);
            }
            return PREPARE_FAILED;
        }
        db->tables[db->table_count+1] = new_table;
        db->table_count++;

        statement->type = STATEMENT_CREATE;
        return PREPARE_SUCCESS;
    
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;

        // args_assigned: stores the count of successfully assigned inputs from sscanf
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
  
    if (strncmp(input_buffer->buffer, "select", 6) == 0) {
        
        //-- If we want to select all --//
        char* str = input_buffer->buffer;
        str+=7; // we will point to the character of after 'select'
        if (*str == '*')
        {
            str++;
            if (*str == '\0')
            {
                statement->type = STATEMENT_SELECT_ALL;
                return PREPARE_SUCCESS;
            }
            return PREPARE_SYNTAX_ERROR;
        }
        //-- select by id --//
        statement->type = STATEMENT_SELECT;
        int args_assigned = sscanf(input_buffer->buffer,"select %d %s %s",&(statement->row_selected.id),statement->row_selected.username,statement->row_selected.email);
        
        if(args_assigned ==0)
        {
            return PREPARE_SYNTAX_ERROR;
        }
        
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
    */
}