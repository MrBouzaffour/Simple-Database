#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <string.h>
#include <stdlib.h>
#include "inputbuffer_structure.h"

typedef enum{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
}MetaCommandResult;

MetaCommandResult do_meta_command(InputBuffer* input_buffer);

#endif // COMMAND_PROCESSOR_H