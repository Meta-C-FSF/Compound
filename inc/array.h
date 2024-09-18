#ifndef COMPOUND_ARRAY_H
# define COMPOUND_ARRAY_H

# include <Compound/memory.h>

typedef struct {
  /* A Memory pointer to the array instance. */
  const Memory *data;
  const int len;
  bool alive;
} Array;

static const Type TArray = {
  .identifier = nameof(Array),
  .size = sizeof(Array)
};

#endif  /* COMPOUND_ARRAY_H */
