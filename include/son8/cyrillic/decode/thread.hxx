#ifndef SON8_CYRILLIC_DECODE_THREAD_HXX
#define SON8_CYRILLIC_DECODE_THREAD_HXX

#include <son8/cyrillic/decoded.hxx>

namespace son8::cyrillic {
    [[nodiscard]]
    auto decode( Decoded::In in ) -> Decoded;
} // namespace

#endif//SON8_CYRILLIC_DECODE_THREAD_HXX
