#ifndef COMPOUND_PLATFORM_H
# define COMPOUND_PLATFORM_H

/* Environmental Constants. */
#  define __COMPOUND_STACK_MAXIMUM__  0x100000L  // 1 MiB

/* Architecture. */
# if defined __x86_64__ || defined __x86_64
#  define __COMPOUND_64__
#  define __COMPOUND_PRODUCT__  compound64
# elif defined __i386__ || __i486__ || __i586__ || __i686__ || _X86_ || __X86__
#  define __COMPOUND_32__
#  define __COMPOUND_PRODUCT__  compound32
# else
#  error Architecture not supported.  Please issue this on github.com/Wilhelm-Lee/Compound if necessary.  --William
# endif

/* Platform-specific control characters. */
# define LF  "\n"
# define CR  "\r"
# define CRLF  "\r\n"

# ifdef __APPLE__
#  define NEWLINE  CR
# elif defined __linux__
#  define NEWLINE  LF
# else
#  define NEWLINE  CRLF
# endif

#endif  /* COMPOUND_PLATFORM_H */
