#include "database.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void init_database(Database* db) {
    db->table_count = 0;
    for (int i = 0; i < MAX_TABLES; i++) {
        db->tables[i] = NULL;
    }
    printf("Database is Initilized ...\n");
}

Table* create_table(Database* db, const char* name, Column* columns, int num_columns) {

    if (db->table_count >= MAX_TABLES) {
        printf("Error: Database has reached the limit of %d tables.\n", MAX_TABLES);
        return NULL;
    }

    // Check if a table with the same name already exists
    for (int i = 0; i < db->table_count; i++) {
        if (strcmp(db->tables[i]->name, name) == 0) {
            printf("Error: Table '%s' already exists.\n", name);
            return NULL;
        }
    }

    // Allocate memory for the new table
    Table* table = (Table*)malloc(sizeof(Table));
    if (table == NULL) {
        perror("Failed to allocate memory for the table");
        return NULL;
    }

    // Initialize the table structure
    table->name = strdup(name);
    table->num_columns = num_columns;
    table->columns = (Column*)malloc(sizeof(Column) * num_columns);
    if (table->columns == NULL) {
        perror("Failed to allocate memory for columns");
        free(table->name);
        free(table);
        return NULL;
    }

    for (int i = 0; i < num_columns; i++) {
        // Deep copy each column
        table->columns[i].name = strdup(columns[i].name);
        table->columns[i].type = columns[i].type;
        table->columns[i].size = columns[i].size;
        table->columns[i].not_null = columns[i].not_null;
        table->columns[i].is_primary_key = columns[i].is_primary_key;
        table->columns[i].is_unique = columns[i].is_unique;
        table->columns[i].default_value = columns[i].default_value ? strdup(columns[i].default_value) : NULL;
    }

    table->num_rows = 0;
    table->pages = (void**)calloc(TABLE_MAX_PAGES, sizeof(void*));
    if (table->pages == NULL) {
        perror("Failed to allocate memory for pages");
        free_table(table);
        return NULL;
    }

    // Add the table to the database
    db->tables[db->table_count++] = table;
    return table;
}

void delete_table(Database* db, const char* name) {
    for (int i = 0; i < db->table_count; i++) {
        if (strcmp(db->tables[i]->name, name) == 0) {
            free_table(db->tables[i]);
            db->tables[i] = db->tables[db->table_count - 1];
            db->tables[--db->table_count] = NULL;
            printf("Table '%s' has been successfully deleted.\n", name);
            return;
        }
    }
    printf("Error: Table '%s' not found.\n", name);
}

void free_table(Table* table) {
    if (table != NULL) {
        free(table->name);
        for (int i = 0; i < table->num_columns; i++) {
            free(table->columns[i].name);
            free(table->columns[i].default_value);
        }
        free(table->columns);

        for (int i = 0; i < TABLE_MAX_PAGES; i++) {
            free(table->pages[i]);
        }
        free(table->pages);
        free(table);
    }
}

Table* get_table(Database* db, const char* name) {
    for (int i = 0; i < db->table_count; i++) {
        if (strcmp(db->tables[i]->name, name) == 0) {
            return db->tables[i];
        }
    }
    return NULL;  // Table not found
}
