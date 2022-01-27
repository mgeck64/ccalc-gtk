#include "main_window.hpp"
#include <gtkmm/eventcontrollerkey.h>
#include <iostream>

#include "ccalc/calc_outputter.hpp"
#include "ccalc/calc_parse_error.hpp"

constexpr auto default_margin = 4;

main_window::main_window() :
        vbox(Gtk::Orientation::VERTICAL),
        expr_do("="),
        parser(args.default_number_type_code, args.default_number_radix, args.int_word_size) {
    vbox.set_margin(default_margin);
    set_child(vbox);

    vbox.append(expr_hbox);

    expr_entry.set_margin(default_margin);
    expr_entry.set_hexpand(true);
    {
        auto controller = Gtk::EventControllerKey::create(); // note: returns smart pointer
        controller->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
        controller->signal_key_pressed().connect(sigc::mem_fun(*this, &main_window::on_entry_key_pressed), true);
        expr_entry.add_controller(controller);
    }
    expr_hbox.append(expr_entry);

    expr_do.set_margin(default_margin);
    expr_do.set_size_request(20, 20);
    expr_do.signal_clicked().connect(sigc::mem_fun(*this, &main_window::on_expr_do_clicked));
    expr_hbox.append(expr_do);

    result_label.set_margin(default_margin);
    result_label.set_halign(Gtk::Align::START);
    vbox.append(result_label);
}

bool main_window::on_entry_key_pressed(guint keyval, guint, Gdk::ModifierType) {
    switch (keyval) {
        case GDK_KEY_Return:
        case GDK_KEY_KP_Enter:
        case GDK_KEY_ISO_Enter:
        case GDK_KEY_3270_Enter:
            evaluate();
            return true;
        default:
            return false;
    }
}

void main_window::on_expr_do_clicked() {
    evaluate();
}

void main_window::evaluate() {
    auto expr_str = expr_entry.get_text();
    output_options out_options(args);

    if (!expr_str.is_ascii()) {
        result_label.set_text("Only U.S. ASCII characters are allowed.");
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
        last_result_was_error = false;
    } catch (const calc_parse_error& e) {
        expr_entry.select_region(e.token().view_offset, e.token().view_offset + e.token().view.size());
        result_label.set_text(e.error_str());
        last_result_was_error = true;
    } catch (const calc_parser::void_expression) {
        if (last_result_was_error)
            result_label.set_text("");
    }
}

void main_window::help() {
    result_label.set_text("Help is not implemented yet.");
}