// #include <Compound/memory.h>
// #include <Compound/stack.h>
// #include <Compound/status.h>

// Status Stack_Create(Stack *inst, size_t size, int max_len)
// {
//   nonull(inst, apply(UnavailableInstance));
//   state(inst->alive, apply(InstanceStillAlive));
//   state(!size, apply(annot(InvalidSize, "Stack element sizes cannot be ZERO.")));
//   state(max_len <= 0,
//     apply(annot(InvalidStackLength, "Stack max length can only be positive.")));
  
//   state(!(inst->data = calloc(max_len, size)), apply(InsufficientMemory));
//   inst->current = NULL;
//   inst->END = inst->data + (size * max_len);
//   inst->alive = true;
  
//   return apply(NormalStatus);
// }

// Status Stack_Delete(Stack *inst)
// {
//   nonull(inst, apply(UnavailableInstance));
//   state(!inst->alive, apply(InstanceNotAlive));
//   state(!inst->data, apply(NullPointerEncountered));
  
//   free((void *)inst->data);
//   inst->current = NULL;
//   inst->END = NULL;
//   inst->alive = false;
  
//   return apply(NormalStatus);
// }
// /* Returns false when @current equals @END (no more room). */
// bool Stack_Push(Stack *inst, Memory *elem)
// {
//   nonull(inst, false);
//   state(!inst->alive, false);
//   nonull(elem, false);
  
//   state(Stack_Full(*inst), false);
  
//   /* Reassign @inst->current to @inst->data once there's no element. */
//   if (!inst->current) {
//     inst->current = inst->data;
//   }
  
//   /* Move @current. */
//   inst->current += sizeof(Memory *);

//   /* Assign @elem. */
//   inst->data[Stack_Occupied(*inst)] = *elem;
  
//   return true;
// }

// /* Return false when @current equals NULL (no more element). */
// bool Stack_Pop(Stack *inst)
// {
//   nonull(inst, false);
//   state(!inst->alive, false);
  
//   state(Stack_Empty(*inst), false);

//   /* Erase element. */
//   inst->data[Stack_Occupied(*inst)] = (Memory)EMPTY;

//   /* Move @current. */
//   inst->current -= sizeof(Memory *);

//   /* Reassign @inst->current to NULL once there's no element left. */
//   if (inst->current == inst->data) {
//     inst->current = NULL;
//   }
  
//   return true;
// }
