#ifndef COMPOUND_DESTRUCTOR_H
# define COMPOUND_DESTRUCTOR_H

# include <Compound/var.h>

typedef Status (*destructor_t)(Var(?) *);

/* The default destruction handler. */
static inline Status Destructor(Var(?) *inst)
{
  nonull(inst, apply(UnavailableInstance));
  
  return apply(FunctionNotDeployed);
}

#endif  /* COMPOUND_DESTRUCTOR_H */
