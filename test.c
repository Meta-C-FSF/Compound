#include <Compound/array.h>
#include <Compound/catlog.h>
#include <Compound/common.h>
#include <Compound/memman.h>
#include <Compound/status.h>
#include <Compound/var.h>

Status func(void)
{
  return apply(
    error(ErrorStatus, "This function does not accept any parameters!"));
}

__attribute__((constructor))
void __CONSTRUCT__() {
  cat("Hello, Compound!\n");
}

__attribute__((destructor))
void __DESTRUCT__() {}

Status Main(void)
{
  // Memory mem1;
  // seek(Memory_Create(&mem1, INT64_MAX), {
  //   print_status(_);
  // });
  // seek(Memory_Allocate(&mem1), {
  //   print_status(_);
  // });
  // seek(Memory_Allocate(&mem1), {
  //   print_status(_);
  // });
  // seek(Memory_Release(&mem1), {
  //   print_status(_);
  // });
  // seek(Memory_Release(&mem1), {
  //   print_status(_);
  // });
  // seek(Memory_Delete(&mem1), {
  //   print_status(_);
  // });
  
  // PrintStatusDump(unknown(normal(MaximumLiteralisationLengthExceeded, ":O"), "OMGIDKWTD", 1));
  // PrintStatusDump(apply(extend(MaximumLiteralisationLengthExceeded, normal(UnavailableBuffer, "OMGIDKWTD"))));
  PrintStatusDump(MaximumLiteralisationLengthExceeded);

  return apply(NormalStatus);
}

int main(void)
{
  return Main().value;
}



