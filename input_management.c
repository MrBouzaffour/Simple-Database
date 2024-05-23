#include "input_management.h"


InputBuffer* new_input_buffer() {
    /*
    *This function creates a new InputBuffer structure and initializes its properties.
    */

    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}


/** Printing a prompt for the user. */
void print_prompt() { printf("db > "); }


void read_input(InputBuffer* input_buffer) {
    /**
    *   This function reads a line of input from the standard input (stdin)
    *   and store it into an InputBuffer structure.
    *   @param InputBuffer* input_buffer : A pointer to an InputBuffer instance where the input will be stored.
    */
    
    // Read a line from stdin into input_buffer->buffer. Automatically allocate or resize the buffer as necessary. 
    // The size of the allocated memory is updated in input_buffer->buffer_length. 
    // The function returns the number of characters read, including the newline character, but excluding the null terminator, 
    // and stores this count in bytes_read. If the function encounters an EOF or an error, bytes_read is set to -1.
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);}
 
    input_buffer->input_length = bytes_read - 1;    // remove the newline count
    input_buffer->buffer[bytes_read - 1] = 0;
}


void close_input_buffer(InputBuffer* input_buffer) {
    /** This function frees the memory allocated for the buffer within the InputBuffer struct and itself*/

    free(input_buffer->buffer);
    free(input_buffer);
}
