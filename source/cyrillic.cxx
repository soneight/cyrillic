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
// macros
#define STRUCT_VALIDATE_TAG( Name ) template< bool Append, bool Ignore > struct Name{ }
#define METHOD_VALIDATE_CACHE_UPDATE( Name ) template< bool Append, bool Ignore > void update( Tag::Name< Append, Ignore > )
#define METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Name, Symbol ) template< bool Append, bool Ignore > void update( Tag::Name< Append, Ignore > ) {\
    charAppends_[Symbol] = Append;\
    charIgnores_[Symbol] = Ignore;\
}
#define METHOD_VALIDATE_CACHE_UPDATE_BRACKETS( Name, Open, Close) template< bool Append, bool Ignore > void update( Tag::Name< Append, Ignore > ) {\
    charAppends_[Open] = Append; charAppends_[Close] = Append;\
    charIgnores_[Open] = Ignore; charIgnores_[Close] = Ignore;\
}
#define METHOD_VALIDATE_CACHE_UPDATE_RANGE( Name, From, Toeq ) template< bool Append, bool Ignore > void update( Tag::Name< Append, Ignore > ) {\
    for ( auto i = From; i <= Toeq; ++i ) {\
        charAppends_[i] = Append;\
        charIgnores_[i] = Ignore;\
    }\
}
#define CASE_VALIDATE_FLAG_TAG( Name ) case ValidateFlags::Name: ValidateFlagCache_.update( Tag::Name< Append, Ignore >{ } ); break

namespace son8::cyrillic {
    // private implementation
    namespace {
        // flag cache helper
        namespace Tag {
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Null );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Space );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Underscore );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Gravequote );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Singlequote );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Doublequote );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Backslash );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Audio );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Backspace );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Tab );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Newline );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Verticaltab );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Formfeed );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Return );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Hash );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Currency );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Percent );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Equal );
            STRUCT_VALIDATE_TAG( Ascii_Symbol_Commercial );
            STRUCT_VALIDATE_TAG( Ascii_Brackets_Round );
            STRUCT_VALIDATE_TAG( Ascii_Brackets_Angle );
            STRUCT_VALIDATE_TAG( Ascii_Brackets_Array );
            STRUCT_VALIDATE_TAG( Ascii_Brackets_Curly );
            STRUCT_VALIDATE_TAG( Ascii_Range_Digit );
            STRUCT_VALIDATE_TAG( Ascii_Range_Upper );
            STRUCT_VALIDATE_TAG( Ascii_Range_Lower );
            STRUCT_VALIDATE_TAG( Ascii_List_Text );
            STRUCT_VALIDATE_TAG( Ascii_List_Bitwise );
            STRUCT_VALIDATE_TAG( Ascii_List_Arithmetic );
            STRUCT_VALIDATE_TAG( Ascii_Bytes_Control );
        };
        class CharFlagCache {
            std::bitset< 128 > charIgnores_;
            std::bitset< 128 > charAppends_;
        public:
            CharFlagCache( ) = default;
            using f = ValidateFlags;
            bool ignore( Unt0 byte ) const { return charIgnores_[byte]; }
            bool append( Unt0 byte ) const { return charAppends_[byte]; }
            void reset( ) { charIgnores_.reset(), charAppends_.reset( ); }
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Null          , 0x00u )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Space         , 0x20u )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Underscore    , 0x5Fu )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Gravequote    , 0x60u )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Singlequote   , 0x27u )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Doublequote   , 0x22u )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Backslash     , 0x5Cu )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Audio         , 0x07u )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Backspace     , 0x08u )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Tab           , 0x09u )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Newline       , 0x0Au )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Verticaltab   , 0x0Bu )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Formfeed      , 0x0Cu )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Return        , 0x0Du )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Hash          , 0x23u )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Currency      , 0x24u )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Percent       , 0x25u )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Equal         , 0x3Du )
            METHOD_VALIDATE_CACHE_UPDATE_SYMBOL( Ascii_Symbol_Commercial    , 0x40u )
            METHOD_VALIDATE_CACHE_UPDATE_BRACKETS( Ascii_Brackets_Round, 0x28u, 0x29u )
            METHOD_VALIDATE_CACHE_UPDATE_BRACKETS( Ascii_Brackets_Angle, 0x3Cu, 0x3Eu )
            METHOD_VALIDATE_CACHE_UPDATE_BRACKETS( Ascii_Brackets_Array, 0x5Bu, 0x5Du )
            METHOD_VALIDATE_CACHE_UPDATE_BRACKETS( Ascii_Brackets_Curly, 0x7Bu, 0x7Du )
            METHOD_VALIDATE_CACHE_UPDATE_RANGE( Ascii_Range_Digit, 0x30u, 0x39u )
            METHOD_VALIDATE_CACHE_UPDATE_RANGE( Ascii_Range_Upper, 0x41u, 0x5Au )
            METHOD_VALIDATE_CACHE_UPDATE_RANGE( Ascii_Range_Lower, 0x61u, 0x7Au )
            METHOD_VALIDATE_CACHE_UPDATE( Ascii_List_Text ) {
                for ( auto const i : { 0x21u, 0x2Cu, 0x2Eu, 0x3Au, 0x3Bu, 0x3Fu } ) {
                    charAppends_[i] = Append;
                    charIgnores_[i] = Ignore;
                }
            }
            METHOD_VALIDATE_CACHE_UPDATE( Ascii_List_Bitwise ) {
                for ( auto const i : { 0x26u, 0x5Eu, 0x7Cu, 0x7Eu } ) {
                    charAppends_[i] = Append;
                    charIgnores_[i] = Ignore;
                }
            }
            METHOD_VALIDATE_CACHE_UPDATE( Ascii_List_Arithmetic ) {
                for ( auto const i : { 0x2Au, 0x2Bu, 0x2Du, 0x2Fu } ) {
                    charAppends_[i] = Append;
                    charIgnores_[i] = Ignore;
                }
            }
            METHOD_VALIDATE_CACHE_UPDATE( Ascii_Bytes_Control ) {
                for ( auto const i : {  0x01u, 0x02u, 0x03u, 0x04u, 0x05u, 0x06u, 0x0Eu, 0x0Fu
                                , 0x10u, 0x11u, 0x12u, 0x13u, 0x14u, 0x15u, 0x16u, 0x17u
                                , 0x18u, 0x19u, 0x1Au, 0x1Bu, 0x1Cu, 0x1Du, 0x1Eu, 0x1Fu
                                , 0x7Fu } ) {
                    charAppends_[i] = Append;
                    charIgnores_[i] = Ignore;
                }
            }
        };
        // state variables
        thread_local Language Language_{ Language::None };
        thread_local Error Error_{ Error::None };
        thread_local Validate Validate_{ Validate::None };
        thread_local CharFlagCache ValidateFlagCache_{ };
        // update cache
        template< bool Append, bool Ignore >
        void char_flag_cache_update( ValidateFlags flag ) {
            using f = ValidateFlags;
            switch ( flag ) {
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Null );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Space );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Underscore );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Gravequote );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Singlequote );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Doublequote );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Backslash );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Audio );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Backspace );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Tab );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Newline );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Verticaltab );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Formfeed );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Return );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Hash );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Currency );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Percent );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Equal );
            CASE_VALIDATE_FLAG_TAG( Ascii_Symbol_Commercial );
            CASE_VALIDATE_FLAG_TAG( Ascii_Brackets_Round );
            CASE_VALIDATE_FLAG_TAG( Ascii_Brackets_Angle );
            CASE_VALIDATE_FLAG_TAG( Ascii_Brackets_Array );
            CASE_VALIDATE_FLAG_TAG( Ascii_Brackets_Curly );
            CASE_VALIDATE_FLAG_TAG( Ascii_Range_Digit );
            CASE_VALIDATE_FLAG_TAG( Ascii_Range_Upper );
            CASE_VALIDATE_FLAG_TAG( Ascii_Range_Lower );
            CASE_VALIDATE_FLAG_TAG( Ascii_List_Text );
            CASE_VALIDATE_FLAG_TAG( Ascii_List_Bitwise );
            CASE_VALIDATE_FLAG_TAG( Ascii_List_Arithmetic );
            CASE_VALIDATE_FLAG_TAG( Ascii_Bytes_Control );
            default: {
                assert( false && "assert should be unreacheble" ); break;
            }}
        }
        // global helpers
        // -- compile-time sorted check for static assert
        template< typename T >
        constexpr auto check_sorted( std::basic_string_view< T > t ) -> bool {
            auto second = t.begin( ) + 1;
            for ( auto first = t.begin( ); second < t.end( ); ++second ) {
                if ( *second <= *first ) return false;
                first = second;
            }
            return true;
        }
        // -- compile-time language size check for static assert
        constexpr auto check_langsize( unsigned size ) -> bool { return Language::Size_ == static_cast< Language >( size ); }
        static_assert( check_langsize( 3 ) );
        // -- validate flags size
        constexpr auto validate_flags_size( ) { return static_cast< ValidateFlagsVeiled >( ValidateFlags::Size_ ); }
        static_assert( validate_flags_size( ) == Validate_Half_Bits
            , "son8::cyrillic validate flags size requires to be equal to half of the Validate bits size" );
        // -- check flag is set
        template< bool Append >
        struct validate {
            bool operator()( ValidateFlags bit ) const noexcept {
                auto f = this_thread::state_validate_veiled( );
                auto b = static_cast< ValidateFlagsVeiled >( bit );
                if constexpr ( Append ) b += Validate_Half_Bits;
                return f & ( 1ull << b );
            }
        };
        using validate_append = validate< ValidateFlagAppend::append >;
        using validate_ignore = validate< ValidateFlagAppend::ignore >;
        // encode detail implementation and it helpers
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
                bool lang = static_cast< unsigned >( this_thread::state_language( ) ) - 1u;
                auto col = it - beg;
                auto row = Letters_Mixed_Flags_[col] != lang ? 1 : 0;
                tmp.append( Encode_Letters_Mixed_[row][col] );
                return true;
            };
            auto find_latin = [&tmp]( auto word ) -> bool {
                bool upper = 'A' <= word && word <= 'Z';
                bool lower = 'a' <= word && word <= 'z';
                if ( not ( upper || lower ) ) return false;
                tmp.push_back( lower ? 'x' : 'X' );
                tmp.push_back( static_cast< unsigned char >( word ) );
                return true;
            };
            auto find_other = [&tmp]( auto word ) -> bool {
                if ( word >> 8u ) tmp.push_back( word >> 8u );
                tmp.push_back( static_cast< unsigned char >( word ) );
                return true;
            };
            auto find_valid = [&tmp]( auto word ) -> bool {
                using charType = typename Encoded::Data::value_type;
                auto const charHi = static_cast< charType >( word >> 8u );
                auto const charLo = static_cast< charType >( word );
                if ( charHi ) {
                    bool const ignore = validate_ignore{ }( ValidateFlags::Wide_Bytes );
                    bool const append = validate_append{ }( ValidateFlags::Wide_Bytes );
                    if ( not ignore and not append ) return false;
                    if ( append ) {
                        tmp.push_back( charHi );
                        tmp.push_back( charLo );
                    }
                    return true;
                } else if ( 0x80u <= charLo ) {
                    bool const ignore = validate_ignore{ }( ValidateFlags::Ascii_Bytes_Extended );
                    bool const append = validate_append{ }( ValidateFlags::Ascii_Bytes_Extended );
                    if ( not ignore and not append ) return false;
                    if ( append ) tmp.push_back( charLo );
                    return true;
                } else {
                    bool const ignore = ValidateFlagCache_.ignore( charLo );
                    bool const append = ValidateFlagCache_.append( charLo );
                    if ( not ignore and not append ) return false;
                    if ( append ) {
                        if ( std::islower( charLo ) ) tmp.push_back( 'x' );
                        else if ( std::isupper( charLo ) ) tmp.push_back( 'X' );
                        tmp.push_back( charLo );
                    }
                    return true;
                }
                return true;
            };

            for ( Unt2 word : in ) {
                // continue Success, break Failure
                if ( find_plain( word ) ) continue;
                if ( find_mixed( word ) ) continue;
                switch ( this_thread::state_validate( ) ) {
                case Validate::None: break;
                case Validate::IgnoreAll: continue;
                case Validate::AppendAll: {
                    if ( find_latin( word ) ) continue;
                    if ( find_other( word ) ) continue;
                    break;
                }
                default: {
                    if ( find_valid( word ) ) continue;
                    break;
                }}
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
        // decode detail implementation and it helpers
        // -- detail helpers
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
           u"жчщюяэёыъ",// ru jj lower
           u"ЖЧЩЮЯЭЁЫЪ",// ru jj upper
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
        // -- detail implementation
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
        // convert detail implementation
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
        // validate detail implementation
        // -- flag
        template< bool Append, bool Ignore >
        void validate_flag_impl( ValidateFlags flag ) {
            static_assert ( not ( Append and Ignore )
                , "son8::cyrillic: validate flag implementation requires append and ignore to be not set at the same time" );
            ValidateVeiled shift{ 1u };
            auto bit = static_cast< ValidateFlagsVeiled >( flag );
            auto bitLo = shift << bit;
            auto bitHi = shift << ( bit + Validate_Half_Bits );
            auto value = this_thread::state_validate_veiled( );
            if/*_*/ constexpr ( Append and not Ignore ) value |= bitHi, value &=~bitLo;
            else if constexpr ( Ignore and not Append ) value &=~bitHi, value |= bitLo;
            else value &= ~( bitHi | bitLo );
            char_flag_cache_update< Append, Ignore >( flag );
            this_thread::state( static_cast< Validate >( value ) );
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
            "son8::cyrillic: convert failed",
            "son8::cyrillic: validate misconfigured",
        }};
    } // anonymous namespace
    // state implementation
    namespace this_thread {
        // state setters
        static void state( Error error ) noexcept { Error_ = error; }
        void state( Language language ) noexcept { Language_ = language; }
        void state( Validate validate ) noexcept { Validate_ = validate; }
        void state( ValidateVeiled flags ) noexcept {
            auto append = static_cast< ValidateVeiledHalf >( flags >> Validate_Half_Bits );
            auto ignore = static_cast< ValidateVeiledHalf >( flags );
            bool misconfigured = ( append & ignore ) != 0;
            if ( misconfigured ) state( Error::ValidateMisconfigured );
            state( static_cast< Validate >( flags ) );
        }
        void state( ValidateFlagAppend flag ) noexcept {
            validate_flag_impl< flag.append, flag.ignore >( flag );
        }
        void state( ValidateFlagIgnore flag ) noexcept {
            validate_flag_impl< flag.append, flag.ignore >( flag );
        }
        void state( ValidateFlagZeroed flag ) noexcept {
            validate_flag_impl< flag.append, flag.ignore >( flag );
        }
        // state getters
        auto state_language( ) noexcept -> Language { return Language_; }
        auto state_validate( ) noexcept -> Validate { return Validate_; }
        auto state_validate_veiled( ) noexcept -> ValidateVeiled { return static_cast< ValidateVeiled >( state_validate( ) ); }
        // state only getters
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
        this_thread::state( encode_impl( ret.out( ), in ) );
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
        this_thread::state( decode_impl( ret.out( ), in ) );
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
        this_thread::state( convert_impl( out, in ) );
        return out;
    }
    [[nodiscard]] auto string_word( StringByteView in ) -> StringWord {
        StringWord out;
        this_thread::state( convert_impl( out, in ) );
        return out;
    }
    // exception implementation
    Exception::Exception( Error code ) noexcept : code_{ code } { assert( code != Error::None ); }
    auto Exception::code( ) const noexcept -> Error { return code_; }
    auto Exception::what( ) const noexcept -> char const * { return error_message( code( ) ); }

} // namespace

// Ⓒ 2025-2026 Oleg'Ease'Kharchuk ᦒ
