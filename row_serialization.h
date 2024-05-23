#ifndef ROW_SERIALIZATION_H
#define ROW_SERIALIZATION_H

#include "table.h"

void serialize_row(Row* source, void* destination);     // takes a source Row structure and copies each of its fields into the destination memory block
void deserialize_row(void* source, Row* destination);   // reads data from a memory block and copies it into the corresponding fields of a destination Row structure

#endif // ROW_SERIALIZATION_H
