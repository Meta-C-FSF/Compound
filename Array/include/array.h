#ifndef ARRAY_H
# define ARRAY_H

# include <Compound/var.h>

typedef struct {
  int len;
  Var *members;
} Array;

static Status ArrayIndexOutOfBound = {
  .description = "Given index was accessing illegal address.",
  .characteristic = STATUS_ERROR,
  .prev = &MemoryViolation
};

static Status InvalidArrayLength = {
  .description = "Given length is invalid.",
  .characteristic = STATUS_ERROR,
  .prev = &ErrorStatus
};

/* Elementary. */
Status Array_Create(Array *inst, int len);
Status Array_CopyOf(Array *inst, Array *other);
Status Array_Delete(Array *inst);
Status Array_GetIdx(Array *inst, Var *store, int index);
Status Array_SetIdx(Array *inst, Var *source, int index);
Status Array_Literalise(Array *inst, char const *store);
bool   Array_Equal(Array *arr1, Array *arr2);

/* Extensional. */
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

#endif  /* ARRAY_H */