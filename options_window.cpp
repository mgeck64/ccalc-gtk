#include "options_window.hpp"
#include "gcalc_basics.hpp"
#include "main_window.hpp"
#include "help_window.hpp"

#include <cassert>

options_window::options_window(gcalc_app& app_) :
    app(app_),
    win_vbox(Gtk::Orientation::VERTICAL),
    content_vbox(Gtk::Orientation::VERTICAL),
    options_hbox(Gtk::Orientation::HORIZONTAL),
    prev_option("\u25b2"),
    next_option("\u25bc"),
    option_vbox(Gtk::Orientation::VERTICAL),
    buttons_hbox(Gtk::Orientation::HORIZONTAL),
    help("Help"),
    defaults("Defaults"),
    accept("Accept"),
    cancel("Cancel"),
    option_0bi("Signed integer type, binary base (@0b or @0bi)"),
    option_0oi("Signed integer type, octal base (@0o or @0oi)"),
    option_0di("Signed integer type, decimal base (@0d or @0di)"),
    option_0xi("Signed integer type, hexadecimal base (@0x or @0xi)"),
    option_0bu("Unsigned integer type, binary base (@0bu)"),
    option_0ou("Unsigned integer type, octal base (@0ou)"),
    option_0du("Unsigned integer type, decimal base (@0du)"),
    option_0xu("Unsigned integer type, hexadecimal base (@0xu)"),
    option_0bn("Complex type, binary base (@0bn)"),
    option_0on("Complex type, octal base (@0on)"),
    option_0dn("Complex type, decimal base (@0dn)"),
    option_0xn("Complex type, hexadecimal base (@0xn)"),
    option_ob("Binary (@ob)"),
    option_oo("Octal (@oo)"),
    option_od("Decimal (@od)"),
    option_ox("Hexadecimal (@ox)"),
    option_pn("Normalized scientific P notation (@pn)"),
    option_pu("Unnormalized scientific P notation (@pu)"),
    precision_hbox(Gtk::Orientation::HORIZONTAL),
    option_pr("Floating point precision (@pr):"),
    option_w8("8 bits (@w8)"),
    option_w16("16 bits (@w16)"),
    option_w32("32 bits (@w32)"),
    option_w64("64 bits (@w64)"),
    option_w128("128 bits (@w128)"),
    message(*this, "")
{
    set_default_size(450, 500);
    set_child(win_vbox);

    win_vbox.append(content_vbox);
    content_vbox.set_margin(default_margin);

    content_vbox.append(title);
    title.set_margin(default_margin);
    title.set_markup("<big><b>Options</b></big>");
    title.set_halign(Gtk::Align::START);

    content_vbox.append(options_hbox);
    options_hbox.set_hexpand(false);
 
    options_hbox.append(options);
    options.set_margin(default_margin);
    options.set_hexpand(true);
    options.append("Input Defaults");
    options.append("Output Base");
    options.append("P Notation");
    options.append("Precision");
    options.append("Integer Word Size");
 
    options.signal_changed().connect(sigc::mem_fun(*this, &options_window::on_options_changed));

    options_hbox.append(prev_option);
    prev_option.set_margin(default_margin);
    prev_option.set_margin_end(0);
    prev_option.signal_clicked().connect(sigc::mem_fun(*this, &options_window::on_prev_option_clicked));


    options_hbox.append(next_option);
    next_option.set_margin(default_margin);
    next_option.set_margin_start(0);
    next_option.signal_clicked().connect(sigc::mem_fun(*this, &options_window::on_next_option_clicked));

    content_vbox.append(option_scroller);

    option_scroller.set_child(option_vbox);

    option_vbox.set_expand(true);

    win_vbox.append(buttons_hbox);
    buttons_hbox.set_vexpand(false);

    buttons_hbox.append(help);
    help.set_margin(0);
    help.set_expand(true);
    help.signal_clicked().connect(sigc::mem_fun(*this, &options_window::on_help_clicked));
 
    buttons_hbox.append(defaults);
    defaults.set_margin(0);
    defaults.set_expand(true);
    defaults.signal_clicked().connect(sigc::mem_fun(*this, &options_window::on_defaults_clicked));

    buttons_hbox.append(cancel);
    cancel.set_margin(0);
    cancel.set_expand(true);
    cancel.signal_clicked().connect(sigc::mem_fun(*this, &options_window::on_cancel_clicked));
 
    buttons_hbox.append(accept);
    accept.set_margin(0);
    accept.set_expand(true);
    accept.signal_clicked().connect(sigc::mem_fun(*this, &options_window::on_accept_clicked));

    constexpr auto dm = default_margin;
    // set only left and rignt margins so these pack vertically:
    option_0bi.set_margin_start(dm); option_0bi.set_margin_end(dm);
    option_0oi.set_margin_start(dm); option_0oi.set_margin_end(dm); option_0oi.set_group(option_0bi);
    option_0di.set_margin_start(dm); option_0di.set_margin_end(dm); option_0di.set_group(option_0bi);
    option_0xi.set_margin_start(dm); option_0xi.set_margin_end(dm); option_0xi.set_group(option_0bi);
    option_0bu.set_margin_start(dm); option_0bu.set_margin_end(dm); option_0bu.set_group(option_0bi);
    option_0ou.set_margin_start(dm); option_0ou.set_margin_end(dm); option_0ou.set_group(option_0bi);
    option_0du.set_margin_start(dm); option_0du.set_margin_end(dm); option_0du.set_group(option_0bi);
    option_0xu.set_margin_start(dm); option_0xu.set_margin_end(dm); option_0xu.set_group(option_0bi);
    option_0bn.set_margin_start(dm); option_0bn.set_margin_end(dm); option_0bn.set_group(option_0bi);
    option_0on.set_margin_start(dm); option_0on.set_margin_end(dm); option_0on.set_group(option_0bi);
    option_0dn.set_margin_start(dm); option_0dn.set_margin_end(dm); option_0dn.set_group(option_0bi);
    option_0xn.set_margin_start(dm); option_0xn.set_margin_end(dm); option_0xn.set_group(option_0bi);

    option_ob.set_margin(default_margin);
    option_oo.set_margin(default_margin); option_oo.set_group(option_ob);
    option_od.set_margin(default_margin); option_od.set_group(option_ob);
    option_ox.set_margin(default_margin); option_ox.set_group(option_ob);

    option_pr.set_margin(default_margin);
    option_pr_entry.set_margin(default_margin);

    option_pn.set_margin(default_margin);
    option_pu.set_margin(default_margin); option_pu.set_group(option_pn);

    option_w8.set_margin(default_margin);
    option_w16.set_margin(default_margin); option_w16.set_group(option_w8);
    option_w32.set_margin(default_margin); option_w32.set_group(option_w8);
    option_w64.set_margin(default_margin); option_w64.set_group(option_w8);
    option_w128.set_margin(default_margin); option_w128.set_group(option_w8);

    message.set_modal(true);
    message.set_hide_on_close(true);
    message.signal_response().connect(sigc::hide(sigc::mem_fun(message, &Gtk::Widget::hide)));

    assert(app.main_win());
    if (auto main_win = app.main_win()) {
        calc_args options;
        auto [parse_options, out_options] = main_win->options();
        options.default_number_type_code = parse_options.default_number_type_code;
        options.default_number_radix = parse_options.default_number_radix;
        options.output_radix = out_options.output_radix;
        options.output_fp_normalized = out_options.output_fp_normalized;
        options.precision = out_options.precision;
        options.int_word_size = parse_options.int_word_size;
        update_from(options, /*force*/ true);
    }

    show_option(0);
}

auto options_window::update_from(const calc_args& options, bool force) -> void {
    // force = true: update all option widgets
    // force = false: update option widgets only for options in args that have
    // been set (its corresponding counter will be non-zero; see
    // calc_parser::evaluate); thus any other pending changes by the user will
    // be preserved

    if (force || options.n_default_options)
        switch (options.default_number_type_code) {
            case calc_val::int_code:
                switch (options.default_number_radix) {
                    case calc_val::base2:  option_0bi.set_active(true); break;
                    case calc_val::base8:  option_0oi.set_active(true); break;
                    case calc_val::base10: option_0di.set_active(true); break;
                    case calc_val::base16: option_0xi.set_active(true); break;
                }
                break;
            case calc_val::uint_code:
                switch (options.default_number_radix) {
                    case calc_val::base2:  option_0bu.set_active(true); break;
                    case calc_val::base8:  option_0ou.set_active(true); break;
                    case calc_val::base10: option_0du.set_active(true); break;
                    case calc_val::base16: option_0xu.set_active(true); break;
                }
                break;
            case calc_val::complex_code:
                switch (options.default_number_radix) {
                    case calc_val::base2:  option_0bn.set_active(true); break;
                    case calc_val::base8:  option_0on.set_active(true); break;
                    case calc_val::base10: option_0dn.set_active(true); break;
                    case calc_val::base16: option_0xn.set_active(true); break;
                }
                break;
        }

    if (force || options.n_output_options)
        switch (options.output_radix) {
            case calc_val::base2:  option_ob.set_active(true); break;
            case calc_val::base8:  option_oo.set_active(true); break;
            case calc_val::base10: option_od.set_active(true); break;
            case calc_val::base16: option_ox.set_active(true); break;
        }

    if (force || options.n_output_fp_normalized_options)
        switch (options.output_fp_normalized) {
            case true:  option_pn.set_active(true); break;
            case false: option_pu.set_active(true); break;
        }

    if (force || options.n_precision_options)
        option_pr_entry.set_text(std::to_string(options.precision));

    if (force || options.n_int_word_size_options)
        switch (options.int_word_size) {
            case calc_val::int_bits_8:   option_w8.set_active(true); break;
            case calc_val::int_bits_16:  option_w16.set_active(true); break;
            case calc_val::int_bits_32:  option_w32.set_active(true); break;
            case calc_val::int_bits_64:  option_w64.set_active(true); break;
            case calc_val::int_bits_128: option_w128.set_active(true); break;
        }
}

auto options_window::show_option(int idx) -> void {
    switch (last_option_idx) {
        case input_default_idx:
            option_vbox.remove(option_0bi);
            option_vbox.remove(option_0oi);
            option_vbox.remove(option_0di);
            option_vbox.remove(option_0xi);
            option_vbox.remove(option_0bu);
            option_vbox.remove(option_0ou);
            option_vbox.remove(option_0du);
            option_vbox.remove(option_0xu);
            option_vbox.remove(option_0bn);
            option_vbox.remove(option_0on);
            option_vbox.remove(option_0dn);
            option_vbox.remove(option_0xn);
            break;
        case output_base_idx:
            option_vbox.remove(option_ob);
            option_vbox.remove(option_oo);
            option_vbox.remove(option_od);
            option_vbox.remove(option_ox);
            break;
        case p_notation_idx:
            option_vbox.remove(option_pn);
            option_vbox.remove(option_pu);
            break;
        case precision_idx:
            precision_hbox.remove(option_pr);
            precision_hbox.remove(option_pr_entry);
            option_vbox.remove(precision_hbox);
            break;
        case integer_word_size_idx:
            option_vbox.remove(option_w8);
            option_vbox.remove(option_w16);
            option_vbox.remove(option_w32);
            option_vbox.remove(option_w64);
            option_vbox.remove(option_w128);
            break;
    }

    switch (idx) {
        case input_default_idx:
            option_vbox.append(option_0bi);
            option_vbox.append(option_0oi);
            option_vbox.append(option_0di);
            option_vbox.append(option_0xi);
            option_vbox.append(option_0bu);
            option_vbox.append(option_0ou);
            option_vbox.append(option_0du);
            option_vbox.append(option_0xu);
            option_vbox.append(option_0bn);
            option_vbox.append(option_0on);
            option_vbox.append(option_0dn);
            option_vbox.append(option_0xn);
            last_option_idx = idx;
            options.set_active(idx);
            break;
        case output_base_idx:
            option_vbox.append(option_ob);
            option_vbox.append(option_oo);
            option_vbox.append(option_od);
            option_vbox.append(option_ox);
            last_option_idx = idx;
            options.set_active(idx);
            break;
        case p_notation_idx:
            option_vbox.append(option_pn);
            option_vbox.append(option_pu);
            last_option_idx = idx;
            options.set_active(idx);
            break;
        case precision_idx:
            option_vbox.append(precision_hbox);
            precision_hbox.append(option_pr);
            precision_hbox.append(option_pr_entry);
            last_option_idx = idx;
            options.set_active(idx);
            break;
        case integer_word_size_idx:
            option_vbox.append(option_w8);
            option_vbox.append(option_w16);
            option_vbox.append(option_w32);
            option_vbox.append(option_w64);
            option_vbox.append(option_w128);
            last_option_idx = idx;
            options.set_active(idx);
            break;
        default:
            assert(false);
    }
}

auto options_window::on_options_changed() -> void {
    auto idx = options.get_active_row_number();
    show_option(idx);
}

auto options_window::on_help_clicked() -> void {
    app.help(this, help_window::options_idx, /*force_topic*/ true);
}

auto options_window::on_cancel_clicked() -> void {
    hide();
}

auto options_window::on_defaults_clicked() -> void {
    update_from(calc_args(), /*force*/ true);
}

auto options_window::on_accept_clicked() -> void {
    auto main_win = app.main_win();
    assert(main_win);
    if (!main_win) {
        hide();
        return;
    }

    auto [parse_options, out_options] = main_win->options();

    if (option_0bi.get_active()) {
        parse_options.default_number_radix = calc_val::base2;
        parse_options.default_number_type_code = calc_val::int_code;
    } else if (option_0oi.get_active()) {
        parse_options.default_number_radix = calc_val::base8;
        parse_options.default_number_type_code = calc_val::int_code;
    } else if (option_0di.get_active()) {
        parse_options.default_number_radix = calc_val::base10;
        parse_options.default_number_type_code = calc_val::int_code;
    } else if (option_0xi.get_active()) {
        parse_options.default_number_radix = calc_val::base16;
        parse_options.default_number_type_code = calc_val::int_code;
    } else if (option_0bu.get_active()) {
        parse_options.default_number_radix = calc_val::base2;
        parse_options.default_number_type_code = calc_val::uint_code;
    } else if (option_0ou.get_active()) {
        parse_options.default_number_radix = calc_val::base8;
        parse_options.default_number_type_code = calc_val::uint_code;
    } else if (option_0du.get_active()) {
        parse_options.default_number_radix = calc_val::base10;
        parse_options.default_number_type_code = calc_val::uint_code;
    } else if (option_0xu.get_active()) {
        parse_options.default_number_radix = calc_val::base16;
        parse_options.default_number_type_code = calc_val::uint_code;
    } else if (option_0bn.get_active()) {
        parse_options.default_number_radix = calc_val::base2;
        parse_options.default_number_type_code = calc_val::complex_code;
    } else if (option_0on.get_active()) {
        parse_options.default_number_radix = calc_val::base8;
        parse_options.default_number_type_code = calc_val::complex_code;
    } else if (option_0dn.get_active()) {
        parse_options.default_number_radix = calc_val::base10;
        parse_options.default_number_type_code = calc_val::complex_code;
    } else if (option_0xn.get_active()) {
        parse_options.default_number_radix = calc_val::base16;
        parse_options.default_number_type_code = calc_val::complex_code;
    }

    if (option_ob.get_active())
        out_options.output_radix = calc_val::base2;
    else if (option_oo.get_active())
        out_options.output_radix = calc_val::base8;
    else if (option_od.get_active())
        out_options.output_radix = calc_val::base10;
    else if (option_ox.get_active())
        out_options.output_radix = calc_val::base16;

    if (option_pn.get_active())
        out_options.output_fp_normalized = true;
    else if (option_pu.get_active())
        out_options.output_fp_normalized = false;

    try {
        auto text = option_pr_entry.get_text();
        size_t idx = 0;
        auto precision = std::stoi(text, &idx);
        while (idx < text.size() && isspace(text[idx]))
            ++idx;
        if (precision < 0 || !text.is_ascii() || idx != text.size())
            throw std::invalid_argument("Invalid value");
        out_options.precision = precision;
    } catch (...) {
        show_option(precision_idx);
        message.set_message("Floating point precision value is invalid");
        message.set_modal(true);
        message.show();
        return;
    }

    if (option_w8.get_active())
        parse_options.int_word_size = calc_val::int_bits_8;
    else if (option_w16.get_active())
        parse_options.int_word_size = calc_val::int_bits_16;
    else if (option_w32.get_active())
        parse_options.int_word_size = calc_val::int_bits_32;
    else if (option_w64.get_active())
        parse_options.int_word_size = calc_val::int_bits_64;
    else if (option_w128.get_active())
        parse_options.int_word_size = calc_val::int_bits_128;

    main_win->options(parse_options, out_options);
    hide();
}

auto options_window::on_prev_option_clicked() -> void {
    auto idx = options.get_active_row_number();
    if (idx > 0)
        show_option(idx - 1);
    else if (auto p = get_display())
        gdk_display_beep(p->gobj());
}

auto options_window::on_next_option_clicked() -> void {
    auto idx = options.get_active_row_number();
    if (idx < num_options - 1)
        show_option(idx + 1);
    else if (auto p = get_display())
        gdk_display_beep(p->gobj());
}
