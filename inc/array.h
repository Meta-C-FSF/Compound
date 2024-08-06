#ifndef ARRAY_H
# define ARRAY_H

# include <Compound/var.h>

typedef struct {
  Var *members;
  int len;
  size_t size;
  bool alive;
  LITERALISE;
} Array;

Status Array_Create(Array *inst, int len, size_t size, literalisation_t lit);
Status Array_CopyOf(Array *inst, Array *other);
Status Array_Allocate(Array *inst);
Status Array_Reallocate(Array *inst, size_t size);
Status Array_Release(Array *inst);
Status Array_Delete(Array *inst);
Status Array_Literalise(Array *inst, Array(char) *buff);
bool   Array_Equals(Array *arr1, Array *arr2);

/* Insert given array before the element from @inst at @off. */
Status ArrayUtils_Insert(Array *inst, Array *item, int off);

/* Remove elements from @off to @off+@len from @inst. */
Status ArrayUtils_Remove(Array *inst, int off, int len);

/* Extract a subarray from @inst, stored into @store, from @off to @off+@len */
Status ArrayUtils_Subarray(Array *inst, Array *store, int off, int len);

/* Fill up elements from @inst, from @off to @off+@len with @elem. */
Status ArrayUtils_Fill(Array *inst, Var *elem, int off, int len);

/* Split @inst into two arrays at @index, separately into @fore and @rear. */
Status ArrayUtils_Split(Array *inst, Array *fore, Array *rear, int index);

#endif  /* ARRAY_H */
