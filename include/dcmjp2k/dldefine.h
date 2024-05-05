#pragma once

#include "dcmtk/ofstd/ofexport.h"

#ifdef dcmjp2k_EXPORTS
#define DCMJP2K_EXPORT DCMTK_DECL_EXPORT
#else
#define DCMJP2K_EXPORT DCMTK_DECL_IMPORT
#endif
