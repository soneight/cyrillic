#ifndef SON8_CYRILLIC_STATE_HXX
#define SON8_CYRILLIC_STATE_HXX

#include <son8/cyrillic/error.hxx>
#include <son8/cyrillic/validate.hxx>

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
        void state( Validate validate ) noexcept;
        void state( ValidateFlagAppend flag ) noexcept;
        void state( ValidateFlagIgnore flag ) noexcept;
        void state( ValidateVeiled flags ) noexcept;
        // state getters
        auto state_language( ) noexcept -> Language;
        auto state_error( ) noexcept -> Error;
        auto state_validate( ) noexcept -> Validate;
        auto state_validate_veiled( ) noexcept -> ValidateVeiled;
    }
}

#endif//SON8_CYRILLIC_STATE_HXX

// Ⓒ 2025-2026 Oleg'Ease'Kharchuk ᦒ
