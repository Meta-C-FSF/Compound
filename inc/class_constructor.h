#ifndef COMPOUND_CLASS_CONSTRUCTOR_H
# define COMPOUND_CLASS_CONSTRUCTOR_H

# include <Compound/access_permission_qualifier.h>
# include <Compound/array.h>
# include <Compound/lifespan_qualifier.h>
# include <Compound/status.h>
# include <Compound/type.h>

# define CLASS_CONSTRUCTOR_IDENTITY_LENGTH_MAXIMUM  64

typedef struct {
  AccessPermissionQualifier perm;
  LifespanQualifier lfspn;
  char identity[CLASS_CONSTRUCTOR_IDENTITY_LENGTH_MAXIMUM];
} ClassConstructor;

Status ClassConstructor_Create(ClassConstructor *inst,
                               const AccessPermissionQualifier perm,
                               const char *content, const char *fmt, ...);
Status ClassConstructor_CopyOf(ClassConstructor *inst,
                               const ClassConstructor other);
Status ClassConstructor_Delete(ClassConstructor *inst);
bool   ClassConstructor_Equals(const ClassConstructor constr1,
                               const ClassConstructor constr2);

/* Based on given @identity, writes processed string into @buff. */
Status ClassConstructor_GenerateIdentity(char *buff, const char *signature);

#endif  /* COMPOUND_CLASS_CONSTRUCTOR_H */
