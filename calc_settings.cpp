#include "calc_settings.hpp"
#include <filesystem>

calc_settings::calc_settings(Gtk::Window& parent_win) :
    error_msg(parent_win, "", /*use_markup*/ false, Gtk::MessageType::ERROR, Gtk::ButtonsType::OK, /*modal*/ true)
{
    error_msg.set_hide_on_close(true);
    error_msg.signal_response().connect(sigc::hide(sigc::mem_fun(error_msg, &Gtk::Widget::hide)));
}

auto calc_settings::make_file_pathname() -> const std::string& {
    if (auto config_home = getenv("XDG_CONFIG_HOME"))
        file_pathname = config_home;
    else if (auto home = getenv("HOME")) {
        file_pathname = home;
        if (!file_pathname.empty())
            file_pathname += "/.config";
    }
    if (file_pathname.empty())
        throw boost::property_tree::ptree_error(
            "Unable to determine the file's location; set XDG_CONFIG_HOME or HOME environment variable");
    file_pathname += "/gcalc.conf";
    return file_pathname;
}

auto calc_settings::to_radix(std::string_view str) -> calc_val::radices {
    if (str == "base2") return calc_val::base2;
    if (str == "base8") return calc_val::base8;
    if (str == "base10") return calc_val::base10;
    if (str == "base16") return calc_val::base16;
    throw boost::property_tree::ini_parser_error("Bad radix value in file", file_pathname, 0);
}

static auto to_str(calc_val::radices radix) -> const char* {
    switch (radix) {
        case calc_val::base2: return "base2";
        case calc_val::base8: return "base8";
        case calc_val::base10: return "base10";
        case calc_val::base16: return "base16";
        default: assert(false); // missing case(s)
    }
}

auto calc_settings::to_number_type_code(std::string_view str) -> calc_val::number_type_codes {
    if (str == "complex_code") return calc_val::complex_code;
    if (str == "uint_code") return calc_val::uint_code;
    if (str == "int_code") return calc_val::int_code;
    throw boost::property_tree::ini_parser_error("Bad number type code value in file", file_pathname, 0);
}

static auto to_str(calc_val::number_type_codes code) -> const char* {
    switch (code) {
        case calc_val::complex_code: return "complex_code";
        case calc_val::uint_code: return "uint_code";
        case calc_val::int_code: return "int_code";
        default: assert(false); // missing case(s)
    }
}

auto calc_settings::to_int_word_size(std::string_view str) -> calc_val::int_word_sizes {
    if (str == "int_bits_8") return calc_val::int_bits_8;
    if (str == "int_bits_16") return calc_val::int_bits_16;
    if (str == "int_bits_32") return calc_val::int_bits_32;
    if (str == "int_bits_64") return calc_val::int_bits_64;
    if (str == "int_bits_128") return calc_val::int_bits_128;
    throw boost::property_tree::ini_parser_error("Bad int word size value in file", file_pathname, 0);
}

static auto to_str(calc_val::int_word_sizes code) -> const char* {
    switch (code) {
        case calc_val::int_bits_8: return "int_bits_8";
        case calc_val::int_bits_16: return "int_bits_16";
        case calc_val::int_bits_32: return "int_bits_32";
        case calc_val::int_bits_64: return "int_bits_64";
        case calc_val::int_bits_128: return "int_bits_128";
        default: assert(false); // missing case(s)
    }
}

auto calc_settings::load(parser_options& parse_options, output_options& out_options) -> void {
    boost::property_tree::ptree tree;

    if (!std::filesystem::exists(std::filesystem::path(make_file_pathname())))
        return;

    try {
        boost::property_tree::read_ini(file_pathname, tree);

        std::string str;
        str.reserve(32);

        str = tree.get("parse_options.default_number_radix", to_str(parse_options.default_number_radix));
        parse_options.default_number_radix = to_radix(str);

        str = tree.get("parse_options.default_number_type_code", to_str(parse_options.default_number_type_code));
        parse_options.default_number_type_code = to_number_type_code(str);

        str = tree.get("parse_options.int_word_size", to_str(parse_options.int_word_size));
        parse_options.int_word_size = to_int_word_size(str);

        out_options.output_fp_normalized = tree.get("out_options.output_fp_normalized", out_options.output_fp_normalized);

        str = tree.get("out_options.output_radix", to_str(out_options.output_radix));
        out_options.output_radix = to_radix(str);

        static_assert(std::is_unsigned_v<decltype(out_options.precision)>);
        out_options.precision = tree.get("out_options.precision", out_options.precision);
    } catch (const boost::property_tree::ptree_error& e) {
        error_msg.set_message("An error occurred loading the settings file");
        error_msg.set_secondary_text(e.what());
        error_msg.show();
        return;
    }
}

auto calc_settings::save(const parser_options& parse_options, const output_options& out_options) -> void {
    boost::property_tree::ptree tree;

    try {
        tree.put("parse_options.default_number_radix", to_str(parse_options.default_number_radix));
        tree.put("parse_options.default_number_type_code", to_str(parse_options.default_number_type_code));
        tree.put("parse_options.int_word_size", to_str(parse_options.int_word_size));

        tree.put("out_options.output_fp_normalized", out_options.output_fp_normalized);
        tree.put("out_options.output_radix", to_str(out_options.output_radix));
        tree.put("out_options.precision", out_options.precision);

        boost::property_tree::write_ini(make_file_pathname(), tree);
    } catch (const boost::property_tree::ptree_error& e) {
        error_msg.set_message("An error occurred saving the settings file");
        error_msg.set_secondary_text(e.what());
        error_msg.show();
        return;
    }
}
