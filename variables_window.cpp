#include "variables_window.hpp"
#include "gcalc_basics.hpp"

#include <gtkmm/scrollbar.h>

#include "ccalc/calc_outputter.hpp"

variables_window::variables_window() {
    set_title("Variables");
    set_default_size(250, 250);

    set_child(variables_scroller);
    variables_scroller.set_margin(default_margin * 2);
    variables_scroller.set_child(variables_lbl);

    variables_scroller.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
    // let window expand horizontially for wide content

    variables_lbl.set_halign(Gtk::Align::START);
    variables_lbl.set_valign(Gtk::Align::START);
    variables_lbl.set_expand(true);
    variables_lbl.set_wrap(true);
}

void variables_window::set(calc_parser::variables_itr begin, calc_parser::variables_itr end, const output_options& out_options) {
    variables_lbl.set_selectable(true); // this should be done in ctor but when
    // done there the cursor inexplicibly shows; doing this here won't cause the
    // cursor to show. see also main_window::on_variables_btn_clicked

    if (begin == end) {
        variables_lbl.set_label("No variables are defined.");
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
    variables_lbl.set_label(buf.str());
}
