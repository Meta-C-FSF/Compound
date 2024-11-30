#include <Compound/class_register.h>

Status ClassRegister_Search(ClassRegister *inst, Class *store,
                            const char *identity)
{
  avail(inst);
  avail(store);
  avail(identity);
  
  /* testing. */
  
  RETURN(NormalStatus);
}
