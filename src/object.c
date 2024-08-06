#include <Compound/object.h>
#include <Compound/status.h>

Status Object_Create(Object *inst, Type(?) type, Var(?) data)
{
  nonull(inst, apply(UnavailableInstance));
  state(!ObjectUtils_IsAlive(inst), apply(InstanceNotAlive));
  
  
}
