#ifndef COMPOUND_REPORT_H
# define COMPOUND_REPORT_H

# include <Compound/status.h>

typedef enum {
  REPORT_SENDING_PRIORITY_ALL = 0,  // Highest level; least value.
  REPORT_SENDING_PRIORITY_FATAL,
  REPORT_SENDING_PRIORITY_EXCEPTIONAL,
  REPORT_SENDING_PRIORITY_CRITICAL,
  REPORT_SENDING_PRIORITY_MAJOR,
  REPORT_SENDING_PRIORITY_NORMAL,
  REPORT_SENDING_PRIORITY_MINOR,
  REPORT_SENDING_PRIORITY_DEBUG,
  REPORT_SENDING_PRIORITY_NONE,  // Lowest level, greatest value.
} ReportLevel;

typedef enum {
  REPORT_SENDING_TASK_STATUS_FINISHED = 0,
  REPORT_SENDING_TASK_STATUS_PENDING,
  REPORT_SENDING_TASK_STATUS_PROCEEDING,
  REPORT_SENDING_TASK_STATUS_PAUSED,
  REPORT_SENDING_TASK_STATUS_NOTFOUND
} ReportStatus;

/* "Report" recollects essential informations, included but not limited to
   Status and others for making an report for debugging and such. */
typedef struct {
  Status content;
  char *initiator;
  time_t time;
  ReportLevel level;
  ReportStatus status;
  FILE *dst;  // The destination where the report is sending to.
} Report;

/*
DATETIME [PRIORITY] STATUSNAME (ORIGINATOR): STATUS.DESCRIPTION
    at LOCATION.FILE:LOCATION.LINE, LOCATION.FUNC
    at LOCATION.FILE:LOCATION.LINE, LOCATION.FUNC
    at LOCATION.FILE:LOCATION.LINE, LOCATION.FUNC
    at LOCATION.FILE:LOCATION.LINE, LOCATION.FUNC


Fri 10 May 03:02:37 CST 2024 [URGENT] InvalidParameter (Nullity): Given buffer was unavailable.
    at /external/Documents/Projects/Compound/Status/src/status.c:104, Report_Literalise
    at /external/Documents/Projects/Compound/Status/src/status.c:114, ReportSender_Send
    at /external/Documents/Projects/Compound/Status/src/status.c:69, _throw
!!!!at /external/Documents/Projects/Compound/Array/src/array.c:16, array_create
    at /external/Documents/Projects/Compound/test.c:24, main

*/

// DATETIME [LEVEL] STATUS.IDENTITY (INITIATOR): STATUS.DESCRIPTION
# define REPORT_LITERALISE_FORMAT_HEADER  "%s [%d] %s (%s): %s\n\tat %s:%d, %s\n%s"

// STATUS.IDENTITY, STATUS.PREV.IDENTITY, STATUS.VALUE, STATUS.CHARACTERISTIC,
// FILE, LINE, FUNC
# define REPORT_LITERALISE_FORMAT_DETAIL  "\t%s(%s, %d, %d)  at %s:%d, %s\n"

typedef enum {
  REPORT_RESULT_SUCCEEDED,
  REPORT_RESULT_FAILED,
  REPORT_RESULT_PROGRESSING,
  REPORT_RESULT_PENDING,
} ReportResult;

typedef struct {
  thrd_t thread;
  Report report;
  time_t elapsed;
  ReportResult result;
} ReportSender;

typedef int (*ReportTask)(Report *);
typedef int ReportTaskID;

Status Report_Create(Report *inst, Status *stat, FILE *dest, char *initiator,
                     int priority);
Status Report_CopyOf(Report *inst, Report *other);
Status Report_Literalise(Report *inst, char *buff);
void   Report_Delete(Report *inst);
bool   Report_Equals(Report repo1, Report repo2);

// Status ReportSender_Create(ReportSender *inst, Report *report, thrd_start_t *handler);
Status ReportSender_Create(ReportSender *inst, Report *report);
Status ReportSender_Send(ReportSender *inst, ReportTask task);

// ReportTaskStatus
// ReportSender_GetStatus(ReportSender *inst);

/* Add location parameter requirement in order to give proper information
 * before throwing the report out. */
// # define throw(report)  THROW(report, __HERE__)

// ReportTaskID THROW(Report report, Location loc);
// Report CATCH(ReportTaskID taskid, Status (*handler)());
int HANDLER(void *report);

#endif  /* COMPOUND_REPORT_H */
