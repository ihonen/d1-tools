#pragma once

// -----------------------------------------------------------------------------

typedef struct D1DvmFile D1DvmFile;
typedef struct D1Map     D1Map;

// -----------------------------------------------------------------------------

D1DvmFile* D1DvmFile_newFromFile(
    const char* path
);

void D1DvmFile_free(
    D1DvmFile* file
);

D1Map* D1DvmFile_map(
    const D1DvmFile* file
);
