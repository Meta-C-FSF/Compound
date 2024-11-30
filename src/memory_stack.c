#include <Compound/memory_stack.h>

Status MemoryStack_Create(MemoryStack *inst, const size_t length)
{
  avail(inst);
  state(!length, (InvalidStackLength));
  
  state(!(inst->data = calloc(length, sizeof(Memory))),
    apply(InsufficientMemory));
  
  (void)memset(inst->data, 0, inst->length);

  inst->length = length;
  inst->current = NULL;

  RETURN(NormalStatus);
}

Status MemoryStack_CopyOf(MemoryStack *inst, const MemoryStack *other)
{
  avail(inst);
  avail(other);
  state(!other->length, (InvalidStackLength));
  
  state(!(inst->data = calloc(other->length, sizeof(Memory))),
    apply(InsufficientMemory));
  inst->length = other->length;
  inst->current = NULL;
  
  RETURN(NormalStatus);
}

Status MemoryStack_Delete(MemoryStack *inst)
{
  avail(inst);
  state(!inst->data, (InstanceNotAlive));
  
  MemoryStack_PopAll(inst);
  
  free(inst->data);
  inst->length = 0;
  inst->current = NULL;
  
  RETURN(NormalStatus);
}

Status MemoryStack_Push(MemoryStack *inst, const Memory elem)
{
  avail(inst);
  state(MemoryStack_Full(*inst), (StackFull));
  
  if (!inst->current) {
    inst->current = inst->data;
  } else {
    inst->current += sizeof(Memory);
  }
  
  inst->data[MemoryStack_Offset(*inst)] = elem;
  
  RETURN(NormalStatus);
}

Status MemoryStack_Pop(MemoryStack *inst)
{
  avail(inst);  
  state(MemoryStack_Empty(*inst), (StackEmpty));

  Memory_Release(inst->data[MemoryStack_Offset(*inst)]);
  
  if (inst->current == inst->data) {
    inst->current = NULL;
  } else {
    inst->current -= sizeof(Memory);
  }
  
  RETURN(NormalStatus);
}

void MemoryStack_PopAll(MemoryStack *inst)
{
  svoid(!inst);
  svoid(!inst->length);

  while (inst->current) {
    (void)MemoryStack_Pop(inst);
  }
}

inline bool MemoryStack_Full(MemoryStack mstk)
{
  return (MemoryStack_Offset(mstk) >= (mstk.length - 1));
}

inline bool MemoryStack_Empty(MemoryStack mstk)
{
  return !mstk.current;
}

inline size_t MemoryStack_Offset(MemoryStack mstk)
{
  if (!mstk.current)  return 0;

  return (mstk.current - mstk.data) / sizeof(Memory);
}
