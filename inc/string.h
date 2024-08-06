#ifndef COMPOUND_STRING_H
# define COMPOUND_STRING_H

# include <complex.h>
# include <wchar.h>

# include <Compound/char.h>
# include <Compound/array.h>

// typedef enum {
//   ASCII,
//   UTF8,
//   /* etc. */
// } StringEncoding;

/* Conventional character array string. */
typedef Array(Char) String;

Status String_Create(String *inst, size_t width, int len);
Status String_CopyOf(String *inst, String *other);
Status String_Delete(String *inst);
// Status String_Encode(String *inst, StringEncoding encoding);
// Status String_Decode(String *inst, StringEncoding encoding);
Status String_Format(String *inst, String *store, const String *fmt, ...);
Status String_Literalise(String *inst, String *store);

Status StringUtils_FromInteger(String *inst, int value, int base);
Status StringUtils_FromShortInteger(String *inst, short int value, int base);
Status StringUtils_FromLongInteger(String *inst, long int value, int base);
Status StringUtils_FromLongLongInteger(String *inst, long long int value, int base);
Status StringUtils_FromFloat(String *inst, float value, int base);
Status StringUtils_FromDouble(String *inst, double value, int base);
Status StringUtils_FromLongDouble(String *inst, long double value, int base);
Status StringUtils_FromComplexInteger(String *inst, _Complex int value, int base);
Status StringUtils_FromComplexShortInteger(String *inst, _Complex short int value, int base);
Status StringUtils_FromComplexLongInteger(String *inst, _Complex long int value, int base);
Status StringUtils_FromComplexLongLongInteger(String *inst, _Complex long long value, int base);
Status StringUtils_FromComplexFloat(String *inst, _Complex float value, int base);
Status StringUtils_FromComplexDouble(String *inst, _Complex double value, int base);
Status StringUtils_FromComplexLongDouble(String *inst, _Complex long double value, int base);
Status StringUtils_FromUnsignedInteger(String *inst, unsigned int value, int base);
Status StringUtils_FromUnsignedShortInteger(String *inst, unsigned short int value, int base);
Status StringUtils_FromUnsignedLongInteger(String *inst, unsigned long int value, int base);
Status StringUtils_FromUnsignedLongLongInteger(String *inst, unsigned long long int value, int base);
Status StringUtils_FromUnsignedComplexInteger(String *inst, unsigned _Complex int value, int base);
Status StringUtils_FromUnsignedComplexShortInteger(String *inst, unsigned _Complex short int value, int base);
Status StringUtils_FromUnsignedComplexLongInteger(String *inst, unsigned _Complex long int value, int base);
Status StringUtils_FromUnsignedComplexLongLongInteger(String *inst, unsigned _Complex long long value, int base);
Status StringUtils_FromAddress(String *inst, void *store);
Status StringUtils_FromCharBuff(String *inst, char const *buff);
Status StringUtils_FromWideCharBuff(String *inst, wchar_t const *buff);
Status StringUtils_FromCharSeq(String *inst, const CharSeq *buff);
Status StringUtils_ToInteger(String *inst, int *store, int base);
Status StringUtils_ToShortInteger(String *inst, short int *store, int base);
Status StringUtils_ToLongInteger(String *inst, long int *store, int base);
Status StringUtils_ToLongLongInteger(String *inst, long long int *store, int base);
Status StringUtils_ToFloat(String *inst, float *store, int base);
Status StringUtils_ToDouble(String *inst, double *store, int base);
Status StringUtils_ToLongDouble(String *inst, long double *store, int base);
Status StringUtils_ToComplexInteger(String *inst, _Complex int *store, int base);
Status StringUtils_ToComplexShortInteger(String *inst, _Complex short int *store, int base);
Status StringUtils_ToComplexLongInteger(String *inst, _Complex long int *store, int base);
Status StringUtils_ToComplexLongLongInteger(String *inst, _Complex long long *store, int base);
Status StringUtils_ToComplexFloat(String *inst, _Complex float *store, int base);
Status StringUtils_ToComplexDouble(String *inst, _Complex double *store, int base);
Status StringUtils_ToUnsignedInteger(String *inst, unsigned int *store, int base);
Status StringUtils_ToUnsignedShortInteger(String *inst, unsigned short int *store, int base);
Status StringUtils_ToUnsignedLongInteger(String *inst, unsigned long int *store, int base);
Status StringUtils_ToUnsignedLongLongInteger(String *inst, unsigned long long int *store, int base);
Status StringUtils_ToUnsignedComplexInteger(String *inst, unsigned _Complex int *store, int base);
Status StringUtils_ToUnsignedComplexShortInteger(String *inst, unsigned _Complex short int *store, int base);
Status StringUtils_ToUnsignedComplexLongInteger(String *inst, unsigned _Complex long int *store, int base);
Status StringUtils_ToUnsignedComplexLongLongInteger(String *inst, unsigned _Complex long long *store, int base);
Status StringUtils_ToAddress(String *inst, void **store);
Status StringUtils_ToCharBuff(String *inst, char const *store);
Status StringUtils_ToWideCharBuff(String *inst, wchar_t const *store);
Status StringUtils_ToCharSeq(String *inst, const CharSeq *store);
Status StringUtils_Tokenise(String *inst, const String *delim, String *store);
Status StringUtils_Concatenate(String *inst, String *other);
Status StringUtils_Split(String *inst, String *store);
bool   StringUtils_IsBlank(String *inst);
int    StringUtils_Compare(String *a, String *b);

#endif  /* COMPOUND_STRING_H */
