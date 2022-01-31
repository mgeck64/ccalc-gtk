#include "main_window.hpp"
#include "gcalc_app.hpp"
#include "gcalc_basics.hpp"

//#include <iostream>
#include "ccalc/calc_parse_error.hpp"
#include "ccalc/calc_outputter.hpp"

#include <gtkmm/eventcontrollerkey.h>
#include <gtkmm/gestureclick.h>
#include <giomm/simpleactiongroup.h>
#include <giomm/menu.h>

main_window::main_window(gcalc_app& app_) :
        app{app_},
        vbox(Gtk::Orientation::VERTICAL),
        expr_hbox(Gtk::Orientation::HORIZONTAL),
        menus_hbox(Gtk::Orientation::HORIZONTAL),
        expr_do("="),
        out_options(args),
        parser(args.default_number_type_code, args.default_number_radix, args.int_word_size) {
    set_child(vbox);
    vbox.set_margin(default_margin);

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

    vbox.append(menus_hbox);
    {
        auto functions_action_group = Gio::SimpleActionGroup::create();
        insert_action_group("function", functions_action_group);

        auto add_action = [&](Gio::Menu& menu, const char* label, const char* action, const char* full_action) {
            functions_action_group->add_action(action, sigc::bind(sigc::mem_fun(*this, &main_window::on_function_action), label));
            menu.append(label, full_action);
        };

        functions_a_do.set_label("Funcs");
        functions_a_do.set_tooltip_text("General Functons");
        functions_a_do.set_margin(default_margin);
        functions_a_do.set_hexpand(true);

        functions_a_menu = Gio::Menu::create();
        functions_a_do.set_menu_model(functions_a_menu);

        menus_hbox.append(functions_a_do);

        add_action(*functions_a_menu, "exp() - e raised to the argument's power", "exp", "function.exp");
        add_action(*functions_a_menu, "ln() - Natural (base e) log", "ln", "function.ln");
        add_action(*functions_a_menu, "log10() - Base 10 log", "log10", "function.log10");
        add_action(*functions_a_menu, "log2() - Base 2 log", "log2", "function.log2");
        add_action(*functions_a_menu, "sqrt() - Square root", "sqrt", "function.sqrt");
        add_action(*functions_a_menu, "cbrt() - Cubic root", "cbrt", "function.cbrt");
        add_action(*functions_a_menu, "gamma() - Gamma function", "gamma", "function.gamma");
        add_action(*functions_a_menu, "lgamma() - Log gamma function", "lgamma", "function.lgamma");
        add_action(*functions_a_menu, "arg() - Phase angle", "arg", "function.arg");
        add_action(*functions_a_menu, "norm() - Squared magnitude", "norm", "function.norm");
        add_action(*functions_a_menu, "conj() - Conjugate", "conj", "function.conj");
        add_action(*functions_a_menu, "proj() - Projection onto the Riemann sphere", "proj", "function.proj");

        functions_b_do.set_label("Trig Funcs");
        functions_b_do.set_margin(default_margin);
        functions_b_do.set_tooltip_text("Trigonometric Functons");
        functions_b_do.set_hexpand(true);

        functions_b_menu = Gio::Menu::create();
        functions_b_do.set_menu_model(functions_b_menu);

        menus_hbox.append(functions_b_do);
    
        add_action(*functions_b_menu, "sin() - Sine", "sin", "function.sin");
        add_action(*functions_b_menu, "cos() - Cosine", "cos", "function.cos");
        add_action(*functions_b_menu, "tan() - Tangent", "tan", "function.tan");
        add_action(*functions_b_menu, "asin() - Arc sin", "asin", "function.asin");
        add_action(*functions_b_menu, "acos() - Arc cos", "acos", "function.acos");
        add_action(*functions_b_menu, "atan() - Arc tan", "atan", "function.atan");
        add_action(*functions_b_menu, "sinh() - Hyperbolic sin", "sinh", "function.sinh");
        add_action(*functions_b_menu, "cosh() - Hyperbolic cos", "cosh", "function.cosh");
        add_action(*functions_b_menu, "tanh() - Hyperbolic tan", "tanh", "function.tanh");
        add_action(*functions_b_menu, "asinh() - Inverse hyperbolic sin", "asinh", "function.asinh");
        add_action(*functions_b_menu, "acosh() - Inverse hyperbolic cos", "acosh", "function.acosh");
        add_action(*functions_b_menu, "atanh() - Inverse hyperbolic tan", "atanh", "function.atanh");
    }

    {
        auto more_action_group = Gio::SimpleActionGroup::create();
        insert_action_group("more", more_action_group);

        more_do.set_label("More");
        more_do.set_margin(default_margin);
        more_do.set_hexpand(false);

        more_menu = Gio::Menu::create();
        more_do.set_menu_model(more_menu);

        menus_hbox.append(more_do);

        more_action_group->add_action("options", sigc::mem_fun(*this, &main_window::on_options_do_clicked));
        more_menu->append("Options", "more.options");

        more_action_group->add_action("variables", sigc::mem_fun(*this, &main_window::on_variables_do_clicked));
        more_menu->append("Variables", "more.variables");

        more_action_group->add_action("help", sigc::mem_fun(*this, &main_window::on_help_do_clicked));
        more_menu->append("Help", "more.help");
    }
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

void main_window::on_function_action(const char* label) {
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

void main_window::on_options_do_clicked() {
    options();
    expr_entry.grab_focus_without_selecting();
}

void main_window::on_variables_do_clicked() {
    show_variables();
    expr_entry.grab_focus_without_selecting();
}

void main_window::on_help_do_clicked() {
    help();
    expr_entry.grab_focus_without_selecting();
}

void main_window::evaluate() {
    auto expr_str = expr_entry.get_text();

    if (!expr_str.is_ascii()) {
        result_label.set_text("Only ASCII characters are allowed.");
        return;
    }

    try {
        auto result = parser.evaluate(
            std::string_view(expr_str.data(), expr_str.size()),
            std::bind(&main_window::help, this),
            out_options);
        std::ostringstream out;
        out << calc_outputter(out_options)(result);
        result_label.set_text(out.str());
        last_result_was_value = true;
        expr_entry.set_text(Glib::ustring());
    } catch (const calc_parse_error& e) {
        expr_entry.select_region(e.token().view_offset, e.token().view_offset + e.token().view.size());
        result_label.set_text(e.error_str());
        last_result_was_value = false;
    } catch (const calc_parser::void_expression) {
        expr_entry.set_text(Glib::ustring());
        if (!last_result_was_value)
            result_label.set_text(Glib::ustring()); // clear error message
    }
}

void main_window::options() {
    result_label.set_text("Options is not implemented yet.");
    last_result_was_value = false;
}

void main_window::show_variables() {
    result_label.set_text("Show variables is not implemented yet.");
    last_result_was_value = false;
}

void main_window::help() {
    app.help();
}
