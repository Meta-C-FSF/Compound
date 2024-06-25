#include <Compound/var.h>

int main(void)
{
  Var v1 = {
    .addr = malloc(sizeof(int)),
    .sz = sizeof(int)
  };
  
  Var v2 = (Var){v1.addr, v1.sz};
  
  wchar_t wbuff[UINT8_MAX + 1] = {};
  wchar_t *wp = wbuff;
  
  (void)var_literalise(v1, &wp);
  
  (void)wprintf(L"%ls\n", wp);
  
  (void)var_literalise(v2, &wp);
  
  (void)wprintf(L"%ls\n", wp);
  
  free(v1.addr);
  
  return 0;
}
