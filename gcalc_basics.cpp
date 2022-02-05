#include "gcalc_basics.hpp"

bool is_blank(const Glib::ustring& str) {
    for (auto c : str)
        if (!isspace(c))
            return false;
    return true;
}
