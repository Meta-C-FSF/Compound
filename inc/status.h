#ifndef COMPOUND_STATUS_H
# define COMPOUND_STATUS_H

# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <threads.h>

# include <Compound/common.h>
# include <Compound/platform.h>

/* Status characteristics */
typedef enum {
  STATUS_UNKNOWN  = -1,
  STATUS_NORMAL   = 0,
  STATUS_ERROR    = 1
} StatusCharacteristics;

typedef enum {
  /* Settlement. */
  ARGUE_RESULT_FINALISED =  0b01,
  ARGUE_RESULT_UNSETTLED = -0b01,

  /* Nature. */
  ARGUE_RESULT_POSITIVE  =  0b10,
  ARGUE_RESULT_NEGATIVE  = -0b10,
} ArgueResult;

# define __HERE__  (Location){                             \
  .file = (char *)__FILE__,                                \
  .line = __LINE__,                                        \
  .func = (char *)__func__                                 \
}

# define __GLOBAL__ (Location){                            \
  .file = (char *)__FILE__,                                \
  .line = __LINE__,                                        \
  .func = (char *)"(GLOBAL)"                               \
}

/* Indicated the exact location where the "issue" was occurred at. */
typedef struct {
  char *file;
  int line;
  char *func;
} Location;

/* Common return type for reporting functions that require to give more
   information about the procedure. */
typedef struct _Status {
  char *identity;
  int value;  /* Traditional returning data "int". Only used when the function
                 called and received legacy functions that uses "int" as the
                 returning type that wish to have place to hold the value.
                 Otherwise, the function would just return the structure Status. */
  char *description;
  int characteristic;
  Location loc;
  struct _Status *prev;
} Status;

# define DEFSTATUS(i, v, d, c, p)                          \
  static const Status i = {                                \
    .identity = nameof(i),                                 \
    .value = v,                                            \
    .description = d,                                      \
    .characteristic = c,                                   \
    .loc = __GLOBAL__,                                     \
    .prev = (Status *)p                                    \
  }

# define LOCATION_LITERALISE_FORMAT  "at %s:%d, in function `%s\'"

# define STATUS_LITERALISE_FORMAT \
    "%s:  \"%s\"\n\tpredecessor=<%s> value=(%d) characteristic=(%d)\n\t%s"

// typedef thrd_start_t  ArgueStart;

// typedef struct {
//   ArgueStart handler;
//   void *external_param;
// } ArgueStartParam;

// /* Argument levels (qualities) */
// typedef enum {
//   ARGUMENT_NONE = 0,
//   ARGUMENT_MINOR,
//   ARGUMENT_NORMAL,
//   ARGUMENT_MAJOR,
//   ARGUMENT_CRITICAL,
//   ARGUMENT_SEVERE,
//   ARGUMENT_ALL,
// } ArgumentLevel;

// typedef struct {
//   ReportSender stream;
//   ArgueStartParam handler;  // Obsolete?
//   ArgumentLevel level;
//   bool muted;
// } Argument;

// typedef struct {
//   Argument *members;
//   int (*announcer) (Argument);
// } ArgumentAnnouncer;

# define STATUS_REGISTRY_BUFFER_MAXIMUM_LENGTH  0xFFFF

Status Location_Literalise(Location *inst, char *buff);
bool   Location_Equals(Location lc1, Location lc2);
Status Status_Literalise(Status *inst, char *buff);
Status Status_Register(Status *inst, Status *buff);
bool   Status_Equal(Status *stat1, Status *stat2);
void   StatusUtils_Dump(Status *inst, Status *store);
bool   StatusUtils_HasPrev(Status inst);
bool   StatusUtils_IsOkay(Status inst);
bool   StatusUtils_IsRecursive(Status inst);
int    StatusUtils_Depth(Status *inst);

// Status
// arguestarter_create(ArgueStartParam *inst, void *external_param);
// Status
// arguestarter_constr(ArgueStartParam *inst, ArgueStart argue_start,
//                     void *external_param);
// Status
// arguestarter_start(ArgueStartParam *inst);
// bool
// arguestarter_equal(ArgueStartParam *inst1, ArgueStartParam *inst2);
// Status arguestarter_current(void);
// Status arguestarter_sleep(const struct timespec *time_point,
//                           struct timespec *remaining);
// void arguestarter_exit(int code) __attribute__ ((__noreturn__));
// Status arguestarter_join(ArgueStart thrd);


// Status
// argument_create(Argument *inst, ReportSender *streams, ArgueStartParam handler,
//                 int level, bool muted);

// ---------------------ELEMENTARY-------------------------

DEFSTATUS(UnknownStatus, -1, "An unknown status.", STATUS_UNKNOWN, &UnknownStatus);
DEFSTATUS(NormalStatus, 0, "A normal status.", STATUS_NORMAL, &NormalStatus);
DEFSTATUS(ErrorStatus, 1, "An error status.", STATUS_ERROR, &ErrorStatus);

// ----------------------EXTENDED--------------------------

DEFSTATUS(Failure, 1, 
  "Given status did not pass the failure detection.",
  STATUS_ERROR, &Failure);

DEFSTATUS(MemoryViolation, 1,
  "Illegal access on certain memory address.",
  STATUS_ERROR, &ErrorStatus);

DEFSTATUS(NullPointerEncountered, 1,
  "Trying to operate with a null pointer.",
  STATUS_ERROR, &ErrorStatus);

DEFSTATUS(InvalidObject, 1,
  "An invalid object was presented.",
  STATUS_ERROR, &ErrorStatus);

DEFSTATUS(UnavailableObject, 1,
  "An unavailable object was presented.",
  STATUS_ERROR, &ErrorStatus);

DEFSTATUS(InvalidParameter, 1,
  "An invalid parameter was presented.",
  STATUS_ERROR, &InvalidObject);

DEFSTATUS(InvalidSize, 1,
  "Given size is either invalid for being ZERO, or, invalid according to certain criteria.",
  STATUS_ERROR, &InvalidObject);

DEFSTATUS(InsufficientMemory, 1,
  "Not enough room for further memory allocations.",
  STATUS_ERROR, &ErrorStatus);

DEFSTATUS(ArithmeticError, 1,
  "An arithmetic error occurred.",
  STATUS_ERROR, &ErrorStatus);

DEFSTATUS(IntegerOverFlow, 1,
  "An integer had overflowed.",
  STATUS_ERROR, &ArithmeticError);

DEFSTATUS(InvalidOperation, 1,
  "An invalid operation was detected.",
  STATUS_ERROR, &ErrorStatus);

DEFSTATUS(RuntimeError, 1,
  "A runtime error had occurred.",
  STATUS_ERROR, &ErrorStatus);

DEFSTATUS(UnexpectedSituation, 1,
  "This thread had ran into an unexpected situation.",
  STATUS_ERROR, &RuntimeError);

DEFSTATUS(InstanceStillAlive, 1,
  "Given instance was still alive.",
  STATUS_ERROR, &RuntimeError);

DEFSTATUS(InstanceNotAlive, 1,
  "Given instance was not alive.",
  STATUS_ERROR, &RuntimeError);

DEFSTATUS(SourceNotAlive, 1,
  "Given source was not alive.",
  STATUS_ERROR, &InstanceNotAlive);

DEFSTATUS(StoreNotAlive, 1,
  "Given object for storing was not alive.",
  STATUS_ERROR, &InstanceNotAlive);

DEFSTATUS(InvalidOperationBetweenAliveAndNonAlive, 1,
  "Given two instances were incompatible with each other for any operation.",
  STATUS_ERROR, &InvalidOperation);

DEFSTATUS(InstanceCreatingFailure, 1,
  "Cannot create the instance.",
  STATUS_ERROR, &RuntimeError);

DEFSTATUS(InvalidArrayLength, 1,
  "Given length is invalid.",
  STATUS_ERROR, &InvalidObject);

DEFSTATUS(InvalidStackLength, 1,
  "Given length is invalid.",
  STATUS_ERROR, &InvalidObject);

DEFSTATUS(ArrayIndexOutOfBound, 1,
  "Given index was accessing illegal address.",
  STATUS_ERROR, &MemoryViolation);

DEFSTATUS(VariableFormatMismatch, 1,
  "Given format does not match with given subjects.",
  STATUS_ERROR, &ErrorStatus);

DEFSTATUS(ImprecisionError, 1,
  "Precision was not enough for handling the calculation.",
  STATUS_ERROR, &RuntimeError);


// ---------------------USER DEFINED-----------------------

// The meaning of value is defined by the function itself.
DEFSTATUS(TraditionalFunctionReturn, 0,
  "Function has returned an integer.",
  STATUS_UNKNOWN, &UnknownStatus);

DEFSTATUS(RecursionTerminated, 0,
  "Function with recursive calling has terminated.",
  STATUS_UNKNOWN, &UnknownStatus);

DEFSTATUS(UnavailableInstance, 1,
  "An unavailable instance was presented.",
  STATUS_ERROR, &NullPointerEncountered);

DEFSTATUS(UnavailableIdentifier, 1,
  "Given identifier was unavailable.",
  STATUS_ERROR, &UnavailableObject);

DEFSTATUS(UnavailableParameter, 1,
  "An unavailable instance was given as a parameter.",
  STATUS_ERROR, &UnavailableInstance);

DEFSTATUS(UnavailableSource, 1,
  "Given source is unavailable.",
  STATUS_ERROR, &UnavailableParameter);

DEFSTATUS(UnavailableStore, 1,
  "Given object for storing was unavailable.",
  STATUS_ERROR, &UnavailableParameter);

DEFSTATUS(InvalidReportTask, 1,
  "An unavailable or illegal report task was given.",
  STATUS_ERROR, &InvalidParameter);

DEFSTATUS(UnableToThrowError, 1,
  "Unable to report an exceptional situation.",
  STATUS_ERROR, &RuntimeError);

DEFSTATUS(ReadWriteError, 1,
  "Error occurred during IO session.",
  STATUS_ERROR, &RuntimeError);

DEFSTATUS(FileNotFound, 1,
  "Target file was unavailable and unable to find.",
  STATUS_ERROR, &ReadWriteError);

DEFSTATUS(InvalidFileName, 1,
  "Given file name was invalid.",
  STATUS_ERROR, &ReadWriteError);

DEFSTATUS(UnavailableFileName, 1,
  "Given file name was unavailable.",
  STATUS_ERROR, &UnavailableObject);

DEFSTATUS(UnavailableFileAccessMode, 1,
  "Given file accessing mode was unavailable.",
  STATUS_ERROR, &UnavailableObject);

DEFSTATUS(InsufficientAccessPermission, 1,
  "Given permission does not suffice to access.",
  STATUS_ERROR, &ReadWriteError);

DEFSTATUS(ReportThrown, 1,
  "This function has thrown a report, following instructions aborted.",
  STATUS_ERROR, &RuntimeError);

DEFSTATUS(ReportMessageTooLong, 1,
  "Given message is too long.",
  STATUS_ERROR, &InvalidArrayLength);

DEFSTATUS(MaximumLengthExceeded, 1,
  "Maximum length had exceeded.",
  STATUS_ERROR, &InvalidArrayLength);

DEFSTATUS(MaximumLiteralisationLengthExceeded, 1,
  "Literalisation was too long.",
  STATUS_ERROR, &MaximumLengthExceeded);

DEFSTATUS(UnavailableBuffer, 1,
  "Given buffer was unavailable.",
  STATUS_ERROR, &UnavailableInstance);

DEFSTATUS(InvalidLiteralisingBuffer, 1,
  "Given buffer does not have a good integrity on its length.",
  STATUS_ERROR, &InvalidObject);

DEFSTATUS(NoBytesWereRead, 1,
  "Called function had returned ZERO indicating no bytes were read.",
  STATUS_ERROR, &ReadWriteError);

DEFSTATUS(NoBytesWereWritten, 1,
  "Called function had returned ZERO indicating no bytes were written.",
  STATUS_ERROR, &ReadWriteError);

DEFSTATUS(StringConversionPrecisionError, 1,
  "Unpreventable precision loss was found during conversion between string "
  "and raw data.", STATUS_ERROR, &ImprecisionError);

DEFSTATUS(UnsupportedEncoding, 1,
  "Given encoding is not supported.",
  STATUS_ERROR, &InvalidObject);

DEFSTATUS(FunctionNotDeployed, 1,
  "The function called have not been deployed.",
  STATUS_ERROR, &InvalidOperation);

DEFSTATUS(ReadonlyTarget, 1,
  "Given target does not support such modifications.",
  STATUS_ERROR, &InvalidOperation);

DEFSTATUS(IncorrectLiveness, 1,
  "Given instance does not have required liveness for further operations.",
  STATUS_ERROR, &InvalidObject);

// ========================================================

static Status PrintStatus(Status s)
{
  /* Literalise. */
  char buff[LITERALISATION_LENGTH_MAXIMUM];
  
  /* Handle returning value. */
  /* No bytes were written to buffer. */
  zero(Status_Literalise(&s, buff).value, {
    return apply(NoBytesWereWritten);
  })

  /* Output. */
  where(fprintf(stderr, "%s\n", buff), {
    /* Pass on returning value. */
    return apply(value(TraditionalFunctionReturn, _));
  })
}

static void PrintStatusDump(Status s)
{
  /* Create dump. */
  /* Calculate depth for dumping. */
  const int dump_len = StatusUtils_Depth(&s);

  /* Skip when "s" is either unavailable or is at the buttom of status stack. */
  if (dump_len == -1) {
    PrintStatus(s);
    return;
  }
    
  Status dump[dump_len];
  Status current = s;
  dump[0] = current;  // Put self at leading.
  for (register int i = 1; i < dump_len; i++) {
    // StatusUtils_Dump will only access (storage) the prev.
    // It does not include this status itself.
    StatusUtils_Dump(&current, &dump[i]);
    
    current = *current.prev;
  }

  /* Output by iterating. */
  for (register int i = 0; i < dump_len; i++) {
    /* Print out indexer. */
    (void)printf("\e[1m[%d/%d]\e[0m", (dump_len - i), dump_len);
    
    /* Print dumped status. */
    unsure(PrintStatus(dump[i]), !_.value, {
      (void)fprintf(stderr, "Unable to literalise.\n");
    })
  }
}

#endif  /* COMPOUND_STATUS_H */
