#ifndef SON8_CYRILLIC_ERROR_HXX
#define SON8_CYRILLIC_ERROR_HXX

#include <string_view>

namespace son8::cyrillic {

    enum class Error : unsigned {
        None,
        Language,
        InvalidWord,
        // !IMPORTANT must be last element
        Size_,
    };

    auto error_message( Error code ) -> std::string_view;

}

#endif//SON8_CYRILLIC_ERROR_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
