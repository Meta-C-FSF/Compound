#ifndef COMPOUND_PLATFORM_H
# define COMPOUND_PLATFORM_H

# if defined __x86_64__ || defined __x86_64
#  define __COMPOUND_64__
#  define __COMPOUND_PRODUCT__  compound64
#  define __COMPOUND_STACK_MAXIMUM__  0x800000L  // 8 MiB
# elif defined __i386__ || __i486__ || __i586__ || __i686__ || _X86_ || __X86__
#  define __COMPOUND_32__
#  define __COMPOUND_PRODUCT__  compound32
#  define __COMPOUND_STACK_MAXIMUM__  0x800000L  // 8 MiB
# else
#  error Platform not supported.  Please issue this on github.com/Wilhelm-Lee/Compound if necessary.  --William
# endif

// # if defined _WIN16 || defined _WIN32 || defined _WIN64
// #  define COMPOUND_STDIN_PATH 

#endif  /* COMPOUND_PLATFORM_H */
