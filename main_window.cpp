#include "main_window.hpp"
#include "gcalc_app.hpp"
#include "gcalc_basics.hpp"

#include <gtkmm/eventcontrollerkey.h>
#include <gtkmm/gestureclick.h>
#include <giomm/simpleactiongroup.h>
#include <giomm/menu.h>
#include <iostream>

#include "ccalc/calc_outputter.hpp"
#include "ccalc/calc_parse_error.hpp"

main_window::main_window(gcalc_app& app_) :
        app{app_},
        vbox(Gtk::Orientation::VERTICAL),
        expr_hbox(Gtk::Orientation::HORIZONTAL),
        bottom_hbox(Gtk::Orientation::HORIZONTAL),
        expr_do("="),
        options_do("Options"),
        help_do("Help"),
        parser(args.default_number_type_code, args.default_number_radix, args.int_word_size) {
    vbox.set_margin(default_margin);
    set_child(vbox);

    vbox.append(expr_hbox);

    expr_entry.set_margin(default_margin);
    expr_entry.set_hexpand(true);
    {
        auto controller = Gtk::EventControllerKey::create(); // note: returns smart pointer
        controller->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
        controller->signal_key_pressed().connect(sigc::mem_fun(*this, &main_window::on_expr_entry_key_pressed), true);
        expr_entry.add_controller(controller);
    }
    expr_hbox.append(expr_entry);

    expr_do.set_margin(default_margin);
    expr_do.signal_clicked().connect(sigc::mem_fun(*this, &main_window::on_expr_do_clicked));
    expr_hbox.append(expr_do);

    result_label.set_margin(default_margin);
    result_label.set_vexpand(true);
    result_label.set_halign(Gtk::Align::START);
    result_label.set_selectable(true);
    vbox.append(result_label);

    vbox.append(functions_hbox);
    functions.set_margin(default_margin);
    functions.set_hexpand(true);
    functions.append("Function");
    functions.append("exp() - e raised to the argument's power");
    functions.append("ln() - Natural (base e) log");
    functions.append("log10() - Base 10 log");
    functions.append("log2() - Base 2 log");
    functions.append("sqrt() - Square root");
    functions.append("cbrt() - Cubic root");
    functions.append("sin() - Sine");
    functions.append("cos() - Cosine");
    functions.append("tan() - Tangent");
    functions.append("asin() - Arc sin");
    functions.append("acos() - Arc cos");
    functions.append("atan() - Arc tan");
    functions.append("sinh() - Hyperbolic sin");
    functions.append("cosh() - Hyperbolic cos");
    functions.append("tanh() - Hyperbolic tan");
    functions.append("asinh() - Inverse hyperbolic sin");
    functions.append("acosh() - Inverse hyperbolic cos");
    functions.append("atanh() - Inverse hyperbolic tan");
    functions.append("gamma() - Gamma function");
    functions.append("lgamma() - Log gamma function");
    functions.append("arg() - Phase angle");
    functions.append("norm() - Squared magnitude");
    functions.append("conj() - Conjugate");
    functions.append("proj() - Projection onto the Riemann sphere");
    functions.set_active(0);
    functions.signal_changed().connect(sigc::mem_fun(*this, &main_window::on_functions_changed));
    functions_hbox.append(functions);

    vbox.append(bottom_hbox);

    options_do.set_margin(default_margin);
    options_do.signal_clicked().connect(sigc::mem_fun(*this, &main_window::on_options_do_clicked));
    bottom_hbox.append(options_do);

    help_do.set_margin(default_margin);
    help_do.signal_clicked().connect(sigc::mem_fun(*this, &main_window::on_help_do_clicked));
    bottom_hbox.append(help_do);
}

main_window::~main_window() {
}

bool main_window::on_expr_entry_key_pressed(guint keyval, guint, Gdk::ModifierType) {
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
        default:
            return false;
    }
}

void main_window::on_expr_do_clicked() {
    evaluate();
    expr_entry.grab_focus_without_selecting();
}

void main_window::on_functions_changed()
{
    auto text = functions.get_active_text();
    auto active_idx = functions.get_active_row_number();
    auto rparen_pos = text.find(')');
 
    if (active_idx != 0 && rparen_pos != decltype(text)::npos) {
        expr_entry.delete_selection(); // incase there's a selection
        int cursor_pos = expr_entry.get_position();
        expr_entry.insert_text(text, rparen_pos + 1, cursor_pos);
        expr_entry.set_position(cursor_pos - 1);
    }

    functions.set_active(0); // so it will show Functions on exit
    expr_entry.grab_focus_without_selecting();
}

void main_window::on_options_do_clicked() {
    options();
    expr_entry.grab_focus_without_selecting();
}

void main_window::on_help_do_clicked() {
    help();
}

void main_window::evaluate() {
    auto expr_str = expr_entry.get_text();
    output_options out_options(args);

    if (!expr_str.is_ascii()) {
        result_label.set_text("Only ASCII characters are allowed.");
        return;
    }

    try {
        auto result = parser.evaluate(
            std::string_view(expr_str.data(), expr_str.size()),
            std::bind(&main_window::help, this),
            out_options);

        calc_outputter outputter{out_options};
        std::ostringstream out;
        out << outputter(result);
        result_label.set_text(out.str());
        last_result_was_value = true;

        expr_entry.set_text(Glib::ustring());
    } catch (const calc_parse_error& e) {
        expr_entry.select_region(e.token().view_offset, e.token().view_offset + e.token().view.size());
        result_label.set_text(e.error_str());
        last_result_was_value = false;
    } catch (const calc_parser::void_expression) {
        result_label.set_text(Glib::ustring());
        last_result_was_value = false;
    }
}

void main_window::options() {
    result_label.set_text("Options is not implemented yet.");
    last_result_was_value = false;
}

void main_window::help() {
    app.help();
}
