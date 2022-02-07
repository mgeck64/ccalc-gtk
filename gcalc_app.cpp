#include "gcalc_app.hpp"
#include <glibmm/miscutils.h>

#include "main_window.hpp"
#include "help_window.hpp"
#include "options_window.hpp"
#include "variables_window.hpp"

gcalc_app::gcalc_app() : Gtk::Application("ccalc-gtk.mgeck64.com.github") {
    Glib::set_application_name("gcalc");
}

auto gcalc_app::create() -> Glib::RefPtr<gcalc_app> {
    return Glib::make_refptr_for_instance<gcalc_app>(new gcalc_app());
}

auto gcalc_app::on_activate() -> void {
    main_win_ = std::make_unique<main_window>(*this);
    add_window(*main_win_);

    main_win_->signal_unmap().connect(sigc::bind(sigc::mem_fun(*this, &gcalc_app::on_window_unmask), main_win_.get()));
    main_win_->show();
}

auto gcalc_app::on_window_unmask(Gtk::Window* win) -> void {
    assert(win);
    if (win == main_win_.get()) {
        if (options_win_)
            options_win_->hide();
        remove_window(*win);
        main_win_.release();
        main_win_invoked_help = false;
    } else if (win == help_win_.get()) {
        remove_window(*win);
        help_win_.release();
        main_win_invoked_help = false;
        option_win_invoked_help = false;
    } else if (win == options_win_.get()) {
        remove_window(*win);
        options_win_.release();
        if (help_win_ && option_win_invoked_help && !main_win_invoked_help)
            help_win_->hide();
        option_win_invoked_help = false;
    } else if (win == variables_win_.get()) {
        remove_window(*win);
        variables_win_.release();
    }
}

auto gcalc_app::help(Gtk::Window* invoker, int topic_idx, bool force_topic) -> void {
    if (help_win_) {
        help_win_->present();
        if (force_topic)
            help_win_->show_topic(topic_idx);
    } else {
        help_win_ = std::make_unique<help_window>(topic_idx);
        add_window(*help_win_);
        help_win_->signal_unmap().connect(sigc::bind(sigc::mem_fun(*this, &gcalc_app::on_window_unmask), help_win_.get()));
        help_win_->show();
    }
    if (invoker == main_win_.get())
        main_win_invoked_help = true;
    else if (invoker == options_win_.get())
        option_win_invoked_help = true;
}

auto gcalc_app::options() -> void {
    if (options_win_)
        options_win_->present();
    else {
        options_win_ = std::make_unique<options_window>(*this);
        add_window(*options_win_);
        options_win_->signal_unmap().connect(sigc::bind(sigc::mem_fun(*this, &gcalc_app::on_window_unmask), options_win_.get()));
        options_win_->show();
    }
}

auto gcalc_app::variables() -> void {
    if (variables_win_)
        variables_win_->present();
    else {
        variables_win_ = std::make_unique<variables_window>();
        add_window(*variables_win_);
        variables_win_->signal_unmap().connect(sigc::bind(sigc::mem_fun(*this, &gcalc_app::on_window_unmask), variables_win_.get()));
        variables_win_->show();
    }
}
