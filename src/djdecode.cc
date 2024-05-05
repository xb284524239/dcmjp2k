#include "dcmjp2k/djdecode.h"

#include "dcmjp2k/djcodecd.h"
#include "dcmjp2k/djcparam.h"
#include "dcmtk/dcmdata/dccodec.h" /* for DcmCodecStruct */


// initialization of static members
OFBool DCMJP2kDecoderRegistration::registered_ = OFFalse;
DJPEG2KCodecParameter *DCMJP2kDecoderRegistration::cp_ = NULL;
DJPEG2KDecoder *DCMJP2kDecoderRegistration::decoder_ = NULL;

void DCMJP2kDecoderRegistration::registerCodecs(J2K_UIDCreation uidcreation, J2K_PlanarConfiguration planarconfig, OFBool ignoreOffsetTable) {
    if (!registered_) {
        cp_ = new DJPEG2KCodecParameter(uidcreation, planarconfig, ignoreOffsetTable);
        if (cp_) {
            decoder_ = new DJPEG2KDecoder();
            if (decoder_) DcmCodecList::registerCodec(decoder_, NULL, cp_);

            registered_ = OFTrue;
        }
    }
}

void DCMJP2kDecoderRegistration::cleanup() {
    if (registered_) {
        DcmCodecList::deregisterCodec(decoder_);
        delete decoder_;
        delete cp_;
        registered_ = OFFalse;
#ifdef DEBUG
        // not needed but useful for debugging purposes
        decoder_ = NULL;
        cp_ = NULL;
#endif
    }
}

OFString DCMJP2kDecoderRegistration::getLibraryVersionString() { return FMJPEG2K_JPEG_VERSION_STRING; }
