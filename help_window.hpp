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
    help_window();

private:
    Gtk::Box vbox;
    Gtk::Label title;
    Gtk::Box top_hbox;
    Gtk::ComboBoxText topics;
    Gtk::Button prev_topic;
    Gtk::Button next_topic;
    Gtk::ScrolledWindow help_frame;
    Gtk::Label help_text;

    void on_topics_changed();
    void on_prev_topic_clicked();
    void on_next_topic_clicked();

    void show_topic(int idx);
};

#endif // HELP_WINDOW_HPP