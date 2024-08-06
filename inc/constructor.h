#ifndef COMPOUND_CONSTRUCTOR_H
# define COMPOUND_CONSTRUCTOR_H

# include <Compound/var.h>

typedef Status (*constructor_t)(Var(?) *, Var(?) *);

/* The default construction handler. */
static inline Status Constructor(Var(?) *inst, Var(?) *param)
{
  nonull(inst, apply(UnavailableInstance));
  nonull(param, apply(UnavailableParameter));
  
  return apply(FunctionNotDeployed);
}

#endif  /* COMPOUND_CONSTRUCTOR_H */
