#ifndef COMPOUND_TYPE_H
# define COMPOUND_TYPE_H

# include <string.h>
# include <stdint.h>

# include <Compound/common.h>

// typedef struct {
//   const char *identifier;
//   const size_t size;
//   const bool is_long;  // Counteracts when both "long" and "short".
//   const bool is_short;
//   const bool is_unsigned;
//   const bool is_pointer;
//   const bool is_restrict;  // ISO-C99 and above.
//   const bool is_function;
//   const bool is_variadic;
//   const bool is_constant;
//   const bool is_static;
//   const bool is_register;  // ISO-C99 and above.
//   const bool is_volatile;
//   const bool is_complex;  // ISO-C99 and above.
//   const bool is_imaginary;  // Oracle C compiler only.  No effect otherwise.
// } Type;

typedef struct {
  const char *identifier;
  const size_t size;
  const unsigned int qualifier;
} Type;

enum {
  TYPE_QUALIFIER_NULL      = 0b0000000000000,
  TYPE_QUALIFIER_LONG      = 0b0000000000001,
  TYPE_QUALIFIER_SHORT     = 0b0000000000010,
  TYPE_QUALIFIER_UNSIGNED  = 0b0000000000100,
  TYPE_QUALIFIER_POINTER   = 0b0000000001000,
  TYPE_QUALIFIER_RESTRICT  = 0b0000000010000,
  TYPE_QUALIFIER_FUNCTION  = 0b0000000100000,
  TYPE_QUALIFIER_VARIADIC  = 0b0000001000000,
  TYPE_QUALIFIER_CONSTANT  = 0b0000010000000,
  TYPE_QUALIFIER_STATIC    = 0b0000100000000,
  TYPE_QUALIFIER_REGISTER  = 0b0001000000000,
  TYPE_QUALIFIER_VOLATILE  = 0b0010000000000,
  TYPE_QUALIFIER_COMPLEX   = 0b0100000000000,
  TYPE_QUALIFIER_IMAGINARY = 0b1000000000000,
};

# define DEFTYPE(Ty, sz)  static const Type Ty = (type((Ty), (sz)));
# define REDEFTYPE(Ty, other)  const Type Ty = (retype(Ty, (other)));

/* Construct Type @Ty with given size @sz.
   Other members not specified remain as false. */
# define type(Ty, sz)  ((Type) {                           \
  .identifier = nameof(Ty),                                \
  .size = sz,                                              \
  .qualifier = 0                                           \
})

/* Turn off every qualifier. */
# define clear(Ty)  ((Type) {                              \
  .identifier = Ty.identifier,                             \
  .size = Ty.size,                                         \
  .qualifier = 0                                           \
})

/* Reassign size. */
# define resize(Ty, sz)  ((Type) {                         \
  .identifier = nameof(Ty),                                \
  .size = sz,                                              \
  .qualifier = Ty.qualifier                                \
})

/* Construct Type @Ty with @other.
   Overwriting every member except for @identifier. */
# define retype(Ty, other)  ((Type) {                      \
  .identifier = nameof(Ty),                                \
  .size = other.size,                                      \
  .qualifier = Ty.qualifier                                \
})

# define qualify(Ty, quality)  ((Type) {                   \
  .identifier = Ty.identifier,                             \
  .size = Ty.size,                                         \
  .qualifier = ((Ty.qualifier) | (quality))                \
})

# define long(Ty)       (qualify(Ty, (1 << 0)))
# define short(Ty)      (qualify(Ty, (1 << 1)))
# define unsigned(Ty)   (qualify(Ty, (1 << 2)))
# define pointer(Ty)    (qualify(Ty, (1 << 3)))
# define restrict(Ty)   (qualify(Ty, (1 << 4)))
# define function(Ty)   (qualify(Ty, (1 << 5)))
# define variadic(Ty)   (qualify(Ty, (1 << 6)))
# define constant(Ty)   (qualify(Ty, (1 << 7)))
# define statical(Ty)   (qualify(Ty, (1 << 8)))
# define register(Ty)   (qualify(Ty, (1 << 9)))
# define volatile(Ty)   (qualify(Ty, (1 << 10)))
# define complex(Ty)    (qualify(Ty, (1 << 11)))
# ifdef ORA_PROC
#  define imaginary(Ty)  (qualify(Ty, (Ty.qualifier << 12)))
# endif  /* ORA_PROC */

DEFTYPE(TType, sizeof(Type));

/////////////////// FUNDAMENTAL TYPES /////////////////////
//------------------// SIGNED DATA //--------------------//
DEFTYPE(TInt8, sizeof(int8_t));
DEFTYPE(TInt16, sizeof(int16_t));
DEFTYPE(TInt32, sizeof(int32_t));
DEFTYPE(TInt64, sizeof(int64_t));

DEFTYPE(TFastInt8, sizeof(int_fast8_t));
DEFTYPE(TFastInt16, sizeof(int_fast16_t));
DEFTYPE(TFastInt32, sizeof(int_fast32_t));
DEFTYPE(TFastInt64, sizeof(int_fast64_t));

DEFTYPE(TLeastInt8, sizeof(int_least8_t));
DEFTYPE(TLeastInt16, sizeof(int_least16_t));
DEFTYPE(TLeastInt32, sizeof(int_least32_t));
DEFTYPE(TLeastInt64, sizeof(int_least64_t));

DEFTYPE(TIntMax, sizeof(intmax_t));
DEFTYPE(TIntPtr, sizeof(intptr_t));

//-----------------// UNSIGNED DATA //-------------------//
DEFTYPE(TUInt8, sizeof(uint8_t));
DEFTYPE(TUInt16, sizeof(uint16_t));
DEFTYPE(TUInt32, sizeof(uint32_t));
DEFTYPE(TUInt64, sizeof(uint64_t));

DEFTYPE(TUFastInt8, sizeof(uint_fast8_t));
DEFTYPE(TUFastInt16, sizeof(uint_fast16_t));
DEFTYPE(TUFastInt32, sizeof(uint_fast32_t));
DEFTYPE(TUFastInt64, sizeof(uint_fast64_t));

DEFTYPE(TULeastInt8, sizeof(uint_least8_t));
DEFTYPE(TULeastInt16, sizeof(uint_least16_t));
DEFTYPE(TULeastInt32, sizeof(uint_least32_t));
DEFTYPE(TULeastInt64, sizeof(uint_least64_t));

DEFTYPE(TUIntMax, sizeof(uintmax_t));
DEFTYPE(TUIntPtr, sizeof(uintptr_t));

///////////////////// C-STYLE TYPES ///////////////////////
DEFTYPE(TVoid, sizeof(void));
DEFTYPE(TBool, sizeof(bool));
DEFTYPE(TFloat, sizeof(float));
DEFTYPE(TDouble, sizeof(double));
DEFTYPE(TLongDouble, sizeof(long double));

//------------------// SIGNED DATA //--------------------//
DEFTYPE(TChar, sizeof(char));
DEFTYPE(TShort, sizeof(short int));
DEFTYPE(TInt, sizeof(int));
DEFTYPE(TLong, sizeof(long int));
DEFTYPE(TLongLong, sizeof(long long int));

DEFTYPE(TCChar, sizeof(char _Complex));
DEFTYPE(TCShort, sizeof(short int _Complex));
DEFTYPE(TCInt, sizeof(int _Complex));
DEFTYPE(TCLong, sizeof(long int _Complex));
DEFTYPE(TCLongLong, sizeof(long long int _Complex));

/* For type _Imaginary.  Only implemented by Oracle C compiler.
   https://en.cppreference.com/w/c/numeric/complex/imaginary */
# ifdef ORA_PROC
DEFTYPE(TIChar, sizeof(char _Imaginary));
DEFTYPE(TIShort, sizeof(short int _Imaginary));
DEFTYPE(TIInt, sizeof(int _Imaginary));
DEFTYPE(TILong, sizeof(long int _Imaginary));
DEFTYPE(TILongLong, sizeof(long long int _Imaginary));
# endif  /* ORA_PROC */

//-----------------// UNSIGNED DATA //-------------------//
DEFTYPE(TUChar, sizeof(unsigned char));
DEFTYPE(TUShort, sizeof(unsigned short int));
DEFTYPE(TUInt, sizeof(unsigned int));
DEFTYPE(TULong, sizeof(unsigned long int));
DEFTYPE(TULongLong, sizeof(unsigned long long int));

DEFTYPE(TUCChar, sizeof(unsigned char _Complex));
DEFTYPE(TUCShort, sizeof(unsigned short int _Complex));
DEFTYPE(TUCInt, sizeof(unsigned int _Complex));
DEFTYPE(TUCLong, sizeof(unsigned long int _Complex));
DEFTYPE(TUCLongLong, sizeof(unsigned long long int _Complex));

# ifdef ORA_PROC
DEFTYPE(TUIChar, sizeof(unsigned char _Imaginary));
DEFTYPE(TUIShort, sizeof(unsigned short int _Imaginary));
DEFTYPE(TUIInt, sizeof(unsigned int _Imaginary));
DEFTYPE(TUILong, sizeof(unsigned long int _Imaginary));
DEFTYPE(TUILongLong, sizeof(unsigned long long int _Imaginary));
# endif  /* ORA_PROC */

int Type_Interpret(Type *inst, char const *restrict str_expr);
int Type_Literalise(Type *inst, char const *buff);

#endif  /* COMPOUND_TYPE_H */
