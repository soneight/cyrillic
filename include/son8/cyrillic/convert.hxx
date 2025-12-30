#ifndef SON8_CYRILLIC_CONVERT_HXX
#define SON8_CYRILLIC_CONVERT_HXX

#include <son8/cyrillic/alias.hxx>

namespace son8::cyrillic {

    [[nodiscard]] auto string_byte( StringWordView in ) -> StringByte;
    [[nodiscard]] auto string_word( StringByteView in ) -> StringWord;

}

#endif//SON8_CYRILLIC_CONVERT_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
