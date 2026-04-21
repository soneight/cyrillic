cmake_minimum_required( VERSION 3.8...3.27 )
project( cyrillic VERSION 0.0.0 LANGUAGES CXX )
set( SON8_LIB son8__${PROJECT_NAME} )
# Private configuration under source directory
add_subdirectory( source )
add_library( son8::${PROJECT_NAME} ALIAS ${SON8_LIB} )
target_compile_features( ${SON8_LIB} PUBLIC cxx_std_17 )
target_compile_options( ${SON8_LIB} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/utf-8 /permissive- /Zc:__cplusplus> )
target_include_directories( ${SON8_LIB} PUBLIC include )

# Apache License 2.0
# NO WARRANTY OF ANY KIND see <http://www.apache.org/licenses/LICENSE-2.0>
# SPDX-License-Identifier: Apache-2.0
# lib: `cyrillic` C++17 Reversible EruaN Romanization
# Ⓒ Copyright (c) 2025-2026 Oleg'Ease'Kharchuk ᦒ
