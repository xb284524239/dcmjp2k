#pragma once

#include "dcmjp2k/dldefine.h"
#include "dcmtk/dcmdata/dccodec.h" /* for class DcmCodec */
#include "dcmtk/ofstd/ofstring.h"

/* forward declaration */
class DcmJp2kCodecParameter;

/** abstract codec class for JPEG-2000 decoders.
 *  This abstract class contains most of the application logic
 *  needed for a dcmdata codec object that implements a JPEG-2000 decoder.
 *  This class only supports decompression, it neither implements
 *  encoding nor transcoding.
 */
class DCMJP2K_EXPORT DcmJp2kDecoderBase : public DcmCodec {
   public:
    /// default constructor
    DcmJp2kDecoderBase();

    /// destructor
    virtual ~DcmJp2kDecoderBase();

    /** decompresses the given pixel sequence and
     *  stores the result in the given uncompressedPixelData element.
     *  @param fromRepParam current representation parameter of compressed data, may be NULL
     *  @param pixSeq compressed pixel sequence
     *  @param uncompressedPixelData uncompressed pixel data stored in this element
     *  @param cp codec parameters for this codec
     *  @param objStack stack pointing to the location of the pixel data
     *    element in the current dataset.
     *  @return EC_Normal if successful, an error code otherwise.
     */
    virtual OFCondition decode(const DcmRepresentationParameter *fromRepParam, DcmPixelSequence *pixSeq, DcmPolymorphOBOW &uncompressedPixelData, const DcmCodecParameter *cp,
                               const DcmStack &objStack) const;

    /** decompresses the given pixel sequence and
     *  stores the result in the given uncompressedPixelData element.
     *  @param fromRepParam current representation parameter of compressed data, may be NULL
     *  @param pixSeq compressed pixel sequence
     *  @param uncompressedPixelData uncompressed pixel data stored in this element
     *  @param cp codec parameters for this codec
     *  @param objStack stack pointing to the location of the pixel data
     *    element in the current dataset.
     *  @param removeOldRep boolean flag that should be set to false before this method call
     *    and will be set to true if the codec modifies the DICOM dataset such
     *    that the pixel data of the original representation may not be usable
     *    anymore.
     *  @return EC_Normal if successful, an error code otherwise.
     */
    virtual OFCondition decode(const DcmRepresentationParameter *fromRepParam, DcmPixelSequence *pixSeq, DcmPolymorphOBOW &uncompressedPixelData, const DcmCodecParameter *cp, const DcmStack &objStack,
                               OFBool &removeOldRep) const;

    /** decompresses a single frame from the given pixel sequence and
     *  stores the result in the given buffer.
     *  @param fromParam representation parameter of current compressed
     *    representation, may be NULL.
     *  @param fromPixSeq compressed pixel sequence
     *  @param cp codec parameters for this codec
     *  @param dataset pointer to dataset in which pixel data element is contained
     *  @param frameNo number of frame, starting with 0 for the first frame
     *  @param startFragment index of the compressed fragment that contains
     *    all or the first part of the compressed bitstream for the given frameNo.
     *    Upon successful return this parameter is updated to contain the index
     *    of the first compressed fragment of the next frame.
     *    When unknown, zero should be passed. In this case the decompression
     *    algorithm will try to determine the index by itself, which will always
     *    work if frames are decompressed in increasing order from first to last,
     *    but may fail if frames are decompressed in random order, multiple fragments
     *    per frame and multiple frames are present in the dataset, and the offset
     *    table is empty.
     *  @param buffer pointer to buffer where frame is to be stored
     *  @param bufSize size of buffer in bytes
     *  @param decompressedColorModel upon successful return, the color model
     *    of the decompressed image (which may be different from the one used
     *    in the compressed images) is returned in this parameter.
     *  @return EC_Normal if successful, an error code otherwise.
     */
    virtual OFCondition decodeFrame(const DcmRepresentationParameter *fromParam, DcmPixelSequence *fromPixSeq, const DcmCodecParameter *cp, DcmItem *dataset, Uint32 frameNo, Uint32 &startFragment,
                                    void *buffer, Uint32 bufSize, OFString &decompressedColorModel) const;

    /** compresses the given uncompressed DICOM image and stores
     *  the result in the given pixSeq element.
     *  @param pixelData pointer to the uncompressed image data in OW format
     *    and local byte order
     *  @param length of the pixel data field in bytes
     *  @param toRepParam representation parameter describing the desired
     *    compressed representation (e.g. JPEG quality)
     *  @param pixSeq compressed pixel sequence (pointer to new DcmPixelSequence object
     *    allocated on heap) returned in this parameter upon success.
     *  @param cp codec parameters for this codec
     *  @param objStack stack pointing to the location of the pixel data
     *    element in the current dataset.
     *  @return EC_Normal if successful, an error code otherwise.
     */
    virtual OFCondition encode(const Uint16 *pixelData, const Uint32 length, const DcmRepresentationParameter *toRepParam, DcmPixelSequence *&pixSeq, const DcmCodecParameter *cp,
                               DcmStack &objStack) const;

    /** compresses the given uncompressed DICOM image and stores
     *  the result in the given pixSeq element.
     *  @param pixelData pointer to the uncompressed image data in OW format
     *    and local byte order
     *  @param length of the pixel data field in bytes
     *  @param toRepParam representation parameter describing the desired
     *    compressed representation (e.g. JPEG quality)
     *  @param pixSeq compressed pixel sequence (pointer to new DcmPixelSequence object
     *    allocated on heap) returned in this parameter upon success.
     *  @param cp codec parameters for this codec
     *  @param objStack stack pointing to the location of the pixel data
     *    element in the current dataset.
     *  @param removeOldRep boolean flag that should be set to false before this method call
     *    and will be set to true if the codec modifies the DICOM dataset such
     *    that the pixel data of the original representation may not be usable
     *    anymore.
     *  @return EC_Normal if successful, an error code otherwise.
     */
    virtual OFCondition encode(const Uint16 *pixelData, const Uint32 length, const DcmRepresentationParameter *toRepParam, DcmPixelSequence *&pixSeq, const DcmCodecParameter *cp, DcmStack &objStack,
                               OFBool &removeOldRep) const;

    /** transcodes (re-compresses) the given compressed DICOM image and stores
     *  the result in the given toPixSeq element.
     *  @param fromRepType current transfer syntax of the compressed image
     *  @param fromRepParam current representation parameter of compressed data, may be NULL
     *  @param fromPixSeq compressed pixel sequence
     *  @param toRepParam representation parameter describing the desired
     *    new compressed representation (e.g. JPEG quality)
     *  @param toPixSeq compressed pixel sequence (pointer to new DcmPixelSequence object
     *    allocated on heap) returned in this parameter upon success.
     *  @param cp codec parameters for this codec
     *  @param objStack stack pointing to the location of the pixel data
     *    element in the current dataset.
     *  @return EC_Normal if successful, an error code otherwise.
     */
    virtual OFCondition encode(const E_TransferSyntax fromRepType, const DcmRepresentationParameter *fromRepParam, DcmPixelSequence *fromPixSeq, const DcmRepresentationParameter *toRepParam,
                               DcmPixelSequence *&toPixSeq, const DcmCodecParameter *cp, DcmStack &objStack) const;

    /** transcodes (re-compresses) the given compressed DICOM image and stores
     *  the result in the given toPixSeq element.
     *  @param fromRepType current transfer syntax of the compressed image
     *  @param fromRepParam current representation parameter of compressed data, may be NULL
     *  @param fromPixSeq compressed pixel sequence
     *  @param toRepParam representation parameter describing the desired
     *    new compressed representation (e.g. JPEG quality)
     *  @param toPixSeq compressed pixel sequence (pointer to new DcmPixelSequence object
     *    allocated on heap) returned in this parameter upon success.
     *  @param cp codec parameters for this codec
     *  @param objStack stack pointing to the location of the pixel data
     *    element in the current dataset.
     *  @param removeOldRep boolean flag that should be set to false before this method call
     *    and will be set to true if the codec modifies the DICOM dataset such
     *    that the pixel data of the original representation may not be usable
     *    anymore.
     *  @return EC_Normal if successful, an error code otherwise.
     */
    virtual OFCondition encode(const E_TransferSyntax fromRepType, const DcmRepresentationParameter *fromRepParam, DcmPixelSequence *fromPixSeq, const DcmRepresentationParameter *toRepParam,
                               DcmPixelSequence *&toPixSeq, const DcmCodecParameter *cp, DcmStack &objStack, OFBool &removeOldRep) const;

    /** checks if this codec is able to convert from the
     *  given current transfer syntax to the given new
     *  transfer syntax
     *  @param oldRepType current transfer syntax
     *  @param newRepType desired new transfer syntax
     *  @return true if transformation is supported by this codec, false otherwise.
     */
    virtual OFBool canChangeCoding(const E_TransferSyntax oldRepType, const E_TransferSyntax newRepType) const;

    /** determine color model of the decompressed image
     *  @param fromParam representation parameter of current compressed
     *    representation, may be NULL
     *  @param fromPixSeq compressed pixel sequence
     *  @param cp codec parameters for this codec
     *  @param dataset pointer to dataset in which pixel data element is contained
     *  @param dataset pointer to DICOM dataset in which this pixel data object
     *    is located. Used to access photometric interpretation.
     *  @param decompressedColorModel upon successful return, the color model
     *    of the decompressed image (which may be different from the one used
     *    in the compressed images) is returned in this parameter
     *  @return EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition determineDecompressedColorModel(const DcmRepresentationParameter *fromParam, DcmPixelSequence *fromPixSeq, const DcmCodecParameter *cp, DcmItem *dataset,
                                                        OFString &decompressedColorModel) const;

   private:
    // static private helper methods

    /** decompresses a single frame from the given pixel sequence and
     *  stores the result in the given buffer.
     *  @param fromPixSeq compressed pixel sequence
     *  @param cp codec parameters for this codec
     *  @param dataset pointer to dataset in which pixel data element is contained
     *  @param frameNo number of frame, starting with 0 for the first frame
     *  @param startFragment index of the compressed fragment that contains
     *    all or the first part of the compressed bitstream for the given frameNo.
     *    Upon successful return this parameter is updated to contain the index
     *    of the first compressed fragment of the next frame.
     *    When unknown, zero should be passed. In this case the decompression
     *    algorithm will try to determine the index by itself, which will always
     *    work if frames are decompressed in increasing order from first to last,
     *    but may fail if frames are decompressed in random order, multiple fragments
     *    per frame and multiple frames are present in the dataset, and the offset
     *    table is empty.
     *  @param buffer pointer to buffer where frame is to be stored
     *  @param bufSize size of buffer in bytes
     *  @param imageFrames number of frames in this image
     *  @param imageColumns number of columns for each frame
     *  @param imageRows number of rows for each frame
     *  @param imageSamplesPerPixel number of samples per pixel
     *  @param bytesPerSample number of bytes per sample
     *  @return EC_Normal if successful, an error code otherwise.
     */
    static OFCondition decodeFrame(DcmPixelSequence *fromPixSeq, const DcmJp2kCodecParameter *cp, DcmItem *dataset, Uint32 frameNo, Uint32 &startFragment, void *buffer, Uint32 bufSize,
                                   Sint32 imageFrames, Uint16 imageColumns, Uint16 imageRows, Uint16 imageSamplesPerPixel, Uint16 bytesPerSample);

    /** determines if a given image requires color-by-plane planar configuration
     *  depending on SOP Class UID (DICOM IOD) and photometric interpretation.
     *  All SOP classes defined in the 2003 edition of the DICOM standard or earlier
     *  are handled correctly.
     *  @param sopClassUID SOP Class UID
     *  @param photometricInterpretation decompressed photometric interpretation
     *  @return legal value for planar configuration
     */
    static Uint16 determinePlanarConfiguration(const OFString &sopClassUID, const OFString &photometricInterpretation);

    /** computes the number of fragments (pixel items) that comprise the current
     *  frame in the compressed pixel sequence. This method uses various approaches
     *  to compute the number of fragments for a frame, including a check of the
     *  offset table and checking the start of each fragment for JPEG SOI markers.
     *  @param numberOfFrames total number of frames of the DICOM object
     *  @param currentFrame index of current frame (0..numberOfFrames-1)
     *  @param startItem index of fragment (pixel item) the frame starts with
     *  @param ignoreOffsetTable flag instructing the method to ignore the offset table
     *    even if present and presumably useful
     *  @param pixSeq the compressed JPEG-2000 pixel sequence
     *  @return number of fragments for the current frame, zero upon error
     */
    static Uint32 computeNumberOfFragments(Sint32 numberOfFrames, Uint32 currentFrame, Uint32 startItem, OFBool ignoreOffsetTable, DcmPixelSequence *pixSeq);

    /** check whether the given buffer contains a JPEG-2000 start-of-image code
     *  @param fragmentData pointer to 4 or more bytes of JPEG-2000 data
     *  @returns true if the first four bytes of the code stream indicate that
     *     this fragment is the start of a new JPEG-2000 image, i.e. starts with
     *     an SOI marker followed by SOF, COM or APPn.
     */
    static OFBool isJPEGLSStartOfImage(Uint8 *fragmentData);

    /** converts an RGB or YBR frame with 8 bits/sample from
     *  color-by-pixel to color-by-plane planar configuration.
     *  @param imageFrame pointer to image frame, must contain
     *    at least 3*columns*rows bytes of pixel data.
     *  @param columns columns
     *  @param rows rows
     *  @return EC_Normal if successful, an error code otherwise
     */
    static OFCondition createPlanarConfiguration1Byte(Uint8 *imageFrame, Uint16 columns, Uint16 rows);

    /** converts an RGB or YBR frame with 16 bits/sample from
     *  color-by-pixel to color-by-plane planar configuration.
     *  @param imageFrame pointer to image frame, must contain
     *    at least 3*columns*rows words of pixel data.
     *  @param columns columns
     *  @param rows rows
     *  @return EC_Normal if successful, an error code otherwise
     */
    static OFCondition createPlanarConfiguration1Word(Uint16 *imageFrame, Uint16 columns, Uint16 rows);

    /** converts an RGB or YBR frame with 8 bits/sample from
     *  color-by-plane to color-by-pixel planar configuration.
     *  @param imageFrame pointer to image frame, must contain
     *    at least 3*columns*rows bytes of pixel data.
     *  @param columns columns
     *  @param rows rows
     *  @return EC_Normal if successful, an error code otherwise
     */
    static OFCondition createPlanarConfiguration0Byte(Uint8 *imageFrame, Uint16 columns, Uint16 rows);

    /** converts an RGB or YBR frame with 16 bits/sample from
     *  color-by-plane to color-by-pixel planar configuration.
     *  @param imageFrame pointer to image frame, must contain
     *    at least 3*columns*rows words of pixel data.
     *  @param columns columns
     *  @param rows rows
     *  @return EC_Normal if successful, an error code otherwise
     */
    static OFCondition createPlanarConfiguration0Word(Uint16 *imageFrame, Uint16 columns, Uint16 rows);
};

/** codec class for JPEG-2000 lossy and lossless TS decoding
 */
class DCMJP2K_EXPORT DcmJp2kDecoder : public DcmJp2kDecoderBase {};
