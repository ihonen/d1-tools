#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <bzlib.h>

// -----------------------------------------------------------------------------
// MACROS
// -----------------------------------------------------------------------------

#define PRINT_ERROR(f, ...) fprintf(stderr, "ERROR: " f "\n", ...)

// -----------------------------------------------------------------------------
// TYPEDEFS
// -----------------------------------------------------------------------------

typedef  int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef  uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// -----------------------------------------------------------------------------
// STATIC FUNCTIONS
// -----------------------------------------------------------------------------

static void printUsageAndExit(int argc, char** argv)
{
    printf("USAGE: %s <DVD file>\n", argv[0]);
    exit(EXIT_FAILURE);
}

static void extractSector_AI(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector AI\n");
}

static void extractSector_BGND(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector BGND\n");

    u32 version;
    fread(&version, sizeof(u32), 1, in);

    u16 filename_len;
    fread(&filename_len, sizeof(u16), 1, in);

    char filename[FILENAME_MAX];
    *filename = '\0';
    fread(&filename, sizeof(char), filename_len, in);

    u16 width;
    fread(&width, sizeof(u16), 1, in);

    u16 height;
    fread(&height, sizeof(u16), 1, in);

    u32 compr_algo;
    fread(&compr_algo, sizeof(u32), 1, in);

    u32 compr_len;
    fread(&compr_len, sizeof(u32), 1, in);

    u8* compr_data = malloc(compr_len);
    fread(compr_data, 1, compr_len, in);

    u32 decompr_len = width * height * 2;
    u8* decompr_data = malloc(decompr_len);

    int status = BZ2_bzBuffToBuffDecompress(
        decompr_data,
        decompr_len,
        compr_data,
        compr_len,
        0,
        0
    );

    free(compr_data);
    fwrite(decompr_data, 1, decompr_len, out);
}

static void extractSector_BOND(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector BOND\n");
}

static void extractSector_BUIL(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector BUIL\n");
}

static void extractSector_CART(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector CART\n");
}

static void extractSector_DLGS(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector DLGS\n");
}

static void extractSector_ELEM(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector ELEM\n");
}

static void extractSector_FXBK(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector FXBK\n");
}

static void extractSector_JUMP(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector JUMP\n");
}

static void extractSector_LIFT(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector LIFT\n");
}

static void extractSector_MASK(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector MASK\n");
}

static void extractSector_MAT(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector MAT\n");
}

static void extractSector_MISC(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector MISC\n");
}

static void extractSector_MOVE(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector MOVE\n");
}

static void extractSector_MSIC(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector MSIC\n");
}

static void extractSector_PAT(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector PAT\n");
}

static void extractSector_SCRP(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector SCRP\n");
}

static void extractSector_SGHT(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector SGHT\n");
}

static void extractSector_SND(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector SND\n");
}

static void extractSector_WAYS(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector WAYS\n");
}

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    printf("main\n");
    if (argc < 2)
    {
        printUsageAndExit(argc, argv);
    }

    FILE* in = fopen(argv[1], "rb");
    FILE* out;

    while (!feof(in))
    {
        u32 sector_id;
        fread(&sector_id, sizeof(u32), 1, in);

        u32 sector_size;
        fread(&sector_size, sizeof(u32), 1, in);

        switch (sector_id)
        {
        case 0x20204941: out = fopen("AI",   "wb"); extractSector_AI  (in, out, sector_size); fclose(out); break;
        case 0x444E4742: out = fopen("BGND", "wb"); extractSector_BGND(in, out, sector_size); fclose(out); break;
        case 0x444E4F42: out = fopen("BOND", "wb"); extractSector_BOND(in, out, sector_size); fclose(out); break;
        case 0x4C495542: out = fopen("BUIL", "wb"); extractSector_BUIL(in, out, sector_size); fclose(out); break;
        case 0x54524143: out = fopen("CART", "wb"); extractSector_CART(in, out, sector_size); fclose(out); break;
        case 0x53474C44: out = fopen("DLGS", "wb"); extractSector_DLGS(in, out, sector_size); fclose(out); break;
        case 0x4D454C45: out = fopen("ELEM", "wb"); extractSector_ELEM(in, out, sector_size); fclose(out); break;
        case 0x4B425846: out = fopen("FXBK", "wb"); extractSector_FXBK(in, out, sector_size); fclose(out); break;
        case 0x504D554A: out = fopen("JUMP", "wb"); extractSector_JUMP(in, out, sector_size); fclose(out); break;
        case 0x5446494C: out = fopen("LIFT", "wb"); extractSector_LIFT(in, out, sector_size); fclose(out); break;
        case 0x4B53414D: out = fopen("MASK", "wb"); extractSector_MASK(in, out, sector_size); fclose(out); break;
        case 0x2054414D: out = fopen("MAT",  "wb"); extractSector_MAT (in, out, sector_size); fclose(out); break;
        case 0x4353494D: out = fopen("MISC", "wb"); extractSector_MISC(in, out, sector_size); fclose(out); break;
        case 0x45564F4D: out = fopen("MOVE", "wb"); extractSector_MOVE(in, out, sector_size); fclose(out); break;
        case 0x4349534D: out = fopen("MSIC", "wb"); extractSector_MSIC(in, out, sector_size); fclose(out); break;
        case 0x20544150: out = fopen("PAT",  "wb"); extractSector_PAT (in, out, sector_size); fclose(out); break;
        case 0x50524353: out = fopen("SCRP", "wb"); extractSector_SCRP(in, out, sector_size); fclose(out); break;
        case 0x54484753: out = fopen("SGHT", "wb"); extractSector_SGHT(in, out, sector_size); fclose(out); break;
        case 0x20444E53: out = fopen("SND",  "wb"); extractSector_SND (in, out, sector_size); fclose(out); break;
        case 0x53594157: out = fopen("WAYS", "wb"); extractSector_WAYS(in, out, sector_size); fclose(out); break;
        }

        u8 dummy;
        for (u32 i = 0; i < sector_size; ++i)
        {
            fread(&dummy, 1, 1, in);
        }
    }

    fclose(in);
    return EXIT_SUCCESS;
}
