#include <Compound/status.h>

Status Location_Literalise(Location *inst, char *buff)
{
  nonull(inst, apply(UnavailableInstance));
  nonull(buff, apply(UnavailableBuffer));
  
  /* Literalise line. */
  char line_buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
  Utils_LiteraliseInteger(inst->line, line_buff);

  where(
    snprintf(buff, LITERALISATION_LENGTH_MAXIMUM,
              LOCATION_LITERALISE_FORMAT,inst->file,inst->line,inst->func),
    return apply(value(TraditionalFunctionReturn, _));
  );
  
  return apply(NormalStatus);
}

bool Location_Equal(Location *lc1, Location *lc2)
{
  state(lc1 == NULL || lc2 == NULL, false);

  return ((!strcmp(lc1->file, lc2->file)) && (lc1->line == lc2->line) &&
          (!strcmp(lc1->func, lc2->func)));
}

bool Status_Equal(Status *stat1, Status *stat2)
{
  state(stat1 == NULL || stat2 == NULL, false);

  return (
    stat1->value == stat2->value &&
    !strcmp(stat1->description, stat2->description) &&
    stat1->characteristic == stat2->characteristic &&
    Location_Equal(&stat1->loc, &stat2->loc) &&
    ((StatusUtils_HasPrev(*stat1) && StatusUtils_HasPrev(*stat2))
            ? Status_Equal(stat1->prev, stat2->prev)
            : true)
  );
}

Status Status_Literalise(Status *inst, char *buff)
{
  /* Skip unavailable instance and invalid parameter. */
  nonull(inst, apply(UnavailableInstance));
  nonull(buff, apply(UnavailableBuffer));

  /* Literalise loc. */
  char loc_buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;
  (void)printf("%s\n", loc_buff);
  unsure(Location_Literalise(&inst->loc, loc_buff), !_.value, {
    (void)printf("failed on loc liter.\n");
    return apply(_);
  });

  /* Styling output. */
  // TODO(william): Replace following lines with 
  const char *fmt;
  if (inst->characteristic == STATUS_ERROR) {
    // TODO(william): Replace following line with coloured-term-output function.
    fmt = "\e[38;5;9m\e[1m"STATUS_LITERALISE_FORMAT"\e[0m";
  } else if (inst->characteristic == STATUS_UNKNOWN) {
    // TODO(william): Replace following line with coloured-term-output function.
    fmt = "\e[38;5;11m"STATUS_LITERALISE_FORMAT"\e[0m";
  } else {
    // TODO(william): Replace following line with coloured-term-output function.
    fmt = "\e[38;5;10m"STATUS_LITERALISE_FORMAT"\e[0m";
  }

  /* Concatenate every buffer. */
  where(
    snprintf(buff, LITERALISATION_LENGTH_MAXIMUM, fmt, inst->identity,
             inst->description,
             (!inst->prev ? "(null)" : (inst->prev->identity)),
             inst->value, inst->characteristic, loc_buff), {
    return apply(value(TraditionalFunctionReturn, _));
  });
}

Status Status_LiteraliseForReport(Status *inst, char *buff)
{
  /* Skip unavailable instance and invalid parameter. */
  nonull(inst, apply(UnavailableInstance));
  nonull(buff, apply(UnavailableBuffer));

  where(
    snprintf(buff, LITERALISATION_LENGTH_MAXIMUM, REPORT_LITERALISE_FORMAT_DETAIL,
             strnil(inst->identity), strnil(inst->prev->identity),
             inst->value, inst->characteristic, inst->loc.file, inst->loc.line,
             inst->loc.func), {
    return apply(value(TraditionalFunctionReturn, _));
  });
}

bool StatusUtils_HasPrev(Status stat)
{
  return (stat.prev != NULL);
}

bool StatusUtils_IsOkay(Status stat)
{
  return (!stat.characteristic);
}

bool StatusUtils_IsRecursive(Status stat)
{
  return (stat.prev && stat.prev == &stat);
}

void StatusUtils_Dump(Status *inst, Status *store)
{
  /* Skip when store is unavailable, or, inst is unavailable,
     recursive or does not have any predecessor. */
  svoid(!inst || !store
        || StatusUtils_IsRecursive(*inst) || !StatusUtils_HasPrev(*inst));
  
  *store = *inst->prev;
}

// void StatusUtils_Dump(Status *inst, Status **store, int idx)
// {
//   /* Skip when having invalid inst, store or idx. */
//   svoid(!inst || !store || idx < 0 || StatusUtils_IsRecursive(*inst));
  
//   // store[idx] = *inst;
//   *store[idx] = (Status){
//     .identity = inst->identity,
//     .value = inst->value,
//     .description = inst->description,
//     .characteristic = inst->characteristic,
//     .loc = inst->loc,
//     .prev = inst->prev
//   };
 
//   (void)printf("idx: %d\n", idx);
  
//   StatusUtils_Dump(inst->prev, store, (idx - 1));
// }

int StatusUtils_Depth(Status *stat)
{
  /* Skip unavailable stat. */
  state((!stat || !stat->prev), -1);

  /* Set up counter. */
  int cnt = 1;
  /* Set up current status indication representor. */
  Status current = *stat;
  /* Iterate to accumulate. */
  while (current.prev) {
    current = *current.prev;
    cnt += 1;
  }

  return cnt;
  
  // Status *current = stat;  // Include this layer of Status.
  // register int cnt;
  // for (cnt = 0; (!StatusUtils_IsRecursive(*current)
  //                && StatusUtils_HasPrev(*current)); cnt++) {
  //   current = current->prev;
  // }
  
  // return cnt;
}

// bool arguestarter_equal(ArgueStarter *inst1, ArgueStarter *inst2)
// {
//   /* Skip when either inst1 or inst2 is unavailable. */
//   state(inst1 == NULL || inst2 == NULL, false);

//   return (inst1->argue_start == inst2->argue_start)
//           || (inst1->external_param == inst2->external_param);
// }

ReportTaskID THROW(Report report, Location loc)
{
  // // /* Create new a instance of ReportSender. */
  // // ReportSender sender;
  // // ReportSender_Create(&sender, stderr);

  // // /* Send message. */
  // // /* Initialise sender's thread. */
  // // thrd_t sending;
  // // /* Skip on failing on creating thread. */
  // // if (!thrd_create(&sending, starter, NULL)) {

  // //   /* Conclude the session of sender. */
  // //   report.status = REPORT_SENDING_TASK_STATUS_FINISHED,
  // //   report.result = (ARGUE_RESULT_FINALISED | ARGUE_RESULT_NEGATIVE);

  // //   sender.result = REPORT_SENDER_RESULT_FINISHED;
  // //   sender.successful = false;

  // //   return -1;
  // // }

  // // /* Perform sending. */
  // // ReportSender_Send(&sender, NULL);

  // /* Initialise sender. */
  // ReportSender sender;
  // /* Return with -1 when initialisation failed. */
  // state(!(StatusUtils_IsOkay(ReportSender_Create(&sender, &report))), -1);
  
  // /* Inject location information.  Could be more elegant, though. */
  // sender.report->status.loc = loc;
  
  // /* Send. */ /* Return -1 when failed on sending. */
  // state(!StatusUtils_IsOkay(ReportSender_Send(&sender, HANDLER)), -1);
  
  return 0;
}

int HANDLER(void *report)
{
  // /* Throw UnableToThrowError when param is unavailable. */
  // if (report == NULL) {
  //   /* Create report on this. */
  //   Report e;
  //   Report_Create(
  //     &e,
  //     &error(UnableToThrowError, "Cannot perform throwing.  Aborted."),
  //     stderr, nameof(DEFAULT_ARGUE_STARTER),
  //     REPORT_SENDING_PRIORITY_FATAL);

  //   /* Perform throwing. */
  //   (void)throw(e); // Throw the report alone.
  //   return 1;
  // }

  // (void)throw(*(Report *)report); // Lonely throw, no catch will company.
  // return 0;
  
  return 0;
}
