#ifndef SON8_CYRILLIC_DECODE_RETURN_HXX
#define SON8_CYRILLIC_DECODE_RETURN_HXX

#include <son8/cyrillic/alias.hxx>
#include <son8/cyrillic/error.hxx>

namespace son8::cyrillic {
    auto decode( StringWord &out, StringByteView in ) -> Error;
} // namespace

#endif//SON8_CYRILLIC_DECODE_RETURN_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
