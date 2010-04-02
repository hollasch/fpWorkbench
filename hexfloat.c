/*****************************************************************************
**  This program translates between float and double values and their
**  hexadecimal counterparts.  If the program is called with a command-line
**  argument, then it prints out the appropriate information.  If not command-
**  line arguments are given, then it goes into interactive mode.
*****************************************************************************/

#include <stdio.h>
#include <string.h>


    /***  Macro Definitions  ***/

#define print(s)            fputs(s,stdout)
#define fprint(stream,s)    fputs(s,stream)


    /***  Usage Statement  ***/

char usage[] = "\n\
hexfloat:  Convert between hexadecimal and floating-point numbers\n\
usage   :  hexfloat <conversion> <number>\n\
\n\
    <conversion> can be one of the following:\n\
\n\
    hf:  Convert <number> from hexadecimal to float\n\
    hd:  Convert <number> from hexadecimal to double\n\
    fh:  Convert <number> from float  to hexadecimal\n\
    dh:  Convert <number> from double to hexadecimal\n\
\n";

void   PrintBinary (int value, int highbit, int lowbit);

/**************************************************************************/

int  main  (int argc, char *argv[])
{
    char *ptr;		/* Input Pointer */

    if (argc < 3)
    {   fprint (stderr, usage);
	return 1;
    }

    /* Skip leading whitespace. */

    for (ptr=argv[2];  *ptr && ((*ptr == ' ') || (*ptr == '\t'));  ++ptr)
	continue;

    if (0 == stricmp (argv[1], "hf"))
    {
	long val;		/* Hex Value */
	sscanf (ptr, "%lx", &val);
	printf ("%.10e\n", *(float*)(&val));
    }
    else if (0 == strcmp(argv[1],"hd"))
    {
	char   *end;		/* Input String Tail Pointer */
	double  real;		/* Double Precision Real Value */
	long    val_mslw;	/* Hex Val (Most-Sig. LongWord) */
	long    val_lslw;	/* Hex Val (Least-Sig. LongWord) */

	/* Find the end of the hex string. */
	for (end=ptr;  *end;  ++end)
	    ;
	if ((end-ptr) < 8)		/* Less than 8 hex digits */
	{   sscanf (ptr, "%lx", &val_lslw);
	    val_mslw = 0;
	}
	else			/* At least 8 hex digits */
	{   sscanf (end-8, "%lx", &val_lslw);
	    end[-8] = 0;
	    sscanf (ptr, "%lx", &val_mslw);
	}

        // Note that this does little-endian (Intel)

	((long*)(&real))[0] = val_lslw;
	((long*)(&real))[1] = val_mslw;
	printf ("%.20le\n", real);
    }
    else if (0 == strcmp(argv[1],"fh"))
    {
	float real_float;	/* Single-Precision Real Value */
	int   intval;

	if (((*ptr < '0')||('9' < *ptr)) && (*ptr != '.') && (*ptr != '-'))
	{   fprint (stderr, usage);
	    fprintf (stderr, "\"%s\" is not a floating point number.\n", ptr);
	    return 1;
	}

	sscanf (ptr, "%f",  &real_float);

	intval = *((long*)(&real_float));

	printf ("0x%08lx\n", intval);

        PrintBinary (intval, 31, 31);
        putchar ('.');
        PrintBinary (intval, 30, 23);
        putchar ('.');
        PrintBinary (intval, 22,  0);
        putchar ('\n');
    }
    else if (0 == strcmp(argv[1],"dh"))
    {
	double  real_double;	/* Double-Precision Real Value */
	long   *longptr;		/* For Hex Values */

	if (((*ptr < '0')||('9' < *ptr)) && (*ptr != '.') && (*ptr != '-'))
	{   fprint (stderr, usage);
	    fprintf (stderr, "\"%s\" is not a floating point number.\n", ptr);
	    return 1;
	}

	sscanf (ptr, "%lf", &real_double);
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
    }
    else
    {   fprint (stderr, usage);
	printf ("Unknown conversion type (%s)\n", argv[1]);
	return 1;
    }

    return 0;
}



/*****************************************************************************
Print portion of an integer in binary notation.
*****************************************************************************/

void PrintBinary (int x, int start, int end)
{
    unsigned int mask    = 1 << start;
    unsigned int endmask = 1 << end;

    while (mask >= endmask)
    {   putchar ((mask & x) ? '1' : '0');
        mask >>= 1;
    }
}
