#pragma once

#include "dcmjp2k/djlsutil.h"    /* for enums */
#include "dcmtk/ofstd/oftypes.h" /* for OFBool */

class DJPEG2KCodecParameter;
class DJPEG2KDecoder;

/** singleton class that registers decoders for all supported JPEG 2000 processes.
 */
class DCMJP2k_EXPORT DCMJP2kDecoderRegistration {
   public:
    /** registers decoder for all supported JPEG-LS processes.
     *  If already registered, call is ignored unless cleanup() has
     *  been performed before.
     *  @param uidcreation flag indicating whether or not
     *    a new SOP Instance UID should be assigned upon decompression.
     *  @param planarconfig flag indicating how planar configuration
     *    of color images should be encoded upon decompression.
     *  @param ignoreOffsetTable flag indicating whether to ignore the offset table when decompressing multiframe images
     */
    static void registerCodecs(J2K_UIDCreation uidcreation = EJ2KUC_default, J2K_PlanarConfiguration planarconfig = EJ2KPC_restore, OFBool ignoreOffsetTable = OFFalse);

    /** deregisters decoders.
     *  Attention: Must not be called while other threads might still use
     *  the registered codecs, e.g. because they are currently decoding
     *  DICOM data sets through dcmdata.
     */
    static void cleanup();

    /** get version information of the CharLS library.
     *  Typical output format: "CharLS, Revision 55020 (modified)"
     *  @return name and version number of the CharLS library
     */
    static OFString getLibraryVersionString();

   private:
    /// flag indicating whether the decoders are already registered.
    static OFBool registered_;

    /// pointer to codec parameter shared by all decoders
    static DJPEG2KCodecParameter *cp_;

    /// pointer to decoder
    static DJPEG2KDecoder *decoder_;
};
