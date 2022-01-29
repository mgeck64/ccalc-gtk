#include "help_window.hpp"
#include "gcalc_basics.hpp"

help_window::help_window() {
    set_default_size(640, 480);

    set_child(frame);
    frame.set_child(text);
    frame.set_margin(default_margin);
    frame.set_expand(true);

    text.set_margin(default_margin);
    text.set_expand(true);
    text.set_selectable(true);
    text.set_wrap(true);

    text.set_markup("\
<markup>\
<big><b>Basic guide</b></big>\n\
\n\
Enter a mathematical expression in text form, e.g.: 2+3*6, or enter \"help\" to \
show this help.\n\
\n\
<b>Basic arithmetic operators</b>\n\
\n\
<b>+</b> (addition and unary plus), <b>-</b> (subtraction and negation), <b>*</b> (multiplication), \
<b>/</b> (division), <b>%</b> (modulus), <b>^</b> or <b>**</b> (exponentiation), <b>!</b> (factorial), <b>!!</b> (double \
factorial) <b>(</b> and <b>)</b> (grouping)\n\
\n\
<b>Available symbolic values</b>\n\
\n\
pi, e (Euler's number), i (imaginary unit), last (last result); e.g., e^(i*pi)+1\n\
\n\
<b>Representation types and numeric bases</b>\n\
\n\
This calculator can process numbers of complex type, signed integer type and \
unsigned integer type. By default, it processes numbers of complex type.\n\
\n\
Complex type: Represents a complex number composed of a real and imaginary part, \
both of which are high precision floating point types (50 significant decimal \
digits). A full complex number can be given in the common form a+bi. \
(A complex type number can also be an ordinary real number, of course.)\n\
\n\
Examples: 10+2i (real part is 10, imaginary part is 2i), 10 (real number; \
imaginary part is 0), 2i (imaginary number; real part is 0).\n\
\n\
This calculator can accept and output numbers in binary, octal, decimal, or \
hexadecimal numeric base. By default, it accepts and outputs numbers in decimal \
numeric base.\n\
\n\
How to work with other representations and bases is explained later.\n\
\n\
<b>Scientific notation</b>\n\
\n\
Decimal numbers may be specified in scientific E notion; e.g., the decimal \
number 1e10 (or 1e+10) is equivalent to 10000000000.\n\
\n\
Binary, octal and hexadecimal numbers may be specified in scientific \"P\" \
notation. In P notation, 'p'/'P' is used instead of 'e'/'E' to delimit the \
exponent, which is a power of 2 (not 10) expressed in decimal.\n\
\n\
Numbers expressed in P notation may be \"normalized\" or \"unnormalized.\" A \
number is normalized if it's integer part is the leading 1 bit of it's equivalent \
binary representation (except if that number is 0); this form can be used in computer \
languages such as C and C++ for hexadecimal floating point numbers. Note that \
this notion of normalization is different than for standard scientific notation.\n\
\n\
Example: 1.ap10 is a number in normalized hexadecimal scientific P notation \
equal to 6.8p8 in unnormalized hexadecimal scientific P notation and 680 in \
plain hexadecimal.\n\
\n\
<b>Prefixes</b>\n\
\n\
A number may optionally be given a prefix to specify its numeric base and \
representation type:\n\
\n\
0b or 0bi - Signed integer type, binary base; e.g.: 0b1010, 0bi1010\n\
0o or 0oi - Signed integer type, octal base; e.g.: 0o12, 0oi12\n\
0d or 0di - Signed ingeger type, decimal base; e.g.: 0d10, 0di10\n\
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
(normalized hexadecimal complex type).\n\
\n\
<b>Implied multiplication</b>\n\
\n\
Implied multiplication (multiplication by juxtaposition) is supported and has \
the same precedence as explicit mulitiplication, e.g,, 6(2pi)sin(3) is valid and \
is equivalent to 6*(2*pi)*sin(3); but there are some cavaets:\n\
\n\
- Variables (described later) and symbolic values may contain multiple characters; \
e.g., 2pi means multiply 2 by pi, not multiply 2 by p and then by i.\n\
\n\
- Scientific notation has precedence; e.g., 1e10 means 10000000000, not 1*e10.\n\
\n\
- Prefix has precedence; e.g., 0d10 means signed integer decimal base 10, not 0*d10.\n\
\n\
<b>Functions</b>\n\
\n\
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
Function arguments are enclosed in parentheses. Example: sin(pi)\n\
\n\
<b>Bitwise operators</b>\n\
\n\
<b>~</b> (not), <b>&amp;</b> (and), <b>|</b> (or), <b>^|</b> (xor), <b>&lt;&lt;</b> and <b>&gt;&gt;</b> \
(shift; algebraic for signed type)\n\
\n\
Note: unlike C, C++ and many other programming languages, <b>^</b> means exponentiation \
here, not bitwise xor; use <b>^|</b> instead for bitwise xor.\n\
\n\
Note 2: When applied to complex type numbers, the calculator will attempt to \
convert them internally into integer type numbers if possible.\n\
\n\
<b>Variables</b>\n\
\n\
Variables can be created and used in expressions, e.g.:\n\
\n\
approx_pi=22/7\n\
r=5\n\
approx_pi*r^2\n\
\n\
Variable assignments can be chained, e.g.: x=y=2 assigns 2 to both x and y.\n\
\n\
A variable can be deleted with the delete command, e.g., delete x.\n\
\n\
<b>Options</b>\n\
\n\
Options may be specified textually or from the UI.\n\
\n\
<i>Input defaults</i>\n\
\n\
Specifies the default representation type and default numeric base for numbers:\n\
\n\
@0b or @0bi - Signed integer type, binary base; e.g.: 1010\n\
@0o or @0oi - Signed integer type, octal base; e.g.: 12\n\
@0d or @0di - Signed integer type, decimal base; e.g.: 10\n\
@0x or @0xi - Signed integer type, hexadecimal base; e.g.: 0a (prepend a number \
with 0 if it consists only of letter digits)\n\
@0bu - Unsigned integer type, binary base\n\
@0ou - Unsigned integer type, octal base\n\
@0du - Unsigned integer type, decimal base\n\
@0xu - Unsigned integer type, hexadecimal base\n\
@0bn - Complex type, binary base; e.g., 1010, 1010+10i\n\
@0on - Complex type, octal base; e.g., 12, 12+2i\n\
@0dn - Complex type, decimal base; e.g., 10, 10+2i -- the initial default\n\
@0xn - Complex type, hexadecimal base; e.g., 0a, 0a+2i\n\
\n\
Note: If a number is specified with a decimal point or exponent then it will be \
represented as complex type regardless of what <i>input defaults</i> specifies; e.g., \
even if @0xi or @0xu is given, the number 0a.1 will be represented as complex type.\n\
\n\
Note 2: The 0b and 0d prefixes are not recognized when the default numeric base is \
hexadecimal because they are valid hexadecimal numbers. (In that case, 0bi and \
0di can be used instead.)\n\
\n\
<i>Output base</i>\n\
\n\
Specifies the default numeric base of the output:\n\
\n\
@ob - Binary\n\
@oo - Octal\n\
@od - Decimal -- the initial default\n\
@ox - Hexadecimal\n\
\n\
<i>Mode</i>\n\
\n\
Combines <i>input defaults</i> and <i>output base</i>: @mb (@0b @ob), @mo (@0o @oo), @md \
(@0d @od), @mx (@0x @ox), @mbi (@0bi @ob), @moi (@0oi @oo), @mdi (@0di @od), @mxi \
(@0xi @ox), @mbu (@0bu @ob), @mou (@0ou @oo), @mdu (@0du @od), @mxu (@0xu @ox), \
@mbn (@0bn @ob), @mon (@0on @oo), @mdn (@0dn @od), @mxn (@0xn @ox).\n\
\n\
<i>P notation</i>\n\
\n\
@pn specifies that binary, octal and hexadecimal floating point type numbers \
be output in normalized scientific P notation.\n\
\n\
@pu specifies that very large and very small binary, octal and hexadecimal \
floating point type numbers be output in unnormalized scientific P notation. -- \
the default\n\
\n\
<i>Precision</i>\n\
\n\
@pr<i>n</i> specifies the maximum precision (number of significant digits) in \
which a number is output, given as <i>n</i>. Affects floating point type \
(complex type) numbers only. E.g., @pr15. The default value is 50. The value 0 \
is special and means full precision including guard digits.\n\
\n\
<i>Integer word size</i>\n\
\n\
Specifies the word size for integer types:\n\
\n\
@w8   -   8 bits\n\
@w16  -  16 bits\n\
@w32  -  32 bits\n\
@w64  -  64 bits\n\
@w128 - 128 bits -- the default\n\
\n\
Note: This does not affect complex type numbers.\n\
\n\
Note 2: Integer calculations are always performed internally in 128 bit\n\
precision and then truncated to the active word size. \
</markup>\
");

    text.grab_focus(); text.select_region(0, 0); // inexplicably, the text is being unwantedly selected by default
    frame.grab_focus(); // hides the cursor
}

help_window::~help_window() {
}
