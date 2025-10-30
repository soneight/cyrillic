set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

add_library( ${SON8PROJ} )
target_sources( ${SON8PROJ} PRIVATE cyrillic.cxx )
target_compile_options( ${SON8PROJ} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/permissive- /utf-8> )
