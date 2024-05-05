#include "dcmjp2k/djcparam.h"

DcmJp2kCodecParameter::DcmJp2kCodecParameter(OFBool jp2k_optionsEnabled, Uint16 jp2k_cblkwidth, Uint16 jp2k_cblkheight, OFBool preferCookedEncoding, Uint32 fragmentSize, OFBool createOffsetTable,
                                             J2K_UIDCreation uidCreation, OFBool convertToSC, J2K_PlanarConfiguration planarConfiguration, OFBool ignoreOffsetTble)
    : DcmCodecParameter(),
      jp2k_optionsEnabled_(jp2k_optionsEnabled),
      jp2k_cblkwidth_(jp2k_cblkwidth),
      jp2k_cblkheight_(jp2k_cblkheight),
      fragmentSize_(fragmentSize),
      createOffsetTable_(createOffsetTable),
      preferCookedEncoding_(preferCookedEncoding),
      uidCreation_(uidCreation),
      convertToSC_(convertToSC),
      planarConfiguration_(planarConfiguration),
      ignoreOffsetTable_(ignoreOffsetTble) {}

DcmJp2kCodecParameter::DcmJp2kCodecParameter(J2K_UIDCreation uidCreation, J2K_PlanarConfiguration planarConfiguration, OFBool ignoreOffsetTble)
    : DcmCodecParameter(),
      jp2k_optionsEnabled_(OFFalse),
      jp2k_cblkwidth_(0),
      jp2k_cblkheight_(1),
      fragmentSize_(0),
      createOffsetTable_(OFTrue),
      preferCookedEncoding_(OFTrue),
      uidCreation_(uidCreation),
      convertToSC_(OFFalse),
      planarConfiguration_(planarConfiguration),
      ignoreOffsetTable_(ignoreOffsetTble) {}

DcmJp2kCodecParameter::DcmJp2kCodecParameter(const DcmJp2kCodecParameter &arg)
    : DcmCodecParameter(arg)

      ,
      jp2k_optionsEnabled_(arg.jp2k_optionsEnabled_),
      jp2k_cblkwidth_(arg.jp2k_cblkwidth_),
      jp2k_cblkheight_(arg.jp2k_cblkheight_),
      fragmentSize_(arg.fragmentSize_),
      createOffsetTable_(arg.createOffsetTable_),
      preferCookedEncoding_(arg.preferCookedEncoding_),
      uidCreation_(arg.uidCreation_),
      convertToSC_(arg.convertToSC_),
      planarConfiguration_(arg.planarConfiguration_),
      ignoreOffsetTable_(arg.ignoreOffsetTable_) {}

DcmJp2kCodecParameter::~DcmJp2kCodecParameter() {}

DcmCodecParameter *DcmJp2kCodecParameter::clone() const { return new DcmJp2kCodecParameter(*this); }

const char *DcmJp2kCodecParameter::className() const { return "DcmJp2kCodecParameter"; }
