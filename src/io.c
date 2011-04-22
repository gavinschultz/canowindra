#include <stdlib.h>
#include "io.h"
#include "debug.h"

char* file_open(const char *filename)
{
    char *buffer = NULL;
    PHYSFS_file *file = NULL;
    PHYSFS_sint64 file_length;
    PHYSFS_sint64 read_length;
    if (filename == NULL)
        return NULL;
    if (!PHYSFS_exists(filename))
    {
        trace("Could not find file %s", filename);
        exit(1);
    }
    file = PHYSFS_openRead(filename);
    file_length = PHYSFS_fileLength(file);
    buffer = (char*)malloc((size_t)file_length);
    read_length = PHYSFS_read(file, buffer, 1, (PHYSFS_uint32)file_length);
    trace("Loaded file %s", filename);
    return buffer;
}
