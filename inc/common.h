#ifndef COMPOUND_COMMON_H
# define COMPOUND_COMMON_H

# include <stdbool.h>
# include <stdlib.h>
# include <wchar.h>

# define EMPTY  {0}

/* Toggle given boolean value. */
# define toggle(b)  (!(b))

/* Get the literal. */
# define nameof(obj)  #obj

/* Return n as the return value, once o is NULL. */
# define nonull(o, n)  { if (!(o)) return (n); }

/* Shortcut for returning UnavailableObject. */
# define avail(o)  { nonull((o), \
  (apply(annot(UnavailableObject, nameof(o)" was unavailable.")))); }

/* Return e as the return value, once v equals e. */
# define trans(v, e)  { if ((v) == (e)) return (e); }

/* Evaluate given statement while the ptr to s is not NULL. */
# define state(s, n)  { if ((s)) return (n); }

/* Evaluate given statement while the ptr to s is not NULL. */
# define svoid(s)  { if ((s)) return; }

/* Another way to handle if statements more cleanly. */
# define solve(s, b)  { if (s) b }

/* Handling expression with its result. */
# define when(expr, b)  { int _ = (expr); if (_) b; }

/* Handling expression with its precalculated result. */
# define where(expr, b)  { int _ = (expr); b; }

/* Execute b whenever finds s is "okay". */
# define ok(s, b)  { Status _ = s;  if (StatusUtils_IsOkay(_))  b }

/* Execute b whenever finds s is "NOT okay". */
# define notok(s, b)  { Status _ = s;  if (!StatusUtils_IsOkay(_))  b }

/* Return e when passing a failing e. */
// # define fail(e)  { notok(e, return apply(extend(Failure, _));) }
# define fail(e)  { notok(e, return (_);) }

/* Return e when passing a failing e commented with c. */
// # define fails(e, c)  { notok(e, return apply(extend(Failure, annot(_, c)));) }
# define fails(e, c)  { notok(e, return (annot(_, c));) }

/* Return value "v" when passing a failing e. */
# define vfail(e, v)  { notok(e, return v;) }

/* Execute b before returning when failing. */
# define onfail(e, b)  { notok(e, { b } return apply(_);) }

/* Execute b for handling UnknownStatus (TraditionalFunctionReturn). */
# define unsure(s, expr, b)  { Status _ = s; \
  if (_.characteristic < 0 && (expr))  b }

/* Execute b whatsoever with s stored. */
# define seek(s, b)  { Status _ = s;  b }

// # define append(p, s)  { Status _ = p;  s.prev = (Status *)&_; }

/* Combinates seek and solve. */
# define settle(e, s, b)  seek(e, solve(s, b))

/* Clone a new varaible "v2" with "v1". */
# define clone(v1, v2)  __typeof__(v1) v2 = v1;

/* Allows different macros using "_" nested with each other. */
# define nest(v1, v2, b)  { clone(v1, v2) b }

/* Cast Var "var" into builtin type in C specified with "type". */
# define cast(var, type)  (*(type *)var.addr)

// # define assign(var, value, type)  { cast(var, type) = cast(value, type); }
# define assign(mem, val)  {  }

/* Useful on handling Status errors in a function returns int. */
# define quit_on_fail(s)  { notok(s, { PrintStatusDump(_); return _.value; }) }

// # define lambda(param, body, capfmt, ...)  {\
//   /* Duplicate everything from cap. */\
//   va_list ptr;\
//   va_start(ptr, capfmt);\
//   __typeof__(ptr) \
//   va_end(ptr);\
// }

/* Create a new UnknownStatus on the fly. */
# define unknown(e, c, v)  ((Status) {\
  .identity = e.identity,\
  .value = v,\
  .description = c,\
  .characteristic = STATUS_UNKNOWN,\
  .loc = e.loc,\
  .prev = e.prev\
})

/* Create a new NormalStatus on the fly. */
# define normal(e, c)  ((Status) {\
  .identity = e.identity,\
  .value = 0,\
  .description = c,\
  .characteristic = STATUS_NORMAL,\
  .loc = e.loc,\
  .prev = e.prev\
})

/* Create a new ErrorStatus on the fly. */
# define error(e, c)  ((Status) {\
  .identity = e.identity,\
  .value = e.value,\
  .description = c,\
  .characteristic = STATUS_ERROR,\
  .loc = e.loc,\
  .prev = e.prev\
})

/* Replace the prev of e with p. */
# define extend(p, e)  ((Status) {\
  .identity = e.identity,\
  .value = p.value,\
  .description = e.description,\
  .characteristic = p.characteristic,\
  .loc = p.loc,\
  .prev = (Status *)&p\
})

// # define anon(e)  ((Status) {\
//   .identity = e.identity,\
//   .value = e.value,\
//   .description = e.description,\
//   .characteristic = e.characteristic,\
//   .loc = e.loc,\
//   .prev = e.prev\
// })

// # define append(p, e)  ()

// # define append(p, e)  ((Status) {\
//   .identity = e.identity,\
//   .value = e.value,\
//   .description = e.description,\
//   .characteristic = e.characteristic,\
//   .loc = e.loc,\
//   .prev = (e.prev = p)\
// })

/* Change the identity of e. */
# define naming(e, i)  ((Status) {\
  .identity = i,\
  .value = e.value,\
  .description = e.description,\
  .characteristic = e.characteristic,\
  .loc = e.loc,\
  .prev = e.prev\
})

/* Create a new Status with v as its value. */
# define value(e, v)  ((Status) {\
  .identity = e.identity,\
  .value = v,\
  .description = e.description,\
  .characteristic = e.characteristic,\
  .loc = e.loc,\
  .prev = e.prev\
})

/* Change the characteristic of e. */
# define shift(e, c)  ((Status) {\
  .identity = e.identity,\
  .value = e.value,\
  .description = e.description,\
  .characteristic = c,\
  .loc = e.loc,\
  .prev= e.prev\
})

// /* Make every literal member supporting wide char. */
// # define widen(s)  ((Status) {\
//   .identity = 
// })

/* Apply a new location to e where this macro is called. */
// # define apply(e)  ((Status) {\
//   .identity = e.identity,\
//   .value = e.value,\
//   .description = e.description,\
//   .characteristic = e.characteristic,\
//   .loc = __HERE__,\
//   .prev = &append(e.prev, e)\
// })
# define apply(e)  ((Status) {\
  .identity = e.identity,\
  .value = e.value,\
  .description = e.description,\
  .characteristic = e.characteristic,\
  .loc = __HERE__,\
  .prev = e.prev\
})

/* Replace the description from @e with @c. */
# define annot(e, c)  ((Status) {\
  .identity = e.identity,\
  .value = e.value,\
  .description = c,\
  .characteristic = e.characteristic,\
  .loc = e.loc,\
  .prev = e.prev\
})

/* Create a Report on the fly. */
# define stamp(e, ini)  ((Report) {\
  .content = e,\
  .initiator = ini,\
  .time = time(NULL),\
  .level = REPORT_SENDING_PRIORITY_NORMAL,\
  .status = REPORT_SENDING_TASK_STATUS_PENDING,\
  .dst = stdout\
})

/* Shortcut for sending a CatLog. */
# define cat(s)  {\
  CatlogMsg msg;\
  CatlogMsg_Create(&msg, CATLOG_LEVEL_DEBUG, "CAT", s);\
  CatlogSender sender;\
  CatlogSender_Create(&sender, &msg, stderr);\
  CatlogSender_Send(&sender);\
}

# define strnil(s)  (!s ? ("(null)") : s)

/* Memory type declaration. */
# define Memory(T)  Memory

/* Var type declaration. */
# define Var(T)  Var

/* Array type declaration. */
# define Array(T)  Array

/* Type declaration. */
# define Type(T)  Type

/* Virtual function declaration attribute for abstract object and interface. */
# define virtual(funcdecl)

typedef enum {
  COMMON_ERROR_NULLPTR = 1,
  COMMON_ERROR_INVALID_ARGUMENT,
  COMMON_ERROR_OUT_OF_MEMORY,
  COMMON_ERROR_ARITHMETIC,
} CommonError;

typedef struct {
  int x;
  int y;
} Coordination;

typedef struct {
  Coordination start;
  Coordination end;
} Selection;

// typedef struct {
//   void *addr;
//   size_t sz;
// } MemoryInst;

typedef Coordination ArrayIndexerRange;
typedef bool Bit;

# define WHICH_MIN(a, b)  

# define INRANGE(lf, inclf, rt, incrt, v) \
  (!(((lf) > (rt)) || (((v) <= (lf) && !(inclf)) || ((v) >= (rt) && !(incrt)))))

# define ATRANGE(lf, rt, v) \
  (INRANGE(lf, true, rt, true, v)) ? 0 : (((v) < (lf)) ? ((v) - (lf)) : ((v) - (rt)))

# define LITERALISATION_LENGTH_MAXIMUM  0xFFFFL
# define STATUS_STACK_LENGTH_MAXIMUM  __COMPOUND_STACK_MAXIMUM__

/* Only effect (probably) when formal Attribute is defined. 
 * ATTRIBUTABLE indicates this field is used for further process by Attribute.
 * Or, to put this way, this field has attributions not used so far, but
 * eventually will.
 */
# define USE_ATTRIBUTABLE
# define attr(a)

/* Useless in C, only for human to see.
   Probably rewrite this in Classic. */
# define throws(e)

/* Interfaces for handling various customisable
   user-defining functions for
   literalisations/ construction/ destruction of an object. */
# define LITERALISE  literalisation_t Literalise
# define CONSTRUCTOR  constructor_t Constructor
# define DESTRUCTOR  destructor_t Destructor

# define DEAD
# define ALIVE
# define SKELETON

typedef enum {
  LIVENESS_DEAD        = 0b000,
  LIVENESS_SKELETON    = 0b001,
  LIVENESS_ALIVE       = 0b010,
  LIVENESS_UNKNOWN     = 0b100,
} Liveness;

/* Any object with this attribute will require PreAllocate and PostRelease. */
# define COMPLEX_STRUCT

#endif /* COMPOUND_COMMON_H */
