#pragma once

#include "dcmjp2k/dldefine.h"
#include "dcmtk/dcmdata/dcpixel.h" /* for class DcmRepresentationParameter */

/** representation parameter for JPEG 2000
 */
class DCMJP2k_EXPORT FMJPEG2KRepresentationParameter : public DcmRepresentationParameter {
   public:
    /** constructor
     *  @param nearlosslessDeviation used as parameter NEAR in JPEG 2000 nearlossless-encoding process
     *  @param losslessProcess true if lossless process is requested
     */
    FMJPEG2KRepresentationParameter(Uint16 PSNR = 0, OFBool losslessProcess = OFTrue);

    /// copy constructor
    FMJPEG2KRepresentationParameter(const FMJPEG2KRepresentationParameter &arg);

    /// destructor
    virtual ~FMJPEG2KRepresentationParameter();

    /** this methods creates a copy of type DcmRepresentationParameter *
     *  it must be overweritten in every subclass.
     *  @return copy of this object
     */
    virtual DcmRepresentationParameter *clone() const;

    /** returns the class name as string.
     *  can be used in operator== as poor man's RTTI replacement.
     */
    virtual const char *className() const;

    /** compares an object to another DcmRepresentationParameter.
     *  Implementation must make sure that classes are comparable.
     *  @param arg representation parameter to compare with
     *  @return true if equal, false otherwise.
     */
    virtual OFBool operator==(const DcmRepresentationParameter &arg) const;

    /** returns the desired NEAR parameter
     *  @return return desired NEAR-Parameter
     */
    Uint16 getnearlosslessPSNR() const { return nearlosslessPSNR_; }

    /** returns true if lossless compression is desired
     *  @return true if lossless compression is desired
     */
    OFBool useLosslessProcess() const { return losslessProcess_; }

   private:
    /** desired PSNR parameter
     *  Default is 0 (automatic selection).
     *  Ignored during lossless compression.
     */
    Uint16 nearlosslessPSNR_;

    /// true if lossless process should be used even in lossy transfer syntax
    OFBool losslessProcess_;
};
