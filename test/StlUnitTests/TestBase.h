
// Borland doesn't support __COUNTER__ so we use the boost version instead.
#if __BORLANDC__
#include <boost/preprocessor/slot/counter.hpp>
#undef TDOG_COUNTER_ID
#define TDOG_COUNTER_ID BOOST_PP_COUNTER
#endif
#pragma warn -8104
#include "tdog.hpp"
#pragma warn .8104
#include <string>
#include <memory>
