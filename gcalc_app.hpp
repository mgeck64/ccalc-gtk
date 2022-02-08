#ifndef GCALC_APP_HPP
#define GCALC_APP_HPP

#include <gtkmm/application.h>
#include <gtkmm/window.h>

class main_window;
class help_window;

class gcalc_app: public Gtk::Application {
public:
    static auto create() -> Glib::RefPtr<gcalc_app>;
 
    auto help(Gtk::Window* invoker, int topic_idx, bool force_topic) -> void;
    auto help_invoker() const -> Gtk::Window* {return help_invoker_;}
    auto close_help() -> void;

private:
    std::unique_ptr<main_window> main_win;
    std::unique_ptr<help_window> help_win;

    Gtk::Window* help_invoker_ = 0;

    gcalc_app();
    auto on_activate() -> void;
    auto on_close_request(Gtk::Window* win) -> bool;
};

#endif // GCALC_APP_HPP