#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>

#include "ccalc/calc_parser.hpp"

class main_window : public Gtk::Window {
public:
    main_window();

private:
    Gtk::Box vbox;
    Gtk::Box expr_hbox;
    Gtk::Entry expr_entry;
    Gtk::Button expr_do;
    Gtk::Label result_label;
    bool on_entry_key_pressed(guint keyval, guint, Gdk::ModifierType);
    void on_expr_do_clicked();

    calc_args args;
    calc_parser parser;
    bool last_result_was_error = false;
    void evaluate();

    void help();
};

#endif // MAIN_WINDOW_H