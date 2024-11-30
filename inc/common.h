#ifndef COMPOUND_COMMON_H
# define COMPOUND_COMMON_H

# include <stdbool.h>
# include <stdlib.h>

/********************************/
/* Status & Returning Handling. */
/********************************/

/* Get the literal. */
# define nameof(obj)  #obj

/* Return n as the return value, once o is NULL. */
# define nonull(o, n)  { if (!(o))  return (n); }

/* Shortcut for returning UnavailableObject. */
# define avail(o)                                          \
{ nonull((o), apply(annot(UnavailableObject, nameof(o)" was unavailable."))); }

/* Return e as the return value, once v equals e. */
# define trans(v, e)  { if ((v) == (e))  return (e); }

/* Evaluate given statement while the ptr to s is not NULL. */
# define state(s, n)  { if ((s))  RETURN(n); }

/* Return @n when @s evaluated as true. */
# define vstate(s, n)  { if (s)  return (n); }

/* Evaluate given statement while the ptr to s is not NULL. */
# define svoid(s)  { if ((s)) return; }

/* Another way to handle if statements more cleanly. */
# define solve(s, b)  { if (s) b }

/* Handling expression. */
# define where(expr, b)  { const int _ = (expr);  b }

/* Handling expression with IF statement for @cond as "condition",
   followed by @b as "block". */
# define when(expr, cond, b)  { const int _ = (expr);  if (cond)  b }

/* Handling expression returned NON-ZERO. */
# define nzero(expr, b)  { const int _ = (expr); if (_) b; }

/* Handling expression returned ZERO. */
# define zero(expr, b)  { const int _ = (expr); if (!(_)) b; }

/* Execute b whenever finds s is "okay". */
# define ok(s, b)  { Status _ = s;  if (StatusUtils_IsOkay(_))  b }

/* Execute b whenever finds s is "NOT okay". */
# define notok(s, b)  { Status _ = s;  if (!StatusUtils_IsOkay(_))  b }

/* Return e when passing a failing e. */
// # define fail(e)  { notok(e, return apply(extend(Failure, _));) }
# define fail(e)  { notok(e, RETURN(_);) }

/* Return e when passing a failing e commented with c. */
# define fails(e, c)  { notok(e, return(annot(_, c));) }

/* Return value "v" when passing a failing e. */
# define vfail(e, v)  { notok(e, return(v);) }

/* Execute b before returning when failing. */
# define onfail(e, b)  { notok(e, { b } return(apply(_));) }

/* Execute b for handling UnknownStatus (TraditionalFunctionReturn). */
# define unsure(s, expr, b)  { Status _ = s; \
  if (_.characteristic < 0 && (expr))  b }

/* Clone a new variable "v2" with "v1". */
# define clone(v1, v2)  __typeof__(v1) v2 = v1;

/* Allows different macros using "_" nested with each other. */
# define nest(v1, v2, b)  { clone(v1, v2) b }

/* Cast Var "var" into builtin type in C specified with "type". */
# define cast(var, type)  (*(type *)(var).addr)

/* Useful on handling Status errors in a function returns int. */
# define quit_on_fail(s)  { notok(s, { PrintStatusDump(_); return _.value; }) }

/* For handling Status at one place. */
# define handle(status, block)  { Status _ = (status); block }

/* For differentiate handling of possible Status. */
# define match(status, block)  { if (Status_Match((_), (status))) block }

/* Detect current Status is based on @status from root. */
# define belong(status, block)  { if (Status_Belong((_), (status))) block }

/* The inverting of "belong". */
# define nbelong(status, block)  { if (!Status_Belong((_), (status))) block }

/* Push into MemoryStack for auto-release. */
# define mpush(memstk, memory)  (MemoryStack_Push((memstk), (memory)))

/* Memory_Release and pop from MemoryStack. */
# define mpop(memstk)  (MemoryStack_Pop(memstk))

/* Global support for @mpush. */
# define push(memory)  (MemoryStack_Push(GlobalMemoryStack, (memory)))

/* Global support for @mpop. */
# define pop()  mpop(GlobalMemoryStack)

/* Push current Status into StatusStack and return with it. */
# define RETURN(status)  { handle((apply(status)), { \
  StatusStack_Push(GlobalStatusStack, _); return (_); }) }

/* Replace string with "(null)" once it's NULL. */
# define strnil(s)  (!(s) ? ("(null)") : (s))

/* Calculate array length. */
# define arrlen(arr)  (sizeof(arr) / sizeof(__typeof__(arr[0])))

# define ELLIPSIS  const char *fmt, ...

/**********************/
/* Variadic contexts. */
/**********************/

/* Proceed following @block with variadic context. */
# define variadic(block)                                   \
{                                                          \
  va_list ap;                                              \
  va_start(ap, fmt);                                       \
  bool _within = false;                                    \
  const char *app = fmt;  /*"app" stands for "ap pointer"*/\
  for (; *app; app++)  block                               \
  va_end(ap);                                              \
}

/* Within any variadic context, propose solutions for @opt, typed with @type. */
# define option(opt, type, block)                          \
{                                                          \
  if (*(app) == (opt)) {                                   \
    const type _ = va_arg(ap, type);  block                \
  }                                                        \
}

/* Within any variadic context, select given prefix @opt
   before proposing options. */
# define prefix(opt, block)                                \
{                                                          \
  if (_within)  block                                      \
  if (*(app) == (opt))  { app+=1;  block }                 \
}

/* Within any variadic context, quit processing when selected with @opt.
   @block is executed before quitting. */
# define escape(opt, block)                                \
{                                                          \
  if (*(app) == (opt))  { block  va_end(ap); break; }      \
}

# define within(opt1, opt2, block, after)                  \
{                                                          \
  if (*(app) == (opt1)) {                                  \
    _within = true;                                        \
    continue;                                              \
  }                                                        \
                                                           \
  if (_within && *(app) != (opt2))  block                  \
                                                           \
  if (*(app) == (opt2)) {                                  \
    _within = false;                                       \
    after                                                  \
  }                                                        \
}

# define until(opt)                                        \
{                                                          \
  if (*(app) != (opt))  continue;                          \
}

/* Within any variadic context, skip given character @opt without processing. */
# define skip(opt)  if (*(app) == (opt)) continue;

/* An alternative for "continue".  Usually used within a variadic context. */
# define finish  continue

/*************************/
/* Status manipulations. */
/*************************/

/* Replace the prev of e with p. */
# define extend(p, e)  ((Status) {\
  .identity = e.identity,\
  .value = p.value,\
  .description = e.description,\
  .characteristic = p.characteristic,\
  .loc = p.loc,\
  .prev = (Status *)&p\
})

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

/******************/
/* Miscellaneous. */
/******************/

# define EMPTY  {0}

# define INRANGE(lf, inclf, rt, incrt, v) \
  (!(((lf) > (rt)) || (((v) <= (lf) && !(inclf)) || ((v) >= (rt) && !(incrt)))))

# define ATRANGE(lf, rt, v) \
  (INRANGE(lf, true, rt, true, v)) ? 0 : (((v) < (lf)) ? ((v) - (lf)) : ((v) - (rt)))

# define LITERALISATION_LENGTH_MAXIMUM  8192

# define IDENTITY_LENGTH_MAXIMUM  64

#endif /* COMPOUND_COMMON_H */
