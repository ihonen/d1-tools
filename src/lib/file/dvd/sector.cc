extern "C" {
#include "lib/file/dvd/sector.h"
}

#include "lib/common/log.hh"

#include <string>

// -----------------------------------------------------------------------------

const char* D1DvdSectorId_toString(D1DvdSectorId id)
{
    switch (id)
    {
    case D1DvdSectorAi:   return "AI";
    case D1DvdSectorBgnd: return "BGND";
    case D1DvdSectorBond: return "BOND";
    case D1DvdSectorBuil: return "BUIL";
    case D1DvdSectorCart: return "CART";
    case D1DvdSectorDlgs: return "DLGS";
    case D1DvdSectorElem: return "ELEM";
    case D1DvdSectorFxbk: return "FXBK";
    case D1DvdSectorJump: return "JUMP";
    case D1DvdSectorLift: return "LIFT";
    case D1DvdSectorMask: return "MASK";
    case D1DvdSectorMat:  return "MAT";
    case D1DvdSectorMisc: return "MISC";
    case D1DvdSectorMove: return "MOVE";
    case D1DvdSectorMsic: return "MSIC";
    case D1DvdSectorPat:  return "PAT";
    case D1DvdSectorScrp: return "SCRP";
    case D1DvdSectorSght: return "SGHT";
    case D1DvdSectorSnd:  return "SND";
    case D1DvdSectorWays: return "WAYS";
    }

    Log::fatal() << "Invalid DVD sector " << id << "\n" << std::flush;
    abort();
}

D1DvdSectorId D1DvdSectorId_fromString(const char* str_)
{
    std::string str = str_;
    if (str == "AI")   return D1DvdSectorAi;
    if (str == "BGND") return D1DvdSectorBgnd;
    if (str == "BOND") return D1DvdSectorBond;
    if (str == "BUIL") return D1DvdSectorBuil;
    if (str == "CART") return D1DvdSectorCart;
    if (str == "DLGS") return D1DvdSectorDlgs;
    if (str == "ELEM") return D1DvdSectorElem;
    if (str == "FXBK") return D1DvdSectorFxbk;
    if (str == "JUMP") return D1DvdSectorJump;
    if (str == "LIFT") return D1DvdSectorLift;
    if (str == "MASK") return D1DvdSectorMask;
    if (str == "MAT")  return D1DvdSectorMat;
    if (str == "MISC") return D1DvdSectorMisc;
    if (str == "MOVE") return D1DvdSectorMove;
    if (str == "MSIC") return D1DvdSectorMsic;
    if (str == "PAT")  return D1DvdSectorPat;
    if (str == "SCRP") return D1DvdSectorScrp;
    if (str == "SGHT") return D1DvdSectorSght;
    if (str == "SND")  return D1DvdSectorSnd;
    if (str == "WAYS") return D1DvdSectorWays;

    Log::fatal() << "Invalid DVD sector " << str << "\n" << std::flush;
    abort();
}
