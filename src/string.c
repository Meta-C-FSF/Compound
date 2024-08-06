#include <Compound/string.h>

Status String_Create(String *inst, Char sample, int len)
{
  nonull(inst, apply(UnavailableInstance));
  state()
}

Status StringUtils_FromCharBuff(String *inst, char const *buff)
{
  nonull(inst, apply(UnavailableInstance));
  nonull(buff, apply(UnavailableBuffer));
  state(inst->alive, apply(InstanceStillAlive));

  /* Create array instance for string. */
  const int bufflen = strlen(buff);
  fails(Array_Create(inst, bufflen + 1, sizeof(char)),
    "Failed on creating array for string instance.");
  
  /* Assign content from buff. */
  for (register int i = 0; i < bufflen; i++) {
    cast(inst->members[i], char) = buff[i];
  }
  
  /* Assign termination character. */
  cast(inst->members[bufflen], char) = '\0';
  
  return apply(NormalStatus);
}

Status StringUtils_FromWideCharBuff(String *inst, wchar_t const *buff)
{
  nonull(inst, apply(UnavailableInstance));
  nonull(buff, apply(UnavailableBuffer));
  state(inst->alive, apply(InstanceStillAlive));

  /* Create array instance for string. */
  const int bufflen = wcslen(buff);
  fails(Array_Create(inst, bufflen + 1, sizeof(wchar_t)),
    "Failed on creating array for string instance.");
  
  /* Assign content from buff. */
  for (register int i = 0; i < bufflen; i++) {
    cast(inst->members[i], wchar_t) = buff[i];
  }
  
  /* Assign termination character. */
  cast(inst->members[bufflen], wchar_t) = '\0';
  
  return apply(NormalStatus);
}

Status StringUtils_ToCharBuff(String *inst, char const *store);

Status StringUtils_ToWideCharBuff(String *inst, wchar_t const *store);
