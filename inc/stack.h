#ifndef COMPOUND_STRUCT_STACK_H
# define COMPOUND_STRUCT_STACK_H

# include <Compound/status.h>
# include <Compound/type.h>

typedef struct _Stack {
  void **data;
  size_t size;
  size_t length;
  void *current;
} Stack;

# define Stack(T)  Stack

DEFTYPE(TStack, sizeof(Stack));

Status Stack_Create(Stack *inst, const size_t size, const size_t length);
Status Stack_CopyOf(Stack *inst, const Stack *other);
Status Stack_Delete(Stack *inst);
bool   Stack_Push(Stack *inst, void const *addr);
bool   Stack_Pop(Stack *inst);
bool   Stack_Full(Stack *inst);
bool   Stack_Empty(Stack *inst);
size_t Stack_CurrentIndexer(Stack *inst);
void   Stack_PopAll(Stack *inst);

DEFSTATUS(StackError, 1,
  "Cannot perform operation on stack.",
  STATUS_ERROR, &InvalidOperation);

DEFSTATUS(StackFull, 1,
  "Stack is full, cannot push.",
  STATUS_ERROR, &StackError);

DEFSTATUS(StackEmpty, 1,
  "Stack is empty, cannot pop.",
  STATUS_ERROR, &StackError);

#endif  /* COMPOUND_STRUCT_STACK_H */
