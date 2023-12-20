/***************************************************************************************************
This program translates between float and double values and their hexadecimal counterparts.  If the
program is called with a command-line argument, then it prints out the appropriate information.  If
not command- line arguments are given, then it goes into interactive mode.
***************************************************************************************************/

#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;


const static string version { "hexfloat 2.0.0-alpha | 2023-12-19 | https://github.com/hollasch/fpWorkbench\n" };

const static string usage { R"(
hexfloat:  Convert between hexadecimal and floating-point numbers
usage   :  hexfloat [--help|-h|/?] [<hex-value>|<number>]

    Prints the hexadecimal, single-precision floating point, and
    double-precision floating point value of the input.

    Hexadecimal values must be prefixed with "0x" or "0X". All other arguments
    are interpreted as numbers. Eight or fewer hexadecimal digits indicate the
    hexadecimal representation of a single-precision (32-bit) floating-point
    value. More than eight hex digits indicate a double-precision (64-bit)
    value. Values should be zero-padded if necessary to specify a
    double-precision value.

    In addition, the special values "NaN", "QNaN", "SNaN", "inf" or "infinity"
    are recognized (case insensitive). The general "NaN" is interpreted as
    "QNaN" (quiet NaN).

)" };


struct FPValue {
    float  float32 { 0 };
    double float64 { 0 };

    uint32_t integer32 { 0 };
    uint64_t integer64 { 0 };

    unsigned int msw() const { return integer64 >> 32; }
    unsigned int lsw() const { return integer64 &  0xffffffffUL; }
};


//----------------------------------------------------------------------------------------------------------------------
bool isNumber (string s) {
    return s.find("0x") != 0 && s.find("0X") != 0;
}


//----------------------------------------------------------------------------------------------------------------------
void printBinary (uint32_t x, int start, int end) {
    // Print portion of an integer in binary notation.

    unsigned int mask    = 1 << start;
    unsigned int endmask = 1 << end;

    while (mask >= endmask) {
        putchar ((mask & x) ? '1' : '0');
        mask >>= 1;
    }
}


//----------------------------------------------------------------------------------------------------------------------
void report(const FPValue& v) {
    cout << '\n';
    cout << "Float32 : " << std::setprecision(9) << v.float32 << '\n';
    cout << "Hex32   : " << std::setw(8) << std::setfill('0') << std::hex << v.integer32 << '\n';
    cout << "Binary32: ";
    printBinary(v.integer32, 31, 31);
    cout << '.';
    printBinary(v.integer32, 30, 23);
    cout << '.';
    printBinary(v.integer32, 22,  0);
    cout << '\n';

    cout << "\nFloat64 : " << std::setprecision(18) << v.float64 << '\n';
    cout << "Hex64   : " << std::setw(8) << std::setfill('0') << std::hex << v.msw() << ' '
                         << std::setw(8) << std::setfill('0') << std::hex << v.lsw() << '\n';
    cout << "Binary64: ";
    printBinary(v.msw(), 31, 31);
    cout << '.';
    printBinary(v.msw(), 30, 20);
    cout << '.';
    printBinary(v.msw(), 19,  0);
    printBinary(v.lsw(), 31,  0);
    cout << '\n';
}


//----------------------------------------------------------------------------------------------------------------------
void interpretNumber(const string& n) {

    FPValue v;

    char const *s = n.c_str();

    // Handle special cases, otherwise interpret as a regular number.
    if (0 == _stricmp(s, "inf") || 0 == _stricmp(s, "infinity")) {
        v.float64 = std::numeric_limits<double>::infinity();
        v.float32 = std::numeric_limits<float>::infinity();
    } else if (0 == _stricmp(s, "nan") || 0 == _stricmp(s, "qnan")) {
        v.float64 = std::numeric_limits<double>::quiet_NaN();
        v.float32 = std::numeric_limits<float>::quiet_NaN();
    } else if (0 == _stricmp(s, "snan")) {
        v.float64 = std::numeric_limits<double>::signaling_NaN();
        v.float32 = std::numeric_limits<float>::signaling_NaN();
    } else {
        v.float64 = atof(n.c_str());
        v.float32 = static_cast<float>(v.float64);
    }

    // Integer analogs
    uint32_t  int32    = *((uint32_t*)(&v.float32));
    uint64_t* int64ptr = (uint64_t*)(&v.float64);

    v.integer32 = *((uint32_t*)(&v.float32));
    v.integer64 = *(uint64_t*)(&v.float64);

    report(v);
}


//----------------------------------------------------------------------------------------------------------------------
void interpretHex(const string& n) {
    FPValue v;

    if (n.length() > 18) {
        cerr << "hexfloat: hex value too long (" << n << ").\n";
        return;
    }

    if (n.length() <= 10) {
        v.integer32 = stoul(n, 0, 16);
        v.float32 = *((float*)(&v.integer32));
        v.float64 = v.float32;
        v.integer64 = *((uint64_t*)(&v.float64));
    } else {
        v.integer64 = stoull(n, 0, 16);
        v.float64 = *((double*)(&v.integer64));
        v.float32 = v.float64;
        v.integer32 = *((uint32_t*)(&v.float32));
    }

    report(v);
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
}
