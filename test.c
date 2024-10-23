#include <Compound/catlog.h>
#include <Compound/common.h>
#include <Compound/memory.h>
#include <Compound/platform.h>
#include <Compound/stack.h>
#include <Compound/status.h>
#include <Compound/type.h>

Status MainCatLog(void);

Status Main(void)
{
  int i = 4;
  while (--i) {
    char buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
    zero(Status_Literalise(((Status *)&InvalidLiteralisingBuffer), buff).value,
      return apply(ReadWriteError););
    error(buff);
    
    info("wow, have\nyou ever been here\nbefore?\n");
  }
  
  return MainCatLog();
}

Status MainCatLog(void)
{
  redir(stdout);
  filter(0);
  
  lowest("abab");
  debug("buggy~");
  info("what are you talking about?\nidk");  // Multi-line interrupt
  warning("im big");
  error("haha!");
  fatal("omg");
  highest("im everything");
  
  info("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 "
       "27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 "
       "50");
  
  // /* Log user's input. */
  // char buff[CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM] = EMPTY;
  // size_t bread = 0;
  // zero(bread = fread(buff, sizeof(buff[0]), CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM, stdin),
  //   return apply(NoBytesWereRead););
  // buff[CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM - 1] = 0;
  // (void)printf("bread: %lu\n", bread);
  // (void)printf("input string length: %lu\n", strlen(buff));
  // info(buff);

  FILE *fp = NULL;
  if (!(fp = fopen("/tmp/catlog", "w"))) {
    warning("Failed to open file.");
    return apply(ReadWriteError);
  }

  redir(fp);

  info("info");
  
  (void)fclose(fp);
  
  warning("This message will not be sent successfully.");
  
  redir(stdout);
  
  debug("You found me!!");
  
  // FILE *fp = fopen("/tmp/catlog", "w");
  // redir(fp);
  
  // regular("what are you talking about?");
  // critical("haha!");
  // none("abab");
  // minor("minority");
  // fatal("omg");
  // debug("buggy~");
  // major("im big");
  // all("im everything");
  
  // (void)fclose(fp);
  
  return apply(NormalStatus);
}

Status MainMemoryAndStack(void)
{
  Stack memstk = EMPTY;
  fail(Stack_Create(&memstk, sizeof(Memory), __COMPOUND_STACK_MAXIMUM__));
  
  Memory mem = EMPTY;
  fail(Memory_Create(&mem, TInt16, &memstk));
  
  (void)printf("%p %lu\n", mem.addr, mem.type.size);
  
  mem = Reallocate(mem, TInt32);
  
  (void)printf("%p %lu\n", mem.addr, mem.type.size);
  
  fail(Memory_Delete(&mem));
  
  (void)printf("%p %lu\n", mem.addr, mem.type.size);
  
  fail(Stack_Delete(&memstk));
  
  return apply(NormalStatus);
}

// Status MainCompoundStackMaximum(void)
// {
//   Stack(Memory) allocations = EMPTY;
//   fail(Stack_Create(&allocations, sizeof(Memory), __COMPOUND_STACK_MAXIMUM__));
  
//   Memory mem = EMPTY;
//   fail(Memory_Create(&allocations, &mem, sizeof(double)));
  
//   cast(mem, double) = 3.14;
  
//   (void)printf("%p: %lf\n", &mem, cast(mem, double));
  
//   fail(Stack_Delete(&allocations));
//   return apply(NormalStatus);
// }

Status StackSimplePerformanceDemo(void)
{
  const size_t len = 0xFFFF;
  
  Stack stk = EMPTY;
  fail(Stack_Create(&stk, sizeof(long long), len));
  
  for (register size_t i = 0; i < len; i++) {
    state(!Stack_Push(&stk, Main), apply(RuntimeError));
  }
  
  Stack_PopAll(&stk);
  
  fail(Stack_Delete(&stk));
  
  return apply(NormalStatus);
}

int main(void)
{
  int rtn = 0;
  notok(Main(), {
    PrintStatusDump(_);
    rtn = _.value;
  })
  
  return rtn;
}
