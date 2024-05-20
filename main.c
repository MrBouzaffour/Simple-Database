#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


ssize_t custom_getline (char** lineptr, size_t* n, FILE* stream ) {
	/*
	 * We tell getline to store the read line in input_buffer->buffer and the size of the allocated buffer in input_buffer->buffer_length.
	 * We store the return value in input_buffer->input_length.
	 *
	 * buffer starts as null, so getline allocates enough memory to hold the line of input and makes buffer point to it.
	 * 
	 * Params:
	 *	 lineptr : a pointer to the variable we use to point to the buffer containing the read line.
	 *	 If it set to NULL it is mallocatted by getline and should thus be freed by the user, even if the command fails.
	 *
	 *	 n : a pointer to the variable we use to save the size of allocated buffer.
	 *	 stream : the input stream to read from. We’ll be reading from standard input. 
	 * 
	 * return:
	 * 	 value : the number of bytes read, which may be less than the size of the buffer.
	 * */	
	if (lineptr == NULL || n == NULL || stream == NULL) {
        	return -1;
    	}

    	size_t pos = 0;
    	int c;

    	if (*lineptr == NULL) {
        	*n = 128; // initial size
        	*lineptr = malloc(*n);
        	if (*lineptr == NULL) {
            		return -1;
        	}
    	}

    	while ((c = fgetc(stream)) != EOF) {
        	if (pos + 1 >= *n) {
            		size_t new_size = *n * 2;
            		char* new_ptr = realloc(*lineptr, new_size);
            		if (new_ptr == NULL) {
                		return -1;
            			}
            		*lineptr = new_ptr;
            		*n = new_size;
        		}
        	(*lineptr)[pos++] = c;
        	if (c == '\n') {
            		break;
        	}
    	}

   	if (pos == 0 && c == EOF) {
        	return -1;
    	}

    	(*lineptr)[pos] = '\0';
    	return pos;
}

typedef struct
{
	char* buffer;
	size_t buffer_length;
	ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer()
{
	InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
	input_buffer->buffer = NULL;
	input_buffer->buffer_length = 0;
	input_buffer->input_length =0;

	return input_buffer;
}

void print_prompt(){ printf(" db > ");}

void read_input(InputBuffer* input_buffer) {
	 // ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
	 ssize_t bytes_read = custom_getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
	 if (bytes_read <= 0) {
		printf("Error reading input\n");
		exit(EXIT_FAILURE);
	 }
	 input_buffer->input_length = bytes_read - 1;
	 input_buffer->buffer[bytes_read - 1] = 0;
	}
void close_input_buffer(InputBuffer* input_buffer)
	{
		free(input_buffer -> buffer);
		free(input_buffer);
	}


// indiacation success or failure (exceptions)
typedef enum {
	META_COMMAND_SUCCESS,
	META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum { 
	PREPARE_SUCCESS, 
	PREPARE_UNRECOGNIZED_STATEMENT 
} PrepareResult;


MetaCommandResult do_meta_command(InputBuffer* input_buffer)
{
	if (strcmp(input_buffer->buffer, ".exit")==0)
	{
		exit(EXIT_SUCCESS);
	}else
	{
		return META_COMMAND_UNRECOGNIZED_COMMAND;
	}
}
typedef enum {
	STATEMENT_INSERT,
	STATEMENT_SELECT 
} StatementType;

typedef struct {
	StatementType type;
} Statement;


// The sql compiler :)
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {  
	if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
		statement->type = STATEMENT_INSERT;
		return PREPARE_SUCCESS;
	}
	if (strcmp(input_buffer->buffer, "select") == 0) {
		statement->type = STATEMENT_SELECT;
		return PREPARE_SUCCESS;
	}

	return PREPARE_UNRECOGNIZED_STATEMENT;
	}

void execute_statement(Statement* statement) {
	switch (statement->type) {
		case (STATEMENT_INSERT):
			printf("This is where we would do an insert.\n");
      			break;
		case (STATEMENT_SELECT):
			printf("This is where we would do a select.\n");
			break;
	}
}
int main(int argc, char* argv[]) {

	(void)argc;
	(void)argv;
	InputBuffer* input_buffer = new_input_buffer();
	while(true)
	{
		print_prompt();
		read_input(input_buffer);
		
		//if (strcmp(input_buffer->buffer, ".exit")== 0){
		//	close_input_buffer(input_buffer);
		//	exit(EXIT_SUCCESS);}
		//else{printf("Unrecognized command '%s' .\n",input_buffer->buffer);}
	

		//Non-SQL statements are called meta-commands like .exit
		if (input_buffer->buffer[0] == '.')
		{
			switch (do_meta_command(input_buffer))
			{
				case(META_COMMAND_SUCCESS):
					continue;
				case(META_COMMAND_UNRECOGNIZED_COMMAND):
					printf("Unrecognized command '%s' \n", input_buffer->buffer);
					continue;
			}
		}


		// we convert our input into an internal representation of a statement
		Statement statement;
		switch(prepare_statement(input_buffer, &statement))
		{
			case(PREPARE_SUCCESS):
				break;
			case(PREPARE_UNRECOGNIZED_STATEMENT):
				printf("Unrecognized keyword at start of '%s' . \n",input_buffer->buffer);
				continue;
		}

		// we execute out statement 
		execute_statement(&statement);
		printf("Executed.\n");
	}
	return 0;
}
