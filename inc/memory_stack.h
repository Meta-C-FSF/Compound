#ifndef COMPOUND_MEMORY_STACK_H
# define COMPOUND_MEMORY_STACK_H

# include <Compound/memory.h>
# include <Compound/stack.h>

typedef struct {
  Memory *data;
  size_t length;
  Memory *current;
} MemoryStack;

DEFTYPE(TMemoryStack, sizeof(MemoryStack));

/* Shorthand for declaring MemoryStack @ms in function.
   "MREG" stands for "MemoryStack Register". */
# define MREG  MemoryStack *ms

Status MemoryStack_Create(MemoryStack *inst, const size_t length);
Status MemoryStack_CopyOf(MemoryStack *inst, const MemoryStack *other);
Status MemoryStack_Delete(MemoryStack *inst);
Status MemoryStack_Push(MemoryStack *inst, const Memory elem);
Status MemoryStack_Pop(MemoryStack *inst);
void   MemoryStack_PopAll(MemoryStack *inst);
bool   MemoryStack_Full(MemoryStack mstk);
bool   MemoryStack_Empty(MemoryStack mstk);
size_t MemoryStack_Offset(MemoryStack mstk);

static MemoryStack *GlobalMemoryStack = NULL;

static inline void MemoryStack_SetGlobal(MemoryStack *inst)
{
  svoid(!inst);

  GlobalMemoryStack = inst;
}

#endif  /* COMPOUND_MEMORY_STACK_H */
