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
  // PrintStatusDump(MaximumLiteralisationLengthExceeded);
  
  DEFSTATUS(TestStatus0, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &MaximumLiteralisationLengthExceeded);
  
  DEFSTATUS(TestStatus1, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus0);
  
  DEFSTATUS(TestStatus2, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus1);
  
  DEFSTATUS(TestStatus3, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus2);
  
  DEFSTATUS(TestStatus4, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus3);
  
  DEFSTATUS(TestStatus5, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus4);
  
  DEFSTATUS(TestStatus6, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus5);
  
  DEFSTATUS(TestStatus7, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus6);
  
  DEFSTATUS(TestStatus8, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus7);
  
  DEFSTATUS(TestStatus9, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus8);
  
  DEFSTATUS(TestStatus10, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus9);
  
  DEFSTATUS(TestStatus11, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus10);
  
  DEFSTATUS(TestStatus12, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus11);
  
  DEFSTATUS(TestStatus13, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus12);
  
  DEFSTATUS(TestStatus14, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus13);
  
  DEFSTATUS(TestStatus15, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus14);
  
  DEFSTATUS(TestStatus16, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus15);
  
  DEFSTATUS(TestStatus17, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus16);
  
  DEFSTATUS(TestStatus18, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus17);
  
  DEFSTATUS(TestStatus19, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus18);
  
  DEFSTATUS(TestStatus20, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus19);
  
  DEFSTATUS(TestStatus21, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus20);
  
  DEFSTATUS(TestStatus22, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus21);
  
  DEFSTATUS(TestStatus23, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus22);
  
  DEFSTATUS(TestStatus24, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus23);
  
  DEFSTATUS(TestStatus25, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus24);
  
  DEFSTATUS(TestStatus26, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus25);
  
  DEFSTATUS(TestStatus27, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus26);
  
  DEFSTATUS(TestStatus28, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus27);
  
  DEFSTATUS(TestStatus29, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus28);
  
  DEFSTATUS(TestStatus30, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus29);
  
  DEFSTATUS(TestStatus31, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus30);
  
  DEFSTATUS(TestStatus32, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus31);
  
  DEFSTATUS(TestStatus33, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus32);
  
  DEFSTATUS(TestStatus34, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus33);
  
  DEFSTATUS(TestStatus35, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus34);
  
  DEFSTATUS(TestStatus36, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus35);
  
  DEFSTATUS(TestStatus37, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus36);
  
  DEFSTATUS(TestStatus38, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus37);
  
  DEFSTATUS(TestStatus39, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus38);
  
  DEFSTATUS(TestStatus40, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus39);
  
  DEFSTATUS(TestStatus41, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus40);
  
  DEFSTATUS(TestStatus42, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus41);
  
  DEFSTATUS(TestStatus43, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus42);
  
  DEFSTATUS(TestStatus44, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus43);
  
  DEFSTATUS(TestStatus45, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus44);
  
  DEFSTATUS(TestStatus46, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus45);
  
  DEFSTATUS(TestStatus47, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus46);
  
  DEFSTATUS(TestStatus48, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus47);
  
  DEFSTATUS(TestStatus49, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus48);
  
  DEFSTATUS(TestStatus50, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus49);
  
  DEFSTATUS(TestStatus51, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus50);
  
  DEFSTATUS(TestStatus52, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus51);
  
  DEFSTATUS(TestStatus53, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus52);
  
  DEFSTATUS(TestStatus54, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus53);
  
  DEFSTATUS(TestStatus55, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus54);
  
  DEFSTATUS(TestStatus56, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus55);
  
  DEFSTATUS(TestStatus57, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus56);
  
  DEFSTATUS(TestStatus58, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus57);
  
  DEFSTATUS(TestStatus59, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus58);
  
  DEFSTATUS(TestStatus60, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus59);
  
  DEFSTATUS(TestStatus61, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus60);
  
  DEFSTATUS(TestStatus62, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus61);
  
  DEFSTATUS(TestStatus63, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus62);
  
  DEFSTATUS(TestStatus64, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus63);
  
  DEFSTATUS(TestStatus65, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus64);
  
  DEFSTATUS(TestStatus66, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus65);
  
  DEFSTATUS(TestStatus67, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus66);
  
  DEFSTATUS(TestStatus68, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus67);
  
  DEFSTATUS(TestStatus69, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus68);
  
  DEFSTATUS(TestStatus70, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus69);
  
  DEFSTATUS(TestStatus71, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus70);
  
  DEFSTATUS(TestStatus72, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus71);
  
  DEFSTATUS(TestStatus73, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus72);
  
  DEFSTATUS(TestStatus74, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus73);
  
  DEFSTATUS(TestStatus75, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus74);
  
  DEFSTATUS(TestStatus76, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus75);
  
  DEFSTATUS(TestStatus77, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus76);
  
  DEFSTATUS(TestStatus78, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus77);
  
  DEFSTATUS(TestStatus79, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus78);
  
  DEFSTATUS(TestStatus80, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus79);
  
  DEFSTATUS(TestStatus81, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus80);
  
  DEFSTATUS(TestStatus82, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus81);
  
  DEFSTATUS(TestStatus83, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus82);
  
  DEFSTATUS(TestStatus84, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus83);
  
  DEFSTATUS(TestStatus85, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus84);
  
  DEFSTATUS(TestStatus86, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus85);
  
  DEFSTATUS(TestStatus87, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus86);
  
  DEFSTATUS(TestStatus88, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus87);
  
  DEFSTATUS(TestStatus89, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus88);
  
  DEFSTATUS(TestStatus90, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus89);
  
  DEFSTATUS(TestStatus91, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus90);
  
  DEFSTATUS(TestStatus92, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus91);
  
  DEFSTATUS(TestStatus93, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus92);
  
  DEFSTATUS(TestStatus94, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus93);
  
  DEFSTATUS(TestStatus95, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus94);
  
  DEFSTATUS(TestStatus96, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus95);
  
  DEFSTATUS(TestStatus97, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus96);
  
  DEFSTATUS(TestStatus98, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus97);
  
  DEFSTATUS(TestStatus99, 1,
    "This status is used for displaying multi-layer of status dumping.",
    STATUS_NORMAL, &TestStatus98);
  
  
  PrintStatusDump(apply(TestStatus99));

  return apply(NormalStatus);
}

int main(void)
{
  return Main().value;
}
