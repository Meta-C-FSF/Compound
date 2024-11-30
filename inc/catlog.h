#ifndef COMPOUND_CATLOG_H
# define COMPOUND_CATLOG_H

# include <stdarg.h>

# include <Compound/common.h>
# include <Compound/status.h>
# include <Compound/status_stack.h>

# define CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM  1024
# define CATLOG_MESSAGE_INITIATOR_LENGTH_MAXIMUM  64
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
} CatlogMessage;

Status CatlogMessage_Create(CatlogMessage *inst, CatlogLevel level,
  const char *initiator, const char *fmt, ...);
Status CatlogMessage_CopyOf(CatlogMessage *inst, CatlogMessage *other);
bool   CatlogMessage_Equals(CatlogMessage *inst, CatlogMessage *other);

typedef struct {
	CatlogMessage msg;
	FILE *dst;
	bool successful;
	struct timespec elapsed;
  CatlogLevel filter;
} CatlogSender;

static CatlogSender *GlobalCatlogSender = NULL;

static inline void CatlogSender_SetGlobal(CatlogSender *inst)
{
  svoid(!inst);

  GlobalCatlogSender = inst;
}

/* Shorthand for declaring CatlogSender @cs in function parameters.
   "CATS" stands for "Catlog Sender". */
# define CATS  CatlogSender *cs

Status CatlogSender_Create(CatlogSender *inst, CatlogMessage msg, FILE *dst);
Status CatlogSender_CopyOf(CatlogSender *inst, CatlogSender *other);
Status CatlogSender_Delete(CatlogSender *inst);
Status CatlogSender_Send(CatlogSender *inst);
bool   CatlogSender_Equals(CatlogSender *inst, CatlogSender *other);
Status cat(CATS, CatlogLevel lvl, const char *initiator, const char *fmt, ...);

/* Preset cats. */
# define lowest(fmt, ...)  cat(cs, CATLOG_LEVEL_DEBUG, __func__, fmt, __VA_ARGS__)
# define debug(fmt, ...)  cat(cs, CATLOG_LEVEL_DEBUG, __func__, fmt, __VA_ARGS__)
# define info(fmt, ...)  cat(cs, CATLOG_LEVEL_DEBUG, __func__, fmt, __VA_ARGS__)
# define warning(fmt, ...)  cat(cs, CATLOG_LEVEL_DEBUG, __func__, fmt, __VA_ARGS__)
# define error(fmt, ...)  cat(cs, CATLOG_LEVEL_DEBUG, __func__, fmt, __VA_ARGS__)
# define fatal(fmt, ...)  cat(cs, CATLOG_LEVEL_DEBUG, __func__, fmt, __VA_ARGS__)
# define highest(fmt, ...)  cat(cs, CATLOG_LEVEL_DEBUG, __func__, fmt, __VA_ARGS__)

# define redir(file)  cs->dst = (file)
# define filter(lvl)  cs->filter = (lvl)

#endif  /* COMPOUND_CATLOG_H */
