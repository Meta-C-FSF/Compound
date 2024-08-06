#ifndef COMPOUND_OBJECT_H
# define COMPOUND_OBJECT_H

# include <Compound/array.h>
# include <Compound/common.h>
# include <Compound/constructor.h>
# include <Compound/destructor.h>
# include <Compound/literary.h>
# include <Compound/status.h>
# include <Compound/type.h>

typedef struct {
  LITERALISE;
  Type(?) type;
  Var(?) data;
} Object;

Status Object_Create(Object *inst, Type(?) type, Var(?) data);
Status Object_CopyOf(Object *inst, Object *other);
Status Object_Delete(Object *inst);
Status Object_Clone(Object *inst, const Object *other);
Status Object_Literalise(Object *inst, char *buff);
bool   ObjectUtils_Equal(Object *inst, Object *other);

typedef struct {
  union {
    Object target;
  };
  Array(constructor_t) Constructors;
  Array(destructor_t)  Destructors;
  bool target_alive;
} Builder;

static bool ObjectUtils_IsAlive(Object *inst)
{
  nonull(inst, false);
  
  return ((Builder *)inst)->target_alive;
}

Status Object_Construct(Var(Object) *inst, Var(Array(char *)) *param);
Status Object_Destruct(Object *inst);

#endif  /* COMPOUND_OBJECT_H */
