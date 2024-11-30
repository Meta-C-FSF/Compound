#ifndef COMPOUND_ARRAY_H
# define COMPOUND_ARRAY_H

# include <Compound/memory.h>
# include <Compound/status_stack.h>
# include <Compound/memory_stack.h>

typedef struct {
  Memory *data;
  size_t length;
} Array;

/* Array type declaration. */
# define Array(T)  Array

DEFTYPE(TArray, sizeof(Array));

/* Operations. */
Status Array_Create(Array *inst, const size_t length);
Status Array_CopyOf(Array *inst, const Array other);
Status Array_Delete(Array *inst);
Status Array_GetIdx(const Array *inst, const size_t index, Memory *elem);
Status Array_SetIdx(Array *inst, const size_t index, const Memory elem);

/* Utilities. */
/* Resize an Array @inst with the new @length.
   If enlarging, the gap will be filled up with empty elements;
   If shrinking, the extra part will be released. */
Status Array_Resize(Array *inst, const size_t length);
/* Insert an element into an Array @inst at @index. */
Status Array_Insert(Array *inst, const size_t index, const Memory elem);
/* Remove an element from an Array @inst at @index. */
Status Array_Remove(Array *inst, const size_t index);
/* Returns true if both Array @arr1 and Array @arr2 have the same elements, and
   length, respectively. */
bool   Array_Equals(const Array arr1, const Array arr2);
/* Fill up an Array @inst with given element Memory @elem from @off
   lasts for @len. */
Status Array_FillUp(Array *inst, const size_t off, const size_t len,
  const Memory elem);
/* Get a copy of a Sub-Array from Array @inst which starts from @off and
   lasts for @len to be stored at Array @store. */
Status Array_SubArr(Array *inst, const size_t off, const size_t len,
  Array *store);
/* Break up an Array @inst from @index and store the latter part, if any, in
   Array @store. */
Status Array_Divide(Array *inst, const size_t index, Array *store);
/* Concatenate an Array @other into Array @inst at @index. */
Status Array_Concat(Array *inst, const size_t index, const Array other);
/* Remove an Sub-Array from Array @inst starts at @off and lasts for @len.
   The remaining parts is reconstructed into one automatically. */
Status Array_Cutout(Array *inst, const size_t off, const size_t len);
/* Revert the order of elements from Array @inst. */
Status Array_Revert(Array *inst);

#endif  /* COMPOUND_ARRAY_H */
