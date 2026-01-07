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
    static_assert( sizeof( ValidateVeiledHalf ) * 2 == sizeof( ValidateVeiled ) );
    constexpr auto Validate_Half_Bits = sizeof( ValidateVeiled ) * 4;

    using ValidateFlagsVeiled = Unt1;
    enum class ValidateFlags : ValidateFlagsVeiled {
        // symbol
        AsciiNullSymbol         = 0x00u, // 00    (  \0   )
        AsciiSpaceSymbol        = 0x01u, // 20    (       )
        AsciiUnderscoreSymbol   = 0x02u, // 5F    (   _   )
        AsciiGraveQuoteSymbol   = 0x03u, // 60    (   `   )
        AsciiSingleQuoteSymbol  = 0x04u, // 27    (  \'   )
        AsciiDoubleQuoteSymbol  = 0x05u, // 22    (  \"   )
        AsciiBackslashSymbol    = 0x06u, // 5C    (  \\   )
        AsciiAudioSymbol        = 0x07u, // 07    (  \a   )
        AsciiBackspaceSymbol    = 0x08u, // 08    (  \b   )
        AsciiTabSymbol          = 0x09u, // 09    (  \t   )
        AsciiNewlineSymbol      = 0x0Au, // 0A    (  \n   )
        AsciiVerticaltabSymbol  = 0x0Bu, // 0B    (  \v   )
        AsciiFormfeedSymbol     = 0x0Cu, // 0C    (  \f   )
        AsciiReturnSymbol       = 0x0Du, // 0D    (  \r   )
        AsciiHashSymbol         = 0x0Eu, // 23    (   #   )
        AsciiCurrencySymbol     = 0x0Fu, // 24    (   $   )
        AsciiPercentSymbol      = 0x10u, // 25    (   %   )
        AsciiEqualSymbol        = 0x11u, // 3D    (   =   )
        AsciiCommercialSymbol   = 0x22u, // 40    (   @   )
        // pair
        AsciiAngleBracketPair   = 0x13u, // 3C,3E ( < , > )
        AsciiCurlyBracketPair   = 0x14u, // 7B,7D ( { , } )
        AsciiRoundBracketPair   = 0x15u, // 28,29 ( ( , ) )
        AsciiArrayBracketPair   = 0x16u, // 5B,5D ( [ , ] )
        // symbols
        AsciiUpperSymbols       = 0x17u, // 41-5A ( A - Z )
        AsciiLowerSymbols       = 0x18u, // 61-7A ( a - z )
        AsciiDigitSymbols       = 0x19u, // 30-39 ( 0 - 9 )
        AsciiTextSymbols        = 0x1Au, // 21,2C,2E,3A,3B,3F ( !,,,.,:,;,? )
        AsciiBitwiseSymbols     = 0x1Bu, // 26,5E,7C,7E ( &,^,|,~ )
        AsciiArithmeticSymbols  = 0x1Cu, // 2A,2B,2D,2F ( *,+,-,/ )
        AsciiOtherSymbols       = 0x1Cu, // 23,24,25,3D,60 ( #,$,%,=,` )
        // bytes
        AsciiControlBytes       = 0x1Du, //
        AsciiExtendedBytes      = 0x1Eu, // 80-FF
        WideBytes               = 0x1Fu, // last bit, wide-like characters
        // IMPORTANT: must be last
        Size_
    };
    static_assert( static_cast< ValidateFlagsVeiled >( ValidateFlags::Size_ ) == Validate_Half_Bits );

    struct ValidateFlagAppend final {
        static constexpr bool append{ true };
        static constexpr bool ignore{ false };
        ValidateFlags data;
        ValidateFlagAppend( ) = delete;
    };
    struct ValidateFlagIgnore final {
        static constexpr bool append{ false };
        static constexpr bool ignore{ true };
        ValidateFlags data;
        ValidateFlagIgnore( ) = delete;
    };
    struct ValidateFlagZeroed final {
        static constexpr bool append{ false };
        static constexpr bool ignore{ false };
        ValidateFlags data;
        ValidateFlagZeroed( ) = delete;
    };

}

#endif//SON8_CYRILLIC_VALIDATE_HXX

// Ⓒ 2025-2026 Oleg'Ease'Kharchuk ᦒ
