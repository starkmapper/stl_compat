#ifndef cppversion_detectionHPP
#define cppversion_detectionHPP
	#if __BORLANDC__
		#define cpp03 1
	#endif
	#if __cplusplus >= 201103L || _MSVC_LANG >= 201103L
		#define cpp11 1
	#endif
	#if __cplusplus >= 201402 || _MSVC_LANG >= 201402
		#define cpp14 1
	#endif
	#if __cplusplus >= 201500 || _MSVC_LANG > 201402
		#define cpp17 1
	#endif

  #include "cpp_compat_directives.hpp"
#endif