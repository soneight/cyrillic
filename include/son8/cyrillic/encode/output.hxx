#ifndef SON8_CYRILLIC_ENCODE_OUTPUT_HXX
#define SON8_CYRILLIC_ENCODE_OUTPUT_HXX

#include <son8/cyrillic/encoded.hxx>
#include <son8/cyrillic/error.hxx>

namespace son8::cyrillic {
    [[nodiscard]]
    auto encode( Encoded::In in, Error &code ) -> Encoded;
} // namespace

#endif//SON8_CYRILLIC_ENCODE_OUTPUT_HXX
