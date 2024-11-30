#ifndef COMPOUND_CLASS_METHOD_H
# define COMPOUND_CLASS_METHOD_H

# include <stdarg.h>

# include <Compound/access_permission_qualifier.h>
# include <Compound/array.h>
# include <Compound/class_field.h>
# include <Compound/lifespan_qualifier.h>
# include <Compound/status.h>
# include <Compound/type.h>

# define CLASS_METHOD_IDENTITY_LENGTH_MAXIMUM  64

typedef struct {
  char identity[CLASS_METHOD_IDENTITY_LENGTH_MAXIMUM];
  Type rtn;
  va_list ap;
  AccessPermissionQualifier perm;
  LifespanQualifier lfspn;
  char *content;
  char *fmt;
  unsigned int numeral_identity;
} ClassMethod;

DEFTYPE(TClassMethod, sizeof(ClassMethod));

# define ClassMethod(rtn, param, ...)  ClassMethod

Status ClassMethod_Create(ClassMethod *inst, const AccessPermissionQualifier perm,
                          const LifespanQualifier lfspn, const Type rtn,
                          const char *identity, const char *content,
                          const char *fmt, ...);
Status ClassMethod_CopyOf(ClassMethod *inst, const ClassMethod other);
Status ClassMethod_Delete(ClassMethod *inst);
bool   ClassMethod_Equals(const ClassMethod method1, const ClassMethod method2);
Status ClassMethod_Override(ClassMethod *inst, const char *content);
/* Takes @fmt as input, returns total amount of items being described. */
size_t ClassMethod_ParamLength(const char *fmt);
Status ClassMethod_Export(const ClassMethod method, FILE *dst);

#endif  /* COMPOUND_CLASS_METHOD_H */
