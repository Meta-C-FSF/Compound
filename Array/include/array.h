#ifndef ARRAY_H
# define ARRAY_H

# include <Compound/var.h>

typedef struct {
  Var *members;
  int len;
  bool alive;
} Array;

DEFSTATUS(ArrayIndexOutOfBound, 1, "Given index was accessing illegal address.", STATUS_ERROR, &MemoryViolation);
DEFSTATUS(InvalidArrayLength, 1, "Given length is invalid.", STATUS_ERROR, &ErrorStatus);

Status Array_Create(Array *inst, int len, size_t size);
Status Array_CopyOf(Array *inst, Array *other);
Status Array_Delete(Array *inst);
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

#endif  /* ARRAY_H */
