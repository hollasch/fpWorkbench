/***************************************************************************************************
This program translates between float and double values and their hexadecimal counterparts.  If the
program is called with a command-line argument, then it prints out the appropriate information.  If
not command- line arguments are given, then it goes into interactive mode.
***************************************************************************************************/

#include <cctype>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;


const static string version { "hexfloat 2.0.0-alpha | 2023-12-14 | https://github.com/hollasch/fpWorkbench\n" };

const static string usage { R"(
hexfloat:  Convert between hexadecimal and floating-point numbers
usage   :  hexfloat [--help|-h|/?] [<hex-value>|<number>]

    Prints the hexadecimal, single-precision floating point, and
    double-precision floating point value of the input.

    Hexadecimal values must be prefixed with "0x" or "0X". All other arguments
    are interpreted as numbers. Eight or fewer hexadecimal digits indicate the
    hexadecimal representation of a single-precision (32-bit) floating-point value.
    More than eight hex digits indicate a double-precision (64-bit) value. Values
    should be zero-padded if necessary to specify a double-precision value.

    In addition, the special values "NaN", "QNaN", "SNaN", "inf" or "infinity"
    are recognized (case insensitive).

)" };


struct FPValue {
    long   hex  { 0 };
    float  fp32 { 0 };
    double fp64 { 0 };
};


//----------------------------------------------------------------------------------------------------------------------
bool isNumber (string s) {
    return s.find("0x") != 0 && s.find("0X") != 0;
}


//----------------------------------------------------------------------------------------------------------------------
void PrintBinary (int x, int start, int end)
{
    // Print portion of an integer in binary notation.

    unsigned int mask    = 1 << start;
    unsigned int endmask = 1 << end;

    while (mask >= endmask) {
        putchar ((mask & x) ? '1' : '0');
        mask >>= 1;
    }
}


//----------------------------------------------------------------------------------------------------------------------
void interpretNumber(const string& n) {
    cout << "<number>\n";
}


//----------------------------------------------------------------------------------------------------------------------
void interpretHex(const string& n) {
    cout << "<hex>\n";
}


//----------------------------------------------------------------------------------------------------------------------
int main (int argc, char *argv[])
{
    vector<string> args { argv, argv + argc };

    FPValue value;

    if (args.size() < 2 || 2 < args.size() || args[1] == "--help" || args[1] == "-h" || args[1] == "/?") {
        cout << usage;
        cout << version;
        return 1;
    }

    auto& arg = args[1];

    if (arg == "--version") {
        cout << version;
        return 0;
    }

    if (isNumber(arg))
        interpretNumber(arg);
    else
        interpretHex(arg);

    return 0;

#if 0
    /* Skip leading whitespace. */

    char *ptr;      /* Input Pointer */
    for (ptr=argv[2];  *ptr && ((*ptr == ' ') || (*ptr == '\t'));  ++ptr)
        continue;

    if (0 == _stricmp (argv[1], "hex-single")) {

        long val;       /* Hex Value */
        sscanf_s (ptr, "%lx", &val);
        // printf ("0x%08lx: %.10e\n", val, *(float*)(&val));
        cout << "0x" << std::hex << std::setfill('0') << std::setw(8) << val
             << ": " << std::setprecision(10) << *(float*)(&val) << '\n';

    } else if (0 == strcmp(argv[1],"hex-double")) {

        char   *end;        /* Input String Tail Pointer */
        double  real;       /* Double Precision Real Value */
        long    val_mslw;   /* Hex Val (Most-Sig. LongWord) */
        long    val_lslw;   /* Hex Val (Least-Sig. LongWord) */

        // Skip past any "0x" prefix.
        if (ptr[0] == '0' && (ptr[1] == 'x' || ptr[1] == 'X'))
            ptr += 2;

        /* Find the end of the hex string. */
        for (end=ptr;  *end;  ++end)
            ;

        if ((end-ptr) <= 8) {    /* Eight or fewer hex digits */
            sscanf_s (ptr, "%lx", &val_lslw);
            val_mslw = 0;
        } else {          /* More than eight hex digits */
            sscanf_s (end-8, "%lx", &val_lslw);
            end[-8] = 0;
            sscanf_s (ptr, "%lx", &val_mslw);
        }

        // Note that this does little-endian (Intel)

        ((long*)(&real))[0] = val_lslw;
        ((long*)(&real))[1] = val_mslw;

        // printf ("0x%08lx %08lx: %.20le\n", val_mslw, val_lslw, real);
        cout << "0x" << std::hex << std::setfill('0') << std::setw(8) << val_mslw
             << ' '  << std::hex << std::setfill('0') << std::setw(8) << val_lslw
             << ": " << std::setprecision(10) << real << '\n';

    } else if (0 == strcmp(argv[1],"single-hex")) {

        float real_float;   /* Single-Precision Real Value */
        int   intval;

        if (((*ptr < '0')||('9' < *ptr)) && (*ptr != '.') && (*ptr != '-')) {
            cerr << usage;
            cerr << "\"" << ptr << "\" is not a floating point number.\n";
            return 1;
        }

        sscanf_s (ptr, "%f",  &real_float);

        intval = *((long*)(&real_float));

        printf ("0x%08lx\n", intval);

        PrintBinary (intval, 31, 31);
        putchar ('.');
        PrintBinary (intval, 30, 23);
        putchar ('.');
        PrintBinary (intval, 22,  0);
        putchar ('\n');

    } else if (0 == strcmp(argv[1],"double-hex")) {

        double  real_double;    /* Double-Precision Real Value */
        long   *longptr;        /* For Hex Values */

        if (((*ptr < '0')||('9' < *ptr)) && (*ptr != '.') && (*ptr != '-')) {
            cerr << usage;
            cerr << "\"" << ptr << "\" is not a floating point number.\n";
            return 1;
        }

        sscanf_s (ptr, "%lf", &real_double);
        longptr = (long*)(&real_double);

        // Note - this is coded for reverse endian (Intel).

        printf ("0x%08lx%08lx\n", longptr[1], longptr[0]);

        PrintBinary (longptr[1], 31, 31);
        putchar ('.');
        PrintBinary (longptr[1], 30, 20);
        putchar ('.');
        PrintBinary (longptr[1], 19,  0);
        PrintBinary (longptr[0], 31,  0);
        putchar ('\n');

    } else {

        printf ("hexfloat: Unknown conversion type (%s)\n", argv[1]);
        return 1;
    }

    return 0;
#endif
}
