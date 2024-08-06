#include <Compound/array.h>
#include <Compound/status.h>
#include <Compound/var.h>

Status Array_Create(Array *inst, int len, size_t size, literalisation_t lit)
{
  nonull(inst, apply(UnavailableInstance));
  state(!size || size < 0, apply(InvalidSize));
  state(inst && inst->alive, apply(InstanceStillAlive));
  
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
  inst->alive = false;
  inst->Literalise = (!lit ? Literalise : lit);
  
  return apply(NormalStatus);
}

Status Array_CopyOf(Array *inst, Array *other)
{
  /* Skip unavailble parameters. */
  nonull(inst,
    apply(annot(UnavailableInstance,
      "Given inst for copying from other was unavailable.")));
  
  nonull(other,
    apply(annot(UnavailableParameter,
      "Given object for copying to inst was unavailable.")));
  
  /* Skip invalid parameters and instances. */
  state(inst->alive,
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
  
  /* Create items from members. */
  int erridx = -1;
  Status errstat = EMPTY;
  for (register int i = 0; i < other->len; i++) {
    notok(Var_Create(&inst->members[i], other->members[0].size, NULL), {
      erridx = i;
      errstat = _;
      break;
    })
    
    notok(Var_CopyOf(&inst->members[i], &other->members[i]), {
      erridx = i;
      errstat = _;
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

Status Array_Allocate(Array *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(inst->alive, apply(InstanceStillAlive));
  
  state(!(inst->members = calloc(inst->len, sizeof(Var))),
    apply(InsufficientMemory));
  
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
  
  inst->alive = true;

  return apply(NormalStatus);
}

Status Array_Reallocate(Array *inst, size_t size)
{
  nonull(inst, apply(UnavailableInstance));
  state(!size || size < 0, apply(InvalidSize));
  state(!inst->alive, apply(InstanceNotAlive));

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

Status Array_Release(Array *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(!inst->alive, apply(InstanceNotAlive));
  
  /* Iterate through each member and delete them. */  
  for (register int i = 0; i < inst->len; i++) {
    fail(Var_Release(&inst->members[i]));
  }
  
  free(inst->members);
  inst->alive = false;
  
  return apply(NormalStatus);
}

Status Array_Delete(Array *inst)
{
  nonull(inst, apply(UnavailableInstance));
  state(inst->alive,
    apply(annot(InstanceStillAlive,
      "Please ensure the instance is released before pushing to delete.")));

  inst->members = NULL;
  inst->len = 0;
  inst->alive = false;  // Enforce the @alive value to be false.
  inst->Literalise = NULL;
  inst = NULL;
  
  return apply(NormalStatus);
}

// Status Array_Literalise(Array *inst, Array(char) *buff)
// {
//   nonull(inst, apply(UnavailableInstance));
//   nonull(buff, apply(UnavailableBuffer));
//   state(!inst->alive, apply(InstanceNotAlive));
//   state(buff->alive, apply(InstanceStillAlive));
  
//   /* Create array buffer. */
//   fails(Array_Create(buff, 1, sizeof(char)),
//     "Failed to create array buffer for array literalisation.");
  
//   /* Assignment for opening decoration. */
//   cast(buff->members[0], char) = '[';
  
//   char varbuff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
//   for (register int i = 0; i < inst->len; i++) {
//     /* Literalise each member from inst. */
//     fail(Var_Literalise(&inst->members[i], varbuff));
    
//     /* Write members' literalisations into varbuff. */
//     unsure(value(TraditionalFunctionReturn,
//       snprintf(varbuff, LITERALISATION_LENGTH_MAXIMUM, "%s", )))
//   }
// }

// Status Array_Literalise(Array *inst, char *buff)
// {
//   nonull(inst, apply(UnavailableInstance));
//   nonull(buff, apply(UnavailableBuffer));
//   state(!inst->alive, apply(InstanceNotAlive));
  
//   buff[0] = '[';
//   for (register int i = 1; i < inst->len - 1; i++) {
//     /* Literalise var from members. */
//     char varbuff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
//     fail(Var_Literalise(&inst->members[i - 1], varbuff));
    
//     /* Write literalisation into buff. */
//     unsure(value(TraditionalFunctionReturn,
//       snprintf(buff, LITERALISATION_LENGTH_MAXIMUM, "%s, ", varbuff)), !_.value, {
//       return apply(annot(_, "Failed to write literalisation into buffer."));
//     })
//   }
  
//   /* Write literalisation of the last member. */
//   char varbuff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
//   fail(Var_Literalise(&inst->members[inst->len - 1], varbuff));
  
//   /* Write literalisation into buff. */
//   unsure(value(TraditionalFunctionReturn,
//     snprintf(buff, LITERALISATION_LENGTH_MAXIMUM, const char *restrict format, ...)))
// }

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

// Status ArrayUtils_Insert(Array *inst, Var *item, int index)
// {
//   nonull(inst, apply(UnavailableInstance));
//   nonull(item, apply(UnavailableInstance));
//   state(index < 0 || index > inst->len + 1, apply(ArrayIndexOutOfBound));
  
//   state(!inst->alive, apply(annot(InstanceNotAlive,
//     "Given Array instance was not alive.")));
//   state(!item->alive, apply(annot(InstanceNotAlive,
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
  
//   state(!inst->alive, apply(annot(InstanceNotAlive,
//     "Given Array instance was not alive.")));
//   state(!item->alive, apply(annot(InstanceNotAlive,
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
//   state(!inst->alive, apply(InstanceNotAlive));
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
//   state(!inst->alive, apply(InstanceNotAlive));
//   state(!item->alive, apply(InstanceNotAlive));
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

Status ArrayUtils_Remove(Array *inst, int off, int len);

Status ArrayUtils_Subarray(Array *inst, Array *store, int off, int len);

Status ArrayUtils_Fill(Array *inst, Var *elem, int off, int len);

Status ArrayUtils_Split(Array *inst, Array *fore, Array *rear, int index);
