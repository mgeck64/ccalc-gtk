#ifndef GCALC_BASICS_HPP
#define GCALC_BASICS_HPP

#include <glibmm/ustring.h>

constexpr auto default_margin = 4;

auto is_blank(const Glib::ustring& str) -> bool;
// returns true if str consists solely of whitespace chars (as defined by
// isspace()) or is empty; false otherwise

constexpr auto app_name = "gcalc";
constexpr auto app_name_bold = "<b>gcalc</b>";
constexpr auto app_id = "com.github.mgeck64.GCalc";
constexpr auto app_icon = "accessories-calculator";
constexpr auto app_version = "0.1.0";
constexpr auto app_copyright = "Copyright \u00a9 2022 Mark Geck";

#endif