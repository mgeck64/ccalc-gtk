#ifndef GCALC_APP_HPP
#define GCALC_APP_HPP

#include <gtkmm/application.h>
#include <gtkmm/window.h>

class main_window;
class help_window;
class options_window;

class gcalc_app: public Gtk::Application {
public:
    static auto create() -> Glib::RefPtr<gcalc_app>;
 
    auto help(Gtk::Window* invoker, int topic_idx, bool force_topic) -> void;
    auto options() -> void;

    auto main_win() -> main_window* {return main_win_.get();}
    auto help_win() -> help_window* {return help_win_.get();}
    auto options_win() -> options_window* {return options_win_.get();}

private:
    std::unique_ptr<main_window> main_win_;
    std::unique_ptr<help_window> help_win_;
    std::unique_ptr<options_window> options_win_;

    bool main_win_invoked_help = false;
    bool option_win_invoked_help = false;

    gcalc_app();
    auto on_activate() -> void;
    auto on_window_unmask(Gtk::Window* win) -> void;
};

#endif // GCALC_APP_HPP