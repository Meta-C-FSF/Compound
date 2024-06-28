#include <Compound/status.h>
#include <Compound/var.h>

Status Var_Create(Var *inst, size_t size)
{
  nonull(inst, apply(UnavailableInstance));
  state(inst->alive, apply(InstanceStillAlive));
  state(!size,
    apply(normal(NormalStatus, "Exited with given parameter size as ZERO.")));
  
  state(((inst->addr = malloc(size)) == NULL), apply(InsufficientMemory));
  inst->size = size;
  inst->alive = true;
  
  return apply(NormalStatus);
}

Status Var_CopyOf(Var *inst, Var *other)
{
  /* Skip when inst or other is unavailable. */
  nonull(inst, apply(UnavailableInstance));
  state(inst->alive, apply(InstanceStillAlive));
  nonull(other, apply(InvalidParameter));
  
  /* Copy members from other.  Only has to apply size, no addr is needed. */
  state(!((inst->addr = malloc(other->size))), apply(InsufficientMemory));
  inst->size = other->size;
  inst->alive = true;
  
  return apply(NormalStatus);
}

Status Var_Delete(Var *inst)
{
  nonull(!inst, apply(UnavailableInstance));
  state(!inst->alive, apply(InstanceNotAlive));
  
  free(inst->addr);
  inst->alive = false;
  inst->addr = NULL;
  inst->size = 0;
  
  return apply(NormalStatus);
}

Status Var_Literalise(Var *inst, char *buff)
{
  /* Skip when inst is unavailable. */
  state(!inst, apply(UnavailableInstance));
  
  /* Write into buffer. */
  state(!sprintf(buff, VAR_LITERALISE_FORMAT"\n", inst->addr, inst->size),
        apply(
          error(RuntimeError, "Sprintf returned 0 where it should never do.")));
  
  return apply(NormalStatus);
}

bool Var_Equals(Var *a, Var *b)
{
  /* Skip unavailable inst and invalid param. */
  state((!a || !b), false);
  
  return (a->addr == b->addr && a->size == b->size);
}

void VarUtils_Swap(Var *v1, Var *v2)
{
  /* Skip when v1 or v2 is unavailable. */
  svoid(!v1 || !v2);
  
  Var v3 = *v1;
  *v1 = *v2;
  *v2 = v3;
}
