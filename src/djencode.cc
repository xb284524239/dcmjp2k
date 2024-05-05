#include "dcmjp2k/djencode.h"

#include "dcmjp2k/djcodece.h"
#include "dcmjp2k/djcparam.h"
#include "dcmtk/dcmdata/dccodec.h" /* for DcmCodecStruct */


// initialization of static members
OFBool DCMJP2KEncoderRegistration::registered_ = OFFalse;
DJPEG2KCodecParameter *DCMJP2KEncoderRegistration::cp_ = NULL;
DJPEG2KLosslessEncoder *DCMJP2KEncoderRegistration::losslessencoder_ = NULL;
DJPEG2KNearLosslessEncoder *DCMJP2KEncoderRegistration::nearlosslessencoder_ = NULL;

void DCMJP2KEncoderRegistration::registerCodecs(OFBool jp2k_optionsEnabled, Uint16 jp2k_cblkwidth, Uint16 jp2k_cblkheight, OFBool preferCookedEncoding, Uint32 fragmentSize, OFBool createOffsetTable,
                                                J2K_UIDCreation uidCreation, OFBool convertToSC) {
    if (!registered_) {
        cp_ = new DJPEG2KCodecParameter(jp2k_optionsEnabled, jp2k_cblkwidth, jp2k_cblkheight, preferCookedEncoding, fragmentSize, createOffsetTable, uidCreation, convertToSC, EJ2KPC_restore, OFFalse);

        if (cp_) {
            losslessencoder_ = new DJPEG2KLosslessEncoder();
            if (losslessencoder_) DcmCodecList::registerCodec(losslessencoder_, NULL, cp_);
            nearlosslessencoder_ = new DJPEG2KNearLosslessEncoder();
            if (nearlosslessencoder_) DcmCodecList::registerCodec(nearlosslessencoder_, NULL, cp_);
            registered_ = OFTrue;
        }
    }
}

void DCMJP2KEncoderRegistration::cleanup() {
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

OFString DCMJP2KEncoderRegistration::getLibraryVersionString() { return FMJPEG2K_JPEG_VERSION_STRING; }
