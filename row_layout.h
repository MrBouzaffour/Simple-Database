#ifndef ROW_LAYOUT_H
#define ROW_LAYOUT_H

#include "row.h"

// Macro to calculate the size of a specific attribute within a structure
// Utilizes the offset of structure pointer technique for portability
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)


// Constants for the sizes of each attribute in the Row structure
const uint32_t ID_SIZE = size_of_attribute(Row, id);    // Size of the 'id' field in bytes
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);    // Size of the 'username' field in bytes
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);  // Size of the 'email' field in bytes.

// Offset constants for each attribute within the Row structure
const uint32_t ID_OFFSET = 0;   // Offset of the 'id'
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;   // Offset of the 'username'
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;  //  Offset of the 'email'

// The total size of the Row structure in bytes
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;     //// Sum of sizes of all fields

#endif // ROW_LAYOUT_H
