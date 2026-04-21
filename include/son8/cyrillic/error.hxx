#ifndef SON8_CYRILLIC_ERROR_HXX
#define SON8_CYRILLIC_ERROR_HXX

namespace son8::cyrillic {

    enum class Error : unsigned {
        None,
        Language,
        InvalidWord,
        InvalidByte,
        ConvertFailed,
        ValidateMisconfigured,
        // !IMPORTANT must be last element
        Size_,
    };

    auto error_message( Error code ) noexcept -> char const *;

} // namespace

#endif//SON8_CYRILLIC_ERROR_HXX

// Apache License 2.0
// NO WARRANTY OF ANY KIND see <http://www.apache.org/licenses/LICENSE-2.0>
// SPDX-License-Identifier: Apache-2.0
// lib: `cyrillic` C++17 Reversible EruaN Romanization
// Ⓒ Copyright (c) 2025-2026 Oleg'Ease'Kharchuk ᦒ
