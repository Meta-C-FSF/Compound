#ifndef COMPOUND_CLASS_FIELD_H
# define COMPOUND_CLASS_FIELD_H

# include <Compound/access_permission_qualifier.h>
# include <Compound/array.h>
# include <Compound/lifespan_qualifier.h>
# include <Compound/status.h>
# include <Compound/memory.h>
# include <Compound/type.h>

# define CLASS_FIELD_IDENTITY_LENGTH_MAX  64

typedef struct {
  AccessPermissionQualifier perm;
  LifespanQualifier lfspn;
  Memory data;
  char identity[CLASS_FIELD_IDENTITY_LENGTH_MAX];
} ClassField;

DEFTYPE(TClassField, sizeof(ClassField));

Status ClassField_Create(ClassField *inst, const AccessPermissionQualifier perm,
                         const LifespanQualifier lfspn, const Memory data,
                         const char *identity);
Status ClassField_CopyOf(ClassField *inst, const ClassField other);
Status ClassField_Delete(ClassField *inst);
bool   ClassField_Equals(const ClassField field1, const ClassField field2);

#endif  /* COMPOUND_CLASS_FIELD_H */
