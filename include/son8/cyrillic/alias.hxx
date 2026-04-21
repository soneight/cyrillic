#ifndef SON8_CYRILLIC_ALIAS_HXX
#define SON8_CYRILLIC_ALIAS_HXX

#include <cstddef> // size_t
#include <cstdint> // u?int*
#include <string>
#include <string_view>

namespace son8::cyrillic {
    // integer aliases
    using Size = std::size_t;
    using Int0 = std::int8_t;
    using Int1 = std::int16_t;
    using Int2 = std::int32_t;
    using Int3 = std::int64_t;
    using Unt0 = std::uint8_t;
    using Unt1 = std::uint16_t;
    using Unt2 = std::uint32_t;
    using Unt3 = std::uint64_t;
    // string aliases
    using StringByte = std::string;
    using StringWord = std::u16string;
    using StringByteView = std::string_view;
    using StringWordView = std::u16string_view;

} // namespace

#endif//SON8_CYRILLIC_ALIAS_HXX

// Apache License 2.0
// NO WARRANTY OF ANY KIND see <http://www.apache.org/licenses/LICENSE-2.0>
// SPDX-License-Identifier: Apache-2.0
// lib: `cyrillic` C++17 Reversible EruaN Romanization
// Ⓒ Copyright (c) 2025-2026 Oleg'Ease'Kharchuk ᦒ
