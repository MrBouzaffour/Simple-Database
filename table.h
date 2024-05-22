#ifndef TABLE_H
#define TABLE_H

#include "row_layout.h"

// Define page size and table constraints
#define TABLE_MAX_PAGES 100     // Maximum number of pages in a table
const uint32_t PAGE_SIZE = 4096;    // Page size in bytes
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE; // Number of rows per page
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES; // Max rows in the table


// Table structure which holds all rows organized in pages.
typedef struct {
    uint32_t num_rows;                 // Total number of rows in the table
    void* pages[TABLE_MAX_PAGES];      // Array of pointers to pages
} Table;


// where to read/write in memory for a particular row
void* row_slot(Table* table, uint32_t row_num);
Table* new_table();
void free_table(Table* table);


#endif // TABLE_H