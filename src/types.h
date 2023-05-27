#ifndef TYPES_INCLUDE
#define TYPES_INCLUDE


#include <zfp.h>
#include <zfp/array2.hpp>
#include "array2d.h"
#include <map>
#include <string>

typedef struct {
        double real, imag;
} Amplitude;

using CompressedAmplitudesVector = zfp::array2d;
//using AmplitudesVector = raw::array2d;
typedef std::vector<double> AmplitudesVector;
typedef std::vector<unsigned int> StatesVector;
typedef std::vector<unsigned int> IntegerVector;

#define e 2.7182818284

#endif
