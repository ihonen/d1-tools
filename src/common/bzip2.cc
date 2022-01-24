#include "common/bzip2.hh"
#include "common/log.hh"

#include <bzlib.h>

// -----------------------------------------------------------------------------

void bzip2Decompress(
    void* dest,
    unsigned* destLen,
    const void* src,
    unsigned srcLen
)
{
    int status = BZ2_bzBuffToBuffDecompress(
        reinterpret_cast<char*>(dest),
        destLen,
        // TODO: Get rid of const_cast.
        reinterpret_cast<char*>(const_cast<void*>(src)),
        srcLen,
        0,
        0
    );

    switch (status)
    {
    case BZ_PARAM_ERROR:
        Log::fatal() << "Bzip2 decompression failed (BZ_PARAM_ERROR)\n" << std::flush;
        abort();
    case BZ_MEM_ERROR:
        Log::fatal() << "Bzip2 decompression failed (BZ_MEM_ERROR)\n" << std::flush;
        abort();
    case BZ_OUTBUFF_FULL:
        Log::fatal() << "Bzip2 decompression failed (BZ_OUTBUFF_FULL)\n" << std::flush;
        abort();
    case BZ_DATA_ERROR:
        Log::fatal() << "Bzip2 decompression failed (BZ_DATA_ERROR)\n" << std::flush;
        abort();
    case BZ_DATA_ERROR_MAGIC:
        Log::fatal() << "Bzip2 decompression failed (BZ_DATA_ERROR_MAGIC)\n" << std::flush;
        abort();
    case BZ_UNEXPECTED_EOF:
        Log::fatal() << "Bzip2 decompression failed (BZ_UNEXPECTED_EOF)\n" << std::flush;
        abort();
    default:
        break;
    }
}
