#include "gcalc_app.hpp"
#include <glibmm/miscutils.h>

#include "main_window.hpp"
#include "help_window.hpp"
#include "variables_window.hpp"
#include "options_window.hpp"

gcalc_app::gcalc_app() : Gtk::Application("ccalc-gtk.mgeck64.com.github") {
    Glib::set_application_name("gcalc");
}

auto gcalc_app::create() -> Glib::RefPtr<gcalc_app> {
    return Glib::make_refptr_for_instance<gcalc_app>(new gcalc_app());
}

auto gcalc_app::on_activate() -> void {
    main_win = std::make_unique<main_window>(*this);
    add_window(*main_win);

    main_win->signal_close_request().connect(sigc::bind(sigc::mem_fun(*this, &gcalc_app::on_close_request), main_win.get()), false);
    main_win->show();
}

auto gcalc_app::on_close_request(Gtk::Window* win) -> bool {
    assert(win);
    if (win == main_win.get()) {
        remove_window(*win);
        if (win == help_invoker_)
            help_invoker_ = 0;
        main_win.reset();
        return true;
    }
    if (win == help_win.get()) {
        remove_window(*win);
        help_win.reset();
        help_invoker_ = 0;
        return true;
    }
    return false;
}

auto gcalc_app::help(Gtk::Window* invoker, int topic_idx, bool force_topic) -> void {
    if (help_win) {
        help_win->present();
        if (force_topic)
            help_win->show_topic(topic_idx);
    } else {
        help_win = std::make_unique<help_window>(topic_idx);
        add_window(*help_win);
        help_win->signal_close_request().connect(sigc::bind(sigc::mem_fun(*this, &gcalc_app::on_close_request), help_win.get()), false);
        help_win->show();
    }
    if (!help_invoker_ || help_invoker_ != main_win.get())
        help_invoker_ = invoker;
}

auto gcalc_app::close_help() -> void {
    if (help_win)
        help_win->close();
}
