#ifndef STATEMENTS_STRUCTURES_H
#define STATEMENTS_STRUCTURES_H

//typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;
typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {
    StatementType type;
} Statement;

#endif // STATEMENTS_STRUCTURES_H