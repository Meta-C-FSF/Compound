#include <Compound/memory.h>

Memory Allocate(Type type, size_t quantity)
{
  return (Memory) {
    .addr = calloc((!quantity ? (1) : quantity), type.size),
    .type = type,
    .stack = NULL
  };
}

Memory Reallocate(Memory mem, Type type)
{
  return (Memory) {
    .addr = realloc(mem.addr, type.size),
    .type = type,
    .stack = NULL
  };
}

void Release(Memory mem)
{
  free(mem.addr);
}

Status Memory_Create(Memory *inst, Type type, Stack *stack)
{
  avail(inst);
  state(alive(*inst), apply(InstanceStillAlive));
  avail(stack);
  
  /* Preserve in @stack. */
  state(Stack_Full(stack), apply(StackFull));
  
  /* Allocate for @inst. */
  *inst = Allocate(type, 0);
  
  /* Register in @stack. */
  state(!Stack_Push(stack, inst->addr),
    apply(annot(StackError, "Failed to push.")));
  
  return apply(NormalStatus);
}

Status Memory_CopyOf(Memory *inst, Memory *other)
{
  avail(inst);
  state(alive(*inst), apply(InstanceStillAlive));
  avail(other);
  state(!alive(*other), apply(SourceNotAlive));
  
  *inst = *other;
  
  return apply(NormalStatus);
}

Status Memory_Delete(Memory *inst)
{
  avail(inst);
  state(!alive(*inst), apply(InstanceNotAlive));
  
  /* Release. */
  Release(*inst);
  
  inst->addr = NULL;
  inst->type = (Type)EMPTY;
  inst->stack = NULL;
  
  return apply(NormalStatus);
}

void Swap(Memory *inst, Memory *other)
{
  svoid(!inst);
  svoid(!other);
  
  Memory mem = *inst;
  *inst = *other;
  *other = mem;
}
