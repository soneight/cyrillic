#ifndef SON8_CYRILLIC_DECODED_HXX
#define SON8_CYRILLIC_DECODED_HXX

#include <son8/cyrillic/alias.hxx>

namespace son8::cyrillic {

    class Decoded {
        using Data_ = StringWord;
        Data_ data_;
    public:
        // public aliases
        using View = StringWordView;
        using Data = Data_;
        using Out = Data &;
        using Ref = Data const &;
        using Fwd = Data &&;
        using Ptr = Data::value_type *;
        using In = StringByteView;
        // constructors
        Decoded( ) = default;
       ~Decoded( ) = default;
        Decoded( In in );
        Decoded( Decoded &&move ) = default;
        Decoded( Decoded const &copy ) = delete;
        Decoded &operator=( Decoded &&move ) = default;
        Decoded &operator=( Decoded const &copy ) = delete;
        // getters
        auto ref( ) const & -> Ref; // read-only access via const reference
        auto ptr( ) &       -> Ptr; // wild pointer access to underlying data
        auto out( ) &       -> Out; // mutable reference for modification
        auto fwd( ) &&      -> Fwd; // forwaring reference for temporaries
        // conversions
        operator View( ) const;
    };

} // namespace

#endif//SON8_CYRILLIC_DECODED_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
