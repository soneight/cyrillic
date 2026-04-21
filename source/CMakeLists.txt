set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

add_library( ${SON8_LIB} )
target_sources( ${SON8_LIB} PRIVATE cyrillic.cxx )

# Apache License 2.0
# NO WARRANTY OF ANY KIND see <http://www.apache.org/licenses/LICENSE-2.0>
# SPDX-License-Identifier: Apache-2.0
# lib: `cyrillic` C++17 Reversible EruaN Romanization
# Ⓒ Copyright (c) 2025-2026 Oleg'Ease'Kharchuk ᦒ
