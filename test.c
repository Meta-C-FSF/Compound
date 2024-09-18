#include <Compound/memory.h>
#include <Compound/status.h>
#include <Compound/type.h>

// Status PrintStack(Stack *inst)
// {
//   avail(inst);
  
  
  
//   return apply(NormalStatus);
// }

// <Compound/StdLib>
static Type(pointer(TVoid)) M_Alloc(Memory(?) *inst, Type(constant(TUInt32)) size)
{
  // nonull(inst, apply(UnavailableInstance));
  // state(!cast(size, size_t), apply(InvalidSize));

  // state(!(inst->addr = malloc(cast(size, size_t))), apply(InsufficientMemory));
  
  // return apply(NormalStatus);
}

Status Main(void)  // Type
{
  REDEFTYPE(TVoidPointer, pointer(TVoid));
  
  (void)printf("%lu\n", TVoidPointer.size);
  
  // Memory mem = EMPTY;
  
  // Type _Ty0 = M_Alloc(&mem, );
  
  return apply(NormalStatus);
}

Status MainBasicTypes(void)
{
  DEFTYPE(TByte, 1);
  DEFTYPE(TWord, 2);
  DEFTYPE(TDoubleWord, 4);
  DEFTYPE(TQuadWord, 8);
  
  REDEFTYPE(TStaticConstantPointerOctoWord,
    statical(constant(pointer(resize(TQuadWord, (TQuadWord.size * 2))))));
  
  Memory var_byte = { .addr = malloc(TByte.size), .type = TByte };
  Memory var_word = { .addr = malloc(TWord.size), .type = TWord };
  Memory var_dword = { .addr = malloc(TDoubleWord.size), .type = TDoubleWord };
  Memory var_qword = { .addr = malloc(TQuadWord.size), .type = TQuadWord };
  Memory var_static_const_pointer_octo_word = { .addr = malloc(TStaticConstantPointerOctoWord.size), .type = TStaticConstantPointerOctoWord };

  cast(var_byte, int) = 10;

  free((void *)var_static_const_pointer_octo_word.addr);
  free((void *)var_byte.addr);
  free((void *)var_qword.addr);
  free((void *)var_dword.addr);
  free((void *)var_word.addr);
   
  // REDEFTYPE(TPointerWord, TWord);
  // REDEFTYPE(TPointerDoubleWord, TDoubleWord);
  
  (void)printf("Type identifier of "nameof(TStaticConstantPointerOctoWord)": "
    "%s\n", TStaticConstantPointerOctoWord.identifier);
  
  return apply(NormalStatus);
}

Status MainStrTok(void)
{
  // char MESSAGE[] = "#include <stdio.h>\n#include <stdlib.h>\nint main(void)\n{\n\n  return 0;\n}\n";
  char buff[10000] = EMPTY;
  FILE *fp = fopen("/tmp/content", "r");
  when(!(fread(buff, sizeof(char), 10000, fp)), {
    return apply(value(annot(ReadWriteError, "Failure on fread."), _));
  });
  
  register int counter = 0;
  const char *restrict delim = "\n";
  char *tok_curr = strtok(buff, delim);
  do {
    (void)printf("%d\t%s\n", ++counter, tok_curr);
    tok_curr = strtok(NULL, delim);
  } while (tok_curr);
  
  when((fclose(fp)), {
    return apply(value(annot(ReadWriteError, "Failure on fclose."), _));
  });
  
  return apply(NormalStatus);
}

// Status Main(void)
// {
//   Stack stk = EMPTY;
//   fail(Stack_Create(&stk, sizeof(Memory *), 255));
  
//   const int max = Stack_MaxLength(stk);
//   (void)printf("len: %d\n", max);

//   Memory mem = {
//     .addr = malloc(sizeof(int)),
//     .size = sizeof(int),
//     .usage = 1,
//     .alive = true
//   };
  
//   (void)fprintf(stderr, nameof(mem)":  @%p, %lu\n", mem.addr, mem.size);

//   for (register int i = 0; i < max; i++) {
//     if (!Stack_Push(&stk, &mem)) {
//       // (void)printf("hit roof at %d!\n", i);
//       break;
//     }
//     // (void)printf("pushed at %d\n", i);
//   }
  
//   for (register int i = 0; i < max; i++) {
//     if (!Stack_Pop(&stk)) {
//       // (void)printf("hit bottom at %d!\n", max - i);
//       break;
//     }
//     // (void)printf("popped at %d\n", max - i);
//   }

//   (void)fprintf(stderr, nameof(mem)":  @%p, %lu\n", mem.addr, mem.size);
//   free((void *)mem.addr);
  
//   fail(Stack_Delete(&stk));
  
//   return apply(NormalStatus);
// }

int main(void)
{
  int rtn = 0;
  notok(Main(), {
    PrintStatusDump(_);
    rtn = _.value;
  })
  
  return rtn;
}
