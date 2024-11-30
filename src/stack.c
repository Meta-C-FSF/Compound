#include <Compound/stack.h>

Status Stack_Create(Stack *inst, const size_t size, const size_t length)
{
  avail(inst);
  state(!size, (InvalidSize));
  state(!length, (InvalidStackLength));
  
  state(!(inst->data = calloc(length, size)), (InsufficientMemory));
  inst->size = size;
  inst->length = length;
  inst->current = NULL;

  RETURN(NormalStatus);
}

Status Stack_CopyOf(Stack *inst, const Stack *other)
{
  avail(inst);
  avail(other);
  state(!other->size, (InvalidSize));
  state(!other->length, (InvalidStackLength));
  
  state(!(inst->data = calloc(other->length, other->size)),
    apply(InsufficientMemory));
  
  inst->size = other->size;
  inst->length = other->length;
  inst->current = (other->current ? (inst->data[Stack_Offset(*other)]) : NULL);
  for (register size_t i = 0; i < inst->length; i++) {
    
  }
  
  RETURN(NormalStatus);
}

Status Stack_Delete(Stack *inst)
{
  avail(inst);
  state(!inst->data, (NormalStatus));

  Stack_PopAll(inst);
  
  free(inst->data);
  inst->size = 0;
  inst->length = 0;
  inst->current = NULL;
  
  RETURN(NormalStatus);
}

bool Stack_Push(Stack *inst, void *addr)
{
  if (!inst)  return false;
  if (Stack_Full(*inst))  return false;
  
  if (!inst->current) {
    inst->current = inst->data;
  } else {
    inst->current += inst->size;
  }
  
  inst->data[Stack_Offset(*inst)] = addr;
  
  return true;
}

bool Stack_Pop(Stack *inst)
{
  if (!inst)  return false; 
  if (Stack_Empty(*inst))  return false;
  
  inst->data[Stack_Offset(*inst)] = NULL;
  
  if (inst->current == inst->data) {
    inst->current = NULL;
  } else {
    inst->current -= inst->size;
  }

  return true;
}

void Stack_PopAll(Stack *inst)
{
  svoid(!inst);
  svoid(!inst->length);
  
  while (Stack_Offset(*inst)) {
    (void)Stack_Pop(inst);
  }
}

inline bool Stack_Full(const Stack stk)
{
  return (stk.current == (stk.data + (stk.size * stk.length)));
}

inline bool Stack_Empty(const Stack stk)
{
  return !stk.current;
}

inline size_t Stack_Offset(const Stack stk)
{
  if (!stk.current)  return 0;
  
  return ((((size_t)stk.current) - ((size_t)stk.data)) / stk.size);
}

// Status Stack_Clean(Stack *inst)
// {
//   avail(inst);

//   bool occupied[inst->length];
//   for (register size_t i = 0; i < inst->length; i++) {
//     occupied[i] = inst->data[i];
//   }

//   for (register size_t i = 0; i < arrlen(occupied); i++) {
//     if (occupied[i]) {
      
//     }
//   }
// }
