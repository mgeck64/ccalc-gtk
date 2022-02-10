#ifndef CALC_SETTINGS_HPP
#define CALC_SETTINGS_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <gtkmm/messagedialog.h>

#include "ccalc/calc_args.hpp"

class calc_settings {
private:
    auto make_file_pathname() -> const std::string&;
    std::string file_pathname;
    Gtk::MessageDialog error_msg;

    auto int_to_radix(int i) -> calc_val::radices;

public:
    calc_settings(Gtk::Window& parent_win);
    // note: because this can show a modal error dialog, make this a member of
    // the parent window to make sure the dialog will persist (i.e., don't use
    // this as local variable else dialog won't persist after function returns)

    auto load(parser_options& parse_options, output_options& out_options) -> void;
    // each field in parse_options and out_options is expected to have a
    // suitable default value, which will be retained if the settings file is
    // missing or doesn't contain a value for that field. If an exception is
    // thrown, the file may have been partially loaded, and parse_options and
    // out_options will reflect that

    auto save(const parser_options& parse_options, const output_options& out_options) -> void;

    auto to_radix(std::string_view str) -> calc_val::radices;
    auto to_number_type_code(std::string_view str) -> calc_val::number_type_codes;
    auto to_int_word_size(std::string_view str) -> calc_val::int_word_sizes;
};

#endif // CALC_SETTINGS_HPP