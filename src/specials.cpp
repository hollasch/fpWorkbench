//==================================================================================================
// specials.c
//
// This program prints out special values of the IEEE 754 floating-point format.
//==================================================================================================

#include <stdio.h>
#include <cmath>

#if defined _MSC_VER
    #pragma warning(disable : 4723 4756)
#endif


char *sprint (float n)
{
    static char buff[256];
    sprintf_s (buff, sizeof(buff), "% f (%08x)", n, *(int*)(&n));
    return buff;
}

char *dprint (double n)
{
    static char buff[256];
    sprintf_s (buff, sizeof(buff), "% lf (%08x%08x)", n, ((int*)(&n))[1], ((int*)(&n))[0]);
    return buff;
}

const char* boolStr(bool b)
{
    return b ? "true" : "false";
}


// These helper functions perform out-of-range floating point operations without triggering constant
// arithmetic warnings from the compiler.

float  mul_s (float a,  float b) { return a * b; }
float  div_s (float a,  float b) { return a / b; }

double mul_d (double a, double b) { return a * b; }
double div_d (double a, double b) { return a / b; }


void PrintNaNOps()
{
    float snan = std::nanf("");

    printf ("\nOperations with NaN:\n\n");

    printf ("      NaN == 0 : %s\n", boolStr(snan == 0));
    printf ("      NaN != 0 : %s\n", boolStr(snan != 0));
    printf ("      NaN == 1 : %s\n", boolStr(snan == 1));
    printf ("      NaN != 1 : %s\n", boolStr(snan != 1));
    printf ("      NaN <  1 : %s\n", boolStr(snan < 1));
    printf ("      NaN >  1 : %s\n", boolStr(snan > 1));
}


int main ()
{
    float  szero = 0;         // Single Precision Zero */
    float  snzero;            // Single Precision Negative Zero
    float  sposinf, sneginf;  // Single Precision + - Infinity
    float  sind;              // Single Precision Indeterminate

    double dzero = 0;         // Double Precision Zero
    double dnzero;            // Double Precision Negative Zero
    double dposinf, dneginf;  // Double Precision + - Infinity
    double dind;              // Double Precision Indeterminate

    float one    =  1;        // Simple Constants
    float negone = -1;
    float zero   =  0;

    float nzeromul = 0;       // Negative-Zero Multiply Operation

    // Set up special values.

    *(int*)(&snzero) = 0x80000000;
    ((int*)(&dnzero))[1] = 0x80000000;
    ((int*)(&dnzero))[0] = 0x00000000;

    sposinf = mul_s ((float)1e30, (float)1e30);     // Overflow to infinity.
    dposinf = mul_d (1e200, 1e200);

    sneginf = -sposinf;               // Get negative infinity.
    dneginf = -dposinf;

    sind = div_s (sposinf, sposinf);  // Generate indeterminate values.
    dind = div_d (dposinf, dposinf);

    // Now print out special values.

    printf ("\n");

    printf ("Zero:           %s\t%s\n", sprint(szero),   dprint(dzero));
    printf ("Negative Zero:  %s\t%s\n", sprint(snzero),  dprint(dnzero));
    printf ("+ Infinity:     %s\t%s\n", sprint(sposinf), dprint(dposinf));
    printf ("- Infinity:     %s\t%s\n", sprint(sneginf), dprint(dneginf));
    printf ("Indeterminates: %s\t%s\n", sprint(sind),    dprint(dind));

    printf ("\nOperations (single precision):\n\n");

    printf ("     inf *  inf:  %s\n", sprint(sposinf * sposinf));
    printf ("     inf * -inf:  %s\n", sprint(sposinf * sneginf));
    printf ("    -inf * -inf:  %s\n", sprint(sneginf * sneginf));
    printf ("      1  /   0 :  %s\n", sprint(one     / zero));
    printf ("     -1  /   0 :  %s\n", sprint(negone  / zero));
    printf ("      1  /  inf:  %s\n", sprint(one     / sposinf));
    printf ("     -1  /  inf:  %s\n", sprint(negone  / sposinf));
    printf ("     inf /  inf:  %s\n", sprint(sposinf / sposinf));
    printf ("     inf +  inf:  %s\n", sprint(sposinf + sposinf));
    printf ("     inf -  inf:  %s\n", sprint(sposinf - sposinf));
    printf ("     inf *   0 :  %s\n", sprint(sposinf * zero));

    nzeromul = snzero * 37;
    printf ("      -0 *  37 :  %s\n", sprint(snzero*37));
    printf ("      -0 == +0 :  %s\n", boolStr(zero == snzero));

    PrintNaNOps();
}
