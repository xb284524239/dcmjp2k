# dcmjp2k

An unofficial plugin for DCMTK and implemention JPEG2000 codec via openjpeg.

## Requirements
- CMake http://www.cmake.org/download/

## Third party dependency
- DCMTK http://dicom.offis.de/
- openjpeg http://www.openjpeg.org/


## Usage
##### Decode
  
   1. DcmJp2kDecoderRegistration::registerCodecs();
   2. DcmJp2kDecoderRegistration::cleanup();

##### Encode
 
   1. DcmJp2kEncoderRegistration::registerCodecs();
   2. DcmJp2kEncoderRegistration::cleanup();
