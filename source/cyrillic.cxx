#include <son8/cyrillic.hxx>
// std headers
#include <algorithm> // find, lower_bound
#include <array> // array
#include <bitset> // bitset
#include <cassert> // (macro) assert
#include <codecvt> // codecvt_utf8_utf16
#include <locale> // wstring_convert
#include <string_view> // basic_string_view
#include <utility> // move

namespace son8::cyrillic {
    // private implementation
    namespace {
        // state variables
        thread_local Language Language_{ Language::None };
        thread_local Error Error_{ Error::None };
        // global helpers
        void state( Error error ) noexcept { Error_ = error; }
        template< typename T >
        constexpr auto check_sorted( std::basic_string_view< T > t ) -> bool {
            auto second = t.begin( ) + 1;
            for ( auto first = t.begin( ); second < t.end( ); ++second ) {
                if ( *second <= *first ) return false;
                first = second;
            }
            return true;
        }
        constexpr auto check_langsize( unsigned size ) -> bool { return Language::Size_ == static_cast< Language >( size ); }
        // encode implementation and it helpers
        // -- helpers
        constexpr Encoded::In const Encode_Sumvolu_Plain_{ u"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЮЯабвгдежзийклмнопрстуфхцчшщьюя" };
        static_assert( check_sorted( Encode_Sumvolu_Plain_ ) && Encode_Sumvolu_Plain_.size( ) == 58 );
        constexpr Encoded::In const Encode_Sumvolu_Mixed_{ u"ЁЄІЇЪЫЭъыэёєіїҐґ" };
        static_assert( Encode_Sumvolu_Mixed_.size( ) == 16 );
        template< unsigned Size >
        using ArrayViewLetter = std::array< Encoded::View, Size >;
        using ArrayPlain = ArrayViewLetter< Encode_Sumvolu_Plain_.size( ) >;
        constexpr ArrayPlain const Encode_Letters_Plain_{{
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
        using ArrayMixed = std::array< ArrayViewLetter< Encode_Sumvolu_Mixed_.size( ) >, 2 >;
        constexpr ArrayMixed const Encode_Letters_Mixed_{{
            //  Ё ,   Є ,   І ,   Ї ,   Ъ ,   Ы ,   Э ,   ъ ,   ы ,   э ,   ё ,   є ,   і ,   ї ,   Ґ ,   ґ
            { "JI", "JE", "JU", "JI", "JQ", "JU", "JE", "jq", "ju", "je", "ji", "je", "ju", "ji", "JQ", "jq" },
            {"JXV","JXE","JXI","JXY","JXQ","JXU","JXZ","jxq","jxu","jxz","jxv","jxe","jxi","jxy","JXG","jxg" },
        }};
        constexpr std::bitset< Encode_Sumvolu_Mixed_.size( ) > Letters_Mixed_Flags_{ 0b1111'1000'0000'1110 };
        // -- implementation
        [[nodiscard]]
        auto encode_impl( Encoded::Out out, Encoded::In in ) -> Error {
            if ( this_thread::state_language( ) == Language::None ) return Error::Language;
            Encoded::Data tmp;
            tmp.reserve( in.size( ) );
            auto find_plain = [&tmp]( auto word ) -> bool {
                auto beg = Encode_Sumvolu_Plain_.begin( );
                auto end = Encode_Sumvolu_Plain_.end( );
                auto it = std::lower_bound( beg, end, word );
                if ( it == end || *it != word ) return false;
                tmp.append( Encode_Letters_Plain_[it - beg] );
                return true;
            };
            auto find_mixed = [&tmp]( auto word ) -> bool {
                auto beg = Encode_Sumvolu_Mixed_.begin( );
                auto end = Encode_Sumvolu_Mixed_.end( );
                auto it = std::find( beg, end, word );
                if ( it == end ) return false;
                static_assert( check_langsize( 3 ) );
                bool lang = static_cast< unsigned >( this_thread::state_language( ) ) - 1u;
                auto col = it - beg;
                auto row = Letters_Mixed_Flags_[col] != lang ? 1 : 0;
                tmp.append( Encode_Letters_Mixed_[row][col] );
                return true;
            };

            for ( auto word : in ) {
                if ( find_plain( word ) ) continue;
                if ( find_mixed( word ) ) continue;
                return Error::InvalidWord;
            }
            // return
            // -- if size equal capacity user possibly expect data to be shrink
            // -- or can force to not shrinking it providing out with capacity
            // -- TODO document this behavior into root README
            if ( out.size( ) == out.capacity( ) ) tmp.shrink_to_fit( );
            out = std::move( tmp );
            return Error::None;
        }
        // decode implementation and it helpers
        // -- helpers
        constexpr Decoded::In   Decode_Letters_Plain_{ "ABCDEFGHIKLMNOPQRSTUVWYZabcdefghiklmnopqrstuvwyz" };
        static_assert( check_sorted( Decode_Letters_Plain_ ) );
        constexpr Decoded::View Decode_Sumvolu_Plain_{u"АБЦДЕФГХЙКЛМНОПЬРСТИВШУЗабцдефгхйклмнопьрстившуз" };
        static_assert( Decode_Letters_Plain_.size( ) == Decode_Sumvolu_Plain_.size( ) );
        using ArrayViewDecodeLetters = std::array< Decoded::In, 4 >;
        // TODO maybe do also 8 to map 1to1, and change order of elements for
        //      most popular ones for each entry to improve find performances
        constexpr ArrayViewDecodeLetters const Decode_Letters_Mixed_{{
            "zcwyaeiuq",
            "ZCWYAEIUQ",
            "quzveiyg",
            "VEIYQUZG",
        }};
        using ArrayViewDecodeSumvolu = std::array< Decoded::View, 8 >;
        constexpr ArrayViewDecodeSumvolu const Decode_Sumvolu_Mixed_{{
           u"жчщюяэёыъ", // ru jj lower
           u"ЖЧЩЮЯЭЁЫЪ", // ru jj upper
           u"ъыэёєіїґ", // ru jx lower
           u"ЁЄІЇЪЫЭҐ", // ru jx upper
           u"жчщюяєїіґ",// ua jj lower
           u"ЖЧЩЮЯЄЇІҐ",// ua jj upper
           u"ъыэёєіїґ", // ua jx lower
           u"ЁЄІЇЪЫЭҐ", // ua jx upper
        }};
        enum class DecodedState : unsigned {
            Defaults,
            Lower_JJ,
            Upper_JJ,
            Lower_JX,
            Upper_JX,
            Pusher_8,
            Error_DS,
        };
        // -- implementation
        [[nodiscard]]
        auto decode_impl( Decoded::Out out, Decoded::In in ) -> Error {
            using State = DecodedState;
            if ( this_thread::state_language( ) == Language::None ) return Error::Language;
            Decoded::Data tmp;
            auto ali = 0; // array letter index
            auto const asi = ( this_thread::state_language( ) == Language::Ukrainian ) ? 4 : 0; // array sumvol index
            auto state = DecodedState::Defaults;
            // lambdas
            auto process_defaults = [&tmp]( auto byte ) -> State {
                if ( byte == 'j' ) return State::Lower_JJ;
                if ( byte == 'J' ) return State::Upper_JJ;
                auto beg = Decode_Letters_Plain_.begin( );
                auto end = Decode_Letters_Plain_.end( );
                auto it = std::lower_bound( beg, end, byte );
                if ( it == end || *it != byte ) return State::Error_DS;
                tmp.push_back( Decode_Sumvolu_Plain_[it - beg] );
                return State::Defaults;
            };
            auto process_lower_jj = [&ali]( auto byte ) -> State {
                if ( byte == 'x' ) return State::Lower_JX;
                ali = 0;
                return State::Pusher_8;
            };
            auto process_upper_jj = [&ali]( auto byte ) -> State {
                if ( byte == 'X' ) return State::Upper_JX;
                ali = 1;
                return State::Pusher_8;
            };
            auto process_lower_jx = [&ali]( ) -> State {
                ali = 2;
                return State::Pusher_8;
            };
            auto process_upper_jx = [&ali]( ) -> State {
                ali = 3;
                return State::Pusher_8;
            };
            auto pusher_8 = [&ali,asi,&tmp]( auto byte ) -> State {
                auto &searched = Decode_Letters_Mixed_[ali];
                auto beg = searched.begin( );
                auto end = searched.end( );
                auto it = std::find( beg, end, byte );
                if ( it == end ) return State::Error_DS;
                auto &replaced = Decode_Sumvolu_Mixed_[ali + asi];
                tmp.push_back( replaced[it - beg] );
                return State::Defaults;
            };
            // process
            for ( auto byte : in ) {
                switch ( state ) {
                    case State::Defaults: state = process_defaults( byte ); break;
                    case State::Lower_JJ: state = process_lower_jj( byte ); break;
                    case State::Upper_JJ: state = process_upper_jj( byte ); break;
                    case State::Lower_JX: state = process_lower_jx( ); break;
                    case State::Upper_JX: state = process_upper_jx( ); break;
                    case State::Pusher_8: assert( false && "should not ever reach this" ); [[fallthrough]];
                    case State::Error_DS: [[fallthrough]];
                    default: return Error::InvalidByte;
                }
                if ( state == State::Pusher_8 ) state = pusher_8( byte );
            }
            if ( state != State::Defaults ) return Error::InvalidByte;
            // return
            // -- if size equal capacity user possibly expect data to be shrink
            // -- or can force to not shrinking it providing out with capacity
            // -- TODO document this behavior into root README
            if ( out.size( ) == out.capacity( ) ) tmp.shrink_to_fit( );
            out = std::move( tmp );
            return Error::None;
        }
        // convert implementation
        // -- convert
        template< typename Out, typename In >
        [[nodiscard]] auto convert_impl( Out &out, In in ) -> Error {
            if ( in.empty( ) ) {
                out.clear( );
                return Error::None;
            }
            using Converter = std::wstring_convert< std::codecvt_utf8_utf16< char16_t >, char16_t >;
            Converter converter{ "", u"" };
            constexpr auto OutSize = sizeof( typename Out::value_type );
            constexpr auto InSize = sizeof( typename In::value_type );
            static_assert( OutSize != InSize, "son8::cyrillic convert requires value types with different sizes" );
            if constexpr ( OutSize < InSize ) out = converter.to_bytes( in.data( ), in.data( ) + in.size( ) );
            else                              out = converter.from_bytes( in.data( ), in.data( ) + in.size( ) );
            if ( out.empty( ) ) return Error::ConvertFailed;
            return Error::None;
        }
        // error implementation
        // -- throw only if error is non-zero
        void error_throw( Error code ) { if ( code != Error::None ) throw Exception{ code }; }
        // -- helper too determine error array size
        constexpr auto error_size( ) -> unsigned { return static_cast< unsigned >( Error::Size_ ); }
        // -- map between error enum and messages
        using ArrayViewError = std::array< char const * ,  error_size( ) >;
        ArrayViewError Error_Messages_{{
            "son8::cyrillic: not an error",
            "son8::cyrillic: language not set",
            "son8::cyrillic: invalid word",
            "son8::cyrillic: invalid byte",
            "son8::cyrillic: convert failed"
        }};
    } // anonymous namespace
    // state implementation
    namespace this_thread {
        // state setters
        void state( Language language ) noexcept { Language_ = language; }
        // state getters
        auto state_language( ) noexcept -> Language { return Language_; }
        auto state_error( ) noexcept -> Error { return Error_; }
    }
    // encode implementation
    // -- return
    auto encode( Encoded::Out out, Encoded::In in ) -> Error { return encode_impl( out, in ); }
    // -- output
    auto encode( Encoded::In in, Error &code ) -> Encoded {
        Encoded ret;
        code = encode_impl( ret.out( ), in );
        return ret;
    }
    // -- thread
    auto encode( Encoded::In in ) -> Encoded {
        Encoded ret;
        state( encode_impl( ret.out( ), in ) );
        return ret;
    }
    // encoded implementation
    Encoded::Encoded( In in ) { error_throw( encode_impl( out( ), in ) ); }
    // -- getters
    auto Encoded::ref( ) const & noexcept -> Ref { return data_; }
    auto Encoded::ptr( ) &       noexcept -> Ptr { return data_.data( ); }
    auto Encoded::out( ) &       noexcept -> Out { return data_; }
    auto Encoded::fwd( ) &       noexcept -> Fwd { return std::move( data_ ); }
    auto Encoded::fwd( ) &&      noexcept ->Data { return std::move( data_ ); }
    // -- conversions
    Encoded::operator View( ) const { return View{ data_ }; }
    // decode implementation
    // -- return
    auto decode( Decoded::Out out, Decoded::In in ) -> Error { return decode_impl( out, in ); }
    // -- output
    auto decode( Decoded::In in, Error &code ) -> Decoded {
        Decoded ret;
        code = decode_impl( ret.out( ), in );
        return ret;
    }
    // -- thread
    auto decode( Decoded::In in ) -> Decoded {
        Decoded ret;
        state( decode_impl( ret.out( ), in ) );
        return ret;
    }
    // decoded implementation
    Decoded::Decoded( In in ) { error_throw( decode_impl( out( ), in ) ); }
    // -- getters
    auto Decoded::ref( ) const & noexcept -> Ref { return data_; }
    auto Decoded::ptr( ) &       noexcept -> Ptr { return data_.data( ); }
    auto Decoded::out( ) &       noexcept -> Out { return data_; }
    auto Decoded::fwd( ) &       noexcept -> Fwd { return std::move( data_ ); }
    auto Decoded::fwd( ) &&      noexcept ->Data { return std::move( data_ ); }
    // -- conversions
    Decoded::operator View( ) const { return View{ data_ }; }
    // error implementation
    auto error_message( Error code ) noexcept -> char const * {
        auto ec = static_cast< unsigned >( code );
        assert( ec < error_size( ) );
        return Error_Messages_[ec];
    }
    // convert implementation
    [[nodiscard]] auto string_byte( StringWordView in ) -> StringByte {
        StringByte out;
        state ( convert_impl( out, in ) );
        return out;
    }
    [[nodiscard]] auto string_word( StringByteView in ) -> StringWord {
        StringWord out;
        state ( convert_impl( out, in ) );
        return out;
    }
    // exception implementation
    Exception::Exception( Error code ) noexcept : code_{ code } { assert( code != Error::None ); }
    auto Exception::code( ) const noexcept -> Error { return code_; }
    auto Exception::what( ) const noexcept -> char const * { return error_message( code( ) ); }

} // namespace

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
