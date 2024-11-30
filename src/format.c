// #include <Compound/class_register.h>
// #include <Compound/common.h>
// #include <Compound/format.h>
// #include <Compound/memory.h>
// #include <Compound/status.h>

// size_t _search_and_literalise_class(CREG, const char *class_identity,
//                                     char **buff)
// {
//   size_t written = 0;
  
//   /* Search for class. */
//   Class found = EMPTY;
//   handle(ClassRegister_Search(cr, &found, class_identity), {
//     belong(ErrorStatus, {
//       /* Class not found, write null indication content instead. */
//       written += sprintf(*buff, "(class not found)");
//     })

//     /* Even as it being unlikely to receive UnknownStatus based returning,
//        print out the Status is purely out of the safe considerations. */
//     belong(UnknownStatus, {
//       PrintStatus(_);
//     })

//     belong(NormalStatus, {
//       /* Class found, literalise and transcribe. */
//       written += sprintf(*buff, "%s", ({
//         char liter[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
//         (void)Class_Literalise(&found, liter);
//         liter;
//       }));
//     })
//   })
  
//   return written;
// }

// size_t _literalise_object(const char *obj_identity, char **buff)
// {
//   if (!obj_identity || !buff || !*buff)  return 0;
  
//   if (!strcmp(obj_identity, "Memory")) {
//     return Memory_Literalise(const Memory mem, char *buff)
//   }
// }

// size_t format(char *buff, const char *fmt, ...)
// {
//   if (!buff)  return 0;
//   if (!fmt)  return 0;
  
//   size_t written = 0;
//   variadic({
//     /* Traditional format prefix.  e.g. %s %d %lf %u %lu */
//     /* Defaultly handled by "vsprintf". */
//     prefix('%', {
//       written = vsprintf(buff, fmt, ap);
//       break;
//     })
    
//     /* Compound-specific format prefix.  e.g. ${Array} ${String} ${Class} */
//     /* See doc/variadic/PREFIX.md for more. */
    
//     /* Skipping for now, since the functionalities for Class and ClassRegister
//        are still in development which are also expected to be held for a period
//        of time. */
//     prefix('$', {
//       prefix('#', {
//         within('{', '}', {
//           skip(*app);
//         }, {})
//       })
//       within('{', '}', {
//         skip(*app);
//       }, {})
//     })
    
    
//   })
  
//   return written;
// }
