#include "statement_executor.h"


ExecuteResult execute_insert(Statement* statement, Table* table) {
    /**
    *   This function inserts a row into a specified Table. It first checks if the table has space for more rows.
    *   If the table is full, it returns EXECUTE_TABLE_FULL. Otherwise, it serializes the row data from the
    *   provided Statement into the next available row slot in the table, increments the row count of the table,
    *   and returns EXECUTE_SUCCESS.
    *
    *   @param statement A pointer to a Statement structure that contains the row data to be inserted
    *   @param table A pointer to the Table where the row will be inserted
    *   @return An ExecuteResult indicating either success (EXECUTE_SUCCESS) or failure (EXECUTE_TABLE_FULL) of the operation
    */

    // Check if the table has reached its maximum number of rows
    if (table->num_rows >= TABLE_MAX_ROWS) {
        return EXECUTE_TABLE_FULL;
    }

    // Get the address of the row data from the statement
    Row* row_to_insert = &(statement->row_to_insert);

    // Serialize the row data into the appropriate slot in the table.
    serialize_row(row_to_insert, row_slot(table, table->num_rows));

    // Increment the row count
    table->num_rows += 1;

    return EXECUTE_SUCCESS;
}


ExecuteResult execute_select(Statement* statement, Table* table) {
    /**
    * This function iterates through all rows in a specified Table and deserializes each row from its 
    * respective storage slot into a temporary Row structure. Each row is then printed. The operation 
    * continues until all rows have been processed. If successful, the function returns EXECUTE_SUCCESS.
    *
    * @param statement A pointer to a Statement structure
    * @param table A pointer to the Table from which rows will be selected and printed
    * @return An ExecuteResult indicating the success of the operation
    */


    Row row; // temporary storage for each deserialized row

    // Iterate over each row in the table
    for (uint32_t i = 0; i < table->num_rows; i++) {
        
        // Deserialize the row data from the appropriate slot in the table into 'row'
        deserialize_row(row_slot(table, i), &row);

        // Print the row data
        print_row(&row);
    }

    return EXECUTE_SUCCESS;
}


ExecuteResult execute_statement(Statement* statement, Table* table) {
    /**
    * This function takes a pointer to a Statement structure, inspects the type of the statement, and executes the corresponding operation.
    * 
    * @param:
    *       statement A pointer to the Statement structure
    * @return 
    *       ExecuteResult struct
    */
    switch (statement->type) {
        case (STATEMENT_INSERT):
            return execute_insert(statement, table);

        case (STATEMENT_SELECT_ALL):
            return execute_select(statement, table);
        case (STATEMENT_SELECT):
            printf("select only");

  }
}