#include <dcmtk/dcmdata/dcfilefo.h>

#include <format>
#include <iostream>

#include "dcmjp2k/djdecode.h"

std::ostream &operator<<(std::ostream &cout, const OFCondition &ofc) {
    cout << std::boolalpha << "{status: " << ofc.good() << ", code: " << ofc.code() << ", text: " << ofc.text() << "}";
    return cout;
}

std::ostream &operator<<(std::ostream &cout, const DcmXfer &xfer) {
    cout << xfer.getXferID() << " [" << xfer.getXferName() << "]";
    return cout;
}

std::string toString(const OFCondition &ofc) { return std::format("[status: {}, code: {}, text: {}]", (ofc.good() ? "true" : "false"), ofc.code(), ofc.text()); }

std::string toString(const DcmXfer &xfer) { return std::format("{} [{}]", xfer.getXferID(), xfer.getXferName()); }

std::string toString(E_TransferSyntax syntax) {
    DcmXfer xfer(syntax);
    return toString(xfer);
}

int main(int argc, char *argv[]) {
    const char *filename2 = R"(C:\Users\paul\Downloads\DICOM\self_pacs\1.2.840.113619.2.80.3009249241.158823.1651195780.2.DCM)";  // JPEG 2000 (Lossless only)

    DcmJp2kDecoderRegistration::registerCodecs();

    DcmFileFormat format;
    std::cout << "reading input file is: " << filename2 << std::endl;

    OFCondition ofc = format.loadFile(filename2);
    if (ofc.bad()) {
        std::cout << toString(ofc) << ": reading file: " << filename2 << std::endl;
        return 1;
    }
    ofc = format.convertToUTF8();
    std::cout << "Convert To Utf8: " << toString(ofc) << std::endl;
    if (format.getDataset()->getCurrentXfer() != EXS_LittleEndianExplicit) {
        ofc = format.chooseRepresentation(EXS_LittleEndianExplicit, nullptr);
        std::cout << "Choose Transfer Syntax: " << toString(ofc) << ", Original Transfer Syntax Is: " << toString(format.getDataset()->getOriginalXfer()) << std::endl;

        bool can = format.canWriteXfer(EXS_LittleEndianExplicit);
        std::cout << "Can Write To New Transfer Syntax: " << std::boolalpha << can << std::endl;
    }
    // deregister global decompression codecs
    DcmJp2kDecoderRegistration::cleanup();

    return 0;
}