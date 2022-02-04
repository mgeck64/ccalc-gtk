#include "help_window.hpp"
#include "gcalc_basics.hpp"
#include <cassert>

namespace {
extern const char quick_start[];
extern const char representation_types_and_numeric_bases[];
extern const char input_output_information_area[];
extern const char scientific_notation[];
extern const char prefixes[];
extern const char implied_multiplication[];
extern const char functions[];
extern const char bitwise_operators[];
extern const char variables[];
extern const char options[];
}

help_window::help_window(int topic_idx) :
    vbox(Gtk::Orientation::VERTICAL),
    top_hbox(Gtk::Orientation::HORIZONTAL),
    prev_topic("\u25b2"),
    next_topic("\u25bc")
{
    set_default_size(550, 500);

    vbox.set_margin(default_margin);
    set_child(vbox);

    title.set_margin(default_margin);
    title.set_halign(Gtk::Align::START);
    title.set_markup("<big><b>Basic guide</b></big>");
    vbox.append(title);

    vbox.append(top_hbox);

    topics.set_margin(default_margin);
    topics.set_hexpand(true);
    topics.append("Quick Start");
    topics.append("Representation Types and Numeric Bases");
    topics.append("Input/Output Information Area");
    topics.append("Scientific Notation");
    topics.append("Prefixes");
    topics.append("Implied Multiplication");
    topics.append("Functions");
    topics.append("Bitwise Operators");
    topics.append("Variables");
    topics.append("Options");
    topics.signal_changed().connect(sigc::mem_fun(*this, &help_window::on_topics_changed));
    top_hbox.append(topics);

    prev_topic.set_margin(default_margin);
    prev_topic.set_margin_end(0);
    prev_topic.signal_clicked().connect(sigc::mem_fun(*this, &help_window::on_prev_topic_clicked));
    top_hbox.append(prev_topic);

    next_topic.set_margin(default_margin);
    next_topic.set_margin_start(0);
    next_topic.signal_clicked().connect(sigc::mem_fun(*this, &help_window::on_next_topic_clicked));
    top_hbox.append(next_topic);

    help_frame.set_child(help_text);
    help_frame.set_margin(default_margin);
    vbox.append(help_frame);

    help_text.set_expand(true);
    help_text.set_valign(Gtk::Align::START);
    help_text.set_halign(Gtk::Align::START);
    help_text.set_selectable(true);
    help_text.set_wrap(true);

    show_topic(topic_idx);
}

void help_window::on_topics_changed() {
    auto idx = topics.get_active_row_number();
    show_topic(idx);
}

void help_window::on_prev_topic_clicked() {
    auto idx = topics.get_active_row_number();
    if (idx > 0)
        show_topic(idx - 1);
    else if (auto p = get_display())
        gdk_display_beep(p->gobj());
}

void help_window::on_next_topic_clicked() {
    auto idx = topics.get_active_row_number();
    if (idx < num_topics - 1)
        show_topic(idx + 1);
    else if (auto p = get_display())
        gdk_display_beep(p->gobj());
}

void help_window::show_topic(int topic_idx) {
    if (topic_idx == last_topic_idx)
        return;
    const char* topic = 0;
    switch (topic_idx) {
        case quick_start_idx:
            topic = quick_start; break;
        case representation_types_and_numeric_bases_idx:
            topic = representation_types_and_numeric_bases; break;
        case input_output_information_area_idx:
            topic = input_output_information_area; break;
        case scientific_notation_idx:
            topic = scientific_notation; break;
        case prefixes_idx:
            topic = prefixes; break;
        case implied_multiplication_idx:
            topic = implied_multiplication; break;
        case functions_idx:
            topic = functions; break;
        case bitwise_operators_idx:
            topic = bitwise_operators; break;
        case variables_idx:
            topic = variables; break;
        case options_idx:
            topic = options; break;
    }
    assert(topic); // topic_idx was invalid if this fails
    if (topic) {
        topics.set_active(topic_idx);
        help_text.set_markup(topic);
        last_topic_idx = topic_idx;
    }
}

namespace {
const char quick_start[] = "\
Type in a mathematical expression in text form; e.g., 2+4*8, which means multiply \
4 by 8 and add 2 to the result; press Enter or click the = button to perform the \
calculation. You can also type in \"help\" instead to show this help. \n\
\n\
<b>Basic arithmetic operators:</b>\n\
\n\
+ Addition and unary plus\n\
- Subtraction and negation\n\
* Multiplication\n\
/ Division\n\
% Modulus (remainder)\n\
^ or ** Exponentiation (right associative)\n\
! Factorial\n\
!! Double factorial\n\
\n\
Operators have the usual mathematical precedence order and associativity; use \
parentheses to change that; e.g., (2+4)*8 means add 2 to 4 and multiply the \
result by 8.\n\
\n\
<b>Available symbolic values:</b>\n\
\n\
pi - Did you know that March 14 is Pi day?\n\
e - Euler's number\n\
i - Imaginary unit\n\
last - The last result\n\
\n\
Example: e^(i*pi)+1";

const char representation_types_and_numeric_bases[] = "\
This calculator can process numbers of complex type, signed integer type and \
unsigned integer type (these are the supported representation types). By \
default, it processes numbers of complex type, but this can be changed via the \
<b>input defaults</b> options.\n\
\n\
Complex type: Represents a complex number composed of a real and imaginary part, \
both of which are high precision floating point types (50 significant decimal \
digits). A full complex number can be specified in the common form a+bi. \
(A complex type number can also be an ordinary real number, of course.)\n\
\n\
Examples: 10+2i (real part is 10, imaginary part is 2i), 10 (real number; \
imaginary part is 0), 2i (imaginary number; real part is 0).\n\
\n\
This calculator can input and output numbers in binary, octal, decimal, or \
hexadecimal numeric base. By default, it inputs and outputs numbers in decimal \
numeric base, but this can be changed via the <b>input defaults</b> and \
<b>output base</b> options.";

const char input_output_information_area[] = "\
The input/output information area near the bottom of the main window displays \
the current default representation type and numeric base for numbers that are \
being input, and the output numeric base for the results of calculations. These \
properties can be changed via the <b>input defaults</b> and <b>output base</b> \
options.\n\
\n\
The following codes are used to report this information:\n\
\n\
cplx - Complex type\n\
int - Signed integer type\n\
uint - Unsigned integer type\n\
binary - Binary numeric base\n\
octal - Octal numeric base\n\
decimal - Decimal numeric base\n\
hex - Hexadecimal numeric base";

const char scientific_notation[] = "\
Decimal numbers may be specified in scientific E notation; e.g., the decimal \
number 1e10 (or 1e+10) is equivalent to 10000000000.\n\
\n\
Binary, octal and hexadecimal numbers may be specified in scientific \"P\" \
notation. In P notation, p/P is used instead of e/E to delimit the exponent, \
which is a power of 2 (not 10) expressed in decimal; e.g., 1.1001p4 (binary) \
and 1.9p4 (hexadecimal) are the same number: 11001 (binary).\n\
\n\
Numbers expressed in P notation may be \"normalized\" or \"unnormalized.\" A \
number is normalized if it's integer part is the leading 1 bit of it's equivalent \
binary representation (except if the number is 0); this form is supported in computer \
languages such as C and C++ for hexadecimal floating point numbers. Note that \
this form of normalization is different than for standard scientific notation.\n\
\n\
Example: 1.ap10 is a number in normalized hexadecimal scientific P notation \
equal to 6.8p8 in unnormalized hexadecimal scientific P notation and 680 in \
plain hexadecimal.";

const char prefixes[] = "\
A number may optionally be given a prefix to specify its numeric base and \
representation type, overriding the default ones:\n\
\n\
0b or 0bi - Signed integer type, binary base; e.g.: 0b1010, 0bi1010\n\
0o or 0oi - Signed integer type, octal base; e.g.: 0o12, 0oi12\n\
0d or 0di - Signed integer type, decimal base; e.g.: 0d10, 0di10\n\
0x or 0xi - Signed integer type, hexadecimal base; e.g.: 0xa, 0xia\n\
0bu - Unsigned integer type, binary base; e.g.: 0bu1010\n\
0ou - Unsigned integer type, octal base; e.g.: 0ou12\n\
0du - Unsigned integer type, decimal base; e.g.: 0du10\n\
0xu - Unsigned integer type, hexadecimal base; e.g.: 0xua\n\
0bn - Complex type, binary base; e.g.: 0bn1010\n\
0on - Complex type, octal base; e.g.: 0on12\n\
0dn - Complex type, decimal base; e.g.: 0dn10\n\
0xn - Complex type, hexadecimal base; e.g.: 0xna\n\
\n\
Exception: If a number has a decimal point or exponent then it will be \
represented as complex type regardless of what the prefix specifies; e.g., 0xa.1 \
and 0xa1p-4 will both be represented as complex type.\n\
\n\
Examples: The following are different ways of expressing the number 314: \
0b100111010 (binary signed integer type), 0ou472 (octal unsigned integer type), \
0d314 or 0di314 (decimal signed integer type), 0x13a or 0xi13a (hexadecimal \
signed integer type), 0b1.0011101p+8 (normalized binary complex type), 0o472.0 \
(octal complex type), 0o1.164p+8 (normalized octal complex type), 0d3.14e+2 \
(decimal complex type), 0x13a.0 (hexadecimal complex type), 0x1.3ap+8 \
(normalized hexadecimal complex type).";

const char implied_multiplication[] = "\
Implied multiplication (multiplication by juxtaposition) is supported and has \
the same precedence as explicit mulitiplication; e.g., 6(2pi)sin(3) is valid and \
is equivalent to 6*(2*pi)*sin(3); but there are some cavaets:\n\
\n\
- Variables (described later) and symbolic values may contain multiple characters; \
e.g., 2pi means multiply 2 by pi, not multiply 2 by p and then by i.\n\
\n\
- Scientific notation has precedence; e.g., 1e10 means 10000000000, not 1*e10.\n\
\n\
- Prefix has precedence; e.g., 0d10 means signed integer decimal base 10, not 0*d10.";

const char functions[] = "\
exp - e raised to the power of the argument\n\
ln - Natural (base e) log\n\
log10 - Base 10 log\n\
log2 - Base 2 log\n\
sqrt - Square root\n\
cbrt - Cubic root\n\
sin - Sine\n\
cos - Cosine\n\
tan - Tangent\n\
asin - Arc sin\n\
acos - Arc cos\n\
atan - Arc tan\n\
sinh - Hyperbolic sin\n\
cosh - Hyperbolic cos\n\
tanh - Hyperbolic tan\n\
asinh - Inverse hyperbolic sin\n\
acosh - Inverse hyperbolic cos\n\
atanh - Inverse hyperbolic tan\n\
gamma - Gamma function\n\
lgamma - Log gamma function\n\
arg - Phase angle\n\
norm - Squared magnitude\n\
conj - Conjugate\n\
proj - Projection onto the Riemann sphere\n\
\n\
Function arguments are enclosed in parentheses. Example: sin(pi)";

const char bitwise_operators[] = "\
Bitwise operators operate on integer type numbers. When applied to complex type \
numbers, the calculator will attempt to convert them into integer type numbers.\n\
\n\
The bitwise operators are:\n\
\n\
~ Not\n\
&amp; And\n\
| Or\n\
^| Xor\n\
&lt;&lt; Shift left\n\
&gt;&gt; Shift right; algebraic for signed integer type\n\
\n\
Note: Unlike C, C++ and many other programming languages, ^ means exponentiation \
here, not bitwise xor; use ^| instead for bitwise xor.";

const char variables[] = "\
Variables can be created and used in expressions; e.g.:\n\
\n\
approx_pi=22/7\n\
r=5\n\
approx_pi*r^2\n\
\n\
Variable names must start with a letter or underscore, which can be followed by \
any number of letters, digits and underscores; e.g., plan_9. Variable names are \
case sensitive; e.g., x and X are different variables.\n\
\n\
Variable assignments can be chained; e.g., x=y=2 assigns 2 to both x and y.\n\
\n\
A variable can be deleted with the delete command; e.g., delete x.";

const char options[] = "\
Options may be specified via the Options window or by typing in their codes; \
e.g., @0b is the code for the <b>input defaults</b> signed integer type, binary \
base option.\n\
\n\
<b>Input defaults:</b>\n\
\n\
Specifies the default representation type and numeric base for numbers that are \
being input:\n\
\n\
@0b or @0bi - Signed integer type, binary base; e.g.: 1010\n\
@0o or @0oi - Signed integer type, octal base; e.g.: 12\n\
@0d or @0di - Signed integer type, decimal base; e.g.: 10\n\
@0x or @0xi - Signed integer type, hexadecimal base; e.g.: 0a (prepend a number \
with 0 if it begins with a letter digit)\n\
@0bu - Unsigned integer type, binary base\n\
@0ou - Unsigned integer type, octal base\n\
@0du - Unsigned integer type, decimal base\n\
@0xu - Unsigned integer type, hexadecimal base\n\
@0bn - Complex type, binary base; e.g., 1010, 1010+10i\n\
@0on - Complex type, octal base; e.g., 12, 12+2i\n\
@0dn - Complex type, decimal base; e.g., 10, 10+2i -- the default default\n\
@0xn - Complex type, hexadecimal base; e.g., 0a, 0a+2i\n\
\n\
Note: If a number is specified with a decimal point or exponent then it will be \
represented as complex type regardless of what <b>input defaults</b> specifies; e.g., \
even if @0xi or @0xu is given, the number 0a.1 will be represented as complex type.\n\
\n\
Note 2: The 0b and 0d prefixes are not recognized when the default numeric base is \
hexadecimal because they are valid hexadecimal numbers. (In that case, 0bi and \
0di can be used instead.)\n\
\n\
<b>Output base:</b>\n\
\n\
Specifies the output numeric base for the results of calculations:\n\
\n\
@ob - Binary\n\
@oo - Octal\n\
@od - Decimal -- the default\n\
@ox - Hexadecimal\n\
\n\
<b>Mode:</b>\n\
\n\
Combines <b>input defaults</b> and <b>output base</b>: @mb (@0b @ob), @mo (@0o @oo), @md \
(@0d @od), @mx (@0x @ox), @mbi (@0bi @ob), @moi (@0oi @oo), @mdi (@0di @od), @mxi \
(@0xi @ox), @mbu (@0bu @ob), @mou (@0ou @oo), @mdu (@0du @od), @mxu (@0xu @ox), \
@mbn (@0bn @ob), @mon (@0on @oo), @mdn (@0dn @od), @mxn (@0xn @ox).\n\
\n\
Mode is not supported in the Options window.\n\
\n\
<b>P notation:</b>\n\
\n\
@pn specifies that binary, octal and hexadecimal floating point type numbers \
be output in normalized scientific P notation.\n\
\n\
@pu specifies that very large and very small binary, octal and hexadecimal \
floating point type numbers be output in unnormalized scientific P notation. -- \
the default\n\
\n\
<b>Precision:</b>\n\
\n\
@pr<i>n</i> specifies the maximum precision (number of significant digits) in \
which a number is output, given as <i>n</i>. Affects floating point type \
(complex type) numbers only. E.g., @pr15. The default value is 50. The value 0 \
is special and means full precision including guard digits.\n\
\n\
<b>Integer word size:</b>\n\
\n\
Specifies the word size for integer types:\n\
\n\
@w8   -   8 bits\n\
@w16  -  16 bits\n\
@w32  -  32 bits\n\
@w64  -  64 bits\n\
@w128 - 128 bits -- the default\n\
\n\
Note: This does not affect complex type numbers.";
} // anonymous namespace