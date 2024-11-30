#ifndef COMPOUND_STATUS_STACK_H
# define COMPOUND_STATUS_STACK_H

# include <Compound/status.h>
# include <Compound/stack.h>

typedef struct {
  Status *data;
  size_t length;
  Status *current;
} StatusStack;

DEFTYPE(TStatusStack, sizeof(StatusStack));

/* Shorthand for declaring StatusStack @ss in function.
   "SREG" stands for "StatusStack Register". */
# define SREG  StatusStack *ss

Status StatusStack_Create(StatusStack *inst, const size_t length);
Status StatusStack_CopyOf(StatusStack *inst, const StatusStack *other);
Status StatusStack_Delete(StatusStack *inst);
Status StatusStack_Push(StatusStack *inst, const Status elem);
Status StatusStack_Pop(StatusStack *inst);
void   StatusStack_PopAll(StatusStack *inst);
bool   StatusStack_Full(StatusStack mstk);
bool   StatusStack_Empty(StatusStack mstk);
size_t StatusStack_Offset(StatusStack mstk);

static StatusStack *GlobalStatusStack = NULL;

static inline void StatusStack_SetGlobal(StatusStack *inst)
{
  svoid(!inst);

  GlobalStatusStack = inst;
}

#endif  /* COMPOUND_STATUS_STACK_H */
