#ifndef COMPOUND_CLASS_METHOD_PARAMETER_H
# define COMPOUND_CLASS_METHOD_PARAMETER_H

# include <Compound/class_method.h>
# include <Compound/class_field.h>

typedef struct {
  ClassMethod *data;
  size_t length;
} ClassMethodParameter;

DEFTYPE(TClassMethodParameter, sizeof(ClassMethodParameter));

Status ClassMethodParameter_Create(ClassMethodParameter *inst,
                                   const size_t length);
Status ClassMethodParameter_CopyOf(ClassMethodParameter *inst,
                                   const ClassMethodParameter other);
Status ClassMethodParameter_Delete(ClassMethodParameter *inst);
Status ClassMethodParameter_GetIdx(const ClassMethodParameter *inst,
                                   const size_t index, ClassMethod *elem);
Status ClassMethodParameter_SetIdx(ClassMethodParameter *inst,
                                   const size_t index, const ClassMethod elem);
/* Insert an element into an Array @inst at @index. */
Status ClassMethodParameter_Insert(ClassMethodParameter *inst, const size_t index,
                                   const ClassMethod elem);

#endif  /* COMPOUND_CLASS_METHOD_PARAMETER_H */
