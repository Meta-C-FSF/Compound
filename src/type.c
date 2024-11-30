#include <Compound/type.h>

bool Type_Equals(Type ty1, Type ty2)
{
  /* Returns true when either Type is NULL, regardless the nullities. */
  if (!ty1.identifier) {
    return (ty1.identifier == ty2.identifier);
  }
  
  return (
    (!strcmp(ty1.identifier, ty2.identifier)) &&
    ty1.size == ty2.size &&
    ty1.qualifier == ty2.qualifier
  );
}

size_t Type_Literalise(const Type ty, char *buff)
{
  if (!buff)  return 0;
  
  return snprintf(buff, LITERALISATION_LENGTH_MAXIMUM,
                  TYPE_LITERALISATION_FORMAT,
                  ty.identifier, ty.size, ty.qualifier);
}
