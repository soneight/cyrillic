#ifndef SON8_CYRILLIC_ENCODE_THREAD_HXX
#define SON8_CYRILLIC_ENCODE_THREAD_HXX

#include <son8/cyrillic/encoded.hxx>

namespace son8::cyrillic {
    [[nodiscard]]
    auto encode( Encoded::In in ) -> Encoded;
} // namespace

#endif//SON8_CYRILLIC_ENCODE_THREAD_HXX
