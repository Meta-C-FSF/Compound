#ifndef COMPOUND_MEMORY_H
# define COMPOUND_MEMORY_H

# include <Compound/status_stack.h>
# include <Compound/status.h>
# include <Compound/type.h>

//                                      @addr:type
# define MEMORY_LITERALISATION_FORMAT  "@[%p]:%s"

typedef struct {
  void *addr;
  Type type;
} Memory;

/* Memory type declaration. */
# define Memory(T)  Memory

DEFTYPE(TMemory, sizeof(Memory));

/* @addr == NULL, not alive;
   @addr != NULL, is alive. */
# define alive(mem)  ((mem).addr)

/* Memory_Allocate a Memory instance with given Type @T. */
# define new(T)  Memory_Allocate((T), 1)

/* Memory_Release a Memory instance @mem. */
# define delete(mem)  Memory_Release((mem))

/* Convert into Memory. */
# define memory(obj)  ((Memory){                           \
  .addr = (&obj),                                          \
  .type = type(unknown, sizeof(obj))                       \
})

/* Reconstructibilities. */
Memory Memory_Allocate(Type type, size_t quantity);
Memory Memory_Reallocate(Memory mem, Type type);
void Memory_Release(Memory mem);

/* Operations. */
Status Memory_Create(Memory *inst, const Type type);
Status Memory_CopyOf(Memory *inst, const Memory *other);
Status Memory_Delete(Memory *inst);

/* Utilities. */
void Memory_Swap(Memory *inst, Memory *other);
bool Memory_Equals(const Memory mem1, const Memory mem2);
size_t Memory_Literalise(const Memory mem, char *buff);

#endif  /* COMPOUND_MEMORY_H */
