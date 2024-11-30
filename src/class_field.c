#include <Compound/class_field.h>

Status ClassField_Create(ClassField *inst, const AccessPermissionQualifier perm,
                         const LifespanQualifier lfspn, const Memory data,
                         const char *identity)
{
  avail(inst);
  avail(identity);
  
  inst->perm = perm;
  inst->lfspn = lfspn;
  inst->data = data;
  (void)strncpy(inst->identity, identity, CLASS_FIELD_IDENTITY_LENGTH_MAX);
  
  RETURN(NormalStatus);
}

Status ClassField_CopyOf(ClassField *inst, const ClassField other)
{
  avail(inst);
  
  inst->perm = other.perm;
  inst->lfspn = other.lfspn;
  (void)Memory_CopyOf(&inst->data, &other.data);
  (void)strncpy(inst->identity, other.identity, CLASS_FIELD_IDENTITY_LENGTH_MAX);
  
  RETURN(NormalStatus);
}

Status ClassField_Delete(ClassField *inst)
{
  avail(inst);
  
  inst->perm = 0;
  inst->lfspn = 0;
  (void)Memory_Delete(&inst->data);
  (void)memset(inst->identity, 0, CLASS_FIELD_IDENTITY_LENGTH_MAX);
  
  RETURN(NormalStatus);
}

bool ClassField_Equals(const ClassField field1, const ClassField field2)
{
  return (field1.perm == field2.perm
          && field1.lfspn == field2.lfspn
          && Memory_Equals(field1.data, field2.data)
          && (!(strcmp(field1.identity, field2.identity))));
}
