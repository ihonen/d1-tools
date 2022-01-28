#pragma once

#include <cstdint>

// ---------------------------------------------------------------------------

// Reads a single element from the buffer pointed to by *currentByte
// and moves currentByte past the read element.
template<typename T>
inline T consume(const uint8_t** currentByte)
{
    T value = *reinterpret_cast<const T*>(*currentByte);
    *currentByte += sizeof(T);
    return value;
}

template<typename T>
inline T peek(const uint8_t* currentByte)
{
    return *reinterpret_cast<const T*>(currentByte);
}
