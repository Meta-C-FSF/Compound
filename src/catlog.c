#include <Compound/catlog.h>

Status CatlogMsg_Create(CatlogMsg *inst, CatlogLevel level,
  const char *initiator, const char *content)
{
  /* Skip unavailable instances and parameters. */
  nonull(inst, apply(UnavailableInstance));
  state((initiator == NULL || content == NULL),
    apply(InvalidParameter));
  state(strlen(initiator) > CATLOG_MESSAGE_INITIATOR_LENGTH_MAXIMUM,
    apply(CatMessageInitiatorTooLong));
  state(strlen(content) > CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM,
    apply(CatMessageContentTooLong));

	inst->time = time(NULL);
	inst->level = level;
  (void)strncpy(inst->initiator, initiator, CATLOG_MESSAGE_INITIATOR_LENGTH_MAXIMUM);
  (void)strncpy(inst->content, content, CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM);

	return apply(NormalStatus);
}

Status CatlogMsg_CopyOf(CatlogMsg *inst, CatlogMsg *other)
{
  /* Skip unavailable instances and parameters. */
  nonull(inst, apply(UnavailableInstance));
  nonull(other, apply(InvalidParameter));

	*inst = *other;

	return apply(NormalStatus);
}

bool CatlogMsg_Equals(CatlogMsg *inst, CatlogMsg *other)
{
  /* Skip unavailable instances and parameters. */
  state((!inst || other == NULL), false);

	return (
		inst->time == other->time &&
		inst->level == other->level &&
		(!strcmp(inst->initiator, other->initiator)) &&
		(!strcmp(inst->content, other->content))
	);
}

Status CatlogSender_Initialise(CatlogSender *inst, CatlogMsg msg, FILE *dst)
{
  /* Skip unavailable instances and parameters. */
  nonull(inst, apply(UnavailableInstance));

  /* Copy and assign. */
  inst->msg = msg;
  inst->dst = (!dst ? stdout : dst);
  inst->successful = false;
  inst->elapsed = (struct timespec) {
    .tv_sec = 0,
    .tv_nsec = 0
  };

  return apply(NormalStatus);
}

Status CatlogSender_CopyOf(CatlogSender *inst, CatlogSender *other)
{
  /* Skip unavailable instances and parameters. */
  nonull(inst, apply(UnavailableInstance));
  nonull(other, apply(InvalidParameter));

  /* Copy and assign */
  inst->msg = other->msg;
  inst->dst = other->dst;
  inst->successful = other->successful;
  inst->elapsed = other->elapsed;

  return apply(NormalStatus);
}

bool CatlogSender_Equals(CatlogSender *inst, CatlogSender *other)
{
  /* Skip unavailable instances and parameters. */
  state((!inst || other == NULL), false);

  return (
    CatlogMsg_Equals(&inst->msg, &other->msg) &&
    inst->dst == other->dst &&
    inst->successful == other->successful &&
    ((inst->elapsed.tv_sec == other->elapsed.tv_sec) &&
    (inst->elapsed.tv_nsec == other->elapsed.tv_nsec))
  );
}

Status CatlogSender_Send(CatlogSender *inst)
{
  /* Skip unavailable instances and parameters. */
  nonull(inst, apply(UnavailableInstance));

  /* Filtering. */
  state(inst->msg.level < inst->filter, apply(CatMessageSuppressed));

  /* Write buffer for timestamp. */
  char tmbuff[30] = EMPTY;
  zero(strftime(tmbuff, CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM, "%c",
    localtime(&inst->msg.time)),
    return apply(annot(NoBytesWereWritten,
      "Failed to write formatted time into buffer for CatLog.")));

  /* Write buffer for header, including timestamp. */
  char header_buffer[CATLOG_MESSAGE_CONTENT_LENGTH_MAXIMUM] = EMPTY;
  zero(sprintf(header_buffer, CATLOG_MESSAGE_FORMAT, tmbuff,
               strlvl(inst->msg.level), inst->msg.initiator),
       return apply(annot(NoBytesWereWritten,
                          "Failed to write content into buffer for CatLog.")));
  const size_t header_buffer_len = strlen(header_buffer);

  /* Write into @inst->dst with lines according to new-line character. */
  char *tok = strtok(inst->msg.content, NEWLINE);
  while (tok) {
    zero(
      fwrite(header_buffer, sizeof(header_buffer[0]),
        header_buffer_len, inst->dst),
      return apply(annot(ReadWriteError,
        "No bytes were written into buffer for header_buffer."));
    );
    zero(
      fwrite(tok, sizeof(inst->msg.content[0]),
        strlen(inst->msg.content), inst->dst),
      return apply(annot(ReadWriteError,
        "No bytes were written into buffer for content."));
    );
    zero(
      fwrite(NEWLINE, sizeof(NEWLINE), strlen(NEWLINE), inst->dst),
      return apply(annot(ReadWriteError,
        "No bytes were written into buffer for line wrapping character for "
        "content."));
    );
    tok = strtok(NULL, NEWLINE);
  }

  return apply(NormalStatus);
}

Status CatlogUtils_OpenFile(FILE *target, const char *filepath,
  const char *restrict mode)
{
  /* Skip unavailable instances and parameters. */
  nonull(target, apply(UnavailableBuffer));
  nonull(filepath, apply(UnavailableFileName));
  nonull(mode, apply(UnavailableFileAccessMode));

  /* Open the file.  Return CatCannotOpenFile once failed. */
  state(!(target = fopen(filepath, mode)),
    apply(CatCannotOpenFile));

  return apply(NormalStatus);
}

Status CatlogUtils_CloseFile(FILE *fileptr)
{
  /* Skip if either the fileptr or the *fileptr is unavailable. */
  state(!fileptr || !fileptr, apply(UnavailableParameter));

  /* Return returning code of fclose, sealed with "value". */
  return apply(value(UnknownStatus, fclose(fileptr)));
}
