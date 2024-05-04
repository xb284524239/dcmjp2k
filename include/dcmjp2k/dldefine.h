/*
 *
 *  Copyright (C) 2015, Ing-Long Eric Kuo
 *  All rights reserved.  See COPYRIGHT file for details.
 *
 *  This software and supporting documentation were developed by
 *
 *
 *
 *  Module:  fmjpeg2k
 *
 *  Author:  Ing-Long Eric Kuo
 *
 *  Purpose: Contains preprocessor definitions
 *
 */


// #ifndef DL2KDEFINE_H
// #define DL2KDEFINE_H
#pragma once

#include "dcmtk/ofstd/ofexport.h"

#ifdef dcmjpg2k_EXPORTS
#define DCMJP2k_EXPORT DCMTK_DECL_EXPORT
#else
#define DCMJP2k_EXPORT DCMTK_DECL_IMPORT
#endif


// #endif
