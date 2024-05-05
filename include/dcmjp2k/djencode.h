#pragma once

#include "dcmjp2k/djcparam.h" /* for class DJP2KCodecParameter */
#include "dcmjp2k/djlsutil.h"
#include "dcmtk/ofstd/oftypes.h" /* for OFBool */


class DcmJp2kCodecParameter;
class DcmJp2kLosslessEncoder;
class DcmJp2kNearLosslessEncoder;

/** singleton class that registers encoders for all supported JPEG 2000 processes.
 */
class DCMJP2K_EXPORT DcmJp2kEncoderRegistration {
   public:
    /** registers encoders for all supported JPEG 2000 processes.
     *  If already registered, call is ignored unless cleanup() has
     *  been performed before.
     *  @param jp2k_optionsEnabled       enable/disable use of all five JPEG 2000 parameters
     *  @param jp2k_cblkwidth            JPEG-2000 parameter "Threshold 1" (used for quantization)
     *  @param jp2k_cblkheight           JPEG-2000 parameter "Threshold 2"
     *  @param preferCookedEncoding      true if the "cooked" lossless encoder should be preferred over the "raw" one
     *  @param fragmentSize              maximum fragment size (in kbytes) for compression, 0 for unlimited.
     *  @param createOffsetTable         create offset table during image compression
     *  @param uidCreation               mode for SOP Instance UID creation
     *  @param convertToSC               flag indicating whether image should be converted to Secondary Capture upon compression
     *  @param jplsInterleaveMode        flag describing which interleave the JPEG-LS datastream should use
     */
    static void registerCodecs(OFBool jp2k_optionsEnabled = OFFalse, Uint16 jp2k_cblkwidth = 64, Uint16 jp2k_cblkheight = 64, OFBool preferCookedEncoding = OFTrue, Uint32 fragmentSize = 0,
                               OFBool createOffsetTable = OFTrue, J2K_UIDCreation uidCreation = EJ2KUC_default, OFBool convertToSC = OFFalse);

    /** deregisters encoders.
     *  Attention: Must not be called while other threads might still use
     *  the registered codecs, e.g. because they are currently encoding
     *  DICOM data sets through dcmdata.
     */
    static void cleanup();

    /** get version information of the CharLS library.
     *  Typical output format: "CharLS, Revision 55020 (modified)"
     *  @return name and version number of the CharLS library
     */
    static OFString getLibraryVersionString();

   private:
    /// flag indicating whether the encoders are already registered.
    static OFBool registered_;

    /// pointer to codec parameter shared by all encoders
    static DcmJp2kCodecParameter *cp_;

    /// pointer to encoder for lossless JPEG 2000
    static DcmJp2kLosslessEncoder *losslessencoder_;

    /// pointer to encoder for lossy JPEG 2000
    static DcmJp2kNearLosslessEncoder *nearlosslessencoder_;
};
