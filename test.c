#include <Compound/array.h>
#include <Compound/catlog.h>
#include <Compound/common.h>
#include <Compound/function.h>
#include <Compound/memman.h>
#include <Compound/status.h>
#include <Compound/type.h>
#include <Compound/var.h>

Status func(void)
{
  return apply(
    annot(ErrorStatus, "This function does not accept any parameters!"));
}

// void __CONSTRUCT__() {
//   MemoryPool 
// }

// void __DESTRUCT__() {}

# define PrintVar(v)  {\
  char buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;\
  unsure(value(TraditionalFunctionReturn, v.Literalise(&v, buff)), !_.value,\
  {\
    return annot(ReadWriteError, _.description);\
  })\
  cat(buff);\
}

int test_var_literalise(void *inst, char *buff)
{
  nonull(inst, 0);
  nonull(buff, 0);
  
  // return snprintf(buff, LITERALISATION_LENGTH_MAXIMUM, VAR_LITERALISE_FORMAT,
  //   ((Var *)inst)->addr, ((Var *)inst)->size);
  
  return snprintf(buff, LITERALISATION_LENGTH_MAXIMUM,
    VAR_LITERALISE_FORMAT"\talive:%d\t%p",
    ((Var *)inst)->addr, ((Var *)inst)->size, ((Var *)inst)->liveness,
    ((Var *)inst)->Literalise);
}

int test_array_literalise(void *inst, char *buff)
{
  nonull(inst, 0);
  nonull(buff, 0);
  
  /* Literalise members. (Var_Literalise) */
  int written = 0;
  char memb_buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
  for (register int i = 0; i < ((Array *)inst)->len; i++) {
    written += ((Array *)inst)->members[i].Literalise(&((Array *)inst)->members[i], memb_buff);
  }
  const int memb_buff_len = strlen(memb_buff);
  
  written +=
    snprintf(((buff + written)),
      LITERALISATION_LENGTH_MAXIMUM,
      "%s, %d, %lu, %d, %p",
      memb_buff, ((Array *)inst)->len, ((Array *)inst)->size,
      ((Array *)inst)->liveness, ((Array *)inst)->Literalise);
  
  return written;
}

# define PrintArray(a, buff)  {\
  unsure(value(TraditionalFunctionReturn, a.Literalise(&a, buff)), !_.value,\
  {\
    return annot(ReadWriteError, _.description);\
  })\
  cat(buff);\
}

Status Main(void)  // ArrayInsertion
{
  Array arr = EMPTY;
  fail(Array_Create(&arr, 3, sizeof(long long), NULL));
  fail(Array_Allocate(&arr));
  
  Array ins = EMPTY;
  fail(Array_Create(&ins, 4, 32, NULL));
  fail(Array_Allocate(&ins));
  
  /* Perform insertion. */
  fail(ArrayUtils_Insert(&arr, &ins, 2));
  
  fail(Array_Release(&ins));
  fail(Array_Delete(&ins));
  
  fail(Array_Release(&arr));
  fail(Array_Delete(&arr));
  
  return apply(NormalStatus);
}

Status MainArrayCopy(void)
{
  Array arr1 = EMPTY;
  Array arr2 = EMPTY;
  
  fail(Array_Create(&arr1, 5, sizeof(int), NULL));
  fail(Array_Create(&arr2, 10, sizeof(int), NULL));
  
  fail(Array_Allocate(&arr1));
  fail(Array_Allocate(&arr2));
  
  cat("Before copying.");
  cat("arr1");
  for (register int i = 0; i < arr1.len; i++) {
    PrintVar(arr1.members[i]);
  }
  cat("arr2");
  for (register int i = 0; i < arr2.len; i++) {
    PrintVar(arr2.members[i]);
  }
  
  /* Perform copying. */  
  fail(Array_CopyOf(&arr1, &arr2));
  
  cat("After copying.")
  cat("arr1");
  for (register int i = 0; i < arr1.len; i++) {
    PrintVar(arr1.members[i]);
  }
  cat("arr2");
  for (register int i = 0; i < arr2.len; i++) {
    PrintVar(arr2.members[i]);
  }
  
  fail(Array_Release(&arr2));
  fail(Array_Release(&arr1));
  
  fail(Array_Delete(&arr2));
  fail(Array_Delete(&arr1));
  
  return apply(NormalStatus);
}

Status MainArrayOperations(void)
{
  char buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
  Array arr = EMPTY;
  
  fail(Array_Create(&arr, 10, sizeof(int), test_array_literalise));
  
  fail(Array_Allocate(&arr));
  PrintArray(arr, buff);
  
  fail(Array_Reallocate(&arr, sizeof(double)));
  PrintArray(arr, buff);
  
  fail(Array_Release(&arr));
  PrintArray(arr, buff);
  
  fail(Array_Delete(&arr));
  
  return apply(NormalStatus);
}

// Status MainVarOperations(void)
// {
//   char buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
//   Var v1 = EMPTY;
  
//   fail(Var_Create(&v1, sizeof(int), test_var_literalise));  
//   PrintVar(v1, buff);
  
//   fail(Var_Allocate(&v1));
//   PrintVar(v1, buff);
  
//   fail(Var_Reallocate(&v1, sizeof(double)));
//   PrintVar(v1, buff);
  
//   fail(Var_Release(&v1));
//   PrintVar(v1, buff);

//   fail(Var_Delete(&v1));
  
//   return apply(NormalStatus);
// }

//////////////////////////////// LEGACY TESTS /////////////////////////////////

// Status MainType(void)
// {
//   Type t1 = type(Status);
//   Type t2 = type(Function);

//   cat(t1.identity);
//   cat(t2.identity);

//   return apply(NormalStatus);
// }

// Status MainFromCharBuff(void)
// {
//   String str = EMPTY;
//   fail(StringUtils_FromCharBuff(&str, "Hello, Compound!"));
//   
//   
//   
//   fail(String_Delete(&str));
//   
//   return apply(NormalStatus);
// }

// Status MainConventionalStringWithCompoundArrayInsertingOperation(void)
// {
//   Array arr = EMPTY;
//   Var elem = EMPTY;
  
//   fail(Var_Create(&elem, sizeof(char)));
  
//   cast(&elem, char) = 'e';
  
//   fail(Array_Create(&arr, 3, sizeof(char)));  // "Or"  ->  "Ore"
//   cast(arr.members[0], char) = 'O';
//   cast(arr.members[1], char) = 'r';
//   cast(arr.members[2], char) = '\0';
  
//   /* Insert at the end (exclude the termination character). */
//   fail(ArrayUtils_Insert(&arr, &elem, arr.len));
  
//   fail(Array_Delete(&arr));
//   fail(Var_Delete(&elem));
  
//   return apply(NormalStatus);
// }

// Status MainConventionalArrayAndCompoundArray(void)
// {
//   Array fruits = EMPTY;
//   fail(Array_Create(&fruits, 5, sizeof(char **)));
  
//   char *_fruits[] = { "Apple", "Banana", "Orange", "Pear", "Grape" };
  
//   /* Initialising fruits. */
//   for (register int i = 0; i < 5; i++) {
//     cast(fruits.members[i], char *) = _fruits[i];
//   }
  
//   /* Literalise array. */
//   for (register int i = 0; i < fruits.len; i++) {
//     (void)printf("%d\t%s\n", i, cast(fruits.members[i], char *));
//   }
  
//   fail(Array_Delete(&fruits));  
  
//   return apply(NormalStatus);
// }

// Status MainArrayComparisonTest(void)
// {
//   Array arr1 = EMPTY;
//   fail(Array_Create(&arr1, 10, 10));
  
//   Array arr2 = EMPTY;
//   fail(Array_Create(&arr2, 10, 10));
  
//   if (Array_Equals(&arr1, &arr2)) {
//     cat("Equal!");
//   } else {
//     cat("Not equal!");
//   }
  
//   Array_Delete(&arr2);
//   Array_Delete(&arr1);
  
//   return apply(NormalStatus);
// }

// Status MainMemoryOperationTest(void)
// {
//   Memory mem = EMPTY;
//   fail(Memory_Create(&mem, sizeof(double)));
  
//   fail(Memory_Allocate(&mem));
  
//   (void)printf("%p:%ld\n", mem.addr, mem.size);
  
//   fail(Memory_Reallocate(&mem, sizeof(char)));

//   (void)printf("%p:%ld\n", mem.addr, mem.size);
  
//   fail(Memory_Release(&mem));
  
//   fail(Memory_Delete(&mem));
  
//   return apply(NormalStatus);
// }

// int tfunc(void)
// {
//   vfail(apply(ErrorStatus), 1);
  
//   return 0;
// }

// Status MainMacroFailsTest(void)
// {  
//   unsure(apply(value(TraditionalFunctionReturn, tfunc())), _.value,
//     nest(_, __, fails(shift(__, STATUS_ERROR), "Failed on execution from tfunc.")));
  
//   return apply(NormalStatus);
// }

// Status MainArrayCreateAndDeleteWithModulatedMemberAccessing(void)
// {
//   Array arr = EMPTY;
//   fail(Array_Create(&arr, 8, sizeof(int)));
  
//   for (register int i = 0; i < arr.len; i++) {
//     Var current = EMPTY;

//     // fails(Var_Create(&current, arr.members[0].size),
//     //   "Failed to create Var current.");

//     state(!current.alive || !arr.members[i].alive,
//       apply(InvalidOperationBetweenAliveAndNonAlive));
//     assign(current, arr.members[i], int);

//     char buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
//     unsure(Var_Literalise(&current, buff), !_.value, {
//       return annot(_, "Failed to literalise Var current.");
//     })
    
//     (void)printf("%s\n", buff);
    
//     // Var_Delete(&current);
//   }
  
//   cat("Get:");
//   Var get = EMPTY;
  
//   fails(Var_Create(&get, arr.members[4].size), "Failed to create Var \"get\".");

//   state(!get.alive || !arr.members[4].alive,
//     apply(InvalidOperationBetweenAliveAndNonAlive));
//   assign(get, arr.members[4], int);
  
//   char buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
//   unsure(Var_Literalise(&get, buff), !_.value, {
//     return annot(_, "Failed to literalise Var current.");
//   })
  
//   Var_Delete(&get);
  
//   // Array_Delete(&arr);
  
//   return apply(NormalStatus);
// }

// Status MainArrayCreateAndDeleteWithTraditionalMemberAccessing(void)
// {
//   // const int len = 8;
  
//   // int iarr[] = {
//   //   1, 2, 4, 8, 16, 32, 64, 128
//   // };
  
//   // Array arr;
//   // fails(Array_Create(&arr, len, sizeof(__typeof__(iarr[0]))),
//   //   "Failed to create an array instance.");
  
//   // /* Array member assignments with iarr. */
//   // for (register int i = 0; i < arr.len; i++) {
//   //   arr.members[i].addr = &iarr[i];
//   // }
  
//   // for (register int i = 0; i < arr.len; i++) {
//   //   (void)printf("%d\n", i);
    
//   //   for (register int j = 0; j < *(int *)arr.members[i].addr; j++) {
//   //     (void)printf("#");
//   //   }
    
//   //   (void)printf("\n");
//   // }
  
//   // // Array_Delete(&arr);


//   Array arr = EMPTY;
//   fail(Array_Create(&arr, 8, sizeof(long long)));
  
//   for (register int i = 0; i < arr.len; i++) {
//     cast(arr.members[i], long long) = INT64_MAX;
//     (void)printf("%lld\n", cast(arr.members[i], long long));
//   }
  
//   Array_Delete(&arr);
  
//   return apply(NormalStatus);
// }

// Status MainStatus(void)
// {
//   // Memory mem1;
//   // seek(Memory_Create(&mem1, INT64_MAX), {
//   //   print_status(_);
//   // });
//   // seek(Memory_Allocate(&mem1), {
//   //   print_status(_);
//   // });
//   // seek(Memory_Allocate(&mem1), {
//   //   print_status(_);
//   // });
//   // seek(Memory_Release(&mem1), {
//   //   print_status(_);
//   // });
//   // seek(Memory_Release(&mem1), {
//   //   print_status(_);
//   // });
//   // seek(Memory_Delete(&mem1), {
//   //   print_status(_);
//   // });
  
//   // PrintStatusDump(unknown(normal(MaximumLiteralisationLengthExceeded, ":O"), "OMGIDKWTD", 1));
//   // PrintStatusDump(apply(extend(MaximumLiteralisationLengthExceeded, normal(UnavailableBuffer, "OMGIDKWTD"))));
//   // PrintStatusDump(MaximumLiteralisationLengthExceeded);
  
//   DEFSTATUS(TestStatus0, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &MaximumLiteralisationLengthExceeded);
  
//   DEFSTATUS(TestStatus1, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus0);
  
//   DEFSTATUS(TestStatus2, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus1);
  
//   DEFSTATUS(TestStatus3, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus2);
  
//   DEFSTATUS(TestStatus4, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus3);
  
//   DEFSTATUS(TestStatus5, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus4);
  
//   DEFSTATUS(TestStatus6, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus5);
  
//   DEFSTATUS(TestStatus7, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus6);
  
//   DEFSTATUS(TestStatus8, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus7);
  
//   DEFSTATUS(TestStatus9, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus8);
  
//   DEFSTATUS(TestStatus10, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus9);
  
//   DEFSTATUS(TestStatus11, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus10);
  
//   DEFSTATUS(TestStatus12, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus11);
  
//   DEFSTATUS(TestStatus13, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus12);
  
//   DEFSTATUS(TestStatus14, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus13);
  
//   DEFSTATUS(TestStatus15, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus14);
  
//   DEFSTATUS(TestStatus16, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus15);
  
//   DEFSTATUS(TestStatus17, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus16);
  
//   DEFSTATUS(TestStatus18, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus17);
  
//   DEFSTATUS(TestStatus19, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus18);
  
//   DEFSTATUS(TestStatus20, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus19);
  
//   DEFSTATUS(TestStatus21, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus20);
  
//   DEFSTATUS(TestStatus22, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus21);
  
//   DEFSTATUS(TestStatus23, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus22);
  
//   DEFSTATUS(TestStatus24, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus23);
  
//   DEFSTATUS(TestStatus25, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus24);
  
//   DEFSTATUS(TestStatus26, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus25);
  
//   DEFSTATUS(TestStatus27, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus26);
  
//   DEFSTATUS(TestStatus28, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus27);
  
//   DEFSTATUS(TestStatus29, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus28);
  
//   DEFSTATUS(TestStatus30, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus29);
  
//   DEFSTATUS(TestStatus31, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus30);
  
//   DEFSTATUS(TestStatus32, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus31);
  
//   DEFSTATUS(TestStatus33, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus32);
  
//   DEFSTATUS(TestStatus34, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus33);
  
//   DEFSTATUS(TestStatus35, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus34);
  
//   DEFSTATUS(TestStatus36, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus35);
  
//   DEFSTATUS(TestStatus37, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus36);
  
//   DEFSTATUS(TestStatus38, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus37);
  
//   DEFSTATUS(TestStatus39, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus38);
  
//   DEFSTATUS(TestStatus40, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus39);
  
//   DEFSTATUS(TestStatus41, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus40);
  
//   DEFSTATUS(TestStatus42, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus41);
  
//   DEFSTATUS(TestStatus43, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus42);
  
//   DEFSTATUS(TestStatus44, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus43);
  
//   DEFSTATUS(TestStatus45, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus44);
  
//   DEFSTATUS(TestStatus46, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus45);
  
//   DEFSTATUS(TestStatus47, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus46);
  
//   DEFSTATUS(TestStatus48, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus47);
  
//   DEFSTATUS(TestStatus49, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus48);
  
//   DEFSTATUS(TestStatus50, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus49);
  
//   DEFSTATUS(TestStatus51, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus50);
  
//   DEFSTATUS(TestStatus52, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus51);
  
//   DEFSTATUS(TestStatus53, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus52);
  
//   DEFSTATUS(TestStatus54, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus53);
  
//   DEFSTATUS(TestStatus55, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus54);
  
//   DEFSTATUS(TestStatus56, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus55);
  
//   DEFSTATUS(TestStatus57, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus56);
  
//   DEFSTATUS(TestStatus58, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus57);
  
//   DEFSTATUS(TestStatus59, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus58);
  
//   DEFSTATUS(TestStatus60, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus59);
  
//   DEFSTATUS(TestStatus61, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus60);
  
//   DEFSTATUS(TestStatus62, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus61);
  
//   DEFSTATUS(TestStatus63, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus62);
  
//   DEFSTATUS(TestStatus64, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus63);
  
//   DEFSTATUS(TestStatus65, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus64);
  
//   DEFSTATUS(TestStatus66, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus65);
  
//   DEFSTATUS(TestStatus67, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus66);
  
//   DEFSTATUS(TestStatus68, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus67);
  
//   DEFSTATUS(TestStatus69, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus68);
  
//   DEFSTATUS(TestStatus70, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus69);
  
//   DEFSTATUS(TestStatus71, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus70);
  
//   DEFSTATUS(TestStatus72, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus71);
  
//   DEFSTATUS(TestStatus73, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus72);
  
//   DEFSTATUS(TestStatus74, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus73);
  
//   DEFSTATUS(TestStatus75, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus74);
  
//   DEFSTATUS(TestStatus76, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus75);
  
//   DEFSTATUS(TestStatus77, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus76);
  
//   DEFSTATUS(TestStatus78, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus77);
  
//   DEFSTATUS(TestStatus79, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus78);
  
//   DEFSTATUS(TestStatus80, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus79);
  
//   DEFSTATUS(TestStatus81, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus80);
  
//   DEFSTATUS(TestStatus82, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus81);
  
//   DEFSTATUS(TestStatus83, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus82);
  
//   DEFSTATUS(TestStatus84, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus83);
  
//   DEFSTATUS(TestStatus85, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus84);
  
//   DEFSTATUS(TestStatus86, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus85);
  
//   DEFSTATUS(TestStatus87, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus86);
  
//   DEFSTATUS(TestStatus88, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus87);
  
//   DEFSTATUS(TestStatus89, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus88);
  
//   DEFSTATUS(TestStatus90, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus89);
  
//   DEFSTATUS(TestStatus91, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus90);
  
//   DEFSTATUS(TestStatus92, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus91);
  
//   DEFSTATUS(TestStatus93, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus92);
  
//   DEFSTATUS(TestStatus94, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus93);
  
//   DEFSTATUS(TestStatus95, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus94);
  
//   DEFSTATUS(TestStatus96, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus95);
  
//   DEFSTATUS(TestStatus97, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus96);
  
//   DEFSTATUS(TestStatus98, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus97);
  
//   DEFSTATUS(TestStatus99, 1,
//     "This status is used for displaying multi-layer of status dumping.",
//     STATUS_NORMAL, &TestStatus98);
  
  
//   PrintStatusDump(apply(TestStatus99));

//   return apply(NormalStatus);
// }

///////////////////////////////////////////////////////////////////////////////

int main(void)
{
  int rtn = 0;
  notok(Main(), {
    rtn = _.value;
    PrintStatusDump(_);
  })
  
  return rtn;
}
