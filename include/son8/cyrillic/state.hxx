#ifndef SON8_CYRILLIC_STATE_HXX
#define SON8_CYRILLIC_STATE_HXX

#include <son8/cyrillic/error.hxx>

namespace son8::cyrillic {

    enum class Language : unsigned {
        None,
        Russian, Rysskui = Russian,
        Ukrainian, Ykrajinsqka = Ukrainian,
        // IMPORTANT must be last
        Size_
    };

    namespace this_thread {
        // state setters
        void state( Language language ) noexcept;
        // state getters
        auto state_language( ) noexcept -> Language;
        auto state_error( ) noexcept -> Error;
    }
}

#endif//SON8_CYRILLIC_STATE_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
