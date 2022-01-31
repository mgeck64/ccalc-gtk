#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "gcalc_app.hpp"

#include "ccalc/calc_parser.hpp"

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/popover.h>
#include <gtkmm/listbox.h>
#include <gtkmm/actionbar.h>

struct gio_menu : public Gio::Menu {
    gio_menu() {} // make protected ctor public
};

class main_window : public Gtk::Window {
public:
    main_window(gcalc_app& app);

private:
    gcalc_app& app;
    Gtk::Box vbox;
    Gtk::Box expr_hbox;
    Gtk::Box menus_hbox;
    Gtk::Entry expr_entry;
    Gtk::Button expr_do;
    Gtk::Label result_label;
    Gtk::MenuButton functions_a_do;
    Gtk::MenuButton functions_b_do;
    Glib::RefPtr<Gio::ActionGroup> functions_action_group;
    Glib::RefPtr<Gio::Menu> functions_a_menu;
    Glib::RefPtr<Gio::Menu> functions_b_menu;
    Glib::RefPtr<Gio::ActionGroup> more_action_group;
    Gtk::MenuButton more_do;
    Glib::RefPtr<Gio::Menu> more_menu;

    bool on_expr_entry_key_pressed(guint keyval, guint, Gdk::ModifierType);
    void on_expr_do_clicked();
    void on_function_action(const char* label);
    void on_options_do_clicked();
    void on_variables_do_clicked();
    void on_help_do_clicked();

    calc_args args;
    output_options out_options;
    calc_parser parser;
    bool last_result_was_value = false;
    void evaluate();

    void options();
    void show_variables();
    void help();
};

#endif // MAIN_WINDOW_H