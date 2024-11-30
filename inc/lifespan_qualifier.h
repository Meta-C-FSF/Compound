#ifndef COMPOUND_LIFESPAN_QUALIFIER_H
# define COMPOUND_LIFESPAN_QUALIFIER_H

typedef enum {
  STATIC = 0,  // Through out the entire lifespan of current programme.
  DYNAMIC = 1,
} LifespanQualifier;

#endif  /* COMPOUND_LIFESPAN_QUALIFIER_H */
