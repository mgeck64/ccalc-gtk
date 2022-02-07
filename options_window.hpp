#ifndef OPTIONS_WINDOW_HPP
#define OPTIONS_WINDOW_HPP

#include "main_window.hpp"

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/label.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/entry.h>

class options_window : public Gtk::Window {
public:
    options_window(gcalc_app& app);
    auto update_from(const calc_args& options, bool force = false) -> void;

private:
    gcalc_app& app;
    Gtk::Box win_vbox;
    Gtk::Box content_vbox;
    Gtk::Label title;
    Gtk::Box options_hbox;
    Gtk::ComboBoxText options;
    Gtk::Button prev_option;
    Gtk::Button next_option;
    Gtk::ScrolledWindow option_scroller;
    Gtk::Box option_vbox;
    Gtk::Box buttons_hbox;
    Gtk::Button help;
    Gtk::Button defaults;
    Gtk::Button accept;
    Gtk::Button cancel;

    Gtk::CheckButton option_0bi;
    Gtk::CheckButton option_0oi;
    Gtk::CheckButton option_0di;
    Gtk::CheckButton option_0xi;
    Gtk::CheckButton option_0bu;
    Gtk::CheckButton option_0ou;
    Gtk::CheckButton option_0du;
    Gtk::CheckButton option_0xu;
    Gtk::CheckButton option_0bn;
    Gtk::CheckButton option_0on;
    Gtk::CheckButton option_0dn;
    Gtk::CheckButton option_0xn;

    Gtk::CheckButton option_ob;
    Gtk::CheckButton option_oo;
    Gtk::CheckButton option_od;
    Gtk::CheckButton option_ox;

    Gtk::CheckButton option_pn;
    Gtk::CheckButton option_pu;

    Gtk::Box precision_hbox;
    Gtk::Label option_pr;
    Gtk::Entry option_pr_entry;

    Gtk::CheckButton option_w8;
    Gtk::CheckButton option_w16;
    Gtk::CheckButton option_w32;
    Gtk::CheckButton option_w64;
    Gtk::CheckButton option_w128;

    enum option_idxs {none_idx = -1, input_default_idx = 0, output_base_idx,
         p_notation_idx, precision_idx, integer_word_size_idx, num_options};

    int last_option_idx = none_idx;

    auto show_option(int idx) -> void;

    auto on_options_changed() -> void;
    auto on_prev_option_clicked() -> void;
    auto on_next_option_clicked() -> void;
    auto on_help_clicked() -> void;
    auto on_cancel_clicked() -> void;
    auto on_defaults_clicked() -> void;
    auto on_accept_clicked() -> void;

    Gtk::MessageDialog error_msg;
};

#endif // OPTIONS_WINDOW_HPP