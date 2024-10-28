#include <Compound/array.h>
#include <Compound/common.h>
#include <Compound/status.h>
#include <string.h>

Status Array_Create(Array *inst, const size_t length)
{
  avail(inst);
  state(inst->data, apply(InstanceStillAlive));
  state(!length, apply(InvalidArrayLength));
  
  state(!(inst->data = calloc(length, sizeof(Memory))),
    apply(InsufficientMemory));
  inst->length = length;
  
  (void)memset(inst->data, 0, length);
  
  return apply(NormalStatus);
}

Status Array_CopyOf(Array *inst, const Array *other)
{
  avail(inst);
  state(inst->data, apply(InstanceStillAlive));
  avail(other);
  state(!other->data, apply(SourceNotAlive));
  
  state(!(inst->data = calloc(other->length, sizeof(Memory))),
    apply(InsufficientMemory));
  
  for (register size_t i = 0; i < other->length; i++) {
    inst->data[i] = other->data[i];
  }
  inst->length = other->length;
  
  return apply(NormalStatus);
}

Status Array_Delete(Array *inst)
{
  avail(inst);
  state(!inst->data, apply(InstanceNotAlive));
  
  free(inst->data);
  inst->length = 0;
  
  return apply(NormalStatus);
}

Status Array_GetIdx(Array *inst, const size_t index, Memory *elem)
{
  avail(inst);
  state(!inst->data, apply(InstanceNotAlive));
  state(index >= inst->length, apply(ArrayIndexOutOfBound));
  avail(elem);
  state(alive(*elem), apply(SourceNotAlive));
  
  *elem = inst->data[index];
  
  return apply(NormalStatus);
}

Status Array_SetIdx(Array *inst, const size_t index, const Memory elem)
{
  avail(inst);
  state(!inst->data, apply(InstanceNotAlive));
  state(index >= inst->length, apply(ArrayIndexOutOfBound));
  
  inst->data[index] = elem;
  
  return apply(NormalStatus);
}

bool Array_Equals(const Array *inst, const Array *other)
{
  state(!inst || !other, false);
  state(!inst->data || !other->data, false);
  state(inst->length != other->length, false);
  
  for (register size_t i = 0; i < inst->length; i++) {
    if (!(Equals(inst->data[i], other->data[i]))) {
      return false;
    }
  }
  
  return true;
}
