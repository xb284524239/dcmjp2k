#pragma once

#include "dcmtk/ofstd/ofcond.h"

/** Helper class for converting between dcmjpls and CharLS error codes
 */
class DJLSError {
   private:
    /// private undefined constructor
    DJLSError();

   public:
    /** This method converts a CharLS error code into a dcmjpls OFCondition
     *  @param error The CharLS error code
     *  @return The OFCondition
     */
    static const OFConditionConst& convert(int error) {
        switch (error) {
            case 0:
                return EC_Normal;
                /*      case UncompressedBufferTooSmall:
                        return EC_J2KUncompressedBufferTooSmall;
                      case CompressedBufferTooSmall:
                        return EC_J2KCompressedBufferTooSmall;
                      case ImageTypeNotSupported:
                        return EC_J2KCodecUnsupportedImageType;
                      case InvalidJlsParameters:
                        return EC_J2KCodecInvalidParameters;
                      case ParameterValueNotSupported:
                        return EC_J2KCodecUnsupportedValue;
                      case InvalidCompressedData:
                        return EC_J2KInvalidCompressedData;
                      case UnsupportedBitDepthForTransform:
                        return EC_J2KUnsupportedBitDepthForTransform;
                      case UnsupportedColorTransform:
                        return EC_J2KUnsupportedColorTransform;
                      case TooMuchCompressedData:
                        return EC_J2KTooMuchCompressedData;*/
            default:
                return EC_IllegalParameter;
        }
    }
};
