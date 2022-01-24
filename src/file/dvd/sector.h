#pragma once

// -----------------------------------------------------------------------------

enum D1DvdSectorId
{
    D1DvdSectorAi    = 0x20204941,
    D1DvdSectorBgnd  = 0x444E4742,
    D1DvdSectorBond  = 0x444E4F42,
    D1DvdSectorBuil  = 0x4C495542,
    D1DvdSectorCart  = 0x54524143,
    D1DvdSectorDlgs  = 0x53474C44,
    D1DvdSectorElem  = 0x4D454C45,
    D1DvdSectorFxbk  = 0x4B425846,
    D1DvdSectorJump  = 0x504D554A,
    D1DvdSectorLift  = 0x5446494C,
    D1DvdSectorMask  = 0x4B53414D,
    D1DvdSectorMat   = 0x2054414D,
    D1DvdSectorMisc  = 0x4353494D,
    D1DvdSectorMove  = 0x45564F4D,
    D1DvdSectorMsic  = 0x4349534D,
    D1DvdSectorPat   = 0x20544150,
    D1DvdSectorScrp  = 0x50524353,
    D1DvdSectorSght  = 0x54484753,
    D1DvdSectorSnd   = 0x20444E53,
    D1DvdSectorWays  = 0x53594157,
};

// -----------------------------------------------------------------------------

const char* D1DvdSectorId_toString(D1DvdSectorId id);

D1DvdSectorId D1DvdSectorId_fromString(const char* str);
