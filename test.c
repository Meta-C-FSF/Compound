#include <Compound/status.h>
#include <Compound/catlog.h>

Status Main(void)
{
  cat("Hello, Compound!");
  
  cat("\n");
  
  cat("The Status literalisation and printing of \""
    nameof(MaximumLiteralisationLengthExceeded)"\":");
  
  PrintStatusDump(apply(MaximumLiteralisationLengthExceeded));
  
  return apply(NormalStatus);
}

int main(void)
{
  return Main().value;
}
