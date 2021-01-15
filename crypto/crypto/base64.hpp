# pragma once
#include <string.h>

// define fixed size integer types
#ifdef _MSC_VER
// Windows
typedef unsigned __int8  uint8_t;
typedef unsigned __int32 uint32_t;
#else
// GCC
#include <stdint.h>
#endif

class BASE64 {
public:
    void    Encode(const char* src, const int len, char* dtc, int* dtc_len);
    int     Decode(const char* src, char* dtc);
};
