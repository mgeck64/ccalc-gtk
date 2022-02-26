# gcalc
## Synopsis
An advanced text-based GUI calculator app. Unlike a typical calculatior apps
that mimics a physical calculator, this app presents a minimalist user
interface with a modest screen footprint.
- Supports complex arithmetic, integer arithmetic and bitwise operations
- Supports implied multiplication (multiplication by justaposition)
- Supports 8, 16, 32, 64 and 128 bit integer types
- Supports binary, octal, decimal and hexadecimal numbers, both integer and
floating point (and complex)
- Supports floating point numbers with 100 decimal significant digits (+ guard
digits)
## Development Notes
I have, for the time being, stopped development of this project, which was
developed for Gtk 4 (gtkmm-4); it is having a number of issues related to Gtk 4:
- Warnings about missed dependencies when loading
- Initial window size is sometimes wrong
- Gtk 4, which is still new, is not available in Ubuntu (21.10)

Moreover, Gtk 3 (and gtkmm-3) is "built into" Manjaro (21.2) and Ubuntu
(21.10), which is not the case for Gtk 4, and thus no other libraries are
required to run the app in those distros. Thus, I ported this to work with the
more stable and convenient to use Gtk 3; that project, ccalc-gtk3, is having
none of these issues, and thus this project is frozen and new development is
happening in ccalc-gtk3. (Written on 2/25/22.)
## Dependencies
This project depends on another of my projects, ccalc-lib; that project provides
the backend to this project's GUI frontend.
- ccalc-lib's header files are assumed to be discoverable in a "ccalc" directory
in the include search path; e.g., /usr/local/include/ccalc.
- The lib files libccalc-rel.a (release library) and libccalc-dbg.a (debugging
library) are assumed to be discoverable in the lib path; e.g., located in
/usr/local/lib.

This project also depends on gtkmm-4.0 for the GUI frontend.

This project also depends on Boost because ccalc-lib does so; see ccalc-lib for
details.

This project has GNU extensions to C++ enabled because ccalc-lib does so.
## Build Quick Help
- 'make' and 'make release' builds the release executable 'gcalc' in a 'release'
directory under the current working directory
- 'make debug' builds the debug executable 'gcalc' in a 'debug' directory under
the current working directory
- 'sudo make install' builds the release executable as described above, unless
already so, and:
    - installs the executable to /usr/bin
    - installs the .desktop file to /usr/share/applications
- 'make clean' deletes the release and debug directories under the current
working directory
- 'sudo make uninstall':
    - deletes the executable from /usr/bin
    - deletes the .desktop file from /usr/share/applications