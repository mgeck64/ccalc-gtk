#include "gcalc_app.hpp"
#include <glibmm/miscutils.h>

#include "main_window.hpp"
#include "help_window.hpp"

gcalc_app::gcalc_app() : Gtk::Application("ccalc-gtk.mgeck64.com.github") {
    Glib::set_application_name("gcalc");
}

Glib::RefPtr<gcalc_app> gcalc_app::create() {
    return Glib::make_refptr_for_instance<gcalc_app>(new gcalc_app());
}

void gcalc_app::on_activate() {
    main_win = new main_window(*this);
    add_window(*main_win);

    main_win->signal_unrealize().connect(sigc::bind(sigc::mem_fun(*this, &gcalc_app::on_window_hide), main_win));
    main_win->show();
}

void gcalc_app::on_window_hide(Gtk::Window* win) {
    assert(win);
    remove_window(*win);
    if (win == main_win)
        main_win = 0;
    else if (win == help_win)
        help_win = 0;
    delete win;
}

void gcalc_app::help() {
    if (help_win)
        help_win->present();
    else {
        help_win = new help_window;
        add_window(*help_win);
        help_win->signal_unrealize().connect(sigc::bind(sigc::mem_fun(*this, &gcalc_app::on_window_hide), help_win));
        help_win->show();
    }
}

gcalc_app::~gcalc_app() {
    delete main_win;
    delete help_win;
}
