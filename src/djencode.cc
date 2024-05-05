#include "dcmjp2k/djencode.h"

#include "dcmjp2k/djcodece.h"
#include "dcmjp2k/djcparam.h"
#include "dcmtk/dcmdata/dccodec.h" /* for DcmCodecStruct */


// initialization of static members
OFBool DcmJp2kEncoderRegistration::registered_ = OFFalse;
DcmJp2kCodecParameter *DcmJp2kEncoderRegistration::cp_ = NULL;
DcmJp2kLosslessEncoder *DcmJp2kEncoderRegistration::losslessencoder_ = NULL;
DcmJp2kNearLosslessEncoder *DcmJp2kEncoderRegistration::nearlosslessencoder_ = NULL;

void DcmJp2kEncoderRegistration::registerCodecs(OFBool jp2k_optionsEnabled, Uint16 jp2k_cblkwidth, Uint16 jp2k_cblkheight, OFBool preferCookedEncoding, Uint32 fragmentSize, OFBool createOffsetTable,
                                                J2K_UIDCreation uidCreation, OFBool convertToSC) {
    if (!registered_) {
        cp_ = new DcmJp2kCodecParameter(jp2k_optionsEnabled, jp2k_cblkwidth, jp2k_cblkheight, preferCookedEncoding, fragmentSize, createOffsetTable, uidCreation, convertToSC, EJ2KPC_restore, OFFalse);

        if (cp_) {
            losslessencoder_ = new DcmJp2kLosslessEncoder();
            if (losslessencoder_) DcmCodecList::registerCodec(losslessencoder_, NULL, cp_);
            nearlosslessencoder_ = new DcmJp2kNearLosslessEncoder();
            if (nearlosslessencoder_) DcmCodecList::registerCodec(nearlosslessencoder_, NULL, cp_);
            registered_ = OFTrue;
        }
    }
}

void DcmJp2kEncoderRegistration::cleanup() {
    if (registered_) {
        DcmCodecList::deregisterCodec(losslessencoder_);
        DcmCodecList::deregisterCodec(nearlosslessencoder_);
        delete losslessencoder_;
        delete nearlosslessencoder_;
        delete cp_;
        registered_ = OFFalse;
#ifdef DEBUG
        // not needed but useful for debugging purposes
        losslessencoder_ = NULL;
        nearlosslessencoder_ = NULL;
        cp_ = NULL;
#endif
    }
}

OFString DcmJp2kEncoderRegistration::getLibraryVersionString() { return DCMJP2k_LIBRARY_VERSION_STRING; }
