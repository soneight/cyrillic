#ifndef SON8_CYRILLIC_DECODE_THREAD_HXX
#define SON8_CYRILLIC_DECODE_THREAD_HXX

#include <son8/cyrillic/decoded.hxx>

namespace son8::cyrillic {
    [[nodiscard]]
    auto decode( Decoded::In in ) -> Decoded;
} // namespace

#endif//SON8_CYRILLIC_DECODE_THREAD_HXX

// Apache License 2.0
// NO WARRANTY OF ANY KIND see <http://www.apache.org/licenses/LICENSE-2.0>
// SPDX-License-Identifier: Apache-2.0
// lib: `cyrillic` C++17 Reversible EruaN Romanization
// Ⓒ Copyright (c) 2025-2026 Oleg'Ease'Kharchuk ᦒ
