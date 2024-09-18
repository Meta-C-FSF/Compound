#ifndef COMPOUND_STACK_H
# define COMPOUND_STACK_H

# include <Compound/memory.h>

typedef struct {
  /* A Memory pointer to the Stack instance. */
  const Memory *data;
  /* A Memory pointer to current object in the Stack instance.
     It points to NULL when the Stack instance has no elements. */
  Memory *current;
  /* A constant Memory pointer to the first element in the Stack instance. */
  const Memory *BEGIN;
  /* A constant Memory pointer to the last element in the Stack instance. */
  const Memory *END;
  /* Stores the quantity of elements in the Stack instance. */
  const int size;
  /* Indicates whether the Stack instance had been allocated. */
  bool alive;
} Stack;

# define Stack(T)  Stack

Status Stack_Create(Stack *inst, size_t size, int max_len);
Status Stack_Delete(Stack *inst);

/* Returns false when @current equals @LAST (no more room). */
bool Stack_Push(Stack *inst, Memory *elem);

/* Return false when @current equals NULL (no more element). */
bool Stack_Pop(Stack *inst);

static inline bool Stack_Empty(Stack inst)
{
  return (!inst.current);
}

static inline bool Stack_Full(Stack inst)
{
  return (inst.current == inst.END);
}

static inline int Stack_Occupied(Stack inst)
{
  if (!inst.current) {
    return 0;
  }

  return (int)((inst.current - inst.data) / sizeof(Memory *));
}

#endif  /* COMPOUND_STACK_H */
