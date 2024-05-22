#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <string.h>
#include <stdlib.h>
#include "inputbuffer_structure.h"

typedef enum{
    META_COMMAND_SUCCESS,   //  Meta-command executed successfully
    META_COMMAND_UNRECOGNIZED_COMMAND   // Meta-command is not recognized
}MetaCommandResult;

MetaCommandResult do_meta_command(InputBuffer* input_buffer);   //checks if the given input matches any known meta-commands

#endif // COMMAND_PROCESSOR_H