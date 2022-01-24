#pragma once

// -----------------------------------------------------------------------------

#include "level/fwd.h"

// -----------------------------------------------------------------------------

D1Level* D1Level_newFromDvdFile(
    const char* path
);

void D1Level_free(
    D1Level* level
);

const char* D1Level_name(
    D1Level* level
);

D1Minimap* D1Level_minimap(
    D1Level* level
);

D1Map* D1Level_map(
    D1Level* level
);
