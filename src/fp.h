/*==================================================================================================

    The following classes provide easy access to the components of single-precision IEEE 32-bit
    floating point values, and double-precision IEEE 64-bit floating point values.

==================================================================================================*/

#include <cstdint>

#if defined _MSC_VER
    #pragma warning(disable:4756)
#endif


struct fp32
{
    // Union of Alternate Representations

    union {

        uint32_t i;

        struct {
            uint32_t mantissa:23;
            uint32_t exponent:8;
            uint32_t sign:1;
        } bits;

        float f;

    } components;

    // Constructors. Note that with the exception of component-wise initialization and uint32_t
    // initialization, the standard conversion from integral to floating-point values applies.

    fp32 (int s, int e, uint32_t m) {
        components.bits.sign = s;
        components.bits.exponent = e;
        components.bits.mantissa = m;
    }

    fp32 (uint32_t value) {
        components.i = value;
    }

    fp32 ()             { components.f = 0.0; }
    fp32 (int value)    { components.f = static_cast<float>(value); }
    fp32 (float value)  { components.f = value; }
    fp32 (double value) { components.f = static_cast<float>(value); }

    // Next/previous representable value operations. These are only valid for finite values not on
    // the edge of representation.

    fp32& operator++ () { ++components.i;  return *this; }
    fp32& operator-- () { --components.i;  return *this; }

    operator float ()    { return components.f; }
    operator uint32_t () { return components.i; }
};


// -----------------------------------------------------------------------------

struct fp64
{
    // Union of Alternate Representations

    union {

        uint64_t i;

        struct {
            uint64_t mantissa:52;
            uint64_t exponent:11;
            uint64_t sign:1;
        } bits;

        double f;

    } components;

    // Constructors. Note that with the exception of component-wise initialization and uint64_t
    // initialization, the standard conversion from integral to floating-point values applies.

    fp64 (int s, int e, uint64_t m) {
        components.bits.sign = s & 0x1;
        components.bits.exponent = e & 0x7ff;
        components.bits.mantissa = m & 0x000fffff;
    }

    fp64 (uint64_t value) {
        components.i = value;
    }

    fp64 ()               { components.f = 0.0;   }
    fp64 (int value)      { components.f = static_cast<double>(value); }
    fp64 (float value)    { components.f = value; }
    fp64 (double value)   { components.f = value; }

    // Next/previous representable value operations. These are only valid for finite values not on
    // the edge of representation.

    fp64& operator++ () { ++components.i;  return *this; }
    fp64& operator-- () { --components.i;  return *this; }

    operator float ()    { return static_cast<float>(components.f); }
    operator uint64_t () { return components.i; }
};
