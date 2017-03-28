#ifndef cppversion_detectionHPP
#define cppversion_detectionHPP
	#if __BORLANDC__
		#define cpp03 1
	#endif
	#if __cplusplus >= 201103L || _MSC_VER >= 1900
		#define cpp11 1
	#endif
	#if __cplusplus >= 201402 || _MSC_VER > 1900
		#define cpp14 1
	#endif
	#if __cplusplus >= 201500 || _MSC_VER > 1900
		#define cpp17 1
	#endif

  #include "cpp_compat_directives.hpp"
#endif