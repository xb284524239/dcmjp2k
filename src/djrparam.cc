#include "dcmjp2k/djrparam.h"

DcmJp2kRepresentationParameter::DcmJp2kRepresentationParameter(Uint16 nearlosslessPSNR, OFBool losslessProcess)
    : DcmRepresentationParameter(), nearlosslessPSNR_(nearlosslessPSNR), losslessProcess_(losslessProcess) {}

DcmJp2kRepresentationParameter::DcmJp2kRepresentationParameter(const DcmJp2kRepresentationParameter &arg)
    : DcmRepresentationParameter(arg), nearlosslessPSNR_(arg.nearlosslessPSNR_), losslessProcess_(arg.losslessProcess_) {}

DcmJp2kRepresentationParameter::~DcmJp2kRepresentationParameter() {}

DcmRepresentationParameter *DcmJp2kRepresentationParameter::clone() const { return new DcmJp2kRepresentationParameter(*this); }

const char *DcmJp2kRepresentationParameter::className() const { return "FMJP2KRepresentationParameter"; }

OFBool DcmJp2kRepresentationParameter::operator==(const DcmRepresentationParameter &arg) const {
    const char *argname = arg.className();
    if (argname) {
        OFString argstring(argname);
        if (argstring == className()) {
            const DcmJp2kRepresentationParameter &argll = OFreinterpret_cast(const DcmJp2kRepresentationParameter &, arg);
            if (losslessProcess_ && argll.losslessProcess_)
                return OFTrue;
            else if (losslessProcess_ != argll.losslessProcess_)
                return OFFalse;
            else if (nearlosslessPSNR_ != argll.nearlosslessPSNR_)
                return OFFalse;
            return OFTrue;
        }
    }
    return OFFalse;
}
