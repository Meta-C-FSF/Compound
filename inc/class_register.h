#ifndef COMPOUND_CLASS_REGISTER_H
# define COMPOUND_CLASS_REGISTER_H

# include <Compound/class.h>

typedef struct {
  Class *data;
  size_t length;
} ClassRegister;

DEFTYPE(TClassRegister, sizeof(ClassRegister));

/* Shorthand for declaring ClassRegister @cr in function.
   "CREG" stands for "Class Register". */
# define CREG  ClassRegister *cr

Status ClassRegister_Create(ClassRegister *inst, const size_t length);
Status ClassRegister_CopyOf(ClassRegister *inst, const ClassRegister other);
Status ClassRegister_Delete(ClassRegister *inst);
/* Returns true if both ClassRegister @reg1 and ClassRegister @reg2 have the
   same elements, and length, respectively. */
bool   ClassRegister_Equals(const ClassRegister reg1, const ClassRegister reg2);
Status ClassRegister_GetIdx(const ClassRegister *inst, const size_t index,
                            Class *elem);
Status ClassRegister_SetIdx(ClassRegister *inst, const size_t index,
                            const Class elem);
/* Insert an element into an ClassRegister @inst at @index. */
Status ClassRegister_Insert(ClassRegister *inst, const size_t index,
                            const Class elem);
/* Remove an element from an ClassRegister @inst at @index. */
Status ClassRegister_Remove(ClassRegister *inst, const size_t index);
Status ClassRegister_Search(ClassRegister *inst, Class *store,
                            const char *identity);

static ClassRegister *GlobalClassRegister = EMPTY;

static inline void ClassRegister_SetGlobal(ClassRegister *inst)
{
  svoid(!inst);

  GlobalClassRegister = inst;
}

#endif  /* COMPOUND_CLASS_REGISTER_H */
