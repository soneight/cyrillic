#ifndef SON8_CYRILLIC_VALIDATE_HXX
#define SON8_CYRILLIC_VALIDATE_HXX

#include <son8/cyrillic/alias.hxx>

namespace son8::cyrillic {

    using ValidateVeiled = Unt3;
    enum class Validate : ValidateVeiled {
        None      = 0x00000000'00000000u,
        IgnoreAll = 0x00000000'FFFFFFFFu,
        AppendAll = 0xFFFFFFFF'00000000u,
    };
    using ValidateVeiledHalf = Unt2;
    constexpr auto Validate_Half_Bits = sizeof( ValidateVeiled ) * 4;

    using ValidateFlagsVeiled = Unt1;
    enum class ValidateFlags : ValidateFlagsVeiled {
        AsciiLatin = 0u,
        Wide = Validate_Half_Bits - 1u // last bit, non-ascii or wide character
    };

    struct ValidateFlagAppend final {
        static constexpr bool type{ true };
        ValidateFlags data;
        ValidateFlagAppend() = delete;
    };
    struct ValidateFlagIgnore final {
        static constexpr bool type{ false };
        ValidateFlags data;
        ValidateFlagIgnore() = delete;
    };

}

#endif//SON8_CYRILLIC_VALIDATE_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
