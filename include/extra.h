#pragma once

#include "main.h"

#ifdef _DEBUG
    #define print(...) wprintf_s(__VA_ARGS__)
#else
    #define print(...) ((void)0)
#endif
