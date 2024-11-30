#include <Compound/class.h>

Status Class_Create(Class *inst, const AccessPermissionQualifier perm,
                    const LifespanQualifier lfspn, const char *identity)
{
  avail(inst);
  state(!identity, InvalidClassIdentity);
  
  RETURN(NormalStatus);
}

Status Class_CopyOf(Class *inst, const Class other);

Status Class_Delete(Class *inst);

bool   Class_Equals(const Class class1, const Class class2);

Status Class_Literalise(Class *inst, char *buff)
{
  avail(inst);
  avail(buff);
  
  /* testing. */
  (void)printf("%s"NEWLINE, inst->identity);
  
  RETURN(NormalStatus);
}
