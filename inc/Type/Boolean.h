#ifndef COMPOUND_TYPE_BOOLEAN_H
# define COMPOUND_TYPE_BOOLEAN_H

# include <stdbool.h>

typedef struct _Boolean {
  bool value;
  const bool default_value;
  struct _Boolean (*Toggle)();
  int (*Literalise)(char *);
  struct _Boolean (*Equals)(struct _Boolean *);
  struct _Boolean (*const CastFrom)(bool);
} Boolean;

Boolean Boolean_Toggle();
int Boolean_Literalise(char *buff);
Boolean Boolean_Equals(Boolean *other);
Boolean Boolean_ValueOf(bool value);

static Boolean GlobalBoolean = {
  .value = false,
  .default_value = false,
  .Toggle = Boolean_Toggle,
  .Literalise = Boolean_Literalise,
  .Equals = Boolean_Equals,
  .CastFrom = Boolean_ValueOf
};

#endif  /* COMPOUND_TYPE_BOOLEAN_H */
