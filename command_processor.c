#include "command_processor.h"

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
    /**
    ** Meta-commands are commands that are not part of the SQL syntax but are used for controlling the application itself.
    * This function checks if the given input matches any known meta-commands.
    *
    * @param :input_buffer A pointer to an InputBuffer structure containing the user input.
    * @return A MetaCommandResult indicating the result of the operation.
    *         Returns META_COMMAND_SUCCESS if a known meta-command is recognized and executed successfully.
    *         Returns META_COMMAND_UNRECOGNIZED_COMMAND if the input does not match any known meta-commands.
    */
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}