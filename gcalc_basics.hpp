#ifndef GCALC_BASICS_HPP
#define GCALC_BASICS_HPP

#include <glibmm/ustring.h>

constexpr auto default_margin = 4;

bool is_blank(const Glib::ustring& str);
// returns true if str consists solely of whitespace chars (as defined by
// isspace()) or is empty; false otherwise

#endif