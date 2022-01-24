#pragma once

#include <string>

// -----------------------------------------------------------------------------

enum class DvdSector
{
    Ai    = 0x20204941,
    Bgnd  = 0x444E4742,
    Bond  = 0x444E4F42,
    Buil  = 0x4C495542,
    Cart  = 0x54524143,
    Dlgs  = 0x53474C44,
    Elem  = 0x4D454C45,
    Fxbk  = 0x4B425846,
    Jump  = 0x504D554A,
    Lift  = 0x5446494C,
    Mask  = 0x4B53414D,
    Mat   = 0x2054414D,
    Misc  = 0x4353494D,
    Move  = 0x45564F4D,
    Msic  = 0x4349534D,
    Pat   = 0x20544150,
    Scrp  = 0x50524353,
    Sght  = 0x54484753,
    Snd   = 0x20444E53,
    Ways  = 0x53594157,
};

// -----------------------------------------------------------------------------

std::string DvdSector_toString(DvdSector sector);

DvdSector DvdSector_fromString(const std::string& str);
