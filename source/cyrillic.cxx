#include <son8/cyrillic.hxx>
// std headers
#include <array>
#include <cassert>
#include <string_view>

namespace son8::cyrillic {
    // private section
    namespace {

        auto encode_impl( Encoded::Out &out, Encoded::In in ) -> Error {
            return Error::Language;
        }

        auto decode_impl( Decoded::Out &out, Decoded::In in ) -> Error {
            return Error::Language;
        }

        void error_throw( Error code ) { if ( code != Error::None ) throw code; }

        constexpr auto error_size( ) -> unsigned { return static_cast< unsigned >( Error::Size_ ); }

        using ArrayViewError = std::array< std::string_view,  error_size( ) >;
        ArrayViewError Error_Messages_{{
            "not an error",
            "language not set",
        }};

    } // anonymous namespace
    // encoded implementation
    Encoded::Encoded( In in ) { error_throw( encode_impl( out( ), in ) ); }
    auto Encoded::out( ) & -> Out & { return out_; }
    // decoded implementation
    Decoded::Decoded( In in ) { error_throw( decode_impl( out( ), in ) ); }
    auto Decoded::out( ) & -> Out & { return out_; }
    // error implementation
    auto error_message( Error code ) -> std::string_view {
        auto ec = static_cast< unsigned >( code );
        assert( ec < error_size( ) );
        return Error_Messages_[ec];
    }
} // namespace

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
