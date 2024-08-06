#ifndef STACK_H
# define STACK_H

# include <Compound/common.h>
# include <Compound/platform.h>

typedef struct {
  Memory data[__COMPOUND_STACK_MAXIMUM__];
  int top;
} Stack;

int Stack_Create(Stack *inst);
int Stack_Delete(Stack *inst);
int Stack_Push(Stack *inst, Memory *item);
int Stack_Pop(Stack *inst);
int StackUtils_IsFull(Stack *inst);
int StackUtils_IsEmpty(Stack *inst);



#endif  /* STACK_H */
