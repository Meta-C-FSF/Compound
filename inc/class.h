#ifndef COMPOUND_CLASS_H
# define COMPOUND_CLASS_H

# include <Compound/access_permission_qualifier.h>
# include <Compound/array.h>
# include <Compound/class_constructor.h>
# include <Compound/class_field.h>
# include <Compound/class_method.h>
# include <Compound/common.h>
# include <Compound/lifespan_qualifier.h>
# include <Compound/status.h>

# define class(AccessPermissionQualifier, LifespanQualifier, identity, block)  \
  {                                                                            \
    Class _c = EMPTY;                                                          \
    Class *THIS = &_c;                                                         \
    fail(Class_Create(&_c, AccessPermissionQualifier, LifespanQualifier,       \
                      nameof(identity)));                                      \
    block                                                                      \
    fail(ClassRegister_Insert(cr, cr->length, *THIS));                         \
  }

#define field(AccessPermissionQualifier, LifespanQualifier, type, identity)    \
  fail(Class_AddField(THIS, ({                                                 \
    ClassField _f = EMPTY;                                                     \
    fail(ClassField_Create(&_f, AccessPermissionQualifier, LifespanQualifier,  \
                           type, identity));                                   \
    _f;                                                                        \
  })))

# define method(AccessPermissionQualifier, LifespanQualifier, rtn, identity,   \
                block, fmt, ...)                                               \
  fail(Class_AddMethod(THIS, ({                                                \
    ClassMethod _m = EMPTY;                                                    \
    fail(ClassMethod_Create(&_m, AccessPermissionQualifier, LifespanQualifier, \
                            rtn, identity, nameof(block), fmt, __VA_ARGS__));  \
    _m;                                                                        \
  })))

# define constructor(AccessPermissionQualifier, block, fmt, ...)               \
  fail(Class_AddConstructor(THIS, ({                                           \
    ClassConstructor _x = EMPTY;                                               \
    fail(ClassConstructor_Create(&_x, AccessPermissionQualifier, nameof(block),\
                                 fmt, __VA_ARGS__));                           \
    _x;                                                                        \
  })))

# define CLASS_IDENTITY_LENGTH_MAXIMUM  64

typedef struct _Class {
  ClassMethod(bool, Class *) Equals;
  ClassMethod(char *, void) Literalise;

  char identity[CLASS_IDENTITY_LENGTH_MAXIMUM];

  Type type;

  Array(Class *)  implementations;
  Array(ClassField)  fields;
  Array(ClassMethod)  methods;
  Array(ClassConstructor)  constructors;

  struct _Class *super;
  struct _Class *self;

  AccessPermissionQualifier perm;
  LifespanQualifier lfspn;
} Class;

DEFTYPE(TClass, sizeof(Class));

Status Class_Create(Class *inst, const AccessPermissionQualifier perm,
                    const LifespanQualifier lfspn, const char *identity);
Status Class_CopyOf(Class *inst, const Class other);
Status Class_Delete(Class *inst);
bool   Class_Equals(const Class class1, const Class class2);
/* Translate @buff into Class @inst. */
Status Class_Encode(Class *inst, char *buff);
/* Translate @inst into readable content, stored in @buff. */
Status Class_Decode(Class *inst, const char *buff);

Status Class_AddField(Class *inst, const ClassField field);
Status Class_AddMethod(Class *inst, const ClassMethod method);
Status Class_AddConstructor(Class *inst, const ClassConstructor constructor);

Status Class_CallMethod(Class *inst, const ClassMethod method);
Status Class_CallConstructor(Class *inst, const ClassConstructor constructor);

Status Class_FindField(Class *inst, const ClassField field);
Status Class_FindMethod(Class *inst, const ClassMethod method);
Status Class_FindConstructor(Class *inst, const ClassConstructor constructor);

Status Class_Literalise(Class *inst, char *buff);

DEFSTATUS(InvalidClassIdentity, 1,
  "Given class identity is invalid.",
  STATUS_ERROR, &InvalidObject);

#endif  /* COMPOUND_CLASS_H */
