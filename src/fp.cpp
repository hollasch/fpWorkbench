#include "fp.h"

#include <limits>
#include <stdio.h>


// Constants

//--------------------------------------------------------------------------------------------------
void printbinary (unsigned int i, unsigned int first, unsigned int last)
{
    // Print the specified binary bits of an unsigned int to standard output.

    const unsigned int masklo = 1 << last;
          unsigned int mask   = 1 << first;

    while ((mask != 0) && (mask >= masklo))
    {
        fputc ((mask & i) ? '1' : '0', stdout);
        mask >>= 1;
    }
}


//--------------------------------------------------------------------------------------------------
void print (char* name, const fp32 &x)
{
    // Print an fp32 value to standard output.
    printf ("%s: %12g  0x%08x  %u'%03u'",
        name, x.components.f, x.components.i, x.components.bits.sign, x.components.bits.exponent);

    printbinary (x.components.bits.mantissa, 22, 0);
    printf ("\n");
}


//--------------------------------------------------------------------------------------------------
void print (char* name, const fp64 &x)
{
    // Print an fp64 value to standard output.
    printf ("%s: %13g  0x%016I64x  %d'%04d'",
        name, x.components.f, x.components.i, int(x.components.bits.sign), int(x.components.bits.exponent));

    printbinary ((unsigned int)(x.components.bits.mantissa >> 32),        19, 0);
    printbinary ((unsigned int)(x.components.bits.mantissa & 0xffffffff), 31, 0);
    printf ("\n");
}


//--------------------------------------------------------------------------------------------------
void main ()
{
    printf ("\n------------------------------------Single Precision (32-bit)\n\n");

    print ("1.0            ", fp32{1.0});
    print ("next after 1   ", ++fp32{1.0});
    print ("next before 1  ", --fp32{1.0});

    printf("\n");
    print ("min()          ", fp32{std::numeric_limits<float>::min()});
    print ("max()          ", fp32{std::numeric_limits<float>::max()});
    print ("lowest()       ", fp32{std::numeric_limits<float>::lowest()});
    print ("denorm_min()   ", fp32{std::numeric_limits<float>::denorm_min()});

    print ("+infinity()    ", fp32{std::numeric_limits<float>::infinity()});
    print ("-infinity()    ", fp32{-std::numeric_limits<float>::infinity()});
    print ("epsilon()      ", fp32{std::numeric_limits<float>::epsilon()});
    print ("quiet_NaN()    ", fp32{std::numeric_limits<float>::quiet_NaN()});
    print ("signaling_NaN()", fp32{std::numeric_limits<float>::signaling_NaN()});
    print ("Real SNaN()    ", fp32{0, 255, 1});

    printf("\n");
    print ("+Zero          ", fp32{0,   0, 0x000000});
    print ("-Zero          ", fp32{1,   0, 0x000000});
    print ("+Infinity      ", fp32{0, 255, 0x000000});
    print ("-Infinity      ", fp32{1, 255, 0x000000});
    print ("+NormMin       ", fp32{0,   1, 0x000000});
    print ("-NormMin       ", fp32{1,   1, 0x000000});
    print ("+NormMax       ", fp32{0, 254, 0x7fffff});
    print ("-NormMax       ", fp32{1, 254, 0x7fffff});
    print ("+DenormMin     ", fp32{0,   0, 0x000001});
    print ("-DenormMin     ", fp32{1,   0, 0x000001});
    print ("+DenormMax     ", fp32{0,   0, 0x7fffff});
    print ("-DenormMax     ", fp32{0,   0, 0x7fffff});
    print ("-QNaNIndef     ", fp32{1, 255, 0x400000});
    print ("+QNaNMin       ", fp32{0, 255, 0x400000});
    print ("+QNaNMax       ", fp32{0, 255, 0x7fffff});
    print ("-QNaNMax       ", fp32{1, 255, 0x7fffff});
    print ("+SNaNMax       ", fp32{0, 255, 0x3fffff});
    print ("-SNaNMax       ", fp32{1, 255, 0x3fffff});
    print ("+SNaNMin       ", fp32{0, 255, 0x000001});
    print ("-SNaNMin       ", fp32{1, 255, 0x000001});

    printf ("\n------------------------------------Double Precision (64-bit)\n\n");

    print ("1.0            ", fp64{1.0});
    print ("next after 1   ", ++fp64{1.0});
    print ("next before 1  ", --fp64{1.0});

    printf("\n");
    print ("min()          ", fp64{std::numeric_limits<double>::min()});
    print ("max()          ", fp64{std::numeric_limits<double>::max()});
    print ("lowest()       ", fp64{std::numeric_limits<double>::lowest()});
    print ("denorm_min()   ", fp64{std::numeric_limits<double>::denorm_min()});

    print ("+infinity()    ", fp64{std::numeric_limits<double>::infinity()});
    print ("-infinity()    ", fp64{-std::numeric_limits<double>::infinity()});
    print ("epsilon()      ", fp64{std::numeric_limits<double>::epsilon()});
    print ("quiet_NaN()    ", fp64{std::numeric_limits<double>::quiet_NaN()});
    print ("signaling_NaN()", fp64{std::numeric_limits<double>::signaling_NaN()});

    printf("\n");
    print ("+Zero          ", fp64{0,    0, 0x0000000000000UL});
    print ("-Zero          ", fp64{1,    0, 0x0000000000000UL});
    print ("+Infinity      ", fp64{0, 2047, 0x0000000000000UL});
    print ("-Infinity      ", fp64{1, 2047, 0x0000000000000UL});
    print ("+NormMin       ", fp64{0,    1, 0x0000000000000UL});
    print ("-NormMin       ", fp64{1,    1, 0x0000000000000UL});
    print ("+NormMax       ", fp64{0, 2046, 0xfffffffffffffUL});
    print ("-NormMax       ", fp64{1, 2046, 0xfffffffffffffUL});
    print ("+DenormMin     ", fp64{0,    0, 0x0000000000001UL});
    print ("-DenormMin     ", fp64{1,    0, 0x0000000000001UL});
    print ("+DenormMax     ", fp64{0,    0, 0xfffffffffffffUL});
    print ("-DenormMax     ", fp64{0,    0, 0xfffffffffffffUL});
    print ("-QNaNIndef     ", fp64{1, 2047, 0x8000000000000UL});
    print ("+QNaNMin       ", fp64{0, 2047, 0x8000000000000UL});
    print ("+QNaNMax       ", fp64{0, 2047, 0xfffffffffffffUL});
    print ("-QNaNMax       ", fp64{1, 2047, 0xfffffffffffffUL});
    print ("+SNaNMax       ", fp64{0, 2047, 0x7ffffffffffffUL});
    print ("-SNaNMax       ", fp64{1, 2047, 0x7ffffffffffffUL});
    print ("+SNaNMin       ", fp64{0, 2047, 0x0000000000001UL});
    print ("-SNaNMin       ", fp64{1, 2047, 0x0000000000001UL});
}
