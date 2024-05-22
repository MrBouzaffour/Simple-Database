#ifndef INPUT_MANAGEMENT_H
#define INPUT_MANAGEMENT_H

//#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputbuffer_structure.h"



InputBuffer* new_input_buffer();    // Creating a new InputBuffer structure and initializes its properties.
void print_prompt();    // Printing a prompt for the user.
void read_input(InputBuffer* input_buffer); // Reading a line of input from stdin and storing it into an InputBuffer structure.
void close_input_buffer(InputBuffer* input_buffer); // This function frees the memory allocated for the buffer 


#endif // INPUT_MANAGEMENT_H
