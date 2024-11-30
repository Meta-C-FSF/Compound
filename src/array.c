#include <Compound/array.h>
#include <Compound/status.h>

Status Array_Create(Array *inst, const size_t length)
{
  avail(inst);
  state(inst->data, (InstanceStillAlive));
  state(!length, (InvalidArrayLength));

  state(!(inst->data = calloc(length, sizeof(Memory))),
    apply(InsufficientMemory));
  push(((Memory){.addr = (void *)inst, .type = EMPTY}));

  inst->length = length;
  (void)memset(inst->data, 0, length);
  
  RETURN(NormalStatus);
}

Status Array_CopyOf(Array *inst, const Array other)
{
  avail(inst);
  state(inst->data, (InstanceStillAlive));
  state(!other.data, (SourceNotAlive));
  
  state(!(inst->data = calloc(other.length, sizeof(Memory))),
    apply(InsufficientMemory));
  push(inst->data[0]);
  
  for (register size_t i = 0; i < other.length; i++) {
    inst->data[i] = other.data[i];
  }
  inst->length = other.length;
  
  RETURN(NormalStatus);
}

Status Array_Delete(Array *inst)
{
  avail(inst);
  state(!inst->data, (InstanceNotAlive));

  free(inst->data);
  
  inst->data = NULL;
  inst->length = 0;
  
  RETURN(NormalStatus);
}

Status Array_GetIdx(const Array *inst, const size_t index, Memory *elem)
{
  avail(inst);
  state(!inst->data, (InstanceNotAlive));
  state(index >= inst->length, (ArrayIndexOutOfBound));
  avail(elem);
  
  *elem = inst->data[index];
  
  RETURN(NormalStatus);
}

Status Array_SetIdx(Array *inst, const size_t index, const Memory elem)
{
  avail(inst);
  state(!inst->data, (InstanceNotAlive));
  state(index >= inst->length, (ArrayIndexOutOfBound));
  
  inst->data[index] = elem;
  
  RETURN(NormalStatus);
}

bool Array_Equals(const Array arr1, const Array arr2)
{
  if (!arr1.data || !arr2.data)  return false;
  if (arr1.length != arr2.length)  return false;
  
  for (register size_t i = 0; i < arr1.length; i++) {
    if (!(Memory_Equals(arr1.data[i], arr2.data[i]))) {
      return false;
    }
  }
  
  return true;
}

Status Array_Resize(Array *inst, const size_t length)
{
  avail(inst);
  state(!length, InvalidArrayLength);

  Array final = EMPTY;
  fail(Array_Create(&final, length));
  for (register size_t i = 0; i < length; i++) {
    /* Get current element. */
    Memory get = EMPTY;
    fail(Array_GetIdx(inst, i, &get));

    /* Intersection, assign directly. */
    if (i < inst->length) {
      fail(Array_SetIdx(&final, i, get));
      continue;
    }

    /* Extra elements, assign with @EMPTY. */
    fail(Array_SetIdx(&final, i, (Memory)EMPTY));

    fail(Array_Delete(inst));
    fail(Array_CopyOf(inst, final));

    fail(Array_Delete(&final));
  }

  RETURN(NormalStatus);
}

/* Examine required. */
Status Array_Insert(Array *inst, const size_t index, const Memory elem)
{
  avail(inst);
  state(!inst->data, (InstanceNotAlive));
  state(index > inst->length, (ArrayIndexOutOfBound));

  // Insert before @index.
  // [I, 1, 2, 3]
  // [1, 2, 3, I]
  // [1, I, 2, 3]
  Array final = EMPTY;
  fail(Array_Create(&final, inst->length + 1));
  for (register size_t i = 0; i < final.length; i++) {
    /* Assign with @elem when @i encounters @index. */
    if (i == index) {
      fail(Array_SetIdx(&final, i, elem));
      continue;
    }

    fail(Array_SetIdx(&final, i, inst->data[i]));
  }

  fail(Array_Delete(inst));
  fail(Array_CopyOf(inst, final));
  
  fail(Array_Delete(&final));
  
  RETURN(NormalStatus);
}

Status Array_Remove(Array *inst, const size_t index);
