cmake_minimum_required( VERSION 3.8...3.27 )
project( cyrillic VERSION 0.0.0 LANGUAGES CXX )

set( SON8PROJ son8__${PROJECT_NAME} )

add_subdirectory( source )
add_library( son8::${PROJECT_NAME} ALIAS ${SON8PROJ} )
target_include_directories( ${SON8PROJ} PUBLIC include )
