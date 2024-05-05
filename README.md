# dcmjp2k

An unofficial plugin for DCMTK and implemention JPEG2000 codec via openjpeg.

## Requirements
- CMake http://www.cmake.org/download/

## Third party dependency
- DCMTK http://dicom.offis.de/
- openjpeg http://www.openjpeg.org/


## Usage
- Decode 
    DCMJP2KDecoderRegistration::registerCodecs();
    DCMJP2KDecoderRegistration::cleanup();

- Encode
    DCMJP2KEncoderRegistration::registerCodecs();
    DCMJP2KEncoderRegistration::cleanup();
