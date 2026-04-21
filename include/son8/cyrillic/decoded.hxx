#ifndef SON8_CYRILLIC_DECODED_HXX
#define SON8_CYRILLIC_DECODED_HXX

#include <son8/cyrillic/alias.hxx>

namespace son8::cyrillic {

    class Decoded final {
        using Data_ = StringWord;
        Data_ data_;
    public:
        // public aliases
        using View = StringWordView;
        using Data = Data_;
        using Out = Data &;
        using Ref = Data const &;
        using Fwd = Data &&;
        using Ptr = Data::value_type *;
        using In = StringByteView;
        // constructors
        Decoded( ) = default;
       ~Decoded( ) = default;
        Decoded( In in );
        Decoded( Decoded &&move ) = default;
        Decoded( Decoded const &copy ) = default;
        Decoded &operator=( Decoded &&move ) = default;
        Decoded &operator=( Decoded const &copy ) = default;
        // getters
        [[nodiscard]] auto ref( ) const & noexcept -> Ref; // reading access via const reference
        [[nodiscard]] auto ptr( ) &       noexcept -> Ptr; // pointer access to underlying data
        [[nodiscard]] auto out( ) &       noexcept -> Out; // mutable access for modification
        [[nodiscard]] auto fwd( ) &       noexcept -> Fwd; // forward borrow resource
        [[nodiscard]] auto fwd( ) &&      noexcept ->Data; // forward steals resource
        // conversions
        operator View( ) const;
    };

} // namespace

#endif//SON8_CYRILLIC_DECODED_HXX

// Apache License 2.0
// NO WARRANTY OF ANY KIND see <http://www.apache.org/licenses/LICENSE-2.0>
// SPDX-License-Identifier: Apache-2.0
// lib: `cyrillic` C++17 Reversible EruaN Romanization
// Ⓒ Copyright (c) 2025-2026 Oleg'Ease'Kharchuk ᦒ
