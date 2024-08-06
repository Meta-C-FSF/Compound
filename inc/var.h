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

Status Var_Create(Var *inst, size_t size, literalisation_t lit);
Status Var_Allocate(Memory *inst);
Status Var_Reallocate(Memory *inst, size_t size);
Status Var_Release(Memory *inst);
Status Var_CopyOf(Var *inst, Var *other);
Status Var_Delete(Var *inst);
// Status Var_Assign(Var *inst, Var *value);
Status Var_Literalise(Var *inst, char *buff);
bool   Var_Equals(Var *a, Var *b);
void   VarUtils_Swap(Var *v1, Var *v2);

#endif  /* COMPOUND_VAR */
