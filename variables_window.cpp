#include "variables_window.hpp"
#include "gcalc_basics.hpp"

#include "ccalc/calc_outputter.hpp"

variables_window::variables_window() :
    content_vbox(Gtk::Orientation::VERTICAL)
{
    set_default_size(450, 400);
    set_child(content_vbox);
    content_vbox.set_margin(default_margin);

    content_vbox.append(title);
    title.set_margin(default_margin);
    title.set_markup("<big><b>Variables</b></big>");
    title.set_halign(Gtk::Align::START);

    content_vbox.append(variables_scroller);
    variables_scroller.set_margin(default_margin);
    variables_scroller.set_child(variables);

    variables.set_expand(true);
    variables.set_halign(Gtk::Align::START);
    variables.set_valign(Gtk::Align::START);
    variables.set_wrap(true);
}

void variables_window::set(calc_parser::variables_itr begin, calc_parser::variables_itr end, const output_options& out_options) {
    variables.set_selectable(true); // this should be done in ctor but when it
    // is done there the cursor inexplicibly shows; doing this here won't cause
    // cursor to show. sigh!

    if (begin == end) {
        variables.set_label("There are no variables defined.");
        return;
    }

    std::stringstream buf;
    for (auto itr = begin; itr != end;) {
        buf << itr->first;
        buf << " = ";
        buf << calc_outputter(out_options)(itr->second);
        if (++itr != end)
            buf << "\n";
    }
    variables.set_label(buf.str());
}
