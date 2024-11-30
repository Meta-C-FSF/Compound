#include <Compound/class_method.h>

Status ClassMethod_Create(ClassMethod *inst, const AccessPermissionQualifier perm,
                          const LifespanQualifier lfspn, const Type rtn,
                          const char *identity, const char *content,
                          const char *fmt, ...)
{
  avail(inst);
  avail(identity);
  
  inst->perm = perm;
  inst->lfspn = lfspn;
  inst->rtn = rtn;
  (void)strncpy(inst->identity, identity, CLASS_METHOD_IDENTITY_LENGTH_MAXIMUM);
  inst->content = (char *)content;
  inst->fmt = (char *)fmt;
  inst->parameters = (Array)EMPTY;
  fail(Array_Create(&inst->parameters, ClassMethod_ParamLength(fmt)));
  
  variadic({
    option('i', int, {
      ClassField curr = EMPTY;
      fail(ClassField_Create(&curr, PRIVATE, DYNAMIC, TInt, va_arg(ap, char *)));
      
      fail(Array_Insert(&inst->parameters, inst->parameters.length,))
    })
  })
}

Status ClassMethod_CopyOf(ClassMethod *inst, const ClassMethod other);

Status ClassMethod_Delete(ClassMethod *inst);

Status ClassMethod_Override(ClassMethod *inst, const char *content);
