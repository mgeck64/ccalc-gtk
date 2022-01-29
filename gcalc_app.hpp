#ifndef APP_H
#define APP_H

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "help_window.hpp"

class gcalc_app: public Gtk::Application {
public:
    static Glib::RefPtr<gcalc_app> create();
    ~gcalc_app();
    void help();

private:
    help_window* help_win = 0;

    gcalc_app();
    void on_activate();
    void on_window_hide(Gtk::Window* win);
};

#endif // APP_H