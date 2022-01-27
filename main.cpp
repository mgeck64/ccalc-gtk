#include "main_window.hpp"
#include <gtkmm/application.h>

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("ccalc-gtk.mgeck64.com.github");
    return app->make_window_and_run<main_window>(argc, argv, app);
}