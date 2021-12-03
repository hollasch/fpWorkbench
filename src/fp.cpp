#include "fp.h"

#include <limits>
#include <stdio.h>


// Constants

const float  SinglePosZero      { fp32 (0,   0, 0x000000) };
const float  SingleNegZero      { fp32 (1,   0, 0x000000) };
const float  SinglePosInfinity  { fp32 (0, 255, 0x000000) };
const float  SingleNegInfinity  { fp32 (1, 255, 0x000000) };
const float  SinglePosNormMin   { fp32 (0,   1, 0x000000) };
const float  SingleNegNormMin   { fp32 (1,   1, 0x000000) };
const float  SinglePosNormMax   { fp32 (0, 254, 0x7fffff) };
const float  SingleNegNormMax   { fp32 (1, 254, 0x7fffff) };
const float  SinglePosDenormMin { fp32 (0,   0, 0x000001) };
const float  SingleNegDenormMin { fp32 (1,   0, 0x000001) };
const float  SinglePosDenormMax { fp32 (0,   0, 0x7fffff) };
const float  SingleNegDenormMax { fp32 (0,   0, 0x7fffff) };
const float  SingleNegQnanIndef { fp32 (1, 255, 0x400000) };
const float  SinglePosQnanMin   { fp32 (0, 255, 0x400000) };
const float  SinglePosQnanMax   { fp32 (0, 255, 0x7fffff) };
const float  SingleNegQnanMax   { fp32 (1, 255, 0x7fffff) };
const float  SinglePosSnanMax   { fp32 (0, 255, 0x3fffff) };
const float  SingleNegSnanMax   { fp32 (1, 255, 0x3fffff) };
const float  SinglePosSnanMin   { fp32 (0, 255, 0x000001) };
const float  SingleNegSnanMin   { fp32 (1, 255, 0x000001) };

const double DoublePosZero      { fp64 (0,    0, 0x0000000000000) };
const double DoubleNegZero      { fp64 (1,    0, 0x0000000000000) };
const double DoublePosInfinity  { fp64 (0, 2047, 0x0000000000000) };
const double DoubleNegInfinity  { fp64 (1, 2047, 0x0000000000000) };
const double DoublePosNormMin   { fp64 (0,    1, 0x0000000000000) };
const double DoubleNegNormMin   { fp64 (1,    1, 0x0000000000000) };
const double DoublePosNormMax   { fp64 (0, 2046, 0xFFFFFFFFFFFFF) };
const double DoubleNegNormMax   { fp64 (1, 2046, 0xFFFFFFFFFFFFF) };
const double DoublePosDenormMin { fp64 (0,    0, 0x0000000000001) };
const double DoubleNegDenormMin { fp64 (1,    0, 0x0000000000001) };
const double DoublePosDenormMax { fp64 (0,    0, 0xFFFFFFFFFFFFF) };
const double DoubleNegDenormMax { fp64 (1,    0, 0xFFFFFFFFFFFFF) };
const double DoubleNegQnanIndef { fp64 (1, 2047, 0x8000000000000) };
const double DoublePosQnanMax   { fp64 (0, 2047, 0xFFFFFFFFFFFFF) };
const double DoubleNegQnanMax   { fp64 (1, 2047, 0xFFFFFFFFFFFFF) };
const double DoublePosQnanMin   { fp64 (0, 2047, 0x8000000000000) };
const double DoublePosSnanMax   { fp64 (0, 2047, 0x7FFFFFFFFFFFF) };
const double DoubleNegSnanMax   { fp64 (1, 2047, 0x7FFFFFFFFFFFF) };
const double DoublePosSnanMin   { fp64 (0, 2047, 0x0000000000001) };
const double DoubleNegSnanMin   { fp64 (1, 2047, 0x0000000000001) };

const fp32 c_one  (1.0f);
const fp32 c_pinf (0x7f800000u);
const fp32 c_ninf (0xff800000u);
const fp32 c_qnan (0x7fffffffu);



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
    printf ("%s: f=%12g, i=0x%08x, fields=%u'%03u'",
        name, x.components.f, x.components.i, x.components.bits.sign, x.components.bits.exponent);

    printbinary (x.components.bits.mantissa, 22, 0);
    printf ("\n");
}


//--------------------------------------------------------------------------------------------------
void print (char* name, const fp64 &x)
{
    // Print an fp64 value to standard output.
    printf ("%s: f=%12g, i=0x%016I64x, fields=%d'%04d'",
        name, x.components.f, x.components.i, int(x.components.bits.sign), int(x.components.bits.exponent));

    printbinary ((unsigned int)(x.components.bits.mantissa >> 32),        19, 0);
    printbinary ((unsigned int)(x.components.bits.mantissa & 0xffffffff), 31, 0);
    printf ("\n");
}


//--------------------------------------------------------------------------------------------------
void main ()
{
    fp32 fmin;
    fp32 fmax;
    fp32 one;

    fmin = std::numeric_limits<float>::min();
    fmax = std::numeric_limits<float>::max();
    one  = 1.0;

    print ("pinf ", c_pinf);
    print ("ninf ", c_ninf);
    print ("qnan ", c_qnan);
    print ("fmin ", fmin);
    print ("fmax ", fmax);
    print ("fhand", fp32(1,255,0xffffff));

    printf("\n");
    print ("one       ", one);
    print ("++one     ", ++one);
    print ("--one     ", --one);
    print ("--one     ", --one);
    one.components.i += 64;
    print ("one+64    ", one);
    one.components.f += 2.0;
    print ("one+64+2.0", one);

    one = 1;
    float        onef = one;
    double       oned = one;
    unsigned int oneu = one;

    printf ("\none float  = %g\n", onef);
    printf ("one double = %lg\n", oned);
    printf ("one uint   = 0x%08x\n", oneu);

    printf ("\n------------------\n\n");

    fp64 dmin;
    fp64 dmax;
    fp64 done;

    dmin = std::numeric_limits<double>::min();
    dmax = std::numeric_limits<double>::max();
    done = 1.0;

    fp64 dpinf (c_pinf.components.f);
    fp64 dninf (c_ninf.components.f);
    fp64 dqnan (c_qnan.components.f);

    print("dpinf", dpinf);
    print("dninf", dninf);
    print("dqnan", dqnan);
    print("dmin ", dmin);
    print("dmax ", dmax);
    print("dhand", fp64(1,678,0x123456789abcdui64));

    printf ("\n");
    print ("done       ", done);
    print("++done     ", ++done);
    print("--done     ", --done);
    print("--done     ", --done);

    done.components.i += 64;
    print("done+64    ", done);
    done.components.f += 2.0;
    print("done+64+2.0", done);

    done = 1.0;
    double           doned = done;
    unsigned __int64 doneu = done;

    printf ("one double = %lg\n", doned);
    printf ("one uint64 = 0x%016I64x\n", doneu);

    printf ("\n------------------------------------Single Precision (32-bit)\n\n");
    print("PosZero     ", fp32(SinglePosZero));
    print("NegZero     ", fp32(SingleNegZero));
    print("PosInfinity ", fp32(SinglePosInfinity));
    print("NegInfinity ", fp32(SingleNegInfinity));
    print("PosNormMin  ", fp32(SinglePosNormMin));
    print("NegNormMin  ", fp32(SingleNegNormMin));
    print("PosNormMax  ", fp32(SinglePosNormMax));
    print("NegNormMax  ", fp32(SingleNegNormMax));
    print("PosDenormMin", fp32(SinglePosDenormMin));
    print("NegDenormMin", fp32(SingleNegDenormMin));
    print("PosDenormMax", fp32(SinglePosDenormMax));
    print("NegDenormMax", fp32(SingleNegDenormMax));
    print("NegQnanIndef", fp32(SingleNegQnanIndef));
    print("PosQnanMin  ", fp32(SinglePosQnanMin));
    print("PosQnanMax  ", fp32(SinglePosQnanMax));
    print("NegQnanMax  ", fp32(SingleNegQnanMax));
    print("PosSnanMax  ", fp32(SinglePosSnanMax));
    print("NegSnanMax  ", fp32(SingleNegSnanMax));
    print("PosSnanMin  ", fp32(SinglePosSnanMin));
    print("NegSnanMin  ", fp32(SingleNegSnanMin));

    printf ("\n------------------------------------Double Precision (64-bit)\n\n");
    print("PosZero     ", fp64(DoublePosZero));
    print("PosZero     ", fp64(DoublePosZero));
    print("NegZero     ", fp64(DoubleNegZero));
    print("PosInfinity ", fp64(DoublePosInfinity));
    print("NegInfinity ", fp64(DoubleNegInfinity));
    print("PosNormMin  ", fp64(DoublePosNormMin));
    print("NegNormMin  ", fp64(DoubleNegNormMin));
    print("PosNormMax  ", fp64(DoublePosNormMax));
    print("NegNormMax  ", fp64(DoubleNegNormMax));
    print("PosDenormMin", fp64(DoublePosDenormMin));
    print("NegDenormMin", fp64(DoubleNegDenormMin));
    print("PosDenormMax", fp64(DoublePosDenormMax));
    print("NegDenormMax", fp64(DoubleNegDenormMax));
    print("NegQnanIndef", fp64(DoubleNegQnanIndef));
    print("PosQnanMax  ", fp64(DoublePosQnanMax));
    print("NegQnanMax  ", fp64(DoubleNegQnanMax));
    print("PosQnanMin  ", fp64(DoublePosQnanMin));
    print("PosSnanMax  ", fp64(DoublePosSnanMax));
    print("NegSnanMax  ", fp64(DoubleNegSnanMax));
    print("PosSnanMin  ", fp64(DoublePosSnanMin));
    print("NegSnanMin  ", fp64(DoubleNegSnanMin));

    printf ("\nmantissa of 1/10 = 0x%06x\n", fp32(1./10.).components.bits.mantissa);
}
