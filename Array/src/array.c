#include <Compound/array.h>
#include <Compound/status.h>

Status Array_Create(Array *inst, int len, size_t size)
{
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
    
    return errstat;
  }
  
  /* Assign rest of the struct members. */
  inst->len = other->len;
  inst->alive = true;
  
  return apply(NormalStatus);
}

void   Array_Delete(Array *inst)
{
  svoid(!inst || !inst->alive);
  
  for (register int i = 0; i < inst->len; i++) {
    Var_Delete(&inst->members[i]);
  }
  
  free(inst->members);
  
  inst->alive = false;
  inst->len = 0;
}

Status Array_GetIdx(Array *inst, Var *store, int index);

Status Array_SetIdx(Array *inst, Var *source, int index);

bool   Array_Equals(Array *arr1, Array *arr2);


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

bool   ArrayUtils_IsBlank(Array *inst);

