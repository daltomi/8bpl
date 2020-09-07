/* ------------------------------------------------------------------------- *\
   TOOL.H :

   Basic definitions (based on A. Glassner in Graphics Gems I)

   by Christophe Schlick (1 June 1992)

   "A Toolbox of Macro Functions for Computer Graphics"
   in Graphics Gems V (edited by A. Paeth), Academic Press
\* ------------------------------------------------------------------------- */

/*
  8bpl - Copyright © daltomi <daltomi@disroot.org>

  Changelog:
    POW, ASIN, ZERO_INIT_MEM, ASSERT_DBG MESSAGE* SHOW_MESSAGE
    BYTE BOOL SHORT WORD SHORTINT LONGWORD LONGINT LLONGWORD LLONGINT SIZEWORD REAL
    IN_EQ
*/


#ifndef LIB_8BPL_TOOL_H_INCLUDED
#define LIB_8BPL_TOOL_H_INCLUDED

#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h> /* memcpy, memset, memcmp */

/* ------------------------------------------------------------------------- *\
                             TYPES AND CONSTANTS
\* ------------------------------------------------------------------------- */

/*
** Type definitions (boolean, BYTE and file)
*/

//typedef unsigned int  BOOL;
//typedef unsigned char BYTE;
//typedef FILE *file;

/*
** Boolean constants
*/
#ifndef TRUE
#define TRUE    (true)
#endif

#ifndef FALSE
#define FALSE   (false)
#endif

#define ON      (1)
#define OFF     (0)

/*
** Mathematical constants
*/

/* 8bpl */
typedef uint8_t   U8;
#define U8MAX     (UINT8_MAX)

typedef bool      BOOL;

typedef int8_t    S8;
#define S8MAX     (INT8_MAX)

typedef uint16_t  U16;
#define U16MAX    (UINT16_MAX)

typedef int16_t   S16;
#define S16MAX    (INT16_MAX)

typedef uint32_t  U32;
#define U32MAX    (UINT32_MAX)

typedef int32_t   S32;
#define S32MAX    (INT32_MAX)

typedef uint64_t  U64;
#define U64MAX    (UINT64_MAX)

typedef int64_t   S64;
#define S64MAX    (INT64_MAX)

typedef size_t    USIZE;
#define USIZEMAX  (SIZE_MAX)
/* 8bpl */

#define BIT_SIZEOF(type) (CHAR_BIT * sizeof(type))

#ifdef SINGLE_REAL
typedef float REAL;
#else
typedef double REAL;
#endif


#ifdef SINGLE_REAL

#define LO_TOL      ((REAL) 0.000010)
#define TOL         ((REAL) 0.000100)
#define HI_TOL      ((REAL) 0.001000)
#define E           ((REAL) 2.718282)
#define PI          ((REAL) 3.141593)
#define HALF_PI     ((REAL) 1.570796)
#define DBLE_PI     ((REAL) 6.283185)
#define SQRT2       ((REAL) 1.414214)
#define HALF_SQRT2  ((REAL) 0.707107)
#define DBLE_SQRT2  ((REAL) 2.828427)
#define SQRT3       ((REAL) 1.732051)
#define HALF_SQRT3  ((REAL) 0.860254)
#define DBLE_SQRT3  ((REAL) 3.464102)
#define GOLD_RATIO  ((REAL) 1.618340)
#define DEG_TO_RAD  ((REAL) 0.017453)
#define RAD_TO_DEG  ((REAL) 57.29578)

#else

#define LO_TOL      ((REAL) 0.0000000000000010)
#define TOL         ((REAL) 0.0000000000000100)
#define HI_TOL      ((REAL) 0.0000000000001000)
#define E           ((REAL) 2.7182818284590498)
#define PI          ((REAL) 3.1415926535897929)
#define HALF_PI     ((REAL) 1.5707963267948965)
#define DBLE_PI     ((REAL) 6.2831853071795858)
#define SQRT2       ((REAL) 1.4142135623730951)
#define HALF_SQRT2  ((REAL) 0.7071067811865476)
#define DBLE_SQRT2  ((REAL) 2.8284271248461902)
#define SQRT3       ((REAL) 1.7320508075688772)
#define HALF_SQRT3  ((REAL) 0.8602540378443859)
#define DBLE_SQRT3  ((REAL) 3.4641016151377544)
#define GOLD_RATIO  ((REAL) 1.6183398874989489)
#define DEG_TO_RAD  ((REAL) 0.0174532925199433)
#define RAD_TO_DEG  ((REAL) 57.295779513082322)

#endif

/* 8bpl */
#define SOFT_SPRING_PI ((REAL)(-3.2 * PI))
#define SPRING_PI      ((REAL)(2 * SOFT_SPRING_PI))

#ifdef SINGLE_REAL
#define POW(a,b)    (powf((a),(b)))
#define ASIN(a)     (asinf((a)))
#else
#define POW(a,b)    (pow((a),(b)))
#define ASIN(a)     (asin((a)))
#endif
/* 8bpl */



/* ------------------------------------------------------------------------- *\
                               MATHEMATICAL MACROS
\* ------------------------------------------------------------------------- */

/*
** ABS(t) = Absolute value of 't'
** SGN(t) = Sign value of 't'
** FLOOR(t) = Map 't' to the default integer
** ROUND(t) = Map 't' to the nearest integer
*/

#define ABS(t)          ((t) < 0 ? -(t) : (t))
#define SGN(t)          ((t) < 0 ? -1 : (t) > 0 ? 1 : 0)
#define FLOOR(t)        ((t) < 0 ? (int) ((t)-1.0) : (int) (t))
#define ROUND(t)        ((t) < 0 ? (int) ((t)-0.5) : (int) ((t)+0.5))

/*
** ZERO(a)    = Test if a =  0 with a given tolerance
** SAME(a,b)  = Test if a =  b with a given tolerance
** LESS(a,b)  = Test if a <  b with a given tolerance
** MORE(a,b)  = Test if a >  b with a given tolerance
** !LESS(a,b) = Test if a >= b with a given tolerance
** !MORE(a,b) = Test if a <= b with a given tolerance
** XXXX_TOL(a,b,t) = Same thing but with a user-provided tolerance
*/

#define ZERO(a)         ((a) > -TOL && (a) < TOL)
#define ZERO_TOL(a,t)   ((a) > -(t) && (a) < (t))
#define SAME(a,b)       ((a) > (b)-TOL && (a) < (b)+TOL)
#define SAME_TOL(a,b,t) ((a) > (b)-(t) && (a) < (b)+(t))
#define LESS(a,b)       ((a) < (b)-TOL)
#define LESS_TOL(a,b,t) ((a) < (b)-(t))
#define MORE(a,b)       ((a) > (b)+TOL)
#define MORE_TOL(a,b,t) ((a) > (b)+(t))

/*
** IN(t,lo,hi)    = Test if t >  lo and t <  hi
** !IN(t,lo,hi)   = Test if t <= lo  or t >= hi
** OUT(t,lo,hi)   = Test if t <  lo  or t >  hi
** !OUT(t,lo,hi)  = Test if t >= lo and t <= hi
** CLAMP(t,lo,hi) = Clamp a value 't' to the range [lo,hi]
*/

#define IN_EQ(t,lo,hi)  ((t) >= (lo) && (t) <= (hi))
#define IN(t,lo,hi)     ((t) > (lo) && (t) < (hi))
#define OUT(t,lo,hi)    ((t) < (lo) || (t) > (hi))
#define CLAMP(t,lo,hi)  ((t) < (lo) ? (lo) : (t) > (hi) ? (hi) : (t))

/*
** MIN(a,b) = Minimum of values 'a' and 'b'
** MAX(a,b) = Maximum of values 'a' and 'b'
** MINMIN(a,b,c) = Minimum of values 'a', 'b' and 'c'
** MAXMAX(a,b,c) = Maximum of values 'a', 'b' and 'c'
*/

#define MIN(a,b)        ((a) < (b) ? (a) : (b))
#define MAX(a,b)        ((a) > (b) ? (a) : (b))
#define MINMIN(a,b,c)   ((a) < (b) ? MIN (a,c) : MIN (b,c))
#define MAXMAX(a,b,c)   ((a) > (b) ? MAX (a,c) : MAX (b,c))

/*
** LERP(t,a,b) = Linear interpolation between 'a' and 'b' using 't' (0<=t<=1)
** ==> LERP(0) = a, LERP(1) = b
**
** HERP(t,a,b) = Hermite interpolation between 'a' and 'b' using 't' (0<=t<=1)
** ==> HERP(0) = a, HERP'(0) = 0, HERP(1) = b, HERP'(1) = 0
**
** CERP(t,a,b) = Cardinal interpolation between 'a' and 'b' using 't' (0<=t<=1)
** ==> CERP(0) = a, CERP'(0) = 0.5*(b-aa), HERP(1) = b, HERP'(1) = 0.5*(bb-a)
*/

#define LERP(t,a,b)       ((a) + ((b)-(a))*(t))
#define HERP(t,a,b)       ((a) + ((b)-(a))*(t)*(t)*(3.0-(t)-(t)))
#define CERP(t,aa,a,b,bb) ((a) + 0.5*(t)*((b)-(aa)+(t)*(2.0*(aa)-5.0*(a)\
                          +4.0*(b)-(bb)+(t)*((bb)-3.0*(b)+3.0*(a)-(aa)))))

/*
** BIAS(t,p) = Rational bias operator (0 <= t <= 1 and 0 < p < 1)
** GAIN(t,p) = Rational gain operator (0 <= t <= 1 and 0 < p < 1)
**
** Note : For details, see the Gem given by C. Schlick in "Graphics Gems IV"
*/

#define BIAS(t,p)       ((p)*(t)/((p)+((p)+(p)-1.0)*((t)-1.0)))
#define GAIN(t,p)       ((t)<0.5 ? (p)*(t)/((p)+((p)+(p)-1.0)*((t)+(t)-1.0)):\
			 (p)*((t)-1.0)/((p)-((p)+(p)-1.0)*((t)+(t)-1.0))+1.0)

/*
** SWAP(a,b,t) = Swap 'a' and 'b' using 't' as temporary variable
**
** Warning : The Gem given by B. Wyvill in "Graphics Gems I" should not be used
**           because it is compiler-dependent when using non-integer variables!
*/

#define SWAP(a,b,t)     ((t) = (a), (a) = (b), (b) = (t))

/*
** Resolution (real solutions only) of a quadratic equation: a*x^2+b*x+c = 0
**
** Warning : This is a hacker-like implementation of a quadratic solver. It
**           is intended to be optimal in terms of floating point operations
**           but warn that values of parameters a, b and c are destroyed!
**
** Return :  a = Smallest solution (if it exists)
**           b = Greatest solution (if it exists)
**           Return value = Number of solutions (0, 1, or 2)
*/

#define QUADRATIC(a,b,c)\
        (ZERO (a) ? ZERO (b) ? 0 : (a = -c / b, b = a, 1) :\
         (a = -0.5 / a, b *= a, c *= a + a, c += b * b,\
         (c >  TOL) ? (c = sqrt (c), a = b - c, b = b + c, 2) :\
         (c < -TOL) ? 0 : (a = b, 1)))

/* ------------------------------------------------------------------------- *\
                            MEMORY MANAGEMENT MACROS
\* ------------------------------------------------------------------------- */

/*
** USR_INIT_MEM = User-provided memory allocation routine (default = malloc)
** USR_EXIT_MEM = User-provided memory deallocation routine (default = free)
**
** Note: If you do not like standard (de)allocation routines, simply redefine
**       USR_INIT_MEM and USR_EXIT_MEM with your favorite functions
*/

//#ifndef USR_INIT_MEM
//#define USR_INIT_MEM  malloc
//#endif
//
//#ifndef USR_EXIT_MEM
//#define USR_EXIT_MEM  free
//#endif

/*
** INIT_MEM(Var,Type,Nbr) = Allocation for 'Nbr' elements of type 'Type'
** EXIT_MEM(Var) = Deallocation of variable 'Var'
** ZERO_MEM(Var,Type,Nbr) = Fill 'Nbr' elements of type 'Type' with zero
** COPY_MEM(Var,Mem,Type,Nbr) = Copy 'Nbr' elements from 'Mem' to 'Var'
** SAME_MEM(Var,Mem,Type,Nbr) = Test if 'Var=Mem' (only 'Nbr' first elements)
** LESS_MEM(Var,Mem,Type,Nbr) = Test if 'Var<Mem' (only 'Nbr' first elements)
** MORE_MEM(Var,Mem,Type,Nbr) = Test if 'Var>Mem' (only 'Nbr' first elements)
*/

//#define INIT_MEM(Var,Type,Nbr)        (Var = (Type*) (malloc(sizeof(Type)*(Nbr))))
//#define ZERO_INIT_MEM(Var,Type,Nbr)   (Var = (Type*) (calloc((Nbr),sizeof(Type))))
//#define EXIT_MEM(Var)                 (free (Var))
//#define ZERO_MEM(Var,Type,Nbr)        (memset (Var,0,sizeof(Type)*(Nbr)))
//#define COPY_MEM(Var,Mem,Type,Nbr)    (memcpy (Mem,Var,sizeof(Type)*(Nbr))))
//#define SAME_MEM(Var,Mem,Type,Nbr)    (memcmp (Var,Mem,sizeof(Type)*(Nbr)) == 0)
//#define LESS_MEM(Var,Mem,Type,Nbr)    (memcmp (Var,Mem,sizeof(Type)*(Nbr))  < 0)
//#define MORE_MEM(Var,Mem,Type,Nbr)    (memcmp (Var,Mem,sizeof(Type)*(Nbr))  > 0)



/* ------------------------------------------------------------------------- *\
                           FILE MANAGEMENT MACROS
\* ------------------------------------------------------------------------- */

/*
** Symbolic constants for standard streams and file modes
*/

//#define SOF stdout      /* Standard output file */
//#define SIF stdin       /* Standard input file */
//#define SEF stderr      /* Standard error file */
//
//#define RFILE "r"       /* Open an existing file in read mode */
//#define WFILE "a"       /* Open an existing file in write mode */
//#define NFILE "w"       /* Create a new file (or recreate an existing one) */

/*
** INIT_FILE(File,Name,Mode) = Open or create file 'Name' in a given 'Mode'
** EXIT_FILE(File) = Close file 'File'
** TEST_FILE(File) = Test if the file pointer is within 'File'
** HEAD_FILE(File) = Set the file pointer at the head of 'File'
** TAIL_FILE(File) = Set the file pointer at the tail of 'File'
*/

//#define INIT_FILE(File,Name,Mode)       ((File) = fopen (Name, Mode))
//#define EXIT_FILE(File)                 (fclose (File))
//#define TEST_FILE(File)                 (!feof (File))
//#define HEAD_FILE(File)                 (fseek (File, (long)0, 0))
//#define TAIL_FILE(File)                 (fseek (File, (long)0, 2))

/*
** GET_BYTE(File,Var) = Get a BYTE in 'File' and put it in 'Var'
** PUT_BYTE(File,Var) = Put a BYTE 'Var' at the current position in 'File'
** GET_STR(File,Var) = Get a string (until the next blank caracter) from 'File'
** PUT_STR(File,Var) = Put a null-terminated string 'Var' in 'File'
** GET_LINE(File,Var,Max) = Get a line of at most 'Max' characters from 'File'
** PUT_LINE(File,Var) = Put a string 'Var' ended with a newline char in 'File'
*/

//#define GET_BYTE(File,Var)      ((Var) = getc (File))
//#define PUT_BYTE(File,Var)      (putc (Var, File))
//#define GET_STR(File,Var)       (fscanf (File, "%s\n", Var))
//#define PUT_STR(File,Var)       (fprintf (File, "%s", Var))
//#define GET_LINE(File,Var,Max)  (fgets (Var, Max, File))
//#define PUT_LINE(File,Var)      (fprintf (File, "%s\n", Var))


#define BIT(b)          (1U << (b))
#define SET_BIT(v, b)   ((v) |= (b))
#define CLR_BIT(v, b)   ((v) &= ~(b))
#define TGL_BIT(v, b)   ((v) ^= (b))
#define CHK_BIT(v, b)   ((v) & (b))
#define NOT_BIT(v, b)   (!CHK_BIT((v),(b)))
#ifndef __i386__
#define COUNT_BITS(b)   (((b) * 0x200040008001ULL & 0x11111111111111UL) %0xf) // CPU 64
#endif


/* ------------------------------------------------------------------------- *\
                         ERROR MANAGEMENT MACROS
\* ------------------------------------------------------------------------- */

/*
** ASSERT(Test) = If 'Test' is false, display a standard error message
//~ ** WARN_ERROR(Test,Mesg,Name) = If 'Test' is false, display an error 'Mesg'
**                              including an eventual identifier 'Name'
//~ ** STOP_ERROR(Test,Mesg,Name) = If 'Test' is false, display an error 'Mesg'
**                              including an identifier 'Name' and stop
//~ ** CURE_ERROR(Test,Cure,Var)  = If 'Test' is false, try to 'Cure' the error
*/

#define STRINGIFY(X) #X

#define STRY(X) STRINGIFY(X)

#define ASSERT(Test)                                                      \
        ((Test) ? TRUE :                                                  \
         (fprintf (stderr, "Assertion \"%s\" failed in file %s at line %d\n",\
          #Test, __FILE__, __LINE__), _exit(EXIT_FAILURE)))

#ifdef DEBUG
#define ASSERT_DBG(Test)\
        (ASSERT(Test))
#else
#define ASSERT_DBG(Test)
#endif

#define SHOW_MESSAGE(Mesg, ...) (fprintf(stderr,"" Mesg "",##__VA_ARGS__))
#define SHOW_MESSAGE_HEADER     (fprintf(stderr,"\n"))
//~ #define SHOW_MESSAGE_HEADER     (fprintf(stderr,"\n%s\n","------------------"))

#define WARNING(...)                              \
do {                                              \
  SHOW_MESSAGE_HEADER;                            \
  SHOW_MESSAGE(" Warning:\n" __VA_ARGS__);        \
  SHOW_MESSAGE_HEADER;                            \
} while(0)

#define MESSAGE(...)                              \
do {                                              \
  SHOW_MESSAGE_HEADER;                            \
  SHOW_MESSAGE("Message:\n" __VA_ARGS__);         \
  SHOW_MESSAGE_HEADER;                            \
} while(0)


#define STOP(...)                                 \
do {                                              \
  SHOW_MESSAGE_HEADER;                            \
  SHOW_MESSAGE("Stop:\n" __VA_ARGS__);            \
  SHOW_MESSAGE_HEADER;                            \
  ASSERT(0);                                      \
} while (0)


#ifdef DEBUG
#define WARNING_DBG(...)                          \
do {                                              \
  SHOW_MESSAGE_HEADER;                            \
  SHOW_MESSAGE("Debug - Warning:\n" __VA_ARGS__); \
  SHOW_MESSAGE_HEADER;                            \
} while(0)

#define MESSAGE_DBG(...)                          \
do {                                              \
  SHOW_MESSAGE_HEADER;                            \
  SHOW_MESSAGE("Debug - Message:\n" __VA_ARGS__); \
  SHOW_MESSAGE_HEADER;                            \
} while(0)

#define STOP_DBG(...)                             \
 do {                                             \
  SHOW_MESSAGE_HEADER;                            \
  SHOW_MESSAGE("Debug - Stop:\n" __VA_ARGS__);    \
  SHOW_MESSAGE_HEADER;                            \
  ASSERT_DBG(0);                                  \
} while (0)

#else

#define WARNING_DBG(...)

#define MESSAGE_DBG(...)

#define STOP_DBG(...)

#endif

#endif // TOOL_H_INCLUDED
