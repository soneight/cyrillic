#ifndef SON8_CYRILLIC_STATE_HXX
#define SON8_CYRILLIC_STATE_HXX

namespace son8::cyrillic {

    enum class Language : unsigned {
        None,
        Russian,
        Ukrainian,
    };

    namespace this_thread {
        // state setters
        void state( Language language ) noexcept;
        // state getters
        auto state_language( ) noexcept -> Language;
    }
}

#endif//SON8_CYRILLIC_STATE_HXX
