/*==============================================================================

    The following classes provide easy access to the components of
    single-precision IEEE 32-bit floating point values, and double-precision
    IEEE 64-bit floating point values.

==============================================================================*/

struct fp32
{
    // Union of Alternate Representations

    union {

        unsigned int i;

        struct {
            unsigned int mantissa:23;
            unsigned int exponent:8;
            unsigned int sign:1;
        };

        float f;
    };

    // Constructors. Note that with the exception of component-wise
    // initialization and unsigned int initialization, the standard
    // conversion from integral to floating-point values applies.

    fp32 (int s, int e, int m) : sign(s), exponent(e), mantissa(m) {}
    fp32 (unsigned int value)  : i(value) {}

    fp32 ()                    : f(0.0)   {}
    fp32 (int value)           : f(value) {}
    fp32 (float value)         : f(value) {}
    fp32 (double value)        : f(value) {}

    // Next/previous representable value operations. These are only valid for
    // finite values not on the edge of representation.

    fp32& operator++ () { ++i;  return *this; }
    fp32& operator-- () { --i;  return *this; }

    operator float ()        { return f; }
    operator unsigned int () { return i; }
};


// -----------------------------------------------------------------------------

struct fp64
{
    // Union of Alternate Representations

    union {

        unsigned __int64 i;

        struct {
            unsigned __int64 mantissa:52;
            unsigned __int64 exponent:11;
            unsigned __int64 sign:1;
        };

        double f;
    };

    // Constructors. Note that with the exception of component-wise
    // initialization and unsigned __int64 initialization, the standard
    // conversion from integral to floating-point values applies.
    
    fp64 (int s, int e, __int64 m) : sign(s), exponent(e), mantissa(m) {}
    fp64 (unsigned __int64 value)  : i(value) {}

    fp64 ()                        : f(0.0)   {}
    fp64 (int value)               : f(value) {}
    fp64 (__int64 value)           : f(value) {}
    fp64 (float value)             : f(value) {}
    fp64 (double value)            : f(value) {}

    // Next/previous representable value operations. These are only valid for
    // finite values not on the edge of representation.

    fp64& operator++ () { ++i;  return *this; }
    fp64& operator-- () { --i;  return *this; }

    operator float ()            { return f; }
    operator unsigned __int64 () { return i; }
};
