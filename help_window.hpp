#ifndef HELP_WINDOW_HPP
#define HELP_WINDOW_HPP

#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/label.h>

class help_window : public Gtk::Window {
public:
    help_window();
    ~help_window();

private:
    Gtk::ScrolledWindow frame;
    Gtk::Label text;
};

#endif // HELP_WINDOW_HPP