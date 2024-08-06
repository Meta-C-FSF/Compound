#ifndef COMPOUND_LITERARY_H
# define COMPOUND_LITERARY_H

# include <stdio.h>

# include <Compound/common.h>

typedef int (*literalisation_t)(void *, char *);

/* The default literalisation handler. */
static inline int Literalise(void *inst, char *buff)
{
  /* Simply write the address of @inst into @buff. */
  return (snprintf(buff, LITERALISATION_LENGTH_MAXIMUM, "%p", inst));
}

#endif  /* COMPOUND_LITERARY_H */
