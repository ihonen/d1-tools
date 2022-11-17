#include "file/dvd/sector.hh"
#include "common/log.hh"

// -----------------------------------------------------------------------------

std::string DvdSector_toString(DvdSector sector)
{
    switch (sector)
    {
    case DvdSector::Ai:   return "AI";
    case DvdSector::Bgnd: return "BGND";
    case DvdSector::Bond: return "BOND";
    case DvdSector::Buil: return "BUIL";
    case DvdSector::Cart: return "CART";
    case DvdSector::Dlgs: return "DLGS";
    case DvdSector::Elem: return "ELEM";
    case DvdSector::Fxbk: return "FXBK";
    case DvdSector::Jump: return "JUMP";
    case DvdSector::Lift: return "LIFT";
    case DvdSector::Mask: return "MASK";
    case DvdSector::Mat:  return "MAT";
    case DvdSector::Misc: return "MISC";
    case DvdSector::Move: return "MOVE";
    case DvdSector::Msic: return "MSIC";
    case DvdSector::Pat:  return "PAT";
    case DvdSector::Scrp: return "SCRP";
    case DvdSector::Sght: return "SGHT";
    case DvdSector::Snd:  return "SND";
    case DvdSector::Ways: return "WAYS";
    }

    Log::fatal() << "Invalid DVD sector " << static_cast<int>(sector) << "\n" << std::flush;
    abort();
}

DvdSector DvdSector_fromString(const std::string& str)
{
    if (str == "AI")   return DvdSector::Ai;
    if (str == "BGND") return DvdSector::Bgnd;
    if (str == "BOND") return DvdSector::Bond;
    if (str == "BUIL") return DvdSector::Buil;
    if (str == "CART") return DvdSector::Cart;
    if (str == "DLGS") return DvdSector::Dlgs;
    if (str == "ELEM") return DvdSector::Elem;
    if (str == "FXBK") return DvdSector::Fxbk;
    if (str == "JUMP") return DvdSector::Jump;
    if (str == "LIFT") return DvdSector::Lift;
    if (str == "MASK") return DvdSector::Mask;
    if (str == "MAT")  return DvdSector::Mat;
    if (str == "MISC") return DvdSector::Misc;
    if (str == "MOVE") return DvdSector::Move;
    if (str == "MSIC") return DvdSector::Msic;
    if (str == "PAT")  return DvdSector::Pat;
    if (str == "SCRP") return DvdSector::Scrp;
    if (str == "SGHT") return DvdSector::Sght;
    if (str == "SND")  return DvdSector::Snd;
    if (str == "WAYS") return DvdSector::Ways;

    Log::fatal() << "Invalid DVD sector " << str << "\n" << std::flush;
    abort();
}
