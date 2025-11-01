#ifndef SON8_CYRILLIC_ENCODE_RETURN_HXX
#define SON8_CYRILLIC_ENCODE_RETURN_HXX

#include <son8/cyrillic/alias.hxx>
#include <son8/cyrillic/error.hxx>

namespace son8::cyrillic {
    auto encode( StringByte &out, StringWordView in ) -> Error;
} // namespace

#endif//SON8_CYRILLIC_ENCODE_RETURN_HXX
