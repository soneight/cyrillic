#ifndef SON8_CYRILLIC_CONVERT_HXX
#define SON8_CYRILLIC_CONVERT_HXX

#include <son8/cyrillic/alias.hxx>

namespace son8::cyrillic {

    [[nodiscard]] auto string_byte( StringWordView in ) -> StringByte;
    [[nodiscard]] auto string_word( StringByteView in ) -> StringWord;

}

#endif//SON8_CYRILLIC_CONVERT_HXX

// Apache License 2.0
// NO WARRANTY OF ANY KIND see <http://www.apache.org/licenses/LICENSE-2.0>
// SPDX-License-Identifier: Apache-2.0
// lib: `cyrillic` C++17 Reversible EruaN Romanization
// Ⓒ Copyright (c) 2025-2026 Oleg'Ease'Kharchuk ᦒ
