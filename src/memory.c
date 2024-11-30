#include <Compound/common.h>
#include <Compound/memory.h>
#include <Compound/type.h>

Memory Memory_Allocate(Type type, size_t quantity)
{
  if (!quantity)  return (Memory)EMPTY;

  return (Memory) {
    .addr = calloc(quantity, type.size),
    .type = type
  };
}

Memory Memory_Reallocate(Memory mem, Type type)
{
  return (Memory) {
    .addr = realloc(mem.addr, type.size),
    .type = type
  };
}

void Memory_Release(Memory mem)
{
  /* Skip non-alive instances. */
  svoid(!mem.addr);

  free(mem.addr);
}

Status Memory_Create(Memory *inst, Type type)
{
  avail(inst);
  state(alive(*inst), (InstanceStillAlive));
  
  /* Memory_Allocate for @inst. */
  *inst = Memory_Allocate(type, 0);
  
  RETURN(NormalStatus);
}

Status Memory_CopyOf(Memory *inst, const Memory *other)
{
  avail(inst);
  state(alive(*inst), (InstanceStillAlive));
  avail(other);
  state(!alive(*other), (SourceNotAlive));
  
  *inst = *other;
  
  RETURN(NormalStatus);
}

Status Memory_Delete(Memory *inst)
{
  avail(inst);
  state(!alive(*inst), (InstanceNotAlive));
  
  Memory_Release(*inst);
  
  inst->addr = NULL;
  inst->type = (Type)EMPTY;
  
  RETURN(NormalStatus);
}

void Memory_Swap(Memory *inst, Memory *other)
{
  svoid(!inst);
  svoid(!other);
  
  Memory mem = *inst;
  *inst = *other;
  *other = mem;
}

bool Memory_Equals(Memory mem1, Memory mem2)
{
  return (
    mem1.addr == mem2.addr &&
    Type_Equals(mem1.type, mem2.type)
  );
}

size_t Memory_Literalise(const Memory mem, char *buff)
{
  if (!buff)  return 0;
  
  size_t written = 0;
  
  /* Literalise type. */
  char type_buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
  written += Type_Literalise(mem.type, type_buff);
  
  return snprintf(buff, LITERALISATION_LENGTH_MAXIMUM,
                  MEMORY_LITERALISATION_FORMAT, mem.addr, type_buff) + written;
}
