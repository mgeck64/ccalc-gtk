#ifndef HELP_WINDOW_HPP
#define HELP_WINDOW_HPP

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/button.h>
#include <gtkmm/scrolledwindow.h>

class help_window : public Gtk::Window {
public:
    enum topic_idxs {quick_start_idx, representation_types_and_numeric_bases_idx,
        input_output_information_area_idx, scientific_notation_idx, prefixes_idx,
        implied_multiplication_idx, functions_idx, bitwise_operators_idx,
        variables_idx, options_idx, num_topics};

    help_window(int topic_idx);
    auto show_topic(int topic_idx) -> void;

private:
    Gtk::Box vbox;
    Gtk::Label title;
    Gtk::Box top_hbox;
    Gtk::ComboBoxText topics;
    Gtk::Button prev_topic;
    Gtk::Button next_topic;
    Gtk::ScrolledWindow help_frame;
    Gtk::Label help_text;

    int last_topic_idx = -1;

    auto on_topics_changed() -> void;
    auto on_prev_topic_clicked() -> void;
    auto on_next_topic_clicked() -> void;
};

#endif // HELP_WINDOW_HPP