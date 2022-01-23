#pragma once

// -----------------------------------------------------------------------------

typedef struct D1DvdFile D1DvdFile;
typedef struct D1Minimap D1Minimap;

// -----------------------------------------------------------------------------

D1DvdFile* D1DvdFile_newFromFile(
    const char* path
);

void D1DvdFile_free(
    D1DvdFile* file
);

D1Minimap* D1DvdFile_stealMinimap(
    D1DvdFile* file
);
