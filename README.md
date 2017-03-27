# stl_compat
STL compatibility library providing modern STL features for not-so-modern compilers

All wrapper classes are defined in the "std_compat" namespace.
Wrapper classes that comply with the STL interface are also pulled into the std namespase with using directives.

So non-conforming implementations can be used by using std_compat namespace.

If an official STL implementation exists, it will be available in the std namespace after include the corresponding header from this library.