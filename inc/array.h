#ifndef COMPOUND_ARRAY_H
# define COMPOUND_ARRAY_H

# include <Compound/memory.h>

typedef struct {
  Memory *data;
  size_t length;
} Array;

/* Operations. */
Status Array_Create(Array *inst, const size_t length);
Status Array_CopyOf(Array *inst, const Array *other);
Status Array_Delete(Array *inst);
Status Array_GetIdx(Array *inst, const size_t index, Memory *elem);
Status Array_SetIdx(Array *inst, const size_t index, const Memory elem);

/* Utilities. */
bool Array_Equals(const Array *inst, const Array *other);

#endif  /* COMPOUND_ARRAY_H */
