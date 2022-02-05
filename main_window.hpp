#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

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

#include <vector>

class main_window : public Gtk::Window {
public:
    main_window(gcalc_app& app);

    std::tuple<parser_options, output_options> options() const
    {return std::make_tuple(parser.options(), out_options);}

    void options(const parser_options& parse_options, const output_options& out_options_)
    {parser.options(parse_options); out_options = out_options_;}

private:
    gcalc_app& app;
    Gtk::Box win_vbox;
    Gtk::Box content_vbox;
    Gtk::Box expr_hbox;
    Gtk::Box in_out_info_hbox;
    Gtk::Box menus_hbox;
    Gtk::Entry expr_entry;
    Gtk::Button expr_do;
    Gtk::Label result_label;
    Gtk::Label in_info_label;
    Gtk::Label out_info_label;
    Gtk::MenuButton functions_a_do;
    Gtk::MenuButton functions_b_do;
    Glib::RefPtr<Gio::ActionGroup> functions_action_group;
    Glib::RefPtr<Gio::Menu> functions_a_menu;
    Glib::RefPtr<Gio::Menu> functions_b_menu;
    Glib::RefPtr<Gio::ActionGroup> more_action_group;
    Gtk::MenuButton more_do;
    Glib::RefPtr<Gio::Menu> more_menu;

    void show_in_out_info();
    void append_history(const Glib::ustring& expr_str);
    void recall_history(bool direction_up);
    bool on_expr_entry_key_pressed(guint keyval, guint, Gdk::ModifierType);
    void on_expr_do_clicked();
    void on_function_action(const char* label);
    void on_options_do_clicked();
    void on_variables_do_clicked();
    void on_help_do_clicked();

    calc_args args;
    output_options out_options;
    calc_parser parser;
    bool last_result_parse_error = false;
    void evaluate();

    using history_list = std::vector<Glib::ustring>;
    history_list history;
    history_list::size_type history_idx = 0;
    static constexpr history_list::size_type max_history_size = 32;
};

#endif // MAIN_WINDOW_HPP