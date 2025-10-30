#include <son8/cyrillic.hxx>
// std headers
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <iterator>
#include <string_view>

namespace son8::cyrillic {
    // private implementation
    namespace {

        thread_local Language Language_{ Language::None };
        // encode implementation and it helpers
        constexpr Encoded::In const Letters_Plain_{ u"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЮЯабвгдежзийклмнопрстуфхцчшщьюя" };
        constexpr Encoded::In const Letters_Mixed_{ u"ЁЄІЇЪЫЭъыэёєіїҐґ" };
        template< unsigned Size >
        using ArrayViewLetter = std::array< Encoded::Ref, Size >;
        using ArrayPlain = ArrayViewLetter< Letters_Plain_.size( ) >;
        constexpr ArrayPlain const Letters_Plain_Trans_{{
            // x is used to prepend english letters
            // upper
            "A", "B", "V", "G", "D", "E","JZ", "Z", // А,Б,В,Г,Д,Е,Ж,З
            "U", "I", "K", "L", "M", "N", "O", "P", // И,Й,К,Л,М,Н,О,П
            "R", "S", "T", "Y", "F", "H", "C","JC", // Р,С,Т,У,Ф,Х,Ц,Ч
            "W","JW", "Q","JY","JA",                // Ш,Щ,Ь,Ю,Я
            // lower
            "a", "b", "v", "g", "d", "e","jz", "z", // а,б,в,г,д,е,ж,з
            "u", "i", "k", "l", "m", "n", "o", "p", // и,й,к,л,м,н,о,п
            "r", "s", "t", "y", "f", "h", "c","jc", // р,с,т,у,ф,х,ц,ч
            "w","jw", "q","jy","ja",                // ш,щ,ь,ю,я
        }};
        using ArrayMixed = std::array< ArrayViewLetter< Letters_Mixed_.size( ) >, 2 >;
        constexpr ArrayMixed const Letters_Mixed_Trans_{{
            //  Ё ,   Є ,   І ,   Ї ,   Ъ ,   Ы ,   Э ,   ъ ,   ы ,   э ,   ё ,   є ,   і ,   ї ,   Ґ ,   ґ
            { "JI", "JE", "JU", "JI", "JQ", "JU", "JE", "jq", "ju", "je", "ji", "je", "ju", "ji", "JQ", "jq" },
            {"JXV","JXE","JXI","JXY","JXQ","JXU","JXZ","jxq","jxu","jxz","jxv","jxe","jxi","jxy","JXG","jxg" },
        }};
        static_assert( Letters_Mixed_.size( ) == 16 );
        constexpr std::bitset< Letters_Mixed_.size( ) > Letters_Mixed_Flags_{ 0b1111'1000'0000'1110 };

        auto encode_impl( Encoded::Out &out, Encoded::In in ) -> Error {
            if ( this_thread::state_language( ) == Language::None ) return Error::Language;
            Encoded::Out tmp;
            tmp.reserve( in.size( ) );
            auto find_plain = [&tmp]( auto word ) -> bool {
                auto beg = Letters_Plain_.begin( );
                auto end = Letters_Plain_.end( );
                auto it = std::lower_bound( beg, end, word );
                if ( it == end || *it != word ) return false;
                tmp.append( Letters_Plain_Trans_[std::distance( beg, it )] );
                return true;
            };
            auto find_mixed = [&tmp]( auto word ) -> bool {
                auto beg = Letters_Mixed_.begin( );
                auto end = Letters_Mixed_.end( );
                auto it = std::find( beg, end, word );
                if ( it == end ) return false;
                auto lang = static_cast< unsigned >( this_thread::state_language( ) ) - 1u;
                assert( lang < 2 );
                auto col = std::distance( beg, it );
                auto row = Letters_Mixed_Flags_[col] != lang;
                tmp.append( Letters_Mixed_Trans_[row][col] );
                return true;
            };

            for ( auto word : in ) {
                if ( find_plain( word ) ) continue;
                if ( find_mixed( word ) ) continue;
                return Error::InvalidWord;
            }

            tmp.shrink_to_fit( );
            out = std::move( tmp );
            return Error::None;
        }

        using ArrayViewBykva = std::array< Decoded::Ref, 8 >;
        constexpr ArrayViewBykva const Bykva_{{
            u"жчщюяэёы", // ru jj lower
            u"ЖЧЩЮЯЭЁЫ", // ru jj upper
            u"ъыэёєіїґ", // ru jx lower
            u"ЪЫЭЁЄІЇҐ", // ru jx upper
            u"жчщюяєїі", // ua jj lower
            u"ЖЧЩЮЯЄЇІ", // ua jj upper
            u"ъыэёєіїґ", // ua jx lower
            u"ЪЫЭЁЄІЇҐ", // ua jx upper
        }};

        [[nodiscard]]
        auto decode_impl( Decoded::Out &out, Decoded::In in ) -> Error {
            if ( this_thread::state_language( ) == Language::None ) return Error::Language;

            Decoded::Out tmp;


            tmp.shrink_to_fit( );
            out = std::move( tmp );
            return Error::None;
        }

        void error_throw( Error code ) { if ( code != Error::None ) throw Exception{ code }; }

        constexpr auto error_size( ) -> unsigned { return static_cast< unsigned >( Error::Size_ ); }

        using ArrayViewError = std::array< std::string_view,  error_size( ) >;
        ArrayViewError Error_Messages_{{
            "not an error",
            "language not set",
            "invalid word",
        }};
    } // anonymous namespace
    // state implementation
    namespace this_thread {
        // state setters
        void state( Language language ) noexcept { Language_ = language; }
        // state getters
        auto state_language( ) noexcept -> Language { return Language_; }
    }
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
    // exception implementation
    Exception::Exception( Error code ) noexcept : code_{ code } { assert( code != Error::None ); }
    auto Exception::code( ) const -> Error { return code_; }
    auto Exception::what( ) const noexcept -> char const * {
        return error_message( code( ) ).data( );
    }

} // namespace

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
