#include "cppversion_detection.hpp"
#if !cpp11
#define noexcept throw()
#define nullptr NULL
#define emplace_back push_back
#define override
#define final 
#endif