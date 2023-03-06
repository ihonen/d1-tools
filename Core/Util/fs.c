#include "fs.h"

// ---------------------------------------------------------

size_t getFileSize(const char* path)
{
    FILE* tmp = fopen(path, "r");
    if (tmp)
    {
        fseek(tmp, 0, SEEK_END);
        size_t size = ftell(tmp);
        fclose(tmp);
        return size;
    }

    return 0;
}
