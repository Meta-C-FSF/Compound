#include <Compound/array.h>
#include <Compound/status.h>

Status Array_Create(Array *inst, int len, size_t size)
{
  nonull(inst, apply(UnavailableInstance));

  /* Skip the living instances. */
  state(inst && inst->alive, apply(InstanceStillAlive));
  
  /* Allocate for members from the inst. */
  state(!(inst->members = calloc(len, sizeof(Var))), apply(InsufficientMemory));
  
  /* Create for each item from members. */
  int erridx = -1;
  Status errstat = EMPTY;
  for (register int i = 0; i < len; i++) {
    notok(Var_Create(&inst->members[i], size), {
      erridx = i;
      errstat = apply(_);
      break;
    })
  }
  
  /* Got problem during allocations. */
  if (erridx >= 0) {
    /* Release members allocated backwardly. */
    for (register int i = erridx - 1; i >= 0; i--) {
      Var_Delete(&inst->members[i]);
    }
    
    /* Release the array inst. */
    free(inst->members);
    
    return errstat;
  }
  
  /* Assign rest of the struct members. */
  inst->len = len;
  inst->alive = true;
  
  return apply(NormalStatus);
}

Status Array_CopyOf(Array *inst, Array *other)
{
  /* Skip unavailble parameters. */
  nonull(other,
    apply(annot(UnavailableInstance,
      "Given object for copying to inst was unavailable.")));
  
  /* Skip invalid parameters and instances. */
  state(inst && inst->alive,
    apply(annot(InstanceStillAlive,
      "Given inst for being copied was still alive.")));
  
  state(!other->alive,
    apply(annot(InstanceNotAlive,
      "Given object for copying to inst was not alive.")));
  
  state(!other->len,
    apply(annot(InvalidArrayLength,
      "Given object for copying to inst has length of ZERO.")));
  
  /* Allocate for members from the inst. */
  state(!(inst->members = calloc(other->len, sizeof(Var))),
    apply(InsufficientMemory));
  
  /* Create for each item from members. */
  int erridx = -1;
  Status errstat = EMPTY;
  for (register int i = 0; i < other->len; i++) {
    notok(Var_Create(&inst->members[i], other->members[0].size), {
      erridx = i;
      errstat = apply(_);
      break;
    })
    
    notok(Var_CopyOf(&inst->members[i], &other->members[i]), {
      erridx = i;
      errstat = apply(_);
      break;
    })
  }
  
  /* Got problem during allocations. */
  if (erridx >= 0) {
    /* Release members allocated backwardly. */
    for (register int i = erridx - 1; i >= 0; i--) {
      Var_Delete(&inst->members[i]);
    }
    
    /* Release the array inst. */
    free(inst->members);
    
    return apply(errstat);
  }
  
  /* Assign rest of the struct members. */
  inst->len = other->len;
  inst->alive = true;
  
  return apply(NormalStatus);
}

Status Array_Delete(Array *inst)
{
  nonull(!inst, apply(UnavailableInstance));
  state(!inst->alive, apply(InstanceNotAlive));

  /* Iterate through each member and delete them. */  
  for (register int i = 0; i < inst->len; i++) {
    fail(Var_Delete(&inst->members[i]));
  }
  
  free(inst->members);
  inst->members = NULL;
  inst->alive = false;
  inst->len = 0;
  
  return apply(NormalStatus);
}

bool Array_Equals(Array *arr1, Array *arr2)
{
  /* Skip unavailable instance and parameter. */
  state(!arr1 || !arr2, false);
  
  /* Skip when arr1 and arr2 have different length. */
  state(arr1->len != arr2->len, false);
  
  /* Skip when operation is not supported. */
  state(!arr1->alive || !arr2->alive, false);
  
  /* Iterate through each member for comparison. */
  for (register int i = 0; i < arr1->len; i++) {
    if (!Var_Equals(&arr1->members[i], &arr2->members[i])) {
      return false;
    }
  }
  
  /* Compare rest of the struct member. */  
  return (arr1->alive == arr2->alive);
}

Status ArrayUtils_Insert(Array *inst, Var *item, int index);

Status ArrayUtils_InsertArray(Array *inst, Array *items, int index);

Status ArrayUtils_Remove(Array *inst, int index);

Status ArrayUtils_RemoveArray(Array *inst, int off, int len);

Status ArrayUtils_Subarray(Array *inst, Array *store, int off, int len);

Status ArrayUtils_Fill(Array *inst, Var *elem, int off, int len);

Status ArrayUtils_Search(Array *inst, Var *item, int *store);

Status ArrayUtils_SearchArray(Array *inst, Array *items, int *store);

Status ArrayUtils_Split(Array *inst, Array *fore, Array *rear, int index);

Status ArrayUtils_Revert(Array *inst);

bool   ArrayUtils_IsEmpty(Array *inst);
