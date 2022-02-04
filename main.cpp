#include "gcalc_app.hpp"
#include "glibmm/init.h"

int main(int argc, char* argv[]) {
    Glib::set_init_to_users_preferred_locale(false);
    // this is necessary otherwise boost's multiprecision floating point stream
    // output produces bad output if precision < 21. i don't know if there are
    // negative consequences to doing this

    return gcalc_app::create()->run(argc, argv);
}