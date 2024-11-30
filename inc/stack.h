#ifndef COMPOUND_STRUCT_STACK_H
# define COMPOUND_STRUCT_STACK_H

# include <Compound/status.h>
# include <Compound/type.h>
# include <Compound/status_stack.h>

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
bool   Stack_Push(Stack *inst, void *addr);
bool   Stack_Pop(Stack *inst);
void   Stack_PopAll(Stack *inst);
bool   Stack_Full(const Stack stk);
bool   Stack_Empty(const Stack stk);
size_t Stack_Offset(const Stack stk);
/* Remove empty elements. */
Status Stack_Clean(Stack *inst);

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
