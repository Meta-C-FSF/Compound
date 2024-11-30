#include <Compound/status.h>

size_t Location_Literalise(const Location inst, char *buff)
{
  if (!buff)  return 0;

  return snprintf(buff, LITERALISATION_LENGTH_MAXIMUM,
      LOCATION_LITERALISE_FORMAT, inst.file, inst.line, inst.func);
}

bool Location_Equal(const Location loc1, const Location loc2)
{
  return (
    !strcmp(loc1.file, loc2.file)
      && (loc1.line == loc2.line)
      && (!strcmp(loc1.func, loc2.func))
  );
}

bool Status_Equal(const Status stat1, const Status stat2)
{
  return (
    !strcmp(stat1.identity, stat2.identity)
      && stat1.value == stat2.value
      && !strcmp(stat1.description, stat2.description)
      && stat1.characteristic == stat2.characteristic
      && Location_Equal(stat1.loc, stat2.loc)
      && stat1.prev == stat2.prev
  );
}

bool Status_Match(const Status stat1, const Status stat2)
{
  if (!stat1.identity || !stat2.identity)  return false;

  return (!strcmp(stat1.identity, stat2.identity));
}

bool Status_Belong(const Status stat1, const Status stat2)
{
  /* Get last Status from @stat. */
  Status last = stat1;
  while (StatusUtils_HasPrev(last)) {
    last = *last.prev;
  }

  return Status_Match(stat2, last);
}

size_t Status_Literalise(const Status inst, char *buff)
{
  if (!buff)  return 0;

  char loc_buff[LITERALISATION_LENGTH_MAXIMUM] = EMPTY;

  return (Location_Literalise(inst.loc, loc_buff) +
    snprintf(buff, LITERALISATION_LENGTH_MAXIMUM,
        STATUS_LITERALISE_FORMAT, inst.identity,
        inst.description,
        (!inst.prev ? "(null)" : (inst.prev->identity)),
        inst.value, inst.characteristic, loc_buff));
}

bool StatusUtils_HasPrev(Status stat)
{
  return (stat.prev != NULL && !StatusUtils_IsRecursive(stat));
}

bool StatusUtils_IsOkay(Status stat)
{
  return (!stat.characteristic);
}

bool StatusUtils_IsRecursive(Status stat)
{
  return (
    stat.prev && Status_Equal(stat, (!stat.prev ? (Status)EMPTY : *stat.prev))
  );
}

void StatusUtils_Dump(const Status inst, Status *store)
{
  /* Skip when store is unavailable, or, inst is unavailable,
     recursive or does not have any predecessor. */
  svoid(
    !store || StatusUtils_IsRecursive(inst) || !StatusUtils_HasPrev(inst)
  );
  
  *store = *inst.prev;
}

int StatusUtils_Depth(const Status stat)
{
  /* Set up counter. */
  int cnt = 1;
  /* Set up current status indication representor. */
  Status current = stat;
  /* Iterate to accumulate. */
  while (current.prev) {
    /* Skip recursive status. */
    if (StatusUtils_IsRecursive(current))  break;
      
    current = *current.prev;
    cnt += 1;
  }

  return cnt;
}
