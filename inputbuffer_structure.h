#ifndef INPUTBUFFER_STRUCTURE
#define INPUTBUFFER_STRUCTURE

typedef struct {
    char* buffer;           // Pointer to the buffer that holds the input string.
    size_t buffer_length;   // Size of the allocated memory for `buffer`.
    ssize_t input_length;   // Length of the input stored in `buffer`.
} InputBuffer;

#endif // INPUTBUFFER_STRUCTURE