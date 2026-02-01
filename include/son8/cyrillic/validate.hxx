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
        Ascii_Symbol_Null       = 0x00u, // 00    (  \0   )
        Ascii_Symbol_Space      = 0x01u, // 20    (       )
        Ascii_Symbol_Underscore = 0x02u, // 5F    (   _   )
        Ascii_Symbol_Gravequote = 0x03u, // 60    (   `   )
        Ascii_Symbol_Singlequote= 0x04u, // 27    (  \'   )
        Ascii_Symbol_Doublequote= 0x05u, // 22    (  \"   )
        Ascii_Symbol_Backslash  = 0x06u, // 5C    (  \\   )
        Ascii_Symbol_Audio      = 0x07u, // 07    (  \a   )
        Ascii_Symbol_Backspace  = 0x08u, // 08    (  \b   )
        Ascii_Symbol_Tab        = 0x09u, // 09    (  \t   )
        Ascii_Symbol_Newline    = 0x0Au, // 0A    (  \n   )
        Ascii_Symbol_Verticaltab= 0x0Bu, // 0B    (  \v   )
        Ascii_Symbol_Formfeed   = 0x0Cu, // 0C    (  \f   )
        Ascii_Symbol_Return     = 0x0Du, // 0D    (  \r   )
        Ascii_Symbol_Hash       = 0x0Eu, // 23    (   #   )
        Ascii_Symbol_Currency   = 0x0Fu, // 24    (   $   )
        Ascii_Symbol_Percent    = 0x10u, // 25    (   %   )
        Ascii_Symbol_Equal      = 0x11u, // 3D    (   =   )
        Ascii_Symbol_Commercial = 0x12u, // 40    (   @   )
        // pair
        Ascii_Brackets_Round     = 0x13u, // 28,29 ( ( , ) )
        Ascii_Brackets_Angle     = 0x14u, // 3C,3E ( < , > )
        Ascii_Brackets_Array     = 0x15u, // 5B,5D ( [ , ] )
        Ascii_Brackets_Curly     = 0x16u, // 7B,7D ( { , } )
        // range
        Ascii_Range_Digit       = 0x17u, // 30-39 ( 0 - 9 )
        Ascii_Range_Upper       = 0x18u, // 41-5A ( A - Z )
        Ascii_Range_Lower       = 0x19u, // 61-7A ( a - z )
        // list
        Ascii_List_Text         = 0x1Au, // 21,2C,2E,3A,3B,3F ( !,,,.,:,;,? )
        Ascii_List_Bitwise      = 0x1Bu, // 26,5E,7C,7E ( &,^,|,~ )
        Ascii_List_Arithmetic   = 0x1Cu, // 2A,2B,2D,2F ( *,+,-,/ )
        // bytes
        Ascii_Bytes_Control     = 0x1Du, //
        Ascii_Bytes_Extended    = 0x1Eu, // 80-FF
        Wide_Bytes              = 0x1Fu, // last bit, wide-like characters
        // IMPORTANT: must be last
        Size_
    };

    template< bool Append, bool Ignore >
    class ValidateFlag final {
        using Data_ = ValidateFlags;
        Data_ data_;
    public:
        static constexpr bool append{ Append };
        static constexpr bool ignore{ Ignore };
        explicit ValidateFlag( Data_ flag ) noexcept : data_{ flag } { }
        operator Data_( ) const noexcept { return data_; }
    };

    using ValidateFlagAppend = ValidateFlag< true, false >;
    using ValidateFlagIgnore = ValidateFlag< false, true >;
    using ValidateFlagZeroed = ValidateFlag< false, false >;

}

#endif//SON8_CYRILLIC_VALIDATE_HXX

// Ⓒ 2025-2026 Oleg'Ease'Kharchuk ᦒ
