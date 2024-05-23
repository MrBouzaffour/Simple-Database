#include "row_serialization.h"
#include <string.h> // memcpy

void serialize_row(Row* source, void* destination) {
    /**
    * This function takes a source Row structure and copies each of its fields into
    * the destination memory block using the predefined offsets for each field.
    * The fields are copied in the order of their offsets: id, username, then email.
    *
    * @param source Pointer to the Row structure to be serialized.
    * @param destination Pointer to the memory location where the serialized data will be stored.
    */
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void* source, Row* destination) {
    /**
    * This function reads data from a memory block (assumed to be a serialized Row)
    * and copies it into the corresponding fields of a destination Row structure.
    * The data is read from the memory block using the predefined offsets for each
    * field and copied into id, username, and email fields of the destination.
    *
    * @param source Pointer to the memory location containing the serialized data.
    * @param destination Pointer to the Row structure where the data will be deserialized into.
    */
    memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}
