#include <fp.h>
#include <stdio.h>
#include <float.h>

void print (const fp32 &v);
void print (const fp64 &v);



// Constants

const float  SINGLE_POSITIVE_ZERO            = fp32 (0,   0, 0x000000);
const float  SINGLE_NEGATIVE_ZERO            = fp32 (1,   0, 0x000000);
const float  SINGLE_POSITIVE_INFINITY        = fp32 (0, 255, 0x000000);
const float  SINGLE_NEGATIVE_INFINITY        = fp32 (1, 255, 0x000000);
const float  SINGLE_POSITIVE_NORM_MIN        = fp32 (0,   1, 0x000000);
const float  SINGLE_NEGATIVE_NORM_MIN        = fp32 (1,   1, 0x000000);
const float  SINGLE_POSITIVE_NORM_MAX        = fp32 (0, 254, 0x7fffff);
const float  SINGLE_NEGATIVE_NORM_MAX        = fp32 (1, 254, 0x7fffff);
const float  SINGLE_POSITIVE_DENORM_MIN      = fp32 (0,   0, 0x000001);
const float  SINGLE_NEGATIVE_DENORM_MIN      = fp32 (1,   0, 0x000001);
const float  SINGLE_POSITIVE_DENORM_MAX      = fp32 (0,   0, 0x7fffff);
const float  SINGLE_NEGATIVE_DENORM_MAX      = fp32 (0,   0, 0x7fffff);
const float  SINGLE_NEGATIVE_QNAN_INDEFINITE = fp32 (1, 255, 0x400000);
const float  SINGLE_POSITIVE_QNAN_MIN        = fp32 (0, 255, 0x400000);
const float  SINGLE_POSITIVE_QNAN_MAX        = fp32 (0, 255, 0x7fffff);
const float  SINGLE_NEGATIVE_QNAN_MAX        = fp32 (1, 255, 0x7fffff);
const float  SINGLE_POSITIVE_SNAN_MAX        = fp32 (0, 255, 0x3fffff);
const float  SINGLE_NEGATIVE_SNAN_MAX        = fp32 (1, 255, 0x3fffff);
const float  SINGLE_POSITIVE_SNAN_MIN        = fp32 (0, 255, 0x000001);
const float  SINGLE_NEGATIVE_SNAN_MIN        = fp32 (1, 255, 0x000001);

const double DOUBLE_POSITIVE_ZERO            = fp64 (0,    0, 0x0000000000000);
const double DOUBLE_NEGATIVE_ZERO            = fp64 (1,    0, 0x0000000000000);
const double DOUBLE_POSITIVE_INFINITY        = fp64 (0, 2047, 0x0000000000000);
const double DOUBLE_NEGATIVE_INFINITY        = fp64 (1, 2047, 0x0000000000000);
const double DOUBLE_POSITIVE_NORM_MIN        = fp64 (0,    1, 0x0000000000000);
const double DOUBLE_NEGATIVE_NORM_MIN        = fp64 (1,    1, 0x0000000000000);
const double DOUBLE_POSITIVE_NORM_MAX        = fp64 (0, 2046, 0xFFFFFFFFFFFFF);
const double DOUBLE_NEGATIVE_NORM_MAX        = fp64 (1, 2046, 0xFFFFFFFFFFFFF);
const double DOUBLE_POSITIVE_DENORM_MIN      = fp64 (0,    0, 0x0000000000001);
const double DOUBLE_NEGATIVE_DENORM_MIN      = fp64 (1,    0, 0x0000000000001);
const double DOUBLE_POSITIVE_DENORM_MAX      = fp64 (0,    0, 0xFFFFFFFFFFFFF);
const double DOUBLE_NEGATIVE_DENORM_MAX      = fp64 (1,    0, 0xFFFFFFFFFFFFF);
const double DOUBLE_NEGATIVE_QNAN_INDEFINITE = fp64 (1, 2047, 0x8000000000000);
const double DOUBLE_POSITIVE_QNAN_MAX        = fp64 (0, 2047, 0xFFFFFFFFFFFFF);
const double DOUBLE_NEGATIVE_QNAN_MAX        = fp64 (1, 2047, 0xFFFFFFFFFFFFF);
const double DOUBLE_POSITIVE_QNAN_MIN        = fp64 (0, 2047, 0x8000000000000);
const double DOUBLE_POSITIVE_SNAN_MAX        = fp64 (0, 2047, 0x7FFFFFFFFFFFF);
const double DOUBLE_NEGATIVE_SNAN_MAX        = fp64 (1, 2047, 0x7FFFFFFFFFFFF);
const double DOUBLE_POSITIVE_SNAN_MIN        = fp64 (0, 2047, 0x0000000000001);
const double DOUBLE_NEGATIVE_SNAN_MIN        = fp64 (1, 2047, 0x0000000000001);


const fp32 c_one  (1.0f);
const fp32 c_pinf (0x7f800000u);
const fp32 c_ninf (0xff800000u);
const fp32 c_qnan (0x7fffffffu);
const fp32 c_fmin (FLT_MIN);
const fp32 c_fmax (FLT_MAX);



void main ()
{
    fp32 fmin;
    fp32 fmax;
    fp32 one;

    fmin = FLT_MIN;
    fmax = FLT_MAX;
    one  = 1.0;

    printf ("pinf : ");  print (c_pinf);
    printf ("ninf : ");  print (c_ninf);
    printf ("qnan : ");  print (c_qnan);
    printf ("fmin : ");  print (fmin);
    printf ("fmax : ");  print (fmax);
    printf ("fhand: ");  print (fp32(1,255,0xffffff));

    printf ("\none       :");  print(one);
    ++one;         printf ("++one     :");  print(one);
    --one;         printf ("--one     :");  print(one);
    --one;         printf ("--one     :");  print(one);
    one.i += 64;   printf ("one+64    :");  print(one);
    one.f += 2.0;  printf ("one+64+2.0:");  print(one);

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

    dmin = DBL_MIN;
    dmax = DBL_MAX;
    done = 1.0;

    fp64 dpinf (c_pinf.f);
    fp64 dninf (c_ninf.f);
    fp64 dqnan (c_qnan.f);

    printf ("dpinf: ");  print (dpinf);
    printf ("dninf: ");  print (dninf);
    printf ("dqnan: ");  print (dqnan);
    printf ("dmin : ");  print (dmin);
    printf ("dmax : ");  print (dmax);
    printf ("dhand: ");  print (fp64(1,678,0x123456789abcdui64));

    printf ("\ndone       :");  print(done);
    ++done;         printf ("++done     :");  print(done);
    --done;         printf ("--done     :");  print(done);
    --done;         printf ("--done     :");  print(done);
    done.i += 64;   printf ("done+64    :");  print(done);
    done.f += 2.0;  printf ("done+64+2.0:");  print(done);

    done = 1.0;
    double           doned = done;
    unsigned __int64 doneu = done;

    printf ("one double = %lg\n", doned);
    printf ("one uint64 = 0x%016I64x\n", doneu);

    printf ("\n------------------------------------\n\n");

    printf ("SINGLE_POSITIVE_ZERO            :");
    print (fp32(SINGLE_POSITIVE_ZERO));

    printf ("SINGLE_NEGATIVE_ZERO            :");
    print (fp32(SINGLE_NEGATIVE_ZERO));

    printf ("SINGLE_POSITIVE_INFINITY        :");
    print (fp32(SINGLE_POSITIVE_INFINITY));

    printf ("SINGLE_NEGATIVE_INFINITY        :");
    print (fp32(SINGLE_NEGATIVE_INFINITY));

    printf ("SINGLE_POSITIVE_NORM_MIN        :");
    print (fp32(SINGLE_POSITIVE_NORM_MIN));

    printf ("SINGLE_NEGATIVE_NORM_MIN        :");
    print (fp32(SINGLE_NEGATIVE_NORM_MIN));

    printf ("SINGLE_POSITIVE_NORM_MAX        :");
    print (fp32(SINGLE_POSITIVE_NORM_MAX));

    printf ("SINGLE_NEGATIVE_NORM_MAX        :");
    print (fp32(SINGLE_NEGATIVE_NORM_MAX));

    printf ("SINGLE_POSITIVE_DENORM_MIN      :");
    print (fp32(SINGLE_POSITIVE_DENORM_MIN));

    printf ("SINGLE_NEGATIVE_DENORM_MIN      :");
    print (fp32(SINGLE_NEGATIVE_DENORM_MIN));

    printf ("SINGLE_POSITIVE_DENORM_MAX      :");
    print (fp32(SINGLE_POSITIVE_DENORM_MAX));

    printf ("SINGLE_NEGATIVE_DENORM_MAX      :");
    print (fp32(SINGLE_NEGATIVE_DENORM_MAX));

    printf ("SINGLE_NEGATIVE_QNAN_INDEFINITE :");
    print (fp32(SINGLE_NEGATIVE_QNAN_INDEFINITE));

    printf ("SINGLE_POSITIVE_QNAN_MIN        :");
    print (fp32(SINGLE_POSITIVE_QNAN_MIN));

    printf ("SINGLE_POSITIVE_QNAN_MAX        :");
    print (fp32(SINGLE_POSITIVE_QNAN_MAX));

    printf ("SINGLE_NEGATIVE_QNAN_MAX        :");
    print (fp32(SINGLE_NEGATIVE_QNAN_MAX));

    printf ("SINGLE_POSITIVE_SNAN_MAX        :");
    print (fp32(SINGLE_POSITIVE_SNAN_MAX));

    printf ("SINGLE_NEGATIVE_SNAN_MAX        :");
    print (fp32(SINGLE_NEGATIVE_SNAN_MAX));

    printf ("SINGLE_POSITIVE_SNAN_MIN        :");
    print (fp32(SINGLE_POSITIVE_SNAN_MIN));

    printf ("SINGLE_NEGATIVE_SNAN_MIN        :");
    print (fp32(SINGLE_NEGATIVE_SNAN_MIN));

    printf ("DOUBLE_POSITIVE_ZERO           :");
    print (fp64(DOUBLE_POSITIVE_ZERO));
    printf ("DOUBLE_POSITIVE_ZERO           :");
    print (fp64(DOUBLE_POSITIVE_ZERO));
    printf ("DOUBLE_NEGATIVE_ZERO           :");
    print (fp64(DOUBLE_NEGATIVE_ZERO));
    printf ("DOUBLE_POSITIVE_INFINITY       :");
    print (fp64(DOUBLE_POSITIVE_INFINITY));
    printf ("DOUBLE_NEGATIVE_INFINITY       :");
    print (fp64(DOUBLE_NEGATIVE_INFINITY));
    printf ("DOUBLE_POSITIVE_NORM_MIN       :");
    print (fp64(DOUBLE_POSITIVE_NORM_MIN));
    printf ("DOUBLE_NEGATIVE_NORM_MIN       :");
    print (fp64(DOUBLE_NEGATIVE_NORM_MIN));
    printf ("DOUBLE_POSITIVE_NORM_MAX       :");
    print (fp64(DOUBLE_POSITIVE_NORM_MAX));
    printf ("DOUBLE_NEGATIVE_NORM_MAX       :");
    print (fp64(DOUBLE_NEGATIVE_NORM_MAX));
    printf ("DOUBLE_POSITIVE_DENORM_MIN     :");
    print (fp64(DOUBLE_POSITIVE_DENORM_MIN));
    printf ("DOUBLE_NEGATIVE_DENORM_MIN     :");
    print (fp64(DOUBLE_NEGATIVE_DENORM_MIN));
    printf ("DOUBLE_POSITIVE_DENORM_MAX     :");
    print (fp64(DOUBLE_POSITIVE_DENORM_MAX));
    printf ("DOUBLE_NEGATIVE_DENORM_MAX     :");
    print (fp64(DOUBLE_NEGATIVE_DENORM_MAX));
    printf ("DOUBLE_NEGATIVE_QNAN_INDEFINITE:");
    print (fp64(DOUBLE_NEGATIVE_QNAN_INDEFINITE));
    printf ("DOUBLE_POSITIVE_QNAN_MAX       :");
    print (fp64(DOUBLE_POSITIVE_QNAN_MAX));
    printf ("DOUBLE_NEGATIVE_QNAN_MAX       :");
    print (fp64(DOUBLE_NEGATIVE_QNAN_MAX));
    printf ("DOUBLE_POSITIVE_QNAN_MIN       :");
    print (fp64(DOUBLE_POSITIVE_QNAN_MIN));
    printf ("DOUBLE_POSITIVE_SNAN_MAX       :");
    print (fp64(DOUBLE_POSITIVE_SNAN_MAX));
    printf ("DOUBLE_NEGATIVE_SNAN_MAX       :");
    print (fp64(DOUBLE_NEGATIVE_SNAN_MAX));
    printf ("DOUBLE_POSITIVE_SNAN_MIN       :");
    print (fp64(DOUBLE_POSITIVE_SNAN_MIN));
    printf ("DOUBLE_NEGATIVE_SNAN_MIN       :");
    print (fp64(DOUBLE_NEGATIVE_SNAN_MIN));

    printf ("\nmantissa of 1/10 = 0x%06x\n", fp32(1./10.).mantissa);
}



// Print the specified binary bits of an unsigned int to standard output.

void printbinary (unsigned int i, unsigned int first, unsigned int last)
{
    const unsigned int masklo = 1 << last;
          unsigned int mask   = 1 << first;

    while ((mask != 0) && (mask >= masklo))
    {
        fputc ((mask & i) ? '1' : '0', stdout);
        mask >>= 1;
    }
}


// Print an fp32 value to standard output.

void print (const fp32 &x)
{
    printf ("f=%12g, i=0x%08x, fields=%u,%03u,",
        x.f, x.i, x.sign, x.exponent);

    printbinary (x.mantissa, 22, 0);
    printf ("\n");
}



// Print an fp64 value to standard output.

void print (const fp64 &x)
{
    printf ("f=%12g, i=0x%016I64x, fields=%d,%03d,",
        x.f, x.i, int(x.sign), int(x.exponent));

    printbinary ((unsigned int)(x.mantissa >> 32),        19, 0);
    printbinary ((unsigned int)(x.mantissa & 0xffffffff), 31, 0);
    printf ("\n");
}
