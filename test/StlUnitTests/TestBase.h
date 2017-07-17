
// Borland doesn't support __COUNTER__ so we use the boost version instead.
#if __BORLANDC__
#include <boost/preprocessor/slot/counter.hpp>
#undef TDOG_COUNTER_ID
#define TDOG_COUNTER_ID BOOST_PP_COUNTER
#endif
#ifdef __BORLANDC__
#pragma warn -8104
#endif
#include "tdog.hpp"
#ifdef __BORLANDC__
#pragma warn .8104
#endif
#include <string>
#include <memory>
