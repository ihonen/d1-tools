#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <bzlib.h>

// -----------------------------------------------------------------------------
// FUNCTION MACROS
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

#pragma pack(push, 1)
typedef struct
{
    u16 b: 5;
    u16 g: 6;
    u16 r: 5;
} Bgr565;

typedef struct
{
    u8 b;
    u8 g;
    u8 r;
} Bgr888;
#pragma pack(pop)

// -----------------------------------------------------------------------------
// CONSTANTS
// -----------------------------------------------------------------------------

#define DVD_SECTOR_ID_AI   UINT32_C(0x20204941)
#define DVD_SECTOR_ID_BGND UINT32_C(0x444E4742)
#define DVD_SECTOR_ID_BOND UINT32_C(0x444E4F42)
#define DVD_SECTOR_ID_BUIL UINT32_C(0x4C495542)
#define DVD_SECTOR_ID_CART UINT32_C(0x54524143)
#define DVD_SECTOR_ID_DLGS UINT32_C(0x53474C44)
#define DVD_SECTOR_ID_ELEM UINT32_C(0x4D454C45)
#define DVD_SECTOR_ID_FXBK UINT32_C(0x4B425846)
#define DVD_SECTOR_ID_JUMP UINT32_C(0x504D554A)
#define DVD_SECTOR_ID_LIFT UINT32_C(0x5446494C)
#define DVD_SECTOR_ID_MASK UINT32_C(0x4B53414D)
#define DVD_SECTOR_ID_MAT  UINT32_C(0x2054414D)
#define DVD_SECTOR_ID_MISC UINT32_C(0x4353494D)
#define DVD_SECTOR_ID_MOVE UINT32_C(0x45564F4D)
#define DVD_SECTOR_ID_MSIC UINT32_C(0x4349534D)
#define DVD_SECTOR_ID_PAT  UINT32_C(0x20544150)
#define DVD_SECTOR_ID_SCRP UINT32_C(0x50524353)
#define DVD_SECTOR_ID_SGHT UINT32_C(0x54484753)
#define DVD_SECTOR_ID_SND  UINT32_C(0x20444E53)
#define DVD_SECTOR_ID_WAYS UINT32_C(0x53594157)

// -----------------------------------------------------------------------------
// IMAGE HANDLING
// -----------------------------------------------------------------------------

static void bgr565_to_bgr888(const Bgr565* src, Bgr888* dest, size_t num_pixels)
{
    const Bgr565 const* src_end  = src  + num_pixels;
    const Bgr888 const* dest_end = dest + num_pixels;

    for (; src < src_end; ++src, ++dest)
    {
        dest->b = (src->b * 527 + 23) >> 6;
        dest->g = (src->g * 259 + 33) >> 6;
        dest->r = (src->r * 527 + 23) >> 6;
    }

    assert(src == src_end);
    assert(dest == dest_end);
}

static void bgr888_to_bgr565(const Bgr888* src, Bgr565* dest, size_t num_pixels)
{
    const Bgr888 const* src_end  = src  + num_pixels;
    const Bgr565 const* dest_end = dest + num_pixels;

    for (; src < src_end; ++src, ++dest)
    {
        dest->b = (src->b * 249 + 1014 ) >> 11;
        dest->g = (src->g * 253 +  505 ) >> 10;
        dest->r = (src->r * 249 + 1014 ) >> 11;
    }

    assert(src == src_end);
    assert(dest == dest_end);
}

static void bgr888_to_ppm(const Bgr888* src, size_t width, size_t height, FILE* out)
{
    // ASCII:
    // fprintf(out, "P3\n");
    // Binary:
    fprintf(out, "P6\n");
    fprintf(out, "%u, %u\n", (unsigned)width, (unsigned)height);
    fprintf(out, "255\n");

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            size_t offset = y * width + x;
            // ASCII:
            // fprintf(out, "% 3u % 3u % 3u\n", src[offset].r, src[offset].g, src[offset].b);
            // Binary:
            fwrite(&src[offset].r, sizeof(u8), 1, out);
            fwrite(&src[offset].g, sizeof(u8), 1, out);
            fwrite(&src[offset].b, sizeof(u8), 1, out);
        }
    }
}

// -----------------------------------------------------------------------------
// FILE HANDLING
// -----------------------------------------------------------------------------

static size_t getFileSize(const char* path)
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

// -----------------------------------------------------------------------------
// DESERIALIZATION
// -----------------------------------------------------------------------------

static u8 read_u8(FILE* in)
{
    u8 value = 0;
    assert(fread(&value, sizeof(u8), 1, in) == 1);
    return value;
}

static u16 read_u16(FILE* in)
{
    u16 value = 0;
    assert(fread(&value, sizeof(u16), 1, in) == 1);
    return value;
}

static u32 read_u32(FILE* in)
{
    u32 value = 0;
    assert(fread(&value, sizeof(u32), 1, in) == 1);
    return value;
}

// -----------------------------------------------------------------------------
// SECTOR DUMPING
// -----------------------------------------------------------------------------

static void dumpSector(FILE* in, u32 size, const char* out_file_name)
{
    const long ftell_orig = ftell(in);

    FILE* out = fopen(out_file_name, "wb");
    assert(out);

    u8* data = malloc(size);
    assert(data);

    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
    fclose(out);

    fseek(in, ftell_orig, SEEK_SET);
    assert(ftell(in) == ftell_orig);
}

// -----------------------------------------------------------------------------
// SECTOR EXTRACTION
// -----------------------------------------------------------------------------

static void extractSector_AI(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector AI (%u bytes)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_BGND(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector BGND (%u bytes)\n", (unsigned)size);

    u32 version = read_u32(in);
    assert(version == 0x04);

    u16 filename_len = read_u16(in);

    char filename[FILENAME_MAX];
    fread(filename, sizeof(char), filename_len, in);
    filename[filename_len] = '\0';

    u16 width  = read_u16(in);
    u16 height = read_u16(in);

    u32 compr_algo = read_u32(in);
    assert(compr_algo == 0x02);

    u32 compr_data_len = read_u32(in);

    u8* compr_data = malloc(compr_data_len);
    assert(compr_data);
    fread(compr_data, sizeof(u8), compr_data_len, in);

    u32 decompr_data_len = width * height * 2; // RGB565

    u8* decompr_data = malloc(decompr_data_len);
    assert(decompr_data);

    assert(BZ2_bzBuffToBuffDecompress(
        (char*)decompr_data,
        &decompr_data_len,
        (char*)compr_data,
        compr_data_len,
        0,
        0
    ) == BZ_OK);

    assert(decompr_data_len == width * height * 2);

    u32 rgb888_data_len = width * height * 3; // RGB888

    u8* rgb888_data = malloc(rgb888_data_len);

    bgr565_to_bgr888(decompr_data, rgb888_data, width * height);
    bgr888_to_ppm(rgb888_data, width, height, out);

    free(compr_data);
    free(decompr_data);
    free(rgb888_data);

    printf("  --> Dimensions: %u x %u\n", (unsigned)width, (unsigned)height);
    printf("  --> Pixel format: BGR565\n");
    printf("  --> Compression: bz2\n");
}

static void extractSector_BOND(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector BOND (%u bytes)\n", (unsigned)size);

    fprintf(out, "---\n");

    u32 version = read_u32(in);
    assert(version == 0x02);
    fprintf(out, "version: %u\n", (unsigned)version);

    fprintf(out, "entries:\n");

    u16 num_entries = read_u16(in);
    for (u16 i_entry = 0; i_entry < num_entries; ++i_entry)
    {
        u16 x1 = read_u16(in);
        fprintf(out, "  - x1: %u\n", (unsigned)x1);

        u16 y1 = read_u16(in);
        fprintf(out, "    y1: %u\n", (unsigned)y1);

        u16 x2 = read_u16(in);
        fprintf(out, "    x2: %u\n", (unsigned)x2);

        u16 y2 = read_u16(in);
        fprintf(out, "    y2: %u\n", (unsigned)y2);

        u16 u16_01 = read_u16(in);
        fprintf(out, "    u16_01: %u\n", (unsigned)u16_01);

        u16 u16_02 = read_u16(in);
        fprintf(out, "    u16_02: %u\n", (unsigned)u16_02);

        u16 u16_03 = read_u16(in);
        fprintf(out, "    u16_03: %u\n", (unsigned)u16_03);
    }

    printf("  --> %u entries\n", (unsigned)num_entries);
}

static void extractSector_BUIL(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector BUIL (%u bytes)\n", (unsigned)size);

    fprintf(out, "---\n");

    u32 version = read_u32(in);
    assert(version == 0x04);

    fprintf(out, "version: %u\n", (unsigned)version);

    fprintf(out, "buildings:\n");

    u16 num_buildings = read_u16(in);

    for (u16 i_building = 0; i_building < num_buildings; ++i_building)
    {
        u8 u8_01 = read_u8(in);
        fprintf(out, "  - u8_01: %u\n", (unsigned)u8_01);

        u8 u8_02 = read_u8(in);
        fprintf(out, "    u8_02: %u\n", (unsigned)u8_02);

        fprintf(out, "    occupants:\n");
        
        u16 num_occupants = read_u16(in);
        for (u16 i_occupant = 0; i_occupant < num_occupants; ++i_occupant)
        {
            u16 occupant_id = read_u16(in);
            fprintf(out, "     - %u\n", (unsigned)occupant_id);
        }

        fprintf(out, "    doors:\n");

        u16 num_doors = read_u16(in);
        for (u16 i_door = 0; i_door < num_doors; ++i_door)
        {
            u8 type = read_u8(in);
            fprintf(out, "      - type: %u\n", (unsigned)type);

            u8 u8_05 = read_u8(in);
            fprintf(out, "        u8_05: %u\n", (unsigned)u8_05);

            u8 locked = read_u8(in);
            fprintf(out, "        locked: %u\n", (unsigned)locked);

            u8 lockpickable = read_u8(in);
            fprintf(out, "        lockpickable: %u\n", (unsigned)lockpickable);

            u8 u8_06 = read_u8(in);
            fprintf(out, "        u8_06: %u\n", (unsigned)u8_06);

            u8 u8_07 = read_u8(in);
            fprintf(out, "        u8_07: %u\n", (unsigned)u8_07);

            u8 u8_08 = read_u8(in);
            fprintf(out, "        u8_08: %u\n", (unsigned)u8_08);

            u8 u8_09 = read_u8(in);
            fprintf(out, "        u8_09: %u\n", (unsigned)u8_09);

            u8 u8_10 = read_u8(in);
            fprintf(out, "        u8_10: %u\n", (unsigned)u8_10);

            u8 u8_11 = read_u8(in);
            fprintf(out, "        u8_11: %u\n", (unsigned)u8_11);

            fprintf(out, "        outline:\n");

            u16 num_frame_coords = read_u16(in);

            for (u16 i_frame_coord = 0; i_frame_coord < num_frame_coords; ++i_frame_coord)
            {
                u16 x = read_u16(in);
                fprintf(out, "        - x: %u\n", (unsigned)x);

                u16 y = read_u16(in);
                fprintf(out, "          y: %u\n", (unsigned)y);
            }

            fprintf(out, "        access:\n");

            u16 num_access_coords = read_u16(in);
            for (u16 i_access_coord = 0; i_access_coord < num_access_coords; ++i_access_coord)
            {
                u16 x = read_u16(in);
                fprintf(out, "        - x: %u\n", (unsigned)x);

                u16 y = read_u16(in);
                fprintf(out, "          y: %u\n", (unsigned)y);

                u16 z = read_u16(in);
                fprintf(out, "          z: %u\n", (unsigned)z);

                u16 elevation = read_u16(in);
                fprintf(out, "          elevation_level: %u\n", (unsigned)elevation);
            }

            u16 u16_01 = read_u16(in);
            fprintf(out, "        u16_01: %u\n", (unsigned)u16_01);

            if (u16_01 != 0xffff)
            {
                u8 u8_12 = read_u8(in);
                fprintf(out, "        - u8_12: %u\n", (unsigned)u8_12);

                u8 u8_13 = read_u8(in);
                fprintf(out, "        - u8_13: %u\n", (unsigned)u8_13);
            }
        }
    }

    fprintf(out, "special_doors:\n");

    u16 num_special_doors = read_u16(in);
    for (u16 i_special_door = 0; i_special_door < num_special_doors; ++i_special_door)
    {
        u8 type = read_u8(in);
        fprintf(out, "  - type: %u\n", (unsigned)type);

        u8 u8_05 = read_u8(in);
        fprintf(out, "    u8_05: %u\n", (unsigned)u8_05);

        u8 locked = read_u8(in);
        fprintf(out, "    locked: %u\n", (unsigned)locked);

        u8 lockpickable = read_u8(in);
        fprintf(out, "    lockpickable: %u\n", (unsigned)lockpickable);

        u8 u8_06 = read_u8(in);
        fprintf(out, "    u8_06: %u\n", (unsigned)u8_06);

        u8 u8_07 = read_u8(in);
        fprintf(out, "    u8_07: %u\n", (unsigned)u8_07);

        u8 u8_08 = read_u8(in);
        fprintf(out, "    u8_08: %u\n", (unsigned)u8_08);

        u8 u8_09 = read_u8(in);
        fprintf(out, "    u8_09: %u\n", (unsigned)u8_09);

        u8 u8_10 = read_u8(in);
        fprintf(out, "    u8_10: %u\n", (unsigned)u8_10);

        u8 u8_11 = read_u8(in);
        fprintf(out, "    u8_11: %u\n", (unsigned)u8_11);

        fprintf(out, "    outline:\n");

        u16 num_frame_coords = read_u16(in);
        for (u16 i_frame_coord = 0; i_frame_coord < num_frame_coords; ++i_frame_coord)
        {
            u16 x = read_u16(in);
            fprintf(out, "    - x: %u\n", (unsigned)x);

            u16 y = read_u16(in);
            fprintf(out, "      y: %u\n", (unsigned)y);
        }

        fprintf(out, "    access:\n");

        u16 num_access_coords = read_u16(in);
        for (u16 i_access_coord = 0; i_access_coord < num_access_coords; ++i_access_coord)
        {
            u16 x = read_u16(in);
            fprintf(out, "    - x: %u\n", (unsigned)x);

            u16 y = read_u16(in);
            fprintf(out, "      y: %u\n", (unsigned)y);

            u16 z = read_u16(in);
            fprintf(out, "      z: %u\n", (unsigned)z);

            u16 elevation = read_u16(in);
            fprintf(out, "      elevation_level: %u\n", (unsigned)elevation);
        }

        u16 u16_01 = read_u16(in);
        fprintf(out, "    u16_01: %u\n", (unsigned)u16_01);
        if (u16_01 != 0xffff)
        {
            u8 u8_03 = read_u8(in);
            fprintf(out, "    - u8_03: %u\n", (unsigned)u8_03);

            u8 u8_04 = read_u8(in);
            fprintf(out, "    - u8_02: %u\n", (unsigned)u8_04);
        }
    }

    printf("  --> %u building entries\n", (unsigned)num_buildings);
    printf("  --> %u special door entries\n", (unsigned)num_special_doors);
}

static void extractSector_CART(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector CART (%u bytes)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_DLGS(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector DLGS (%u bytes)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);

    // FIXME: The below isn't quite right.
    /*
    long ftell_orig = ftell(in);

    printf("INFO: Extracting sector DLGS (%u bytes)\n", (unsigned)size);

    fprintf(out, "---\n");

    u32 version = read_u32(in);
    assert(version == 0x04);
    fprintf(out, "version: %u\n", (unsigned)version);

    u32 index_text = read_u32(in);
    fprintf(out, "index_text: %u\n", (unsigned)index_text);
    printf("  --> text index: %u\n", (index_text));

    u32 index_wave = read_u32(in);
    fprintf(out, "index_wave: %u\n", (unsigned)index_wave);
    printf("  --> wave index: %u\n", (index_wave));

    fprintf(out, "unknown_entries:\n");

    u32 num_unknown_entries = read_u32(in);
    for (u32 i_unknown_entry = 0; i_unknown_entry < num_unknown_entries; ++i_unknown_entry)
    {
        u32 unk_32_00 = read_u32(in);
        fprintf(out, "  - unk_32_00: %u\n", (unsigned)unk_32_00);

        u32 unk_32_01 = read_u32(in);
        fprintf(out, "    unk_32_01: %u\n", (unsigned)unk_32_01);

        u32 unk_32_02 = read_u32(in);
        fprintf(out, "    unk_32_02: %u\n", (unsigned)unk_32_02);
    }

    fprintf(out, "tricks:\n");
    uint32_t index_tricks = read_u32(in);
    fprintf(out, "  - index: %u\n", index_tricks);

    fprintf(out, "    ids:\n");

    uint32_t num_tricks = read_u32(in);
    for (u32 i_trick = 0; i_trick < num_tricks; ++i_trick)
    {
        u32 trick_id = read_u32(in);
        fprintf(out, "     - %u\n", (unsigned)trick_id);
    }

    fprintf(out, "objectives:\n");
    printf("ASD\n");
    uint32_t index_objectives = read_u32(in);
    fprintf(out, "  - index: %u\n", index_objectives);

    fprintf(out, "    ids:\n");

    uint32_t num_objectives = read_u32(in);
    for (u32 i_objective = 0; i_objective < num_objectives; ++i_objective)
    {
        u32 objective_id = read_u32(in);
        fprintf(out, "     - %u\n", (unsigned)objective_id);
    }

    fprintf(out, "debriefing:\n");
    uint32_t index_debriefing = read_u32(in);
    fprintf(out, "  - index: %u\n", index_debriefing);

    fprintf(out, "    ids_1:\n");

    uint32_t num_debriefings1 = read_u32(in);
    for (u32 i_debriefing1 = 0; i_debriefing1 < num_debriefings1; ++i_debriefing1)
    {
        u32 debriefing_id1 = read_u32(in);
        fprintf(out, "     - %u\n", (unsigned)debriefing_id1);
    }

    fprintf(out, "    ids_2:\n");

    uint32_t num_debriefings2 = read_u32(in);
    for (u32 i_debriefing2 = 0; i_debriefing2 < num_debriefings2; ++i_debriefing2)
    {
        u32 debriefing_id2 = read_u32(in);
        fprintf(out, "     - %u\n", (unsigned)debriefing_id2);
    }

    u32 bytes_left = size - (ftell(in) - ftell_orig);
    printf("bytes_left = %u\n", (unsigned)bytes_left);
    for (u32 i_byte = 0; i_byte < bytes_left; ++i_byte)
    {
        u8 byte;
        fread(&byte, 1, 1, in);
    }
    */
}

static void extractSector_ELEM(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector ELEM (%u bytes)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_FXBK(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector FXBK (%u bytes)\n", (unsigned)size);

    fprintf(out, "---\n");

    u32 version = read_u32(in);
    assert(version == 0x03);

    fprintf(out, "version: %u\n", (unsigned)version);

    fprintf(out, "effects:\n");

    u16 num_effects = read_u16(in);
    for (int i_effect = 0; i_effect < num_effects; ++i_effect)
    {
        u16 effect_id = read_u16(in);
        fprintf(out, "  - %u\n", (unsigned)effect_id);
    }

    fprintf(out, "sounds:\n");

    u32 num_sounds = read_u32(in);
    for (int i_sound = 0; i_sound < num_sounds; ++i_sound)
    {
        u32 sound_id = read_u32(in);
        fprintf(out, "  - %u\n", (unsigned)sound_id);
    }

    fprintf(out, "xet:\n");

    u16 num_xet = read_u16(in);
    for (int x = 0; x < num_xet; ++x)
    {
        u16 xet_id = read_u16(in);
        fprintf(out, "  - %u\n", (unsigned)xet_id);
    }

    fprintf(out, "xct:\n");

    u16 num_xct = read_u16(in);
    for (int x = 0; x < num_xct; ++x)
    {
        u16 xct_id = read_u16(in);
        fprintf(out, "  - %u\n", (unsigned)xct_id);
    }

    fprintf(out, "xpt:\n");

    u16 num_xpt = read_u16(in);
    for (int x = 0; x < num_xpt; ++x)
    {
        u16 xpt_id = read_u16(in);
        fprintf(out, "  - %u\n", (unsigned)xpt_id);
    }

    printf("  --> %u effect entries\n", (unsigned)num_effects);
    printf("  --> %u sound entries\n", (unsigned)num_sounds);
    printf("  --> %u .xet entries\n", (unsigned)num_xet);
    printf("  --> %u .xct entries\n", (unsigned)num_xct);
    printf("  --> %u .xpt entries\n", (unsigned)num_xpt);
}

static void extractSector_JUMP(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector JUMP (%u bytes)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_LIFT(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector LIFT (%u bytes)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_MASK(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector MASK (%u bytes)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_MAT(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector MAT (%u bytes)\n", (unsigned)size);

    fprintf(out, "---\n");

    u32 version = read_u32(in);
    assert(version == 0x04);
    fprintf(out, "version: %u\n", (unsigned)version);

    fprintf(out, "sections:\n");

    u16 num_sections = read_u16(in);
    for (u16 i_section = 0; i_section < num_sections; ++i_section)
    {
        u8 u8_01 = read_u8(in);
        fprintf(out, "  - u8_01: %u\n", (unsigned)u8_01);

        u8 u8_02 = read_u8(in);
        fprintf(out, "    u8_02: %u\n", (unsigned)u8_02);

        fprintf(out, "    blocks:\n");

        u16 num_blocks = read_u16(in);
        for (u16 i_block = 0; i_block < num_blocks; ++i_block)
        {
            u8 type = read_u8(in);
            fprintf(out, "    - type: %u\n", (unsigned)type);

            // NOTE: I'm not sure how I came to the conclusion that this is
            // indeed the elevation level, so it could be something else.
            u16 elevation = read_u16(in);
            fprintf(out, "      elevation_level: %u\n", (unsigned)elevation);

            if (type != 0x08)
            {
                u8 u8_03 = read_u8(in);
                fprintf(out, "      u8_03: %u\n", (unsigned)u8_03);

                u8 u8_04 = read_u8(in);
                fprintf(out, "      u8_04: %u\n", (unsigned)u8_04);

                u8 u8_05 = read_u8(in);
                fprintf(out, "      u8_05: %u\n", (unsigned)u8_05);

                u8 u8_06 = read_u8(in);
                fprintf(out, "      u8_06: %u\n", (unsigned)u8_06);

                u8 u8_07 = read_u8(in);
                fprintf(out, "      u8_07: %u\n", (unsigned)u8_07);

                u8 u8_08 = read_u8(in);
                fprintf(out, "      u8_08: %u\n", (unsigned)u8_08);

                u8 u8_09 = read_u8(in);
                fprintf(out, "      u8_09: %u\n", (unsigned)u8_09);

                u32 u32_01 = read_u32(in);
                fprintf(out, "      u32_01: %u\n", (unsigned)u32_01);
            }

            fprintf(out, "    - outline:\n");

            u16 num_coords = read_u16(in);
            for (u16 i_coord = 0; i_coord < num_coords; ++i_coord)
            {
                u16 x = read_u16(in);
                fprintf(out, "        - x: %u\n", x);

                u16 y = read_u16(in);
                fprintf(out, "          y: %u\n", y);
            }
        }
    }

    printf("  --> %u sections\n", (unsigned)num_sections);
}

static void extractSector_MISC(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector MISC (%u bytes)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_MOVE(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector MOVE (%u bytes)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_MSIC(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector MSIC (%u bytes)\n", (unsigned)size);

    fprintf(out, "---\n");

    u32 version = read_u32(in);
    assert(version == 0x01);
    fprintf(out, "version: %u\n", (unsigned)version);

    fprintf(out, "green_tracks:\n");

    u16 num_green = read_u16(in);
    for (u16 i_green = 0; i_green < num_green; ++i_green)
    {
        u16 filename_len;
        fread(&filename_len, sizeof(u16), 1, in);

        char filename[FILENAME_MAX];
        fread(filename, sizeof(char), filename_len, in);
        filename[filename_len] = '\0';

        fprintf(out, "  - %s\n", filename);
    }

    fprintf(out, "orange_tracks:\n");

    u16 num_orange = read_u16(in);
    for (u16 i_orange = 0; i_orange < num_orange; ++i_orange)
    {
        u16 filename_len;
        fread(&filename_len, sizeof(u16), 1, in);

        char filename[FILENAME_MAX];
        fread(filename, sizeof(char), filename_len, in);
        filename[filename_len] = '\0';

        fprintf(out, "  - %s\n", filename);
    }

    fprintf(out, "red_tracks:\n");

    u16 num_red = read_u16(in);
    for (u16 i_red = 0; i_red < num_red; ++i_red)
    {
        u16 filename_len;
        fread(&filename_len, sizeof(u16), 1, in);

        char filename[FILENAME_MAX];
        fread(filename, sizeof(char), filename_len, in);
        filename[filename_len] = '\0';

        fprintf(out, "  - %s\n", filename);
    }

    printf("  --> %u green .wav entries\n", (unsigned)num_green);
    printf("  --> %u orange .wav entries\n", (unsigned)num_orange);
    printf("  --> %u red .wav entries\n", (unsigned)num_red);
}

static void extractSector_PAT(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector PAT (%u bytes)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_SCRP(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector SCRP (%u bytes)\n", (unsigned)size);

    fprintf(out, "---\n");

    u32 version = read_u32(in);
    assert(version == 0x01);

    fprintf(out, "version: %u\n", (unsigned)version);

    fprintf(out, "locations:\n");

    u16 num_entries = read_u16(in);
    for (u16 i_entry = 0; i_entry < num_entries; ++i_entry)
    {
        fprintf(out, "  - coords:\n");

        u16 num_coords = read_u16(in);
        for (u16 i_coord = 0; i_coord < num_coords; ++i_coord)
        {
            u16 x = read_u16(in);
            fprintf(out, "    - x: %u\n", (unsigned)x);

            u16 y = read_u16(in);
            fprintf(out, "      y: %u\n", (unsigned)y);
        }

        u16 u16_01 = read_u16(in);
        fprintf(out, "    u16_01: %u\n", (unsigned)u16_01);

        u16 u16_02 = read_u16(in);
        fprintf(out, "    u16_02: %u\n", (unsigned)u16_02);
        
        u8 class_name_present = read_u8(in);
        if (class_name_present == 0x01)
        {
            u16 class_name_len = read_u16(in);
            char class_name[FILENAME_MAX];
            fread(class_name, sizeof(char), class_name_len, in);
            class_name[class_name_len] = '\0';

            fprintf(out, "    class_name: %s\n", class_name);
        }
    }
}

static void extractSector_SGHT(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector SGHT (%u bytes)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_SND(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector SND (%u bytes)\n", (unsigned)size);
    u8* data = malloc(size);
    fread(data, 1, size, in);
    fwrite(data, 1, size, out);
    free(data);
}

static void extractSector_WAYS(FILE* in, FILE* out, u32 size)
{
    printf("INFO: Extracting sector WAYS (%u bytes)\n", (unsigned)size);
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
        return EXIT_FAILURE;
    }

    size_t in_size = getFileSize(argv[1]);
    FILE* in       = fopen(argv[1], "rb");
    if (!in)
    {
        printf("ERROR: Failed to open file '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("INFO: Extracting file '%s' (%u bytes)\n", argv[1], (unsigned)in_size);

    FILE* out = NULL;

    u32 bytes_read = 0;
    while (!feof(in)
           && !ferror(in)
           && bytes_read < in_size)
    {
        u32 sector_id   = read_u32(in);
        u32 sector_size = read_u32(in);

        switch (sector_id)
        {
        case DVD_SECTOR_ID_AI:
            dumpSector(in, sector_size, "AI.dump.bin");
            assert(out = fopen("AI", "wb"));
            extractSector_AI  (in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_BGND:
            dumpSector(in, sector_size, "BGND.dump.bin");
            assert(out = fopen("BGND.ppm", "wb"));
            extractSector_BGND(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_BOND:
            dumpSector(in, sector_size, "BOND.dump.bin");
            assert(out = fopen("BOND.yaml", "wb"));
            extractSector_BOND(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_BUIL:
            dumpSector(in, sector_size, "BUIL.dump.bin");
            assert(out = fopen("BUIL.yaml", "wb"));
            extractSector_BUIL(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_CART:
            dumpSector(in, sector_size, "CART.dump.bin");
            assert(out = fopen("CART", "wb"));
            extractSector_CART(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_DLGS:
            dumpSector(in, sector_size, "DLGS.dump.bin");
            assert(out = fopen("DLGS", "wb"));
            extractSector_DLGS(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_ELEM:
            dumpSector(in, sector_size, "ELEM.dump.bin");
            assert(out = fopen("ELEM", "wb"));
            extractSector_ELEM(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_FXBK:
            dumpSector(in, sector_size, "FXBK.dump.bin");
            assert(out = fopen("FXBK.yaml", "wb"));
            extractSector_FXBK(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_JUMP:
            dumpSector(in, sector_size, "JUMP.dump.bin");
            assert(out = fopen("JUMP", "wb"));
            extractSector_JUMP(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_LIFT:
            dumpSector(in, sector_size, "LIFT.dump.bin");
            assert(out = fopen("LIFT", "wb"));
            extractSector_LIFT(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_MASK:
            dumpSector(in, sector_size, "MASK.dump.bin");
            assert(out = fopen("MASK", "wb"));
            extractSector_MASK(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_MAT:
            dumpSector(in, sector_size, "MAT.dump.bin");
            assert(out = fopen("MAT.yaml",  "wb"));
            extractSector_MAT (in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_MISC:
            dumpSector(in, sector_size, "MISC.dump.bin");
            assert(out = fopen("MISC", "wb"));
            extractSector_MISC(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_MOVE:
            dumpSector(in, sector_size, "MOVE.dump.bin");
            assert(out = fopen("MOVE", "wb"));
            extractSector_MOVE(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_MSIC:
            dumpSector(in, sector_size, "MSIC.dump.bin");
            assert(out = fopen("MSIC.yaml", "wb"));
            extractSector_MSIC(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_PAT:
            dumpSector(in, sector_size, "PAT.dump.bin");
            assert(out = fopen("PAT",  "wb"));
            extractSector_PAT (in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_SCRP:
            dumpSector(in, sector_size, "SCRP.dump.bin");
            assert(out = fopen("SCRP.yaml", "wb"));
            extractSector_SCRP(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_SGHT:
            dumpSector(in, sector_size, "SGHT.dump.bin");
            assert(out = fopen("SGHT", "wb"));
            extractSector_SGHT(in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_SND:
            dumpSector(in, sector_size, "SND.dump.bin");
            assert(out = fopen("SND",  "wb"));
            extractSector_SND (in, out, sector_size);
            fclose(out);
            break;
        case DVD_SECTOR_ID_WAYS:
            dumpSector(in, sector_size, "WAYS.dump.bin");
            assert(out = fopen("WAYS", "wb"));
            extractSector_WAYS(in, out, sector_size);
            fclose(out);
            break;
        }

        bytes_read += sizeof(sector_id) + sizeof(sector_size) + sector_size;
    }

    fclose(in);
    return EXIT_SUCCESS;
}
