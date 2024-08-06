#ifndef FUNCTION_H
# define FUNCTION_H

# include <Compound/type.h>
# include <Compound/string.h>

typedef struct {
  Type type;
  String identity;  
  Type value;
} Parameter;

typedef void * Block;

typedef struct {
  Type return_type;
  Array(Parameter) params;
  Var(Block) body;
} Function;

Status Function_Create(Function *inst, Type *return_type, Array(Parameter) *params,
                       Var(Block) *body);
Status Function_CopyOf(Function *inst, Function *other);
Status Function_Delete(Function *inst);
Status Function_Literalise(Function *inst, String *buff);
Status Function_Overwrite(Function *inst, Function *other);
bool   Function_Equal(Function *inst, Function *other);
bool   FunctionUtils_IsVariadic(Function *inst);

#endif  /* FUNCTION_H */
