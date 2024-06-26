#pragma once

#include "dcmjp2k/dldefine.h"
#include "dcmtk/oflog/oflog.h"
#include "dcmtk/ofstd/ofcond.h" /* for class OFCondition */

#define DCMJP2k_LIBRARY_VERSION_STRING "dcmjp2k - OpenJPEG (unmodified)"

// global definitions for logging mechanism provided by the oflog module

extern DCMJP2K_EXPORT OFLogger DcmJp2kLogger;

#define DCMJP2K_TRACE(msg) OFLOG_TRACE(DcmJp2kLogger, msg)
#define DCMJP2K_DEBUG(msg) OFLOG_DEBUG(DcmJp2kLogger, msg)
#define DCMJP2K_INFO(msg) OFLOG_INFO(DcmJp2kLogger, msg)
#define DCMJP2K_WARN(msg) OFLOG_WARN(DcmJp2kLogger, msg)
#define DCMJP2K_ERROR(msg) OFLOG_ERROR(DcmJp2kLogger, msg)
#define DCMJP2K_FATAL(msg) OFLOG_FATAL(DcmJp2kLogger, msg)

// include this file in doxygen documentation

/** @file djlsutil.h
 *  @brief enumerations, error constants and helper functions for the dcmjpls module
 */

/** describes the condition under which a compressed or decompressed image
 *  receives a new SOP instance UID.
 */
enum J2K_UIDCreation {
    /** Upon compression, assign new SOP instance UID if compression is lossy.
     *  Upon decompression never assign new SOP instance UID.
     */
    EJ2KUC_default,

    /// always assign new SOP instance UID on compression and decompression
    EJ2KUC_always,

    /// never assign new SOP instance UID
    EJ2KUC_never
};

/** describes how the decoder should handle planar configuration of
 *  decompressed color images.
 */
enum J2K_PlanarConfiguration {
    /// restore planar configuration as indicated in data set
    EJ2KPC_restore,

    /** automatically determine whether color-by-plane is required from
     *  the SOP Class UID and decompressed photometric interpretation
     */
    EJ2KPC_auto,

    /// always create color-by-pixel planar configuration
    EJ2KPC_colorByPixel,

    /// always create color-by-plane planar configuration
    EJ2KPC_colorByPlane
};

/** describes how the encoder handles the image bit depth
 *  upon lossy compression.
 */
enum J2K_CompressionBitDepth {
    /// keep original bit depth
    EJ2KBD_original,

    /** limit bit depth to a certain value, i.e. scale down
     *  if the original image bit depth is larger
     */
    EJ2KBD_limit,

    /** force bit depth to a certain value, i.e. scale up
     *  or scale down the original image to match the given
     *  bit depth.
     */
    EJ2KBD_force
};

// CONDITION CONSTANTS

/// error condition constant: Too small buffer used for image data (internal error)
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KUncompressedBufferTooSmall;

/// error condition constant: Too small buffer used for compressed image data (internal error)
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KCompressedBufferTooSmall;

/// error condition constant: The image uses some features which the codec does not support
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KCodecUnsupportedImageType;

/// error condition constant: The codec was fed with invalid parameters (e.g. height = -1)
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KCodecInvalidParameters;

/// error condition constant: The codec was fed with unsupported parameters (e.g. 32 bit per sample)
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KCodecUnsupportedValue;

/// error condition constant: The compressed image is invalid
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KInvalidCompressedData;

/// error condition constant: The images' color transformation is not supported in this bit depth
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KUnsupportedBitDepthForTransform;

/// error condition constant: The images' color transformation is not supported
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KUnsupportedColorTransform;

/// error condition constant: Unsupported bit depth in JPEG-LS transfer syntax
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KUnsupportedBitDepth;

/// error condition constant: Cannot compute number of fragments for JPEG-LS frame
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KCannotComputeNumberOfFragments;

/// error condition constant: Image data mismatch between DICOM header and JPEG-LS bitstream
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KImageDataMismatch;

/// error condition constant: Unsupported photometric interpretation for near-lossless JPEG-LS compression
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KUnsupportedPhotometricInterpretation;

/// error condition constant: Unsupported pixel representation for near-lossless JPEG-LS compression
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KUnsupportedPixelRepresentation;

/// error condition constant: Unsupported type of image for JPEG-LS compression
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KUnsupportedImageType;

/// error condition constant: Trailing data after image
extern DCMJP2K_EXPORT const OFConditionConst EC_J2KTooMuchCompressedData;
