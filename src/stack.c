#include <Compound/stack.h>
#include <Compound/status.h>

Status Stack_Create(Stack *inst, const size_t size, const size_t length)
{
  avail(inst);
  state(!size, apply(InvalidSize));
  state(!length, apply(InvalidStackLength));
  
  state(!(inst->data = calloc(length, size)), apply(InsufficientMemory));
  inst->size = size;
  inst->length = length;
  inst->current = NULL;

  return apply(NormalStatus);
}

Status Stack_CopyOf(Stack *inst, const Stack *other)
{
  avail(inst);
  avail(other);
  state(!other->size, apply(InvalidSize));
  state(!other->length, apply(InvalidStackLength));
  
  state(!(inst->data = calloc(other->length, other->size)),
    apply(InsufficientMemory));
  inst->size = other->size;
  inst->length = other->length;
  inst->current = NULL;
  
  return apply(NormalStatus);
}

Status Stack_Delete(Stack *inst)
{
  avail(inst);
  state(!inst->data, apply(NormalStatus));

  Stack_PopAll(inst);
  
  free(inst->data);
  inst->size = 0;
  inst->length = 0;
  inst->current = NULL;
  
  return apply(NormalStatus);
}

bool Stack_Push(Stack *inst, void const *addr)
{
  nonull(inst, false);
  
  state(Stack_Full(inst), false);
  
  if (!inst->current) {
    inst->current = inst->data;
  } else {
    inst->current += inst->size;
  }
  
  inst->data[Stack_CurrentIndexer(inst)] = (void *)addr;
  
  return true;
}

bool Stack_Pop(Stack *inst)
{
  nonull(inst, false);
  
  state(Stack_Empty(inst), false);
  
  inst->data[Stack_CurrentIndexer(inst)] = NULL;
  
  if (inst->current == inst->data) {
    inst->current = NULL;
  } else {
    inst->current -= inst->size;
  }
  
  return true;
}

inline bool Stack_Full(Stack *inst)
{
  state(!inst, false);
  
  return (inst->current == (inst->data + (inst->size * inst->length)));
}

inline bool Stack_Empty(Stack *inst)
{
  state(!inst, false);
  
  return !inst->current;
}

size_t Stack_CurrentIndexer(Stack *inst)
{
  state(!inst, 0);
  state(!inst->current, 0);
  
  return ((((size_t)inst->current) - ((size_t)inst->data)) / inst->size);
}

void Stack_PopAll(Stack *inst)
{
  svoid(!inst);
  svoid(!inst->length);
  
  while (inst->current) {
    (void)Stack_Pop(inst);
  }
  
  return;
}
