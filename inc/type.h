#ifndef COMPOUND_TYPE_H
# define COMPOUND_TYPE_H

# include <string.h>
# include <stdint.h>

# include <Compound/common.h>
# include <Compound/status.h>

typedef struct {
  char *identifier;
  size_t size;
  unsigned int qualifier;
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
# define REDEFTYPE(Ty, other)  static const Type Ty = (retype(Ty, (other)));

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
  .qualifier = other.qualifier                             \
})

# define qualify(Ty, quality)  ((Type) {                   \
  .identifier = Ty.identifier,                             \
  .size = Ty.size,                                         \
  .qualifier = ((Ty.qualifier) | (quality))                \
})

# define wide(Ty)  resize((Ty), ((Ty).size * 2))
# define narrow(Ty)  resize((Ty), ((Ty).size / 2))

# define long(Ty)       (wide(qualify(Ty, (1 << 0))))
# define short(Ty)      (narrow(qualify(Ty, (1 << 1))))
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

REDEFTYPE(TUInt8, unsigned(TInt8));
REDEFTYPE(TUInt16, unsigned(TInt16));
REDEFTYPE(TUInt32, unsigned(TInt32));
REDEFTYPE(TUInt64, unsigned(TInt64));
REDEFTYPE(TUFastInt8, unsigned(TFastInt8));
REDEFTYPE(TUFastInt16, unsigned(TFastInt16));
REDEFTYPE(TUFastInt32, unsigned(TFastInt32));
REDEFTYPE(TUFastInt64, unsigned(TFastInt64));
REDEFTYPE(TULeastInt8, unsigned(TLeastInt8));
REDEFTYPE(TULeastInt16, unsigned(TLeastInt16));
REDEFTYPE(TULeastInt32, unsigned(TLeastInt32));
REDEFTYPE(TULeastInt64, unsigned(TLeastInt64));
REDEFTYPE(TUIntMax, unsigned(TIntMax));
REDEFTYPE(TUIntPtr, unsigned(TIntPtr));

DEFTYPE(TVoid, 1);
DEFTYPE(TBool, sizeof(bool));
DEFTYPE(TFloat, sizeof(float));
DEFTYPE(TDouble, sizeof(double));
DEFTYPE(TChar, sizeof(char));
DEFTYPE(TShort, sizeof(short int));
DEFTYPE(TInt, sizeof(int));

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

DEFSTATUS(TypeError, 1,
  "A Type replated error had occurred.",
  STATUS_ERROR, &ErrorStatus);

DEFSTATUS(InvalidType, 1,
  "Given Type is not supported.",
  STATUS_ERROR, &InvalidObject);

DEFSTATUS(InvalidTypeQualifierUsage, 1,
  "Given object has an invalid Type qualifier combination.",
  STATUS_ERROR, &TypeError);

DEFSTATUS(NonPointerButRestrict, 1,
  "The Type qualifier wrongly uses 'restrict' without 'pointer'.",
  STATUS_ERROR, &InvalidTypeQualifierUsage);

DEFSTATUS(NonFunctionButVariadic, 1,
  "The Type qualifier wrongly uses 'variadic' without 'function'.",
  STATUS_ERROR, &InvalidTypeQualifierUsage);

DEFSTATUS(NonPointerButFunction, 1,
  "The Type qualifier wrongly uses 'function' without 'pointer'.",
  STATUS_ERROR, &InvalidTypeQualifierUsage);

DEFSTATUS(BothLongAndShort, 1,
  "The Type qualifier wrongly uses 'long' with 'short'.",
  STATUS_ERROR, &InvalidTypeQualifierUsage);

DEFSTATUS(BothConstantAndVolatile, 1,
  "The Type qualifier wrongly uses 'constant' with 'volatile'.",
  STATUS_ERROR, &InvalidTypeQualifierUsage);

DEFSTATUS(BothConstantAndRegister, 1,
  "The Type qualifier wrongly uses 'constant' with 'register'.",
  STATUS_ERROR, &InvalidTypeQualifierUsage);

DEFSTATUS(BothStaticAndRegister, 1,
  "The Type qualifier wrongly uses 'static' with 'register'.",
  STATUS_ERROR, &InvalidTypeQualifierUsage);

# ifndef ORA_PROC
DEFSTATUS(TypeImaginaryIsUnsupported, 1,
  "Imaginary Type is not supported.",
  STATUS_ERROR, &InvalidType);
# endif  /* ORA_PROC */

static inline bool Type_Equals(Type ty1, Type ty2)
{
  /* Returns true when either Type is NULL, regardless the nullities. */
  if (!ty1.identifier) {
    return (ty1.identifier == ty2.identifier);
  }
  
  return (
    (!strcmp(ty1.identifier, ty2.identifier)) &&
    ty1.size == ty2.size &&
    ty1.qualifier == ty2.qualifier
  );
}

#endif  /* COMPOUND_TYPE_H */
