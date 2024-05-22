#ifndef ROW_H
#define ROW_H

#include <stdint.h>

#define COLUMN_USERNAME_SIZE 32 // Maximum length of username string
#define COLUMN_EMAIL_SIZE 255   // Maximum length of email string


// Row structure
typedef struct
{
    uint32_t id;    // Unique identifier for the row.
    char username[COLUMN_USERNAME_SIZE];    // Buffer for storing the username, fixed length.
    char email[COLUMN_EMAIL_SIZE];      // Buffer for storing the email, fixed length.
} Row;



#endif // ROW_H
