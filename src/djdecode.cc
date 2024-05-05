#include "dcmjp2k/djdecode.h"

#include "dcmjp2k/djcodecd.h"
#include "dcmjp2k/djcparam.h"
#include "dcmtk/dcmdata/dccodec.h" /* for DcmCodecStruct */


// initialization of static members
OFBool DcmJp2kDecoderRegistration::registered_ = OFFalse;
DcmJp2kCodecParameter *DcmJp2kDecoderRegistration::cp_ = NULL;
DcmJp2kDecoder *DcmJp2kDecoderRegistration::decoder_ = NULL;

void DcmJp2kDecoderRegistration::registerCodecs(J2K_UIDCreation uidcreation, J2K_PlanarConfiguration planarconfig, OFBool ignoreOffsetTable) {
    if (!registered_) {
        cp_ = new DcmJp2kCodecParameter(uidcreation, planarconfig, ignoreOffsetTable);
        if (cp_) {
            decoder_ = new DcmJp2kDecoder();
            if (decoder_) DcmCodecList::registerCodec(decoder_, NULL, cp_);

            registered_ = OFTrue;
        }
    }
}

void DcmJp2kDecoderRegistration::cleanup() {
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

OFString DcmJp2kDecoderRegistration::getLibraryVersionString() { return DCMJP2k_LIBRARY_VERSION_STRING; }
