#ifndef COMPOUND_FORMAT_H
# define COMPOUND_FORMAT_H

# include <stdarg.h>
# include <stdio.h>
# include <wchar.h>

# include <Compound/common.h>
# include <Compound/class_register.h>

/* Returns the total bytes written into @buff according to
   @fmt, specific items provided by variadic parameters. */
size_t format(char *buff, const char *fmt, ...);
/* Returns the total bytes written into @buff, as literalising the Class,
   found by provided @class_identity. */
size_t _search_and_literalise_class(CREG, const char *class_identity,
                                           char **buff);
/* Returns the total bytes written into @buff, as literalising the object.
   Literalisation is done by corresponding functions, matching to given
   objects.
   
   Such as "Array" which will be processed with "Array_Literalise". */
size_t _literalise_object(const char *obj_identity, char **buff);

size_t nformat(char *buff, const size_t max, const char *fmt, ...);

/* Returns the total bytes written into @buff according to
   @fmt, specific items provided by variadic parameters. */
size_t wformat(wchar_t *wbuff, const wchar_t *wfmt, ...);
size_t nwformat(wchar_t *buff, const size_t max, const wchar_t *fmt, ...);

#endif  /* COMPOUND_FORMAT_H */
