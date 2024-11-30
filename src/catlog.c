#include <Compound/catlog.h>
#include <Compound/status.h>

Status CatlogMessage_Create(CatlogMessage *inst, CatlogLevel level,
                            const char *initiator, const char *fmt, ...)
{
  avail(inst);
  state((!initiator), (UnavailableBuffer));
  state(strlen(initiator) > CATLOG_MESSAGE_INITIATOR_LENGTH_MAXIMUM,
        CatMessageInitiatorTooLong);

  inst->time = time(NULL);
  inst->level = level;
  (void)strncpy(inst->initiator, initiator,
                CATLOG_MESSAGE_INITIATOR_LENGTH_MAXIMUM);
  
  va_list ap;
  va_start(ap, fmt);
  const int rtncode =
    vsnprintf(inst->content, CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM, fmt, ap);
  va_end(ap);
  
  if (rtncode < 0) {
    RETURN(value(annot(RuntimeError, "Failed on "nameof(vsnprintf)".  "
                       "Value preserved."), rtncode));
  }

  RETURN(NormalStatus);
}

Status CatlogMessage_CopyOf(CatlogMessage *inst, CatlogMessage *other)
{
  nonull(inst, (UnavailableInstance));
  nonull(other, (InvalidParameter));

  inst->time = other->time;
  inst->level = other->level;
  (void)strncpy(inst->initiator, other->initiator,
                CATLOG_MESSAGE_INITIATOR_LENGTH_MAXIMUM);
  (void)strncpy(inst->content, other->content,
                CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM);

  RETURN(NormalStatus);
}

bool CatlogMessage_Equals(CatlogMessage *inst, CatlogMessage *other)
{
  vstate(!inst || other == NULL, false);

  return (inst->time == other->time && inst->level == other->level &&
          (!strcmp(inst->initiator, other->initiator)) &&
          (!strcmp(inst->content, other->content)));
}

Status CatlogSender_Create(CatlogSender *inst, CatlogMessage msg, FILE *dst)
{
  nonull(inst, (UnavailableInstance));

  /* Copy and assign. */
  inst->msg = msg;
  inst->dst = (!dst ? stdout : dst);
  inst->successful = false;
  inst->elapsed = (struct timespec){.tv_sec = 0, .tv_nsec = 0};

  RETURN(NormalStatus);
}

Status CatlogSender_CopyOf(CatlogSender *inst, CatlogSender *other)
{
  nonull(inst, (UnavailableInstance));
  nonull(other, (InvalidParameter));

  /* Copy and assign */
  inst->msg = other->msg;
  inst->dst = other->dst;
  inst->successful = other->successful;
  inst->elapsed = other->elapsed;

  RETURN(NormalStatus);
}

Status CatlogSender_Delete(CatlogSender *inst)
{
  avail(inst);

  inst->msg = (CatlogMessage)EMPTY;
  inst->dst = NULL;
  inst->successful = false;
  inst->elapsed = (struct timespec)EMPTY;

  RETURN(NormalStatus);
}

bool CatlogSender_Equals(CatlogSender *inst, CatlogSender *other)
{
  vstate(!inst || other == NULL, false);

  return (CatlogMessage_Equals(&inst->msg, &other->msg) &&
          inst->dst == other->dst && inst->successful == other->successful &&
          ((inst->elapsed.tv_sec == other->elapsed.tv_sec) &&
           (inst->elapsed.tv_nsec == other->elapsed.tv_nsec)));
}

Status CatlogSender_Send(CatlogSender *inst)
{
  nonull(inst, (UnavailableInstance));

  /* Filtering. */
  state(inst->msg.level < inst->filter, (CatMessageSuppressed));

  /* Literalise time. */
  char tmbuff[30] = EMPTY;
  zero(strftime(tmbuff, CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM, "%c",
                localtime(&inst->msg.time)),
       RETURN(annot(NoBytesWereWritten,
                    "Failed to write formatted time into buffer for CatLog.")));

  /* Literalise header. */
  char header_buffer[CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM] = EMPTY;
  zero(sprintf(header_buffer, CATLOG_MESSAGE_HEADER_FORMAT, tmbuff,
               strlvl(inst->msg.level), inst->msg.initiator),
       RETURN(annot(NoBytesWereWritten,
                    "Failed to write content into buffer for CatLog.")));

  const size_t header_buffer_len = strlen(header_buffer);

  /* Tokenise with @NEWLINE. */
  char *tok = strtok(inst->msg.content, NEWLINE);
  while (tok) {
    zero(
        fwrite(header_buffer, sizeof(header_buffer[0]), header_buffer_len,
               inst->dst),
        RETURN(annot(ReadWriteError,
                     "No bytes were written into buffer for header_buffer.")););
    zero(fwrite(tok, sizeof(inst->msg.content[0]), strlen(inst->msg.content),
                inst->dst),
         RETURN(annot(ReadWriteError,
                      "No bytes were written into buffer for content.")););
    zero(
        fwrite(NEWLINE, sizeof(NEWLINE), strlen(NEWLINE), inst->dst),
        RETURN(annot(
            ReadWriteError,
            "No bytes were written into buffer for line wrapping character for "
            "content.")););
    tok = strtok(NULL, NEWLINE);
  }

  RETURN(NormalStatus);
}

Status cat(CATS, CatlogLevel lvl, const char *initiator, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  Status create = CatlogMessage_Create(&cs->msg, lvl, initiator, fmt, ap);
  va_end(ap);
  
  notok(create, {
    RETURN(_);
  })
  
  /* Send out the message. */
  fail(CatlogSender_Send(cs));

  RETURN(NormalStatus);
}
