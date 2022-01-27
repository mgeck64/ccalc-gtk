#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>

#include "ccalc/calc_parser.hpp"

class main_window : public Gtk::Window {
public:
    main_window(const Glib::RefPtr<Gtk::Application>& app);
    ~main_window();

private:
    Gtk::Box vbox;
    Gtk::Box expr_hbox;
    Gtk::Box functions_hbox;
    Gtk::Box bottom_hbox;
    Gtk::Entry expr_entry;
    Gtk::Button expr_do;
    Gtk::Label result_label;
    Gtk::ComboBoxText functions;
    Gtk::Button options_do;
    Gtk::Button help_do;
    bool on_expr_entry_key_pressed(guint keyval, guint, Gdk::ModifierType);
    void on_result_label_pressed(int n_press, double x, double y);
    void on_expr_do_clicked();
    void on_functions_changed();
    void on_options_do_clicked();
    void on_help_do_clicked();

    calc_args args;
    calc_parser parser;
    bool last_result_was_value = false;
    void evaluate();

    void options();
    void help();
};

#endif // MAIN_WINDOW_H