#include "cppversion_detection.hpp"
#if !cpp11
#define noexcept throw()
#define nullptr NULL
#define emplace_back push_back
#define override
#define final 
#endif
#if cpp11
#define foreach(A,B) for(A:B)
#else
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
#endif