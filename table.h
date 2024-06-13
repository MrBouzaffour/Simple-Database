#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>


/* ------ Row ------ */

#define COLUMN_USERNAME_SIZE 32 // Maximum length of username string
#define COLUMN_EMAIL_SIZE 255   // Maximum length of email string

// Row structure
typedef struct
{
    uint32_t id;                            // Unique identifier for the row.
    char username[COLUMN_USERNAME_SIZE + 1];    // Buffer for storing the username, fixed length.
    char email[COLUMN_EMAIL_SIZE +1             ];          // Buffer for storing the email, fixed length.
} Row;

void print_row(Row* row);   // Prints the contents of a Row structure

/* ------ Row Layout ------ */

// Macro to calculate the size of a specific attribute within a structure
// Utilizes the offset of structure pointer technique for portability
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

extern const uint32_t ID_SIZE;
extern const uint32_t USERNAME_SIZE;
extern const uint32_t EMAIL_SIZE;

extern const uint32_t ID_OFFSET;
extern const uint32_t USERNAME_OFFSET;
extern const uint32_t EMAIL_OFFSET;

extern const uint32_t ROW_SIZE;

/* ------ Table ------ */

// Define page size and table constraints
#define TABLE_MAX_PAGES 100
#define PAGE_SIZE 4096
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGES)

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