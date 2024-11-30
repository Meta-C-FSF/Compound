#include <Compound/common.h>
#include <Compound/status.h>
#include <Compound/status_stack.h>

Status StatusStack_Create(StatusStack *inst, const size_t length)
{
  avail(inst);
  state(!length, (InvalidStackLength));
  
  state(!(inst->data = calloc(length, sizeof(Status))),
    apply(InsufficientMemory));
  
  (void)memset(inst->data, 0, inst->length);

  inst->length = length;
  inst->current = NULL;

  RETURN(NormalStatus);
}

Status StatusStack_CopyOf(StatusStack *inst, const StatusStack *other)
{
  avail(inst);
  avail(other);
  state(!other->length, (InvalidStackLength));
  
  state(!(inst->data = calloc(other->length, sizeof(Status))),
    apply(InsufficientMemory));
  inst->length = other->length;
  inst->current = NULL;
  
  RETURN(NormalStatus);
}

Status StatusStack_Delete(StatusStack *inst)
{
  avail(inst);
  state(!inst->data, (InstanceNotAlive));
  
  StatusStack_PopAll(inst);
  
  free(inst->data);
  inst->length = 0;
  inst->current = NULL;
  
  RETURN(NormalStatus);
}

Status StatusStack_Push(StatusStack *inst, const Status elem)
{
  avail(inst);
  state(StatusStack_Full(*inst), (StackFull));
  
  if (!inst->current) {
    inst->current = inst->data;
  } else {
    inst->current += sizeof(Status);
  }
  
  inst->data[StatusStack_Offset(*inst)] = elem;
  
  RETURN(NormalStatus);
}

Status StatusStack_Pop(StatusStack *inst)
{
  avail(inst);  
  state(StatusStack_Empty(*inst), (StackEmpty));

  // /* test(william):  Print out item popping. */
  // char buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
  // (void)Status_Literalise(inst->data[StatusStack_Offset(*inst)], buff);
  // (void)printf("%s"NEWLINE, buff);

  inst->data[StatusStack_Offset(*inst)] = (Status)EMPTY;
  
  if (inst->current == inst->data) {
    inst->current = NULL;
  } else {
    inst->current -= sizeof(Status);
  }
  
  RETURN(NormalStatus);
}

void StatusStack_PopAll(StatusStack *inst)
{
  svoid(!inst);
  svoid(!inst->length);
  
  while (inst->current) {
    (void)StatusStack_Pop(inst);
  }
}

inline bool StatusStack_Full(StatusStack mstk)
{
  return (StatusStack_Offset(mstk) >= (mstk.length - 1));
}

inline bool StatusStack_Empty(StatusStack mstk)
{
  return !mstk.current;
}

inline size_t StatusStack_Offset(StatusStack mstk)
{
  if (!mstk.current)  return 0;

  return (mstk.current - mstk.data) / sizeof(Status);
}
