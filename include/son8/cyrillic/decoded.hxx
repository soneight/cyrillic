#ifndef SON8_CYRILLIC_DECODED_HXX
#define SON8_CYRILLIC_DECODED_HXX

#include <son8/cyrillic/alias.hxx>

namespace son8::cyrillic {

    class Decoded {
        using Out_ = StringWord;
        Out_ out_;
    public:
        // public aliases
        using Out = Out_;
        using Ref = StringWordView;
        using Ptr = Out::value_type const *;
        using In = StringByteView;
        // constructors
        Decoded( ) = default;
       ~Decoded( ) = default;
        Decoded( In in );
        Decoded( Decoded &&move ) = delete;
        Decoded( Decoded const &copy ) = delete;
        Decoded &operator=( Decoded &&move ) = delete;
        Decoded &operator=( Decoded const &copy ) = delete;
        // getters
        auto ref( ) const -> Ref;
        auto ptr( ) const -> Ptr;
        auto out( ) & -> Out &;
        // conversions
        operator Ref( ) const;
    };

} // namespace

#endif//SON8_CYRILLIC_DECODED_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
