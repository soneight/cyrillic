#ifndef SON8_CYRILLIC_ENCODED_HXX
#define SON8_CYRILLIC_ENCODED_HXX

#include <son8/cyrillic/alias.hxx>

namespace son8::cyrillic {

    class Encoded {
        using Data_ = StringByte;
        Data_ data_;
    public:
        // public aliases
        using View = StringByteView;
        using Data = Data_;
        using Out = Data &;
        using Ref = Data const &;
        using Ptr = Data::value_type *;
        using Fwd = Data &&;
        using In = StringWordView;
        // constructors
        Encoded( ) = default;
       ~Encoded( ) = default;
        Encoded( In in );
        Encoded( Encoded &&move ) = default;
        Encoded( Encoded const &copy ) = delete;
        Encoded &operator=( Encoded &&move ) = default;
        Encoded &operator=( Encoded const &copy ) = delete;
        // getters
        auto ref( ) const & -> Ref; // read-only access via const reference
        auto ptr( ) &       -> Ptr; // wild pointer access to underlying data
        auto out( ) &       -> Out; // mutable reference for modification
        auto fwd( ) &&      -> Fwd; // forwarding reference for temporaries
        // conversions
        operator View( ) const;
    };

} // namespace

#endif//SON8_CYRILLIC_ENCODED_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
