#ifndef DATABASE_H
#define DATABASE_H

#include <stdint.h>
#include <sys/types.h>

#define MAX_TABLES 100
#define TABLE_MAX_PAGES 100
#define PAGE_SIZE 4096
#define MAX_COLUMNS 100

typedef enum { INT, VARCHAR } DataType;

typedef struct {
    char* name;
    DataType type;
    size_t size;
    int not_null;
    int is_primary_key;
    int is_unique;
    char* default_value;
} Column;

typedef struct {
    char* name;
    Column* columns;
    int num_columns;
    void** pages;
    uint32_t num_rows;
} Table;

typedef struct {
    Table* tables[MAX_TABLES];
    int table_count;
} Database;

void init_database(Database* db);
Table* create_table(Database* db, const char* name, Column* columns, int num_columns);
void delete_table(Database* db, const char* name);
void free_table(Table* table);
Table* get_table(Database* db, const char* name);

#endif // DATABASE_H
