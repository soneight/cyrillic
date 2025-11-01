#ifndef SON8_CYRILLIC_DECODE_OUTPUT_HXX
#define SON8_CYRILLIC_DECODE_OUTPUT_HXX

#include <son8/cyrillic/decoded.hxx>
#include <son8/cyrillic/error.hxx>

namespace son8::cyrillic {
    [[nodiscard]]
    auto decode( Decoded::In in, Error &code ) -> Decoded;
} // namespace

#endif//SON8_CYRILLIC_DECODE_OUTPUT_HXX
