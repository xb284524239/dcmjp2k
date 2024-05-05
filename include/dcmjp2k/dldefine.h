#pragma once

#include "dcmtk/ofstd/ofexport.h"

#ifdef dcmjpg2k_EXPORTS
#define DCMJP2k_EXPORT DCMTK_DECL_EXPORT
#else
#define DCMJP2k_EXPORT DCMTK_DECL_IMPORT
#endif
