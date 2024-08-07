#include <Compound/status.h>
#include <Compound/var.h>

Status Var_Create(liveness(DEAD, Var) *inst, size_t size, literalisation_t lit)
{
  nonull(inst, apply(UnavailableInstance));
  state(inst->liveness, apply(InstanceStillAlive));
  state(!size, apply(InvalidSize));

  inst->size = size;
  inst->liveness = false;
  inst->Literalise = (!lit ? Literalise : lit);
  
  return apply(NormalStatus);
}

Status Var_Allocate(liveness(DEAD, Var) *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(inst->liveness, apply(InstanceStillAlive));
  
  state((!(inst->addr = malloc(inst->size))), apply(InsufficientMemory));
  inst->liveness = true;
  
  return apply(NormalStatus);
}

Status Var_Reallocate(liveness(ALIVE, Var) *inst, size_t size)
{
  nonull(inst, apply(UnavailableInstance));
  state(!inst->liveness, apply(InstanceNotAlive));
  
  state((!(inst->addr = realloc(inst->addr, size))), apply(InsufficientMemory));
  
  return apply(NormalStatus);
}

Status Var_Release(liveness(ALIVE, Var) *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(!inst->liveness, apply(InstanceNotAlive));
  
  free(inst->addr);
  inst->addr = NULL;
  inst->liveness = false;
  
  return apply(NormalStatus);
}

Status Var_CopyOf(liveness(DEAD, Var) *inst, liveness(ALIVE, Var) *other)
{
  /* Skip when inst or other is unavailable. */
  nonull(inst, apply(UnavailableInstance));
  state(inst->liveness, apply(InstanceStillAlive));
  nonull(other, apply(InvalidParameter));
  
  /* Copy members from other.  Only has to apply size, no addr is needed. */
  state(!((inst->addr = malloc(other->size))), apply(InsufficientMemory));
  inst->size = other->size;
  inst->liveness = true;
  
  return apply(NormalStatus);
}

Status Var_Delete(liveness(DEAD, Var) *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(inst->liveness,
    apply(annot(InstanceStillAlive,
      "Please ensure the instance is released before pushing to delete.")));

  inst->size = 0;
  inst->liveness = false;  // Enforce the @alive value to be false.
  inst->Literalise = NULL;
  inst = NULL;
  
  return apply(NormalStatus);
}

Status Var_Literalise(liveness(ALIVE, Var) *inst, char *buff)
{
  /* Skip when inst is unavailable. */
  state(!inst, apply(UnavailableInstance));
  
  /* Write into buffer. */
  state(
    !snprintf(buff, LITERALISATION_LENGTH_MAXIMUM, VAR_LITERALISE_FORMAT,
      inst->addr, inst->size),
    apply(error(RuntimeError, "Sprintf returned 0 where it should never do.")));
  
  return apply(NormalStatus);
}

bool Var_Equals(liveness(ALIVE, Var) *a, liveness(ALIVE, Var) *b)
{
  /* Skip unavailable inst and invalid param. */
  state((!a || !b), false);
  
  return (a->addr == b->addr && a->size == b->size);
}

void VarUtils_Swap(liveness(ALIVE, Var) *v1, liveness(ALIVE, Var) *v2)
{
  /* Skip when v1 or v2 is unavailable. */
  svoid(!v1 || !v2);
  
  Var v3 = *v1;
  *v1 = *v2;
  *v2 = v3;
}
