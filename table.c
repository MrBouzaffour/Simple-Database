#include "table.h"
#include <stdlib.h> 
#include <stdio.h>
const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);

const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;

const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

void* row_slot(Table* table, uint32_t row_num) {
    /** 
    *   This function calculates which page and offset within that page a row should be located at,
    *   based on the row number. If the page does not already exist (i.e., is NULL), it allocates
    *   memory for that page. It then returns the pointer to the specific row within the page.
    *
    *   @param table Pointer to the Table containing the row.
    *   @param row_num The zero-based index of the row within the table.
    *   @return Pointer to the row's memory slot within the table.
    */

    uint32_t page_num = row_num / ROWS_PER_PAGE;    // Determine which page the row is on
    void* page = table->pages[page_num];            // Get the pointer to the page
    
    if (page == NULL) {
        
        // Page does not exist, allocate memory for it.
        page = table->pages[page_num] = malloc(PAGE_SIZE);
        
        if (page == NULL) {
            // Handle memory allocation failure; return NULL 
            return NULL;
        }
    }

    uint32_t row_offset = row_num % ROWS_PER_PAGE;  // Calculate row's offset within the page
    uint32_t byte_offset = row_offset * ROW_SIZE;   // Convert row offset to byte offset

    return page + byte_offset;  // Return the pointer to the row's slot
}

void print_row(Row* row) {
    /* Prints the contents of a Row structure */
    printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}
Table* new_table() {
    /**
    *   Creates a new empty Table structure.
    *   Initializes a new Table with all pages set to NULL and the row count set to zero.
    *   The table is capable of holding up to TABLE_MAX_PAGES pages.
    * 
    *   @return A pointer to the newly allocated Table, or NULL if the allocation fails.
    */

    Table* table = (Table*)malloc(sizeof(Table));
    
    if (!table) {
        return NULL;    // Return NULL if memory allocation fails
    }

    table->num_rows = 0;
    
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        table->pages[i] = NULL;
    }

    return table;
}


void free_table(Table* table) {
    /**
    *  Frees a Table structure and all associated memory.
    *  Iterates through the table's pages and frees each allocated page,
    *  then frees the Table structure itself.
    *
    *  @param table A pointer to the Table to be freed.
    */

    if (table) {

        for (int i = 0; i < TABLE_MAX_PAGES && table->pages[i]; i++) {
            free(table->pages[i]);  // Free each allocated page
        }
        free(table); // free the table structure
    }
}
