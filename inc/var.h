#ifndef COMPOUND_VAR
# define COMPOUND_VAR

#include <Compound/literary.h>
# include <stdio.h>

# include <Compound/common.h>
# include <Compound/memman.h>
# include <Compound/status.h>
# include <Compound/catlog.h>

# define VAR_LITERALISE_LENGTH  (16 + 9 + 10)
# define VAR_LITERALISE_FORMAT  "@[%p]: %ld"

typedef Memory Var;

Status Var_Create(liveness(DEAD, Var) *inst, size_t size, literalisation_t lit);
Status Var_CopyOf(liveness(DEAD, Var) *inst, liveness(ALIVE, Var) *other);
Status Var_Allocate(liveness(DEAD, Var) *inst);
Status Var_Reallocate(liveness(ALIVE, Var) *inst, size_t size);
Status Var_Release(liveness(ALIVE, Var) *inst);
Status Var_Delete(liveness(DEAD, Var) *inst);
// Status Var_Assign(Var *inst, Var *value);
Status Var_Literalise(liveness(ALIVE, Var) *inst, char *buff);
bool   Var_Equals(liveness(ALIVE, Var) *a, liveness(ALIVE, Var) *b);
void   VarUtils_Swap(liveness(ALIVE, Var) *v1, liveness(ALIVE, Var) *v2);

#endif  /* COMPOUND_VAR */
