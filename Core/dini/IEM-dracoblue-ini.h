#ifndef INIENGINE_MODULE_DRACOBLUE_H_
#define INIENGINE_MODULE_DRACOBLUE_H_

#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

    #ifdef INIENGINE_MODULE_DRACOBLUE_BUILD
    #define INIENGINE_MODULE_DRACOBLUE_LIB __declspec(dllexport)
    #else
    #define INIENGINE_MODULE_DRACOBLUE_LIB __declspec(dllimport)
    #endif

    #include "../../Modules/dini/Core/dracoblue-implementation.h"

#ifdef __cplusplus
}
#endif


#endif
