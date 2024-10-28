#ifndef COMPOUND_MEMORY_H
# define COMPOUND_MEMORY_H

# include <Compound/stack.h>
# include <Compound/status.h>
# include <Compound/type.h>

typedef struct {
  void *addr;
  Type type;
  Stack *stack;
} Memory;

DEFTYPE(TMemory, sizeof(Memory));
# define alive(mem)  ((mem).addr)

/* Reconstructibilities. */
Memory Allocate(Type type, size_t quantity);
Memory Reallocate(Memory mem, Type type);
void Release(Memory mem);

/* Operations. */
Status Memory_Create(Memory *inst, Type type, Stack *stack);
Status Memory_CopyOf(Memory *inst, Memory *other);
Status Memory_Delete(Memory *inst);

/* Utilities. */
void Swap(Memory *inst, Memory *other);
bool Equals(Memory mem1, Memory mem2);

#endif  /* COMPOUND_MEMORY_H */
