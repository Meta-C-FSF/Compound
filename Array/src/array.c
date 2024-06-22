#include <Compound/array.h>
#include <Compound/status.h>

Status Array_Create(Array *inst, int len, size_t size)
{
  /* Skip unavailable inst and invalid param. */
  nonull(inst, apply(UnavailableInstance));
  state((len < 0), apply(InvalidArrayLength));
  solve((!len), { inst->len = 0; inst->members = NULL; return apply(NormalStatus); })
  
  inst->len = len;
  inst->members = calloc(len, sizeof(Var));
  int erridx = -1;
  for (register int i = 0; i < len; i++) {
    // TODO(william): Throw InsufficientMemory at following line.
    // DONE(william): ensure(Var_Create(&inst->members[i], size), "Failed to create a new var.");
    
    notok((Var_Create(&inst->members[i], size)), {
#ifdef __DEBUG__
      cat("Var_Create failed!\n")
#endif
      erridx = i;
      break;
    } else {
#ifdef __DEBUG__
      cat("Var_Create success!\n")
#endif
    })
  }

  /* Review on erridx.  Release data that allocated. */
  if (erridx != -1) {
    for (register int i = erridx; i >= 0; i--) {      
      Var_Delete(&inst->members[i]);
#ifdef __DEBUG__
      cat("Deleted var from InsufficientMemory from Array_Create!")
#endif
    }
    
    /* Release array itself. */
    free(inst->members);
    
    return apply(InsufficientMemory);
  }

  return apply(NormalStatus);
}

Status Array_CopyOf(Array *inst, Array *other)
{
  // /* Skip unavailable inst and invalid param. */
  // nonull(inst, apply(UnavailableInstance));
  // nonull(other, error(InvalidParameter, "Given other was unavailable."));
  
  // /* Assign value for len. */
  // inst->len = other->len;
  
  // if (inst->members == NULL)  return apply(NormalStatus);
  // match(RuntimeError, Array_Create(inst, other->len), "Failed on recreating "
  //                                                     "array.");
  
  // /* Copy and assign for each member from other to inst. */
  // for (register int i = 0; i < inst->len; i++) {
  //   inst[i] = other[i];
  // }
  
  // return apply(NormalStatus);
  
  
  
  
  /*
    if (other == NULL)  return 1;

    String_Create(inst, other->len);
    for (register int i = 0; i < other->len; i++) {
        inst->arr[i] = other->arr[i];
    }
    
    return 0;
  
  
  */
}

Status Array_Delete(Array *inst)
{
  /* Skip unavailable inst and invalid param. */
  nonull(inst, apply(UnavailableInstance));
  solve((inst->members == NULL), return apply(NormalStatus));
  
  inst->len = 0;
  free(inst->members);
  inst->members = NULL;
  
  return apply(NormalStatus);
}

Status Array_GetIdx(Array *inst, Var *store, int index)
{
  /* Skip unavailable inst and invalid param. */
  nonull(inst, apply(UnavailableInstance));
  nonull(store,
    apply(error(InvalidParameter, "Given reference to store was unavailable.")));
  state((index < 0 || index >= inst->len), apply(ArrayIndexOutOfBound));
  
  *store = inst->members[index];
  
  return apply(NormalStatus);
}

Status Array_SetIdx(Array *inst, Var *source, int index)
{
  /* Skip unavailable inst and invalid param. */
  nonull(inst, apply(UnavailableInstance));
  nonull(source,
    apply(
      error(InvalidParameter, "Given reference to source was unavailable.")));
  state((index < 0 || index >= inst->len), apply(ArrayIndexOutOfBound));
  
  inst->members[index] = *source;
  
  return apply(NormalStatus);  
}

bool Array_Equals(Array *a, Array *b)
{
  /* Skip unavailable inst and invalid param. */
  state((a == NULL || b == NULL), false);
  state((a->len != b->len), false);
  
  for (register int i = 0; i < a->len; i++) {
    if (!Var_Equals(&a->members[i], &b->members[i])) {
      return false;
    }
  }
  
  return true;
}



Status ArrayUtils_Fill(Array *inst, Var *elem, int off, int len)
{
  nonull(inst, apply(UnavailableInstance));
  nonull(elem,
    apply(error(InvalidParameter, "Given reference to elem was unavailable.")));
  state((off + len > inst->len) || (off < 0) || (len < 0),
    apply(ArrayIndexOutOfBound));
  
  /* Copy elem into each specified members from inst with off and len. */
  for (register int i = off; i < (off + len); i++) {
    inst->members[i] = *elem;
  }
  
  return apply(NormalStatus);
}
