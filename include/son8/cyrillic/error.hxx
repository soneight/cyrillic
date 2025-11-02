#ifndef SON8_CYRILLIC_ERROR_HXX
#define SON8_CYRILLIC_ERROR_HXX

namespace son8::cyrillic {

    enum class Error : unsigned {
        None,
        Language,
        InvalidWord,
        InvalidByte,
        // !IMPORTANT must be last element
        Size_,
    };

    auto error_message( Error code ) noexcept -> char const *;

} // namespace

#endif//SON8_CYRILLIC_ERROR_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
