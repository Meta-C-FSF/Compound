#include <Compound/report.h>

Status Report_Create(Report *inst, Status *stat, FILE *dest, char *initiator,
                     int priority)
{
  /* Skip unavailable parameters. */
  nonull(inst, apply(UnavailableInstance));
  nonull(stat, apply(error(InvalidParameter, "Given stat was null.")));
  nonull(initiator, apply(error(InvalidParameter, "Given initiator was null.")));
  state(priority < 0, apply(error(InvalidParameter, "Given priority was negative.")));

  /* Copy and assign. */
  inst->content = *stat;
  inst->initiator = calloc(strlen(initiator), sizeof(char));
  (void)strcpy(inst->initiator, initiator);
  inst->time = time(NULL);
  inst->level = priority;
  inst->status = REPORT_SENDING_TASK_STATUS_PENDING;
  inst->dst = (dest == NULL ? stdout : dest);

  return apply(NormalStatus);
}

Status Report_CopyOf(Report *inst, Report *other)
{
  nonull(inst, apply(UnavailableInstance));
  nonull(other, apply(error(InvalidParameter, "Given report is unavailable.")));

  // Status status;
  // char *initiator;
  // time_t time;
  // ReportLevel priority;
  // ReportTaskStatus taskprint_status;
  // FILE *dest;
  inst->content = other->content;

  return apply(NormalStatus);
}

void Report_Delete(Report *inst)
{
  svoid(inst);

  free(inst->initiator);
  inst->initiator = NULL;
  inst->dst = NULL;
  inst->level = 0;
  inst->content = (Status){};
  inst->status = REPORT_SENDING_TASK_STATUS_NOTFOUND;
  inst->time = 0;
  inst = NULL;
}

/*
  Status status;
  char *initiator;
  time_t time;
  ReportLevel priority;
  ReportTaskStatus taskprint_status;
  FILE *dest;
*/
Status Report_Literalise(Report *inst, char *buff)
{
  nonull(inst, apply(UnavailableInstance));
  nonull(buff, apply(UnavailableBuffer));

  /* Report literalisation. */
  char report_literalising[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;

  /** Status literalisation. **/
  char status_literalising[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;

  /* Fault detection on status literalisation. */
  // settle(Status_LiteraliseForReport(&inst->status, status_literalising),
  //     _.characteristic == STATUS_UNKNOWN, {
  //   nest(_, __, {
  //     /* Skip when ZERO byte were written. (failed to write) */
  //     state(!__.value, apply(
  //       error(value(TraditionalFunctionReturn, __.value),
  //         "ZERO byte were written.")
  //     ));
  //   })
  // });

  /* Traditional function returning handling. */
  settle(Status_LiteraliseForReport(&inst->content, status_literalising),
    !_.value, {
      return apply(annot(RuntimeError, "Failed to literalise status for report."));
  });

  /* Write result to buffer. */
  /* Write the report "header". */
  /* Literalise current time and date. */
  char datetime[LITERALISATION_LENGTH_MAXIMUM];
  // settle(strftime(datetime, 64, "%c", localtime(&inst->time)), )
  
  // DATETIME [LEVEL] STATUS.IDENTITY (INITIATOR): STATUS.DESCRIPTION
  state(!snprintf(report_literalising, LITERALISATION_LENGTH_MAXIMUM,
      REPORT_LITERALISE_FORMAT_HEADER, datetime, inst->level,
      inst->content.identity, inst->initiator, inst->content.description),
    apply(annot(NoBytesWereWritten, "Failed to literalise date and time."))
  );
   
 /* Write the report "detail". */
  
  return apply(NormalStatus);
}

/*
  thrd_t thread;
  Report report;
  time_t elapsed;
  ReportResult result;
*/
Status ReportSender_Create(ReportSender *inst, Report *report)
{
  nonull(inst, apply(UnavailableInstance));
  nonull(report, error(UnavailableParameter, "Given report was unavailable."));

  thrd_create(&inst->thread, &HANDLER, report);
  notok(Report_CopyOf(&inst->report, report),
    return apply(annot(InstanceCreatingFailure,
      "Cannot copy to create new instance of report."));
  );
  inst->report = *report;
  inst->elapsed = 0;
  inst->result = REPORT_RESULT_PENDING;

  return apply(NormalStatus);
}

Status ReportSender_Send(ReportSender *inst, ReportTask task)
{
  // /* Skip when inst or task is unavailable. */
  // nonull(inst,
  //       error(UnavailableInstance, "Report sender was given unavailable."));
  // nonull(task, InvalidReportTask);

  // /* Assign for dest. */
  // const FILE *dest = (inst->report->dest == NULL ? stdout : inst->report->dest);
  // // char buff[];
  // // TODO(william): HERE, Report_Literalise

  // /* Write/Send data. */
  // inst->report->taskprint_status = REPORT_SENDING_TASK_STATUS_PROCEEDING;
  // if (!fprintf(dest, buff)) {
  // }
   
  // /* Sent successfully!  Mark down properties. */
  return apply(NormalStatus);
}
