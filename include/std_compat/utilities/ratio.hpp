#ifndef ratioHPP
#define ratioHPP
#include "../helper/cppversion_detection.hpp"
#if cpp11
#include <ratio>
#else
#include "chrono/ratio_boost_wrapper.hpp"
#endif
#endif