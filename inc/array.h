#ifndef ARRAY_H
# define ARRAY_H

# include <Compound/var.h>

typedef struct {
  Var *members;
  int len;
  size_t size;
  Liveness liveness;
  bool readonly;  // Required to be true once copied from others
                  // to avoid "double free".
  LITERALISE;
} Array;

Status Array_Create(liveness(DEAD, Array) *inst, int len, size_t size,
                    literalisation_t lit);
Status Array_CopyOf(liveness(ALIVE, Array) *inst, liveness(ALIVE, Array) *other);
Status Array_Preallocate(liveness(DEAD, Array) *inst);
Status Array_Allocate(liveness(HALF_ALIVE, Array) *inst);
Status Array_Reallocate(liveness(ALIVE, Array) *inst, size_t size);
Status Array_Release(liveness(ALIVE, Array) *inst);
Status Array_PostRelease(liveness(HALF_ALIVE, Array) *inst);
Status Array_Delete(liveness(DEAD, Array) *inst);
Status Array_Literalise(liveness(ALIVE, Array) *inst, char *buff);
bool   Array_Equals(liveness(ALIVE, Array) *arr1, liveness(ALIVE, Array) *arr2);

/* Insert given array before the element from @inst at @off. */
Status ArrayUtils_Insert(liveness(ALIVE, Array) *inst,
                         liveness(ALIVE, Array) *items, int off);

/* Remove elements from @off to @off+@len from @inst. */
Status ArrayUtils_Remove(liveness(ALIVE, Array) *inst, int off, int len);

/* Extract a subarray from @inst, stored into @store, from @off to @off+@len */
Status ArrayUtils_Subarray(liveness(ALIVE, Array) *inst,
                           liveness(ALIVE, Array) *store, int off, int len);

/* Fill up elements from @inst, from @off to @off+@len with @elem. */
Status ArrayUtils_Fill(liveness(ALIVE, Array) *inst, liveness(ALIVE, Var) *elem,
                       int off, int len);

/* Split @inst into two arrays at @index, separately into @fore and @rear. */
Status ArrayUtils_Split(liveness(ALIVE, Array) *inst,
                        liveness(ALIVE, Array) *fore,
                        liveness(ALIVE, Array) *rear, int index);

#endif  /* ARRAY_H */
