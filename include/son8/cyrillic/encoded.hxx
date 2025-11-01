#ifndef SON8_CYRILLIC_ENCODED_HXX
#define SON8_CYRILLIC_ENCODED_HXX

#include <son8/cyrillic/alias.hxx>

namespace son8::cyrillic {

    class Encoded {
        using Out_ = StringByte;
        Out_ out_;
    public:
        // public aliases
        using Out = Out_;
        using Ref = StringByteView;
        using Ptr = Out::value_type const *;
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
        auto ref( ) const -> Ref; // read-only access via string_view
        auto ptr( ) const -> Ptr; // pointer access to underlying data
        auto out( ) & -> Out &;   // mutable reference for modification
        // conversions
        operator Ref( ) const;
    };

} // namespace

#endif//SON8_CYRILLIC_ENCODED_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
