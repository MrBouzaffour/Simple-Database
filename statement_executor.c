#include "statement_executor.h"


void execute_statement(Statement* statement) {
    /*
    * This function takes a pointer to a Statement structure, inspects the type of the statement,
    * and executes the corresponding operation. Currently, the function handles two types of
    * statements: insert and select.
    *
    * @param:
    *       statement A pointer to the Statement structure which contains the type of the SQL
    */
    switch (statement->type) {
        case (STATEMENT_INSERT):
            printf("This is where we would do an insert.\n");
            break;
        case (STATEMENT_SELECT):
            printf("This is where we would do a select.\n");
            break;
  }
}