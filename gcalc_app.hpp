#ifndef GCALC_APP_HPP
#define GCALC_APP_HPP

#include <gtkmm/application.h>
#include <gtkmm/window.h>

class main_window;
class help_window;
class options_window;

class gcalc_app: public Gtk::Application {
public:
    static Glib::RefPtr<gcalc_app> create();
 
    void help(Gtk::Window* invoker, int topic_idx, bool force_topic);
    void options();

    main_window* main_win() {return main_win_.get();}
    help_window* help_win() {return help_win_.get();}
    options_window* options_win() {return options_win_.get();}

private:
    std::unique_ptr<main_window> main_win_;
    std::unique_ptr<help_window> help_win_;
    std::unique_ptr<options_window> options_win_;

    bool main_win_invoked_help = false;
    bool option_win_invoked_help = false;

    gcalc_app();
    void on_activate();
    void on_window_unmask(Gtk::Window* win);
};

#endif // GCALC_APP_HPP