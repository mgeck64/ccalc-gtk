#include "main_window.hpp"
#include "gcalc_app.hpp"
#include "gcalc_basics.hpp"
#include "help_window.hpp"
#include "options_window.hpp"
#include "variables_window.hpp"

#include "ccalc/calc_parse_error.hpp"
#include "ccalc/calc_outputter.hpp"

#include <gtkmm/eventcontrollerkey.h>
#include <gtkmm/gestureclick.h>
#include <giomm/simpleactiongroup.h>
#include <giomm/menu.h>

main_window::main_window(gcalc_app& app_) :
    app{app_},
    win_vbox(Gtk::Orientation::VERTICAL),
    content_vbox(Gtk::Orientation::VERTICAL),
    expr_hbox(Gtk::Orientation::HORIZONTAL),
    in_out_info_hbox(Gtk::Orientation::HORIZONTAL),
    menus_hbox(Gtk::Orientation::HORIZONTAL),
    expr_btn("="),
    out_options(args),
    parser(args.default_number_type_code, args.default_number_radix, args.int_word_size)
 {
    set_child(win_vbox);

    win_vbox.append(content_vbox);
    content_vbox.set_margin(default_margin);

    content_vbox.append(expr_hbox);

    expr_hbox.append(expr_entry);
    expr_entry.set_margin(default_margin);
    expr_entry.set_hexpand(true);
 
    {
        auto controller = Gtk::EventControllerKey::create();
        expr_entry.add_controller(controller);
        controller->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
        controller->signal_key_pressed().connect(sigc::mem_fun(*this, &main_window::on_expr_entry_key_pressed), true);
    }

    expr_hbox.append(expr_btn);
    expr_btn.set_margin(default_margin);
    expr_btn.signal_clicked().connect(sigc::mem_fun(*this, &main_window::on_expr_btn_clicked));

    content_vbox.append(result_label);
    result_label.set_margin(default_margin);
    result_label.set_vexpand(true);
    result_label.set_halign(Gtk::Align::START);
    result_label.set_selectable(true);
 
    content_vbox.append(in_out_info_hbox);
    in_out_info_hbox.append(in_info_label);
    in_out_info_hbox.append(out_info_label);
    in_info_label.set_margin(default_margin);
    in_info_label.set_hexpand(true);
    in_info_label.set_halign(Gtk::Align::START);
    out_info_label.set_margin(default_margin);
    out_info_label.set_hexpand(true);
    out_info_label.set_halign(Gtk::Align::END);

    win_vbox.append(menus_hbox);

    {
        auto functions_action_group = Gio::SimpleActionGroup::create();
        insert_action_group("functions", functions_action_group);

        auto add_action = [&](Gio::Menu& menu, const char* label, const char* action, const char* full_action) {
            functions_action_group->add_action(action, sigc::bind(sigc::mem_fun(*this, &main_window::on_function_action), label));
            menu.append(label, full_action);
        };

        menus_hbox.append(functions_a_btn);
        functions_a_btn.set_label("Funcs");
        functions_a_btn.set_tooltip_text("General Functons");
        functions_a_btn.set_margin(0);
        functions_a_btn.set_hexpand(true);

        auto functions_a_menu = Gio::Menu::create();
        functions_a_btn.set_menu_model(functions_a_menu);

        add_action(*functions_a_menu, "exp() - e raised to the argument's power", "exp", "functions.exp");
        add_action(*functions_a_menu, "ln() - Natural (base e) log", "ln", "functions.ln");
        add_action(*functions_a_menu, "log10() - Base 10 log", "log10", "functions.log10");
        add_action(*functions_a_menu, "log2() - Base 2 log", "log2", "functions.log2");
        add_action(*functions_a_menu, "sqrt() - Square root", "sqrt", "functions.sqrt");
        add_action(*functions_a_menu, "cbrt() - Cubic root", "cbrt", "functions.cbrt");
        add_action(*functions_a_menu, "gamma() - Gamma function", "gamma", "functions.gamma");
        add_action(*functions_a_menu, "lgamma() - Log gamma function", "lgamma", "functions.lgamma");
        add_action(*functions_a_menu, "arg() - Phase angle", "arg", "functions.arg");
        add_action(*functions_a_menu, "norm() - Squared magnitude", "norm", "functions.norm");
        add_action(*functions_a_menu, "conj() - Conjugate", "conj", "functions.conj");
        add_action(*functions_a_menu, "proj() - Projection onto the Riemann sphere", "proj", "functions.proj");

        menus_hbox.append(functions_b_btn);
        functions_b_btn.set_label("Trig Funcs");
        functions_b_btn.set_margin(0);
        functions_b_btn.set_tooltip_text("Trigonometric Functons");
        functions_b_btn.set_hexpand(true);

        auto functions_b_menu = Gio::Menu::create();
        functions_b_btn.set_menu_model(functions_b_menu);
    
        add_action(*functions_b_menu, "sin() - Sine", "sin", "functions.sin");
        add_action(*functions_b_menu, "cos() - Cosine", "cos", "functions.cos");
        add_action(*functions_b_menu, "tan() - Tangent", "tan", "functions.tan");
        add_action(*functions_b_menu, "asin() - Arc sin", "asin", "functions.asin");
        add_action(*functions_b_menu, "acos() - Arc cos", "acos", "functions.acos");
        add_action(*functions_b_menu, "atan() - Arc tan", "atan", "functions.atan");
        add_action(*functions_b_menu, "sinh() - Hyperbolic sin", "sinh", "functions.sinh");
        add_action(*functions_b_menu, "cosh() - Hyperbolic cos", "cosh", "functions.cosh");
        add_action(*functions_b_menu, "tanh() - Hyperbolic tan", "tanh", "functions.tanh");
        add_action(*functions_b_menu, "asinh() - Inverse hyperbolic sin", "asinh", "functions.asinh");
        add_action(*functions_b_menu, "acosh() - Inverse hyperbolic cos", "acosh", "functions.acosh");
        add_action(*functions_b_menu, "atanh() - Inverse hyperbolic tan", "atanh", "functions.atanh");
    }

    {
        auto more_action_group = Gio::SimpleActionGroup::create();
        insert_action_group("more", more_action_group);

        menus_hbox.append(more_btn);
        more_btn.set_icon_name("open-menu-symbolic");
        more_btn.set_margin(0);
        more_btn.set_hexpand(false);

        auto more_menu = Gio::Menu::create();
        more_btn.set_menu_model(more_menu);

        more_action_group->add_action("options", sigc::mem_fun(*this, &main_window::on_options_btn_clicked));
        more_menu->append("Options", "more.options");

        more_action_group->add_action("variables", sigc::mem_fun(*this, &main_window::on_variables_btn_clicked));
        more_menu->append("Variables", "more.variables");

        more_action_group->add_action("help", sigc::mem_fun(*this, &main_window::on_help_btn_clicked));
        more_menu->append("Help", "more.help");
    }

    show_input_info();
    show_output_info();
}

auto main_window::show_input_info() -> void {
    auto parse_options = parser.options();

    Glib::ustring buf;
    buf.reserve(128);

    buf = "Input: ";
    switch (parse_options.default_number_type_code) {
        case calc_val::int_code: buf += "int "; break;
        case calc_val::uint_code: buf += "uint "; break;
        case calc_val::complex_code: buf += "cplx "; break;
    }
    switch (parse_options.default_number_radix) {
        case calc_val::base2: buf += "binary"; break;
        case calc_val::base8: buf += "octal"; break;
        case calc_val::base10: buf += "decimal"; break;
        case calc_val::base16: buf += "hex"; break;
    }
    in_info_label.set_text(buf);
}

auto main_window::show_output_info() -> void {
    Glib::ustring buf;
    buf.reserve(128);

    buf = "Output: ";
    switch (out_options.output_radix) {
        case calc_val::base2: buf += "binary"; break;
        case calc_val::base8: buf += "octal"; break;
        case calc_val::base10: buf += "decimal"; break;
        case calc_val::base16: buf += "hex"; break;
    }
    out_info_label.set_text(buf);
}

auto main_window::append_history(const Glib::ustring& expr_str) -> void {
    if (is_blank(expr_str))
        return;
    static_assert(max_history_size > 0);
    if (history.size() >= max_history_size)
        history.erase(history.begin());
    history.push_back(expr_str);
    history_idx = history.size(); // 1 past last so pressing up-arrow will recover it
}

auto main_window::recall_history(bool direction_up) -> void {
    bool beep_and_return = false;

    if (direction_up) {
        if (history_idx > 0)
            --history_idx;
        else
            beep_and_return = true;
    } else {
        if (history_idx < history.size()) // allow 1 past last element
            ++history_idx;
        else
            beep_and_return = true;
    }

    if (beep_and_return) {
        if (auto p = get_display())
            gdk_display_beep(p->gobj());
        return;
    }

    static_assert(std::is_unsigned_v<decltype(history_idx)>);
    if (history_idx < history.size()) {
        const auto& text = history[history_idx];
        expr_entry.set_text(text);
        expr_entry.set_position(text.size());
    } else
        expr_entry.set_text(Glib::ustring());
    result_label.set_text(Glib::ustring());
    last_result_kind = none_kind;
}

auto main_window::on_expr_entry_key_pressed(guint keyval, guint, Gdk::ModifierType) -> bool {
    switch (keyval) {
        case GDK_KEY_Return:
        case GDK_KEY_KP_Enter:
        case GDK_KEY_ISO_Enter:
        case GDK_KEY_3270_Enter:
            evaluate();
            return true;
        case GDK_KEY_parenright: {
            auto text = expr_entry.get_text();
            auto pos = expr_entry.get_position();
            if (decltype(text)::size_type(pos) < text.size() && text[pos] == ')') {
                expr_entry.set_position(pos + 1);
                return true;
            }
            return false;
        }
        case GDK_KEY_Up:
            recall_history(/*direction_up*/ true);
            return true;
        case GDK_KEY_Down:
            recall_history(/*direction_up*/ false);
            return true;
        default:
            return false;
    }
}

auto main_window::on_expr_btn_clicked() -> void {
    evaluate();
    expr_entry.grab_focus_without_selecting();
}

auto main_window::on_function_action(const char* label) -> void {
    std::string_view text = label;
    auto rparen_pos = text.find(')');
    if (rparen_pos != decltype(text)::npos) {
        expr_entry.delete_selection(); // incase there's a selection
        int cursor_pos = expr_entry.get_position();
        expr_entry.insert_text(text.data(), rparen_pos + 1, cursor_pos);
        expr_entry.set_position(cursor_pos - 1);
    }
    expr_entry.grab_focus_without_selecting();
}

auto main_window::on_options_btn_clicked() -> void {
    if (options_win)
        options_win->present();
    else {
        options_win = std::make_unique<options_window>(app, *this);
        options_win->signal_close_request().connect(sigc::bind(sigc::mem_fun(*this, &main_window::on_close_request), options_win.get()), false);
        options_win->show();
    }
}

auto main_window::on_variables_btn_clicked() -> void {
    if (variables_win)
        variables_win->present();
    else {
        variables_win = std::make_unique<variables_window>();
        variables_win->signal_close_request().connect(sigc::bind(sigc::mem_fun(*this, &main_window::on_close_request), variables_win.get()), false);

        variables_win->show(); // show needs to be called before set otherwise
        // content will inexplicably be selected and cursor will be visible. see
        // also variables_window::set. sigh!

        variables_win->set(parser.variables_begin(), parser.variables_end(), out_options);
    }
}

auto main_window::on_help_btn_clicked() -> void {
    app.help(this, help_window::quick_start_idx, false);
}

auto main_window::on_variables_changed() -> void {
    if (variables_win)
        variables_win->set(parser.variables_begin(), parser.variables_end(), out_options);
}

auto main_window::evaluate() -> void {
    auto expr_str = expr_entry.get_text();

    if (!expr_str.is_ascii()) {
        result_label.set_text("Only ASCII characters are allowed.");
        return;
    }

    calc_args options;
    auto out_options_ = out_options;
    try {
        auto result = parser.evaluate(
            std::string_view(expr_str.data(), expr_str.size()),
            std::bind(&main_window::on_help_btn_clicked, this),
            out_options_,
            std::bind(&main_window::on_variables_changed, this),
            &options);
        std::ostringstream out;
        out << calc_outputter(out_options_)(result);
        result_label.set_text(out.str());
        last_result_kind = value_kind;
        expr_entry.set_text(Glib::ustring());
        append_history(expr_str);
    } catch (const calc_parse_error& e) {
        expr_entry.select_region(e.token().view_offset, e.token().view_offset + e.token().view.size());
        result_label.set_text(e.error_str());
        last_result_kind = parse_error_kind;
    } catch (const calc_parser::void_expression) { // this is not an error
        expr_entry.set_text(Glib::ustring());
        if (last_result_kind == parse_error_kind) {
            result_label.set_text(Glib::ustring());
            last_result_kind = none_kind;
        }
        append_history(expr_str);
    }
    show_input_info();
    update_if_options_changed(out_options_);
    if (options_win)
        options_win->update_from(options);
}

auto main_window::options(const parser_options& parse_options, const output_options& out_options) -> void {
    parser.options(parse_options);
    show_input_info();
    update_if_options_changed(out_options);
}

auto main_window::update_if_options_changed(const output_options& new_options) -> void {
    if (out_options != new_options) {
        out_options = new_options;
        on_variables_changed(); // output format changed; redisplay
        if (last_result_kind == value_kind) {
            std::ostringstream out;
            out << calc_outputter(out_options)(parser.last_val());
            result_label.set_text(out.str());
        }
        show_output_info();
    }
}

auto main_window::on_close_request(Gtk::Window* win) -> bool {
    assert(win);
    if (win == variables_win.get()) {
        variables_win.reset();
        return true;
    }
    if (win == options_win.get()) {
        options_win.reset();
        return true;
    }
    return false;
}
