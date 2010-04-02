#include <stdio.h>

union intfloat   // This union allows for bit manipulation of floating-point
{   float f;     // values.
    int   i;
};

// Use an epsilon of 0.000001. This seems small enough, and it worked for the
// three test cases I tried, and we can come back and "adjust" this later if we
// have some strange floating-point edge case that costs us three days to track
// down but which we don't understand fully. I think. Maybe 0.00001 would be
// better, perhaps, but then again I'm not sure why.

const float epsilon = 1e-6;

void PrintBinary (int x, int start, int end);
void PrintVal    (intfloat);
void PrintVal    (float);

void main ()
{
    intfloat a = { 16.0f };
    intfloat b = { 16.0f };

    // Increment b so that it's the smallest representable number that is
    // larger than a.

    ++ b.i;

    // Print out the values we'll be working with.

    printf ("a       = "); PrintVal(a);
    printf ("b       = "); PrintVal(b);
    printf ("epsilon = "); PrintVal(epsilon);

    // Print the represented difference between b and a.

    printf ("b-a = ");
    PrintVal (b.f - a.f);

    // Determine if (b-a) is less than epsilon. Since b is the smallest
    // representable number larger than a, if this test fails, then epsilon
    // comparison is no different from identity comparisons for these two
    // numbers, or any numbers larger than these two.

    printf ("(b-a) < epsilon == %s\n",
        ((b.f-a.f) < epsilon) ? "true" : "false");
}

// ---------------------------------------------------------------------------
// Print the floating-point and binary representations of a value.
// ---------------------------------------------------------------------------

void PrintVal (intfloat x)
{
    printf ("%.12f [", x.f);
    PrintBinary (x.i, 31, 31);
    printf (":");
    PrintBinary (x.i, 30, 23);
    printf (":");
    PrintBinary (x.i, 22,  0);
    printf ("]\n");
}


// ---------------------------------------------------------------------------
// Print the value of a floating point number.
// ---------------------------------------------------------------------------

void PrintVal (float f)
{
    intfloat x;
    x.f = f;
    PrintVal (x);
}

// ---------------------------------------------------------------------------
// Helper routine to print out a range of binary bits from a number.
// ---------------------------------------------------------------------------

void PrintBinary (int x, int start, int end)
{
    unsigned int mask    = 1 << start;
    unsigned int endmask = 1 << end;

    while (mask >= endmask)
    {   putchar ((mask & x) ? '1' : '0');
        mask >>= 1;
    }
}
