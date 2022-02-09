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
- Supports floating point numbers up to 50 decimal significant digits (+ guard
digits)
## Dependencies
This project depends on another of my projects, ccalc-lib; that project provides
the backend to this project's GUI frontend.
- ccalc-lib's header files are assumed to be discoverable in a "ccalc" directory
in the include search path; e.g., /usr/local/include/ccalc. I have "ccalc" there
on my system as a symbolic link to my ccalc-lib project directory.
- The lib files libccalc-rel.a (release library) and libccalc-dbg.a (debugging
library) are assumed to be discoverable in the lib path; e.g., located in
/usr/local/lib. I have libccalc-rel.a and libccalc-dbg.a there on my system as
symbolic links to the library files in my ccalc-lib project directory (built in
lib there).

This project also depends on gtkmm 4 for the GUI frontend.

This project also depends on Boost; see ccalc-lib for more information.

This project has GNU extensions to C++ enabled because ccalc-lib does so.