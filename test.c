#include "inc/type.h"
#include <stdint.h>

#include <Compound/array.h>
#include <Compound/catlog.h>
#include <Compound/common.h>
#include <Compound/format.h>
#include <Compound/memory.h>
#include <Compound/memory_stack.h>
#include <Compound/platform.h>
#include <Compound/stack.h>
#include <Compound/status.h>
#include <Compound/status_stack.h>
#include <Compound/type.h>

size_t PrintArray(const Array arr)
{
  size_t written = 0;
  for (register size_t i = 0; i < arr.length; i++) {
    char buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
    Memory get = EMPTY;
    Memory_Literalise(({
      Array_GetIdx(&arr, i, &get);
      get;
    }), buff);
    
    written += printf("%s"NEWLINE, buff);
  }
  
  return written;
}

Status Main(void)  // ArrayUtilities
{
  Array arr1 = EMPTY;
  // Array arr2 = EMPTY;
  
  fail(Array_Create(&arr1, 3));
  // fail(Array_Create(&arr2, 8));

  fail(Array_SetIdx(&arr1, 0, (Memory){Main, statical(pointer(unsigned(TUInt64)))}));
  fail(Array_SetIdx(&arr1, 1, (Memory){Main, TArray}));
  fail(Array_SetIdx(&arr1, 2, (Memory){Main, TClass}));
  
  PrintArray(arr1);
  
  // fail(Array_Resize(&arr1, 5));
  
  // PrintArray(arr2);
  
  // fail(Array_Delete(&arr2));
  fail(Array_Delete(&arr1));
  
  RETURN(NormalStatus);
}

// Status MainFormat(void)
// {
//   char buff[1024] = EMPTY;
  
//   zero(format(buff, "%d %lf ${Compound} $#{Runtime}", 1, 20.2), {
//     RETURN(NoBytesWereWritten);
//   })
  
//   (void)printf("%s"NEWLINE, buff);
  
//   RETURN(NormalStatus);
// }

// /* TODO: Requires function "format". */
// Status MainCatlogVariadic(CATS)
// {
//   redir(stdout);
  
//   debug("Hello! This is %s speaking!!!"NEWLINE, "William");
  
//   info("I can write whatever I what, plus the extra items I would like it to "
//        "print.  Such as, %d, %lf, %s, %lu."NEWLINE
//        "And even these non-standard parameters!"NEWLINE
//        "%l, %b, %t, %m"NEWLINE,
//        12, 3434.4444, "Sub-string!!!!", UINT64_MAX,
//        "a d e 2 5 1", true, InvalidArrayLength, "IDK what m is current is.");

//   RETURN(NormalStatus);
// }

Status MainArrayUtilities(void)
{
  Array arr1 = EMPTY;
  Array arr2 = EMPTY;
  fail(Array_Create(&arr1, 5));
  fail(Array_Create(&arr2, 5));

  (void)printf("%d"NEWLINE, Array_Equals(arr1, arr2));

  fail(Array_Delete(&arr2));
  fail(Array_Delete(&arr1));
  
  RETURN(NormalStatus);
}

// Status MainInformalHeapAllocationsBenchmarkVersusStackAllocationsRecord(void)
// {
//   {
//     /* avg time real 0.4043 */
//     Array arr = EMPTY;
//     fail(Array_Create(&arr, 100));
  
//     for (register size_t i = 0; i < arr.length; i++) {
//       const Memory curr = new(TLongLong);
//       fail(Array_SetIdx(&arr, i, curr));
//       push(curr);
//     }
  
//     fail(Array_Delete(&arr));
//   }

//   {
//     /* avg time real 0.4150 */
//     Memory arr[100] = EMPTY;
//     for (register size_t i = 0; i < arrlen(arr); i++) {
//       arr[i] = new(TLongLong);
//       push(arr[i]);
//     }
//   }

//   RETURN(NormalStatus);
// }

// // Status Main(ELLIPSIS)  // Variadic
// // {
// //   variadic({
// //     option('d', int, {
// //       (void)printf("%d"NEWLINE, _);
// //       finish;
// //     })

// //     option('s', char *, {
// //       (void)printf("%s"NEWLINE, _);
// //       finish;
// //     })
// //   })

// //   RETURN(NormalStatus);
// // }

// Status MainCatlog(CATS)
// {
//   redir(stdout);

//   /* Normal Output. */
//   info("Normal Output.");

//   /* Redirection. */
//   FILE *dst = fopen("/tmp/catlog", "w");
//   redir(dst);

//   info("Redirection.");

//   (void)fclose(dst);

//   redir(stdout);

//   /* Filtering. */
//   lowest("(Before)  Filtering.");
//   debug("(Before)  Filtering.");
//   info("(Before)  Filtering.");
//   warning("(Before)  Filtering.");
//   error("(Before)  Filtering.");
//   fatal("(Before)  Filtering.");
//   highest("(Before)  Filtering.");

//   filter(CATLOG_LEVEL_CRITICAL);

//   lowest("(After)  Filtering.");
//   debug("(After)  Filtering.");
//   info("(After)  Filtering.");
//   warning("(After)  Filtering.");
//   error("(After)  Filtering.");
//   fatal("(After)  Filtering.");
//   highest("(After)  Filtering.");

//   filter(CATLOG_LEVEL_ALL);

//   /* Multi-line Processing. */
//   info("(1) This will be on the first line"NEWLINE
//        "(2) And this is on the second one."NEWLINE
//        "(3) Yet, this will be on the third line."NEWLINE
//        "(4) And fourth."NEWLINE);

//   RETURN(NormalStatus);
// }

// // Status MainStatusStack(MREG)
// // {

// //   RETURN(NormalStatus);
// // }

// Status MainStatusHandleAndAutoFree(MemoryStack *ms)
// {
//   /* Create an instance of Array. */
//   Array arr = EMPTY;
//   handle(Array_Create(&arr, 20), {
//     match(InsufficientMemory, {
//       (void)printf("Handled Status %s"NEWLINE, strnil(_.identity));
//     })
//     match(InstanceStillAlive, {
//       (void)printf("Handled Status "nameof(InstanceStillAlive)NEWLINE);
//     })
//     match(InvalidArrayLength, {
//       (void)printf("Handled Status "nameof(InvalidArrayLength)NEWLINE);
//     })

//     (void)printf("Finished handling."NEWLINE);  // Equivalent to "finally".
//     return apply(_);
//   });
//   /* Memory_Release resources. */
//   fail(Array_Delete(&arr));

  

//   /* Create a Memory instance manually. */
//   Memory i = EMPTY;
//   for (i = new(TInt); cast(i, int) < 10; cast(i, int)++) {
//     (void)printf("%d\n", cast(i, int));
//   }
//   delete(i);

//   /* Create a Memory instance with auto-release. */
//   push(new(TChar));

//   (void)printf("%c\n", ('A' + cast(*ms->current, char)));

//   RETURN(NormalStatus);
// }

// Status MainMemoryStackApplication(MemoryStack *ms)
// {
//   for (register size_t i = 0; i < ms->length; i++) {
//     fail(MemoryStack_Push(ms, new(TInt64)));
//   }

//   return (apply(NormalStatus));
// }

// // Status MainCatlogVariadicContent(void)
// // {
// //   info("Current Unix timestamp is: %d\n"
// //        "And this is another line within the same logging function, "
// //        "its name's %s", 2, nameof(info));
  
// //   debug("debugging log");
  
// //   return (apply(NormalStatus));
// // }

// Status MainArrayInsertAndRemove2(void)
// {
//   Stack ms = EMPTY;
//   fail(Stack_Create(&ms, sizeof(Memory), __COMPOUND_STACK_MAXIMUM__));
  
//   Memory mem1 = EMPTY;
//   Memory mem2 = EMPTY;
//   Memory mem3 = EMPTY;
//   fail(Memory_Create(&mem1, TInt8));
//   fail(Memory_Create(&mem2, TInt16));
//   fail(Memory_Create(&mem3, TInt32));
  
//   fail(Stack_Delete(&ms));
  
//   return (apply(NormalStatus));
// }

// Status MainArrayInsertAndRemove1(void)
// {
//   const int iarr[] = { 1, 2, 3 };
//   const size_t iarr_len = (sizeof(iarr) / sizeof(int));
  
//   Array arr = EMPTY;
//   fail(Array_Create(&arr, iarr_len));

//   Memory get = EMPTY;
  
//   for (register size_t i = 0; i < arr.length; i++) {
//     get = (Memory)EMPTY;
//     fail(Array_SetIdx(&arr, i, (Memory){
//       .addr = (void *)&iarr[i],
//       .type = EMPTY
//     }));
//     fail(Array_GetIdx(&arr, i, &get));
//     (void)printf("%d", cast(get, int));
//   }
  
//   Memory ins = {
//     .addr = (void *)0x1234,
//     .type = EMPTY
//   };

//   (void)printf("\n");
  
//   for (register size_t i = 0; i < arr.length; i++) {
//     fail(Array_GetIdx(&arr, i, &get));
//     (void)printf("%lu:\t%p\n", i, get.addr);
//   }

//   (void)printf("Inserting at 0...\n");
//   fail(Array_Insert(&arr, 0, ins));
  
//   (void)printf("Inserting at 4...\n");
//   fail(Array_Insert(&arr, 4, ins));  // HERE
  
//   (void)printf("Inserting at last...\n");
//   fail(Array_Insert(&arr, arr.length, ins));
  
//   for (register size_t i = 0; i < arr.length; i++) {
//     fail(Array_GetIdx(&arr, i, &get));
//     (void)printf("%lu:\t%p\n", i, get.addr);
//   }
  
//   fail(Array_Delete(&arr));
  
//   return (apply(NormalStatus));
// }

// Status MainArrayFunctions(void)
// {
//   const char *cstr = "Hello!";
//   const size_t cstr_len = strlen(cstr);
  
//   Array carr = EMPTY;
//   fail(Array_Create(&carr, cstr_len + 1));
  
//   (void)printf("=== carr ===\n");
//   for (register size_t i = 0; i < carr.length; i++) {
//     fail(Array_SetIdx(&carr, i, (Memory){
//       .addr = (void *)&cstr[i],
//       .type = EMPTY
//     }));
//     (void)printf("@%lu:  %p %s\n", i, carr.data[i].addr, carr.data[i].type.identifier);
//   }
  
//   (void)printf("\n");
  
//   Array carr1 = EMPTY;
//   fail(Array_CopyOf(&carr1, carr));
  
//   (void)printf("=== carr1 ===\n");
//   for (register size_t i = 0; i < carr1.length; i++) {
//     (void)printf("@%lu:  %p %s\n", i, carr.data[i].addr, carr.data[i].type.identifier);
//   }

//   (void)printf("lengths: %lu vs %lu\n", carr.length, carr1.length);
//   (void)printf("Memory_Equals: %d\n", Array_Equals(carr, carr1));
  
//   fail(Array_Delete(&carr1));
//   fail(Array_Delete(&carr));
  
//   return (apply(NormalStatus));
// }

// Status MainLoggingErrorStatus(CATS)
// {
//   char buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
//   zero(Status_Literalise((InvalidLiteralisingBuffer), buff),
//        return apply(ReadWriteError););
//   error(buff);

//   return (apply(NormalStatus));
// }

// Status MainCatLog(CATS)
// {
//   FILE *fp = NULL;
//   if (!(fp = fopen("/tmp/catlog", "w"))) {
//     warning("Failed to open file.");
//     return apply(ReadWriteError);
//   }
  
//   redir(stdout);
//   filter(0);

//   lowest("abab");
//   debug("buggy~");
//   info("what are you talking about?\nidk");  // Multi-line interrupt
//   warning("im big");
//   error("haha!");
//   fatal("omg");
//   highest("im everything");

//   info("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 "
//        "27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 "
//        "50");

//   redir(fp);

//   info("info");
  
//   (void)fclose(fp);
  
//   redir(stdout);
  
//   debug("You found me!!\nCongratulations!!!\n");

//   return (apply(NormalStatus));
// }

// Status MainMemoryAndStack(void)
// {
//   Stack memstk = EMPTY;
//   fail(Stack_Create(&memstk, sizeof(Memory), __COMPOUND_STACK_MAXIMUM__));
  
//   Memory mem = EMPTY;
//   fail(Memory_Create(&mem, TInt16));
  
//   (void)printf("%p %lu\n", mem.addr, mem.type.size);
  
//   mem = Memory_Reallocate(mem, TInt32);
  
//   (void)printf("%p %lu\n", mem.addr, mem.type.size);
  
//   fail(Memory_Delete(&mem));
  
//   (void)printf("%p %lu\n", mem.addr, mem.type.size);
  
//   fail(Stack_Delete(&memstk));
  
//   return (apply(NormalStatus));
// }

// Status StackSimplePerformanceDemo(void)
// {
//   const size_t len = 0xFFFF;
  
//   Stack stk = EMPTY;
//   fail(Stack_Create(&stk, sizeof(long long), len));
  
//   for (register size_t i = 0; i < len; i++) {
//     state(!Stack_Push(&stk, Main), (RuntimeError));
//   }
  
//   Stack_PopAll(&stk);
  
//   fail(Stack_Delete(&stk));
  
//   return (apply(NormalStatus));
// }

int main(void)
{
  /* Preprocesses. */
  StatusStack ss = EMPTY;
  quit_on_fail(StatusStack_Create(&ss, __COMPOUND_STACK_MAXIMUM__));
  StatusStack_SetGlobal(&ss);

  MemoryStack ms = EMPTY;
  quit_on_fail(MemoryStack_Create(&ms, __COMPOUND_STACK_MAXIMUM__));
  MemoryStack_SetGlobal(&ms);

  CatlogSender cs = EMPTY;
  quit_on_fail(CatlogSender_Create(&cs, (CatlogMessage)EMPTY, stdout));
  CatlogSender_SetGlobal(&cs);

  /* Processes. */
  handle(Main(), {

    /* Handle any non-"NormalStatus"-based Status. */
    nbelong(NormalStatus, {
      PrintStatus(_);
    })

    /* Postprocesses. */
    quit_on_fail(CatlogSender_Delete(&cs));
    quit_on_fail(MemoryStack_Delete(&ms));
    quit_on_fail(StatusStack_Delete(&ss));

    return _.value;
  })
}

// void PrintMemoryStack(const MemoryStack mstk)
// {
//   if (!mstk.length || !mstk.current) {
//     (void)printf("Empty Memory Stack"NEWLINE);
//     return;
//   }

//   for (register size_t i = 0; i < mstk.length; i++) {
//     (void)printf("%lu:  %p (%p)"NEWLINE, i, mstk.data[i].addr, mstk.current);
//   }
// }
