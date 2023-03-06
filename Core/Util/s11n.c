#include "s11n.h"

#include <assert.h>

// ---------------------------------------------------------

u8 read_u8(FILE* in)
{
    u8 value = 0;
    assert(fread(&value, sizeof(u8), 1, in) == 1);
    return value;
}

u16 read_u16(FILE* in)
{
    u16 value = 0;
    assert(fread(&value, sizeof(u16), 1, in) == 1);
    return value;
}

u32 read_u32(FILE* in)
{
    u32 value = 0;
    assert(fread(&value, sizeof(u32), 1, in) == 1);
    return value;
}
