#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

static void dumpSector(FILE* in, u32 size, const char* out_file_name)
{
    const long in_pos_orig = ftell(in);

    FILE* out = fopen(out_file_name, "wb");

    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
    fclose(out);

    fseek(in, in_pos_orig, SEEK_SET);
}

static void extractSector_AI(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector AI (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_BGND(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector BGND (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_BOND(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector BOND (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_BUIL(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector BUIL (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_CART(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector CART (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_DLGS(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector DLGS (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_ELEM(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector ELEM (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_FXBK(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector FXBK (%uB)\n", (unsigned)size);

    fprintf(out, "---\n");

    u32 version;
    fread(&version, sizeof(u32), 1, in);
    assert(version == 0x03);

    fprintf(out, "version: %u\n", (unsigned)version);

    fprintf(out, "effects:\n");

    u16 num_effects;
    fread(&num_effects, sizeof(u16), 1, in);

    for (int e = 0; e < num_effects; ++e)
    {
        u16 effect_id;
        fread(&effect_id, sizeof(u16), 1, in);

        fprintf(out, "  - %u\n", (unsigned)effect_id);
    }

    fprintf(out, "sounds:\n");

    u32 num_sounds;
    fread(&num_sounds, sizeof(u32), 1, in);

    for (int s = 0; s < num_sounds; ++s)
    {
        u32 sound_id;
        fread(&sound_id, sizeof(u32), 1, in);

        fprintf(out, "  - %u\n", (unsigned)sound_id);
    }

    fprintf(out, "xet:\n");

    u16 num_xet;
    fread(&num_xet, sizeof(u16), 1, in);

    for (int x = 0; x < num_xet; ++x)
    {
        u16 xet_id;
        fread(&xet_id, sizeof(u16), 1, in);

        fprintf(out, "  - %u\n", (unsigned)xet_id);
    }

    fprintf(out, "xct:\n");

    u16 num_xct;
    fread(&num_xct, sizeof(u16), 1, in);

    for (int x = 0; x < num_xct; ++x)
    {
        u16 xct_id;
        fread(&xct_id, sizeof(u16), 1, in);

        fprintf(out, "  - %u\n", (unsigned)xct_id);
    }

    fprintf(out, "xpt:\n");

    u16 num_xpt;
    fread(&num_xpt, sizeof(u16), 1, in);

    for (int x = 0; x < num_xpt; ++x)
    {
        u16 xpt_id;
        fread(&xpt_id, sizeof(u16), 1, in);

        fprintf(out, "  - %u\n", (unsigned)xpt_id);
    }
}

static void extractSector_JUMP(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector JUMP (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_LIFT(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector LIFT (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_MASK(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector MASK (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_MAT(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector MAT (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_MISC(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector MISC (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_MOVE(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector MOVE (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_MSIC(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector MSIC (%uB)\n", (unsigned)size);

    u32 version;
    fread(&version, sizeof(u32), 1, in);
    assert(version == 0x01);

    fprintf(out, "---\n");
    fprintf(out, "green:\n");

    u16 num_green;
    fread(&num_green, sizeof(u16), 1, in);
    
    for (u16 g = 0; g < num_green; ++g)
    {
        u16 filename_len;
        fread(&filename_len, sizeof(u16), 1, in);

        char filename[FILENAME_MAX];
        fread(filename, sizeof(char), filename_len, in);
        filename[filename_len] = '\0';

        fprintf(out, "  - %s\n", filename);
    }

    fprintf(out, "orange:\n");

    u16 num_orange;
    fread(&num_orange, sizeof(u16), 1, in);

    for (u16 o = 0; o < num_orange; ++o)
    {
        u16 filename_len;
        fread(&filename_len, sizeof(u16), 1, in);

        char filename[FILENAME_MAX];
        fread(filename, sizeof(char), filename_len, in);
        filename[filename_len] = '\0';

        fprintf(out, "  - %s\n", filename);
    }

    fprintf(out, "red:\n");

    u16 num_red;
    fread(&num_red, sizeof(u16), 1, in);
    
    for (u16 r = 0; r < num_red; ++r)
    {
        u16 filename_len;
        fread(&filename_len, sizeof(u16), 1, in);

        char filename[FILENAME_MAX];
        fread(filename, sizeof(char), filename_len, in);
        filename[filename_len] = '\0';

        fprintf(out, "  - %s\n", filename);
    }
}

static void extractSector_PAT(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector PAT (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_SCRP(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector SCRP (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_SGHT(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector SGHT (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_SND(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector SND (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_WAYS(FILE* in, FILE* out, u32 size)
{
    printf("Extracting sector WAYS (%uB)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("USAGE: %s <DVD file>\n", argv[0]);
        exit(EXIT_FAILURE);
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
        case 0x20204941:
            dumpSector(in, sector_size, "AI.dump.bin");
            out = fopen("AI", "wb");
            extractSector_AI  (in, out, sector_size);
            fclose(out);
            break;
        case 0x444E4742:
            dumpSector(in, sector_size, "BGND.dump.bin");
            out = fopen("BGND", "wb");
            extractSector_BGND(in, out, sector_size);
            fclose(out);
            break;
        case 0x444E4F42:
            dumpSector(in, sector_size, "BOND.dump.bin");
            out = fopen("BOND", "wb");
            extractSector_BOND(in, out, sector_size);
            fclose(out);
            break;
        case 0x4C495542:
            dumpSector(in, sector_size, "BUIL.dump.bin");
            out = fopen("BUIL", "wb");
            extractSector_BUIL(in, out, sector_size);
            fclose(out);
            break;
        case 0x54524143:
            dumpSector(in, sector_size, "CART.dump.bin");
            out = fopen("CART", "wb");
            extractSector_CART(in, out, sector_size);
            fclose(out);
            break;
        case 0x53474C44:
            dumpSector(in, sector_size, "DLGS.dump.bin");
            out = fopen("DLGS", "wb");
            extractSector_DLGS(in, out, sector_size);
            fclose(out);
            break;
        case 0x4D454C45:
            dumpSector(in, sector_size, "ELEM.dump.bin");
            out = fopen("ELEM", "wb");
            extractSector_ELEM(in, out, sector_size);
            fclose(out);
            break;
        case 0x4B425846:
            dumpSector(in, sector_size, "FXBK.dump.bin");
            out = fopen("FXBK.yaml", "wb");
            extractSector_FXBK(in, out, sector_size);
            fclose(out);
            break;
        case 0x504D554A:
            dumpSector(in, sector_size, "JUMP.dump.bin");
            out = fopen("JUMP", "wb");
            extractSector_JUMP(in, out, sector_size);
            fclose(out);
            break;
        case 0x5446494C:
            dumpSector(in, sector_size, "LIFT.dump.bin");
            out = fopen("LIFT", "wb");
            extractSector_LIFT(in, out, sector_size);
            fclose(out);
            break;
        case 0x4B53414D:
            dumpSector(in, sector_size, "MASK.dump.bin");
            out = fopen("MASK", "wb");
            extractSector_MASK(in, out, sector_size);
            fclose(out);
            break;
        case 0x2054414D:
            dumpSector(in, sector_size, "MAT.dump.bin");
            out = fopen("MAT",  "wb");
            extractSector_MAT (in, out, sector_size);
            fclose(out);
            break;
        case 0x4353494D:
            dumpSector(in, sector_size, "MISC.dump.bin");
            out = fopen("MISC", "wb");
            extractSector_MISC(in, out, sector_size);
            fclose(out);
            break;
        case 0x45564F4D:
            dumpSector(in, sector_size, "MOVE.dump.bin");
            out = fopen("MOVE", "wb");
            extractSector_MOVE(in, out, sector_size);
            fclose(out);
            break;
        case 0x4349534D:
            dumpSector(in, sector_size, "MSIC.dump.bin");
            out = fopen("MSIC.yaml", "wb");
            extractSector_MSIC(in, out, sector_size);
            fclose(out);
            break;
        case 0x20544150:
            dumpSector(in, sector_size, "PAT.dump.bin");
            out = fopen("PAT",  "wb");
            extractSector_PAT (in, out, sector_size);
            fclose(out);
            break;
        case 0x50524353:
            dumpSector(in, sector_size, "SCRP.dump.bin");
            out = fopen("SCRP", "wb");
            extractSector_SCRP(in, out, sector_size);
            fclose(out);
            break;
        case 0x54484753:
            dumpSector(in, sector_size, "SGHT.dump.bin");
            out = fopen("SGHT", "wb");
            extractSector_SGHT(in, out, sector_size);
            fclose(out);
            break;
        case 0x20444E53:
            dumpSector(in, sector_size, "SND.dump.bin");
            out = fopen("SND",  "wb");
            extractSector_SND (in, out, sector_size);
            fclose(out);
            break;
        case 0x53594157:
            dumpSector(in, sector_size, "WAYS.dump.bin");
            out = fopen("WAYS", "wb");
            extractSector_WAYS(in, out, sector_size);
            fclose(out);
            break;
        }
    }

    fclose(in);
    return EXIT_SUCCESS;
}
