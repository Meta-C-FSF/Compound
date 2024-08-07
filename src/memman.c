#include <Compound/memman.h>

Status Memory_Create(Memory *inst, size_t size)
{
  nonull(inst, apply(UnavailableInstance));
  
  *inst = (Memory) {
    .addr = NULL,
    .size = size,
    .liveness = false
  };
  
  /* Setting literalisation handler. */
  inst->Literalise = Literalise;
  
  return apply(NormalStatus);
}

Status Memory_Allocate(Memory *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(inst->liveness, apply(InstanceStillAlive));
  
  /* When failed on allocating. */
  state(!(inst->addr = malloc(inst->size)), apply(InsufficientMemory));
  inst->liveness = true;
  
  return apply(NormalStatus);
}

Status Memory_Reallocate(Memory *inst, size_t size)
{
  nonull(inst, apply(UnavailableBuffer));
  state(!inst->liveness, apply(InstanceNotAlive));
  
  /* When failed on reallocating. */
  state(!(inst->addr = realloc(inst->addr, size)),
    apply(error(InsufficientMemory, "Cannot successfully reallocate.")));

  /* Update size from inst. */
  inst->size = size;

  return apply(NormalStatus);
}

Status Memory_Release(Memory *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(!inst->liveness,
    apply(error(InstanceNotAlive, "Cannot release a non-alive instance.")));

  free(inst->addr);
  inst->liveness = false;

  return apply(NormalStatus);
}

Status Memory_Delete(Memory *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(inst->liveness,
    apply(
      error(InstanceStillAlive, "Cannot deinitialise a instance still alive.")));

  inst->addr = NULL;
  inst->size = 0;
  inst = NULL;
  
  /* Setting literalisation handler. */
  inst->Literalise = NULL;

  return apply(NormalStatus);
}

bool Memory_Equals(Memory *inst, Memory *other)
{
  state(!inst || !other, false);

  return (inst->addr == other->addr
          && inst->size == other->size
          && inst->liveness == other->liveness);
}
