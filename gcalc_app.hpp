#ifndef APP_H
#define APP_H

#include <gtkmm/application.h>
#include <gtkmm/window.h>

class main_window;
class help_window;

class gcalc_app: public Gtk::Application {
public:
    static Glib::RefPtr<gcalc_app> create();
    ~gcalc_app();
    void help();

private:
    main_window* main_win = 0;
    help_window* help_win = 0;

    gcalc_app();
    void on_activate();
    void on_window_hide(Gtk::Window* win);
};

#endif // APP_H