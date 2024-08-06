#include <Compound/memman.h>

Status Memory_Create(Memory *inst, size_t size)
{
  nonull(inst, apply(UnavailableInstance));
  
  *inst = (Memory) {
    .addr = NULL,
    .size = size,
    .alive = false
  };
  
  /* Setting literalisation handler. */
  inst->Literalise = Literalise;
  
  return apply(NormalStatus);
}

Status Memory_Allocate(Memory *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(inst->alive, apply(InstanceStillAlive));
  
  /* When failed on allocating. */
  state(!(inst->addr = malloc(inst->size)), apply(InsufficientMemory));
  inst->alive = true;
  
  return apply(NormalStatus);
}

Status Memory_Reallocate(Memory *inst, size_t size)
{
  nonull(inst, apply(UnavailableBuffer));
  state(!inst->alive, apply(InstanceNotAlive));
  
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
  state(!inst->alive,
    apply(error(InstanceNotAlive, "Cannot release a non-alive instance.")));

  free(inst->addr);
  inst->alive = false;

  return apply(NormalStatus);
}

Status Memory_Delete(Memory *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(inst->alive,
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
          && inst->alive == other->alive);
}
