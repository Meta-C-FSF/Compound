#ifndef COMPOUND_CATLOG_H
# define COMPOUND_CATLOG_H

# include <Compound/common.h>
# include <Compound/status.h>

# define CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM  256
# define CATLOG_MESSAGE_INITIATOR_LENGTH_MAXIMUM  32
//                                      time lvl  init
# define CATLOG_MESSAGE_HEADER_FORMAT  "[%s] (%s) @%s:\t"

DEFSTATUS(CatCannotSendMessage, 1,
  "Cat had trouble while sending your message.",
  STATUS_ERROR, &ReadWriteError);

DEFSTATUS(CatMessageContentTooLong, 1,
  "The message content for logging is too long.",
  STATUS_ERROR, &MaximumLengthExceeded);

DEFSTATUS(CatMessageInitiatorTooLong, 1,
  "The message initiator for logging is too long.",
  STATUS_ERROR, &MaximumLengthExceeded);

DEFSTATUS(CatCannotFindFile, 1,
  "Cat cannot have your file found.",
  STATUS_ERROR, &FileNotFound);

DEFSTATUS(CatHasInsufficientPermission, 1,
  "Cat cannot access your file with its given permission.",
  STATUS_ERROR, &InsufficientAccessPermission);

DEFSTATUS(CatCannotOpenFile, 1,
  "Cat cannot open your file because fopen returned NULL.",
  STATUS_ERROR, &ReadWriteError);

DEFSTATUS(CatMessageSuppressed, 0,
  "The message is suppressed.",
  STATUS_NORMAL, &NormalStatus);

typedef enum {
  CATLOG_LEVEL_ALL,  // Least the value, most the information.
  CATLOG_LEVEL_NORMAL,
  CATLOG_LEVEL_MAJOR,
  CATLOG_LEVEL_CRITICAL,
  CATLOG_LEVEL_FATAL,
  CATLOG_LEVEL_DEBUG,
  CATLOG_LEVEL_NONE
} CatlogLevel;

static inline const char *strlvl(CatlogLevel lvl)
{
  switch (lvl)
  {
  case CATLOG_LEVEL_ALL:
    return "ALL";
  case CATLOG_LEVEL_NORMAL:
    return "NOR";
  case CATLOG_LEVEL_MAJOR:
    return "MJR";
  case CATLOG_LEVEL_CRITICAL:
    return "CRI";
  case CATLOG_LEVEL_FATAL:
    return "FAT";
  case CATLOG_LEVEL_DEBUG:
    return "DBG";
  default:
    return "NIL";
  }
}

typedef struct {
	time_t time;
	CatlogLevel level;
	char initiator[CATLOG_MESSAGE_INITIATOR_LENGTH_MAXIMUM];
	char content[CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM];
} CatlogMsg;

Status CatlogMsg_Create(CatlogMsg *inst, CatlogLevel level,
  const char *initiator, const char *content);
Status CatlogMsg_CopyOf(CatlogMsg *inst, CatlogMsg *other);
bool   CatlogMsg_Equals(CatlogMsg *inst, CatlogMsg *other);

typedef struct {
	CatlogMsg msg;
	FILE *dst;
	bool successful;
	struct timespec elapsed;
  CatlogLevel filter;
} CatlogSender;

Status CatlogSender_Initialise(CatlogSender *inst, CatlogMsg msg, FILE *dst);
Status CatlogSender_CopyOf(CatlogSender *inst, CatlogSender *other);
Status CatlogSender_Send(CatlogSender *inst);
bool   CatlogSender_Equals(CatlogSender *inst, CatlogSender *other);

static CatlogSender GlobalCat = EMPTY;

/* Shortcut for sending a CatLog. */
// # define cat(lvl, str)  {\
//   CatlogMsg msg = EMPTY;\
//   notok(CatlogMsg_Create(&msg, lvl, (char *)__func__, str), PrintStatusDump(_););\
//   fail(CatlogSender_Initialise(&GlobalCat, &msg,\
//     (!GlobalCat.dst ? (stdout) : GlobalCat.dst)));\
//   fail(CatlogSender_Send(&GlobalCat));\
// }

static inline Status cat(CatlogLevel lvl, const char *initiator,
  const char *content)
{
  CatlogMsg msg = EMPTY;
  fail(CatlogMsg_Create(&msg, lvl, initiator, content));
  fail(CatlogSender_Initialise(&GlobalCat, msg, GlobalCat.dst));
  fail(CatlogSender_Send(&GlobalCat));
  
  return apply(NormalStatus);
}

/* Preset cats. */
# define lowest(str)   cat(CATLOG_LEVEL_ALL, __func__, str)
# define debug(str)    cat(CATLOG_LEVEL_DEBUG, __func__, str)
# define info(str)     cat(CATLOG_LEVEL_NORMAL, __func__, str)
# define warning(str)  cat(CATLOG_LEVEL_MAJOR, __func__, str)
# define error(str)    cat(CATLOG_LEVEL_CRITICAL, __func__, str)
# define fatal(str)    cat(CATLOG_LEVEL_FATAL, __func__, str)
# define highest(str)  cat(CATLOG_LEVEL_NONE, __func__, str)
# define redir(dst)    CatlogSender_Initialise(&GlobalCat, (CatlogMsg)EMPTY, (dst));
# define filter(lvl)   GlobalCat.filter = (lvl)

#endif  /* COMPOUND_CATLOG_H */
