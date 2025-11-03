#ifndef SON8_CYRILLIC_ENCODED_HXX
#define SON8_CYRILLIC_ENCODED_HXX

#include <son8/cyrillic/alias.hxx>

namespace son8::cyrillic {

    class Encoded final {
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
        Encoded( Encoded const &copy ) = default;
        Encoded &operator=( Encoded &&move ) = default;
        Encoded &operator=( Encoded const &copy ) = default;
        // getters
        [[nodiscard]] auto ref( ) const & noexcept -> Ref; // reading access via const reference
        [[nodiscard]] auto ptr( ) &       noexcept -> Ptr; // pointer access to underlying data
        [[nodiscard]] auto out( ) &       noexcept -> Out; // mutable access for modification
        [[nodiscard]] auto fwd( ) &       noexcept -> Fwd; // forward borrow resource
        [[nodiscard]] auto fwd( ) &&      noexcept ->Data; // forward steals resource
        // conversions
        operator View( ) const;
    };

} // namespace

#endif//SON8_CYRILLIC_ENCODED_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
