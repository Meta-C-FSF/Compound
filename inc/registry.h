#ifndef COMPOUND_REGISTRY_H
# define COMPOUND_REGISTRY_H

# include <Compound/array.h>

typedef struct {
  Array items;
  Array info;
} Registry;

static const Type TRegistry = {
  .identifier = nameof(Registry),
  .size = sizeof(Registry)
};

#endif  /* COMPOUND_REGISTRY_H */
