#ifndef SON8_CYRILLIC_EXCEPTION_HXX
#define SON8_CYRILLIC_EXCEPTION_HXX

#include <son8/cyrillic/error.hxx>
// std headers
#include <exception>

namespace son8::cyrillic {

    class Exception : public std::exception {
        Error code_;
    public:
        Exception( Error code_ ) noexcept;
       ~Exception( ) = default;
        auto code( ) const noexcept -> Error;
        auto what( ) const noexcept -> char const * override;
    };

}

#endif//SON8_CYRILLIC_EXCEPTION_HXX

// Apache License 2.0
// NO WARRANTY OF ANY KIND see <http://www.apache.org/licenses/LICENSE-2.0>
// SPDX-License-Identifier: Apache-2.0
// lib: `cyrillic` C++17 Reversible EruaN Romanization
// Ⓒ Copyright (c) 2025-2026 Oleg'Ease'Kharchuk ᦒ
