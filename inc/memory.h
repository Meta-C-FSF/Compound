#ifndef COMPOUND_MEMORY_H
# define COMPOUND_MEMORY_H

# include <Compound/status.h>
# include <Compound/type.h>

typedef struct {
  /* Actual address pointer, pointing towards address of the object. */
  const void *addr;
  
  /* Type of the object. */
  const Type type;
} Memory;

DEFTYPE(TMemory, sizeof(Memory));

# define MEMORY_STACK_MAXIMUM  65536

// static Memory MEMORY_STACK[MEMORY_STACK_MAXIMUM] = EMPTY;

// static Memory *MEMORY_STACK_INDEXER = MEMORY_STACK;

// static inline long _Memory_CalcStackIndexerOffset()
// {
//   return (MEMORY_STACK_INDEXER - MEMORY_STACK);
// }

// static inline bool _Memory_StackFull()
// {
//   return (_Memory_CalcStackIndexerOffset() == MEMORY_STACK_MAXIMUM);
// }

// static inline bool _Memory_StackEmpty()
// {
//   return (MEMORY_STACK_INDEXER == MEMORY_STACK);
// }

// /* Returns the location within MEMORY_STACK after inserting successfully.
//    Returns NULL if insertion failed. */
// static inline Memory *_Memory_StackPush(Memory *elem)
// {
//   if (!elem)  { return NULL; }
//   if (_Memory_StackFull())  { return NULL; }
  
//   *(++MEMORY_STACK_INDEXER) = *elem;
  
//   return MEMORY_STACK_INDEXER;
// }

// static inline void _Memory_StackPop()
// {
//   if (_Memory_StackEmpty())  { return; }
  
  
// }

#endif  /* COMPOUND_MEMORY_H */
