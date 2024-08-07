#include <Compound/array.h>
#include <Compound/common.h>
#include <Compound/status.h>
#include <Compound/var.h>

Status Array_Create(liveness(DEAD, Array) *inst, int len, size_t size,
                    literalisation_t lit)
{
  nonull(inst, apply(UnavailableInstance));
  state(!size || size < 0, apply(InvalidSize));
  state(inst && inst->liveness, apply(InstanceStillAlive));
  state(inst->readonly, apply(ReadonlyTarget));
  
  /* Allocate for members from the inst. */
  // state(!(inst->members = calloc(len, sizeof(Var))), apply(InsufficientMemory));
  
  /* Create for each item from members. */
  // int erridx = -1;
  // Status errstat = EMPTY;
  // for (register int i = 0; i < len; i++) {
  //   notok(Var_Create(&inst->members[i], size, NULL), {
  //     erridx = i;
  //     errstat = apply(_);
  //     break;
  //   })
  // }
  
  /* Assign rest of the struct members. */
  inst->len = len;
  inst->size = size;
  inst->liveness = false;
  inst->readonly = false;
  inst->Literalise = (!lit ? Literalise : lit);
  
  return apply(NormalStatus);
}

Status Array_CopyOf(liveness(ALIVE, Array) *inst, liveness(ALIVE, Array) *other)
{
  nonull(inst, apply(UnavailableInstance));
  nonull(other, apply(UnavailableSource));
  state(!inst->liveness, apply(InstanceNotAlive));
  state(!other->liveness, apply(SourceNotAlive));
  state(inst->readonly, apply(ReadonlyTarget));

  /* Abolish previous instance @inst. */
  fail(Array_Release(inst));
  fail(Array_Delete(inst));
  
  /* Recreate with @other. */
  fail(Array_Create(inst, other->len, other->size, other->Literalise));

  state(!(inst->members = calloc(inst->len, sizeof(Var))),
    apply(InsufficientMemory));

  inst->liveness = true;
  inst->readonly = true;
  
  /* Copy contents from @other. */
  for (register int i = 0; i < inst->len; i++) {
    inst->members[i] = other->members[i];
  }
  
  return apply(NormalStatus);
}

Status Array_Preallocate(liveness(DEAD, Array) *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(!inst->liveness,
    apply(annot(IncorrectLiveness, "Preallocation requires LIVENESS_DEAD.")));
  
  state(!(inst->members = calloc(inst->len, sizeof(Var))),
    apply(InsufficientMemory));
  
  return apply(NormalStatus);
}

Status Array_Allocate(liveness(HALF_ALIVE, Array) *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(inst->liveness, apply(InstanceStillAlive));
  state(inst->readonly, apply(ReadonlyTarget));
  
  fail(Array_Preallocate(inst));
  
  int erridx = -1;
  Status errstat = EMPTY;
  for (register int i = 0; i < inst->len; i++) {
    fail(Var_Create(&inst->members[i], inst->size, NULL));
    notok(Var_Allocate(&inst->members[i]), {
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
  
  inst->liveness = LIVENESS_ALIVE;

  return apply(NormalStatus);
}

Status Array_Reallocate(liveness(ALIVE, Array) *inst, size_t size)
{
  nonull(inst, apply(UnavailableInstance));
  state(!size || size < 0, apply(InvalidSize));
  state(!inst->liveness, apply(InstanceNotAlive));
  state(inst->readonly, apply(ReadonlyTarget));

  // state((!(inst->addr = realloc(inst->addr, size))), apply(InsufficientMemory));
  /* Reallocate. */
  int erridx = -1;
  Status errstat = EMPTY;
  for (register int i = 0; i < inst->len; i++) {
    notok(Var_Reallocate(&inst->members[i], size), {
      erridx = i;
      errstat = apply(_);
      break;
    })
  }

  /* Got problem during reallocations. */
  if (erridx >= 0) {
    /* Release members allocated backwardly. */
    for (register int i = erridx - 1; i >= 0; i--) {
      Var_Delete(&inst->members[i]);
    }
    
    /* Release the array inst. */
    free(inst->members);
    
    return errstat;
  }

  return apply(NormalStatus);
}

Status Array_Release(liveness(ALIVE, Array) *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(!inst->liveness, apply(InstanceNotAlive));

  /* Cannot allow releasing once the @inst is copied from others.
     @See doc/READONLY for more. */
  if (inst->readonly && inst->members) {
    fail(Array_PostRelease(inst));
    return apply(NormalStatus);
  }
  
  /* Iterate through each member and delete them. */  
  for (register int i = 0; i < inst->len; i++) {
    fail(Var_Release(&inst->members[i]));
  }
  
  fail(Array_PostRelease(inst));
  
  return apply(NormalStatus);
}

Status Array_PostRelease(liveness(HALF_ALIVE, Array) *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(inst->liveness != LIVENESS_HALF_ALIVE,
    apply(annot(IncorrectLiveness, "PostRelease requires LIVENESS_HALF_ALIVE.")));
  
  free(inst->members);
  inst->liveness = LIVENESS_DEAD;
  
  return apply(NormalStatus);
}

Status Array_Delete(liveness(DEAD, Array) *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(inst->liveness, apply(InstanceStillAlive));

  inst->members = NULL;
  inst->len = 0;
  inst->liveness = false;  // Enforce the @alive value to be false.
  inst->readonly = false;  // Just for safety.
  inst->Literalise = NULL;
  inst = NULL;
  
  return apply(NormalStatus);
}

Status Array_Literalise(liveness(ALIVE, Array) *inst, char *buff);

bool Array_Equals(liveness(ALIVE, Array) *arr1, liveness(ALIVE, Array) *arr2)
{
  /* Skip unavailable instance and parameter. */
  state(!arr1 || !arr2, false);
  
  /* Skip when arr1 and arr2 have different length. */
  state(arr1->len != arr2->len, false);
  
  /* Skip when operation is not supported. */
  state(!arr1->liveness || !arr2->liveness, false);
  
  /* Iterate through each member for comparison. */
  for (register int i = 0; i < arr1->len; i++) {
    if (!Var_Equals(&arr1->members[i], &arr2->members[i])) {
      return false;
    }
  }
  
  /* Compare rest of the struct member. */  
  return (arr1->liveness == arr2->liveness);
}

Status ArrayUtils_Insert(liveness(ALIVE, Array) *inst,
                         liveness(ALIVE, Array) *items, int off)
{
  nonull(inst, apply(UnavailableInstance));
  nonull(items, apply(UnavailableParameter));
  state(off < 0 || off > inst->len + 1, apply(ArrayIndexOutOfBound));
  state(inst->readonly, apply(ReadonlyTarget));
  
  Array container = EMPTY;  
  /* The size to the @container is determined by the maximum between
     @inst and @items. */
  fail(Array_Create(&container, inst->len + items->len,
    max(inst->size, items->size), NULL));
  
  /* Copy contents from @inst at fore to @container. */
  for (register int i = 0; i < off; i++) {
    container.members[i] = inst->members[i];
  }
  
  /* Copy contents from @items to @container. */
  const int items_off = off;
  for (register int i = 0; i < items->len; i++) {
    container.members[i + items_off] = items->members[i];
  }
  
  /* Copy contents from @inst at rear to @container. */
  const int rear_off = items_off + items->len;
  for (register int i = 0; i < inst->len - rear_off; i++) {
    container.members[i + rear_off] = inst->members[i];
  }

  /* Recreate @inst with @container. */
  fail(Array_CopyOf(inst, &container));
  
  return apply(NormalStatus);
}

// Status ArrayUtils_Insert(Array *inst, Var *item, int index)
// {
//   nonull(inst, apply(UnavailableInstance));
//   nonull(item, apply(UnavailableInstance));
//   state(index < 0 || index > inst->len + 1, apply(ArrayIndexOutOfBound));
  
//   state(!inst->liveness, apply(annot(InstanceNotAlive,
//     "Given Array instance was not alive.")));
//   state(!item->liveness, apply(annot(InstanceNotAlive,
//     "Given item was not alive.")));
  
//   /* Create a new Array container. */
//   Array container = EMPTY;
//   fails(Array_Create(&container, inst->len + 1, inst->members[0].size),
//     "Failed to create container for array insertion.");
  
//   /* Set item at "index". */
//   fails(Var_Delete(&container.members[index]),
//     "Failed to replace the item from container on deleting Var.");
//   fails(Var_CopyOf(&container.members[index], item),
//     "Failed to replace the item from container on copying Var.");
  
//   /* Copy every else element from inst to container. */
//   for (register int i = 0; i < container.len; i++) {
//     /* Skip the one already copied. (the "index" one) */
//     if (i == index)  continue;
    
//     assign(container.members[i], inst->members[i], Var);
//   }
  
//   /* Delete original inst. */
//   fails(Array_Delete(inst), "Failed to delete original instance of array.");
  
//   /* Reassign inst. */
//   fails(Array_CopyOf(inst, &container), "Failed to copy from container to inst.");
  
//   return apply(NormalStatus);
// }

// Status ArrayUtils_Insert(Array *inst, Var *item, int index)
// {
//   nonull(inst, apply(UnavailableInstance));
//   nonull(item, apply(UnavailableInstance));
//   state(index < 0 || index > inst->len + 1, apply(ArrayIndexOutOfBound));
  
//   state(!inst->liveness, apply(annot(InstanceNotAlive,
//     "Given Array instance was not alive.")));
//   state(!item->liveness, apply(annot(InstanceNotAlive,
//     "Given item was not alive.")));
  
//   /* Create a new Array container. */
//   Array container = EMPTY;
//   fails(Array_Create(&container, inst->len + 1, inst->members[0].size),
//     "Failed to create container for array insertion.");

  

//   /* Reassign inst. */
//   fails(Array_CopyOf(inst, &container), "Failed to copy from container to inst.");
  
//   return apply(NormalStatus);
// }

// Status ArrayUtils_Remove(Array *inst, int index)
// {
//   nonull(inst, apply(UnavailableInstance));
//   state(!inst->liveness, apply(InstanceNotAlive));
//   state(index < 0 || index > inst->len - 1, apply(ArrayIndexOutOfBound));
  
//   /* Create a new Array container. */
//   Array container = EMPTY;
//   fails(Array_Create(&container, inst->len - 1, inst->members[0].size),
//     "Failed to create container for array insertion.");
  
//   /* HERE */
// }

// Status ArrayUtils_Insert(Array *inst, Array *item, int off)
// {
//   nonull(inst, apply(UnavailableInstance));
//   nonull(item, apply(UnavailableParameter));
//   state(off < 0 || off > inst->len, apply(ArrayIndexOutOfBound));
//   state(!inst->liveness, apply(InstanceNotAlive));
//   state(!item->liveness, apply(InstanceNotAlive));
//   state(!item->len, apply(NormalStatus));
  
//   Array container = EMPTY;
//   fail(Array_Create(&container, inst->len + item->len, inst->members[0].size));
  
//   for (register int i = 0; i < container.len; i++) {
//     /* Only assign @inst elements to container if @i < @off. */
//     if (i < off) {
// # ifdef __DEBUG__
//       /* Output current index, compared with total length (@container.len). */
//       (void)printf("DEBUG> a:  %d/%d", i, inst->len);
// # endif  /* __DEBUG__ */
//       container.members[i] = inst->members[i];
      
//     }
//   }
// }

Status ArrayUtils_Remove(liveness(ALIVE, Array) *inst, int off, int len);

Status ArrayUtils_Subarray(liveness(ALIVE, Array) *inst,
                           liveness(ALIVE, Array) *store, int off, int len);

Status ArrayUtils_Fill(liveness(ALIVE, Array) *inst, liveness(ALIVE, Var) *elem,
                       int off, int len);

Status ArrayUtils_Split(liveness(ALIVE, Array) *inst,
                        liveness(ALIVE, Array) *fore,
                        liveness(ALIVE, Array) *rear, int index);
