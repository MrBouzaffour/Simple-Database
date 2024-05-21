
#ifndef INPUT_MANAGEMENT_H
#define INPUT_MANAGEMENT_H

//#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char* buffer;           // Pointer to the buffer that holds the input string.
    size_t buffer_length;   // Size of the allocated memory for `buffer`.
    ssize_t input_length;   // Length of the input stored in `buffer`.
} InputBuffer;


InputBuffer* new_input_buffer();    // Creating a new InputBuffer structure and initializes its properties.
void print_prompt();    // Printing a prompt for the user.
void read_input(InputBuffer* input_buffer); // Reading a line of input from stdin and storing it into an InputBuffer structure.
void close_input_buffer(InputBuffer* input_buffer); // This function frees the memory allocated for the buffer 


#endif // INPUT_MANAGEMENT_H
