#include <stdio.h>
#include <time.h>

#include <Compound/status.h>

int main(void) {

  Status Example1Status = {.description = "Example1 Status",
                           .characteristic = STATUS_NORMAL,
                           .prev = &NormalStatus};
  Status Example2Status = {.description = "Example2 Status",
                           .characteristic = STATUS_NORMAL,
                           .prev = &Example1Status};
  Status Example3Status = {.description = "Example3 Status",
                           .characteristic = STATUS_NORMAL,
                           .prev = &Example2Status};
  Status Example4Status = {.description = "Example4 Status",
                           .characteristic = STATUS_NORMAL,
                           .prev = &Example3Status};
  Status Example5Status = {.description = "Example5 Status",
                           .characteristic = STATUS_NORMAL,
                           .prev = &Example4Status};
  Status Example6Status = {.description = "Example6 Status",
                           .characteristic = STATUS_NORMAL,
                           .prev = &Example5Status};
  Status Example7Status = {.description = "Example7 Status",
                           .characteristic = STATUS_NORMAL,
                           .prev = &Example6Status};
  Status Example8Status = {.description = "Example8 Status",
                           .characteristic = STATUS_NORMAL,
                           .prev = &Example7Status};
  Status Example9Status = {.description = "Example9 Status",
                           .characteristic = STATUS_NORMAL,
                           .prev = &Example8Status};
  Status Example10Status = {.description = "Example10 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example9Status};
  Status Example11Status = {.description = "Example11 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example10Status};
  Status Example12Status = {.description = "Example12 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example11Status};
  Status Example13Status = {.description = "Example13 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example12Status};
  Status Example14Status = {.description = "Example14 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example13Status};
  Status Example15Status = {.description = "Example15 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example14Status};
  Status Example16Status = {.description = "Example16 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example15Status};
  Status Example17Status = {.description = "Example17 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example16Status};
  Status Example18Status = {.description = "Example18 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example17Status};
  Status Example19Status = {.description = "Example19 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example18Status};
  Status Example20Status = {.description = "Example20 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example19Status};
  Status Example21Status = {.description = "Example21 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example20Status};
  Status Example22Status = {.description = "Example22 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example21Status};
  Status Example23Status = {.description = "Example23 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example22Status};
  Status Example24Status = {.description = "Example24 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example23Status};
  Status Example25Status = {.description = "Example25 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example24Status};
  Status Example26Status = {.description = "Example26 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example25Status};
  Status Example27Status = {.description = "Example27 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example26Status};
  Status Example28Status = {.description = "Example28 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example27Status};
  Status Example29Status = {.description = "Example29 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example28Status};
  Status Example30Status = {.description = "Example30 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example29Status};
  Status Example31Status = {.description = "Example31 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example30Status};
  Status Example32Status = {.description = "Example32 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example31Status};
  Status Example33Status = {.description = "Example33 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example32Status};
  Status Example34Status = {.description = "Example34 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example33Status};
  Status Example35Status = {.description = "Example35 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example34Status};
  Status Example36Status = {.description = "Example36 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example35Status};
  Status Example37Status = {.description = "Example37 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example36Status};
  Status Example38Status = {.description = "Example38 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example37Status};
  Status Example39Status = {.description = "Example39 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example38Status};
  Status Example40Status = {.description = "Example40 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example39Status};
  Status Example41Status = {.description = "Example41 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example40Status};
  Status Example42Status = {.description = "Example42 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example41Status};
  Status Example43Status = {.description = "Example43 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example42Status};
  Status Example44Status = {.description = "Example44 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example43Status};
  Status Example45Status = {.description = "Example45 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example44Status};
  Status Example46Status = {.description = "Example46 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example45Status};
  Status Example47Status = {.description = "Example47 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example46Status};
  Status Example48Status = {.description = "Example48 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example47Status};
  Status Example49Status = {.description = "Example49 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example48Status};
  Status Example50Status = {.description = "Example50 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example49Status};
  Status Example51Status = {.description = "Example51 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example50Status};
  Status Example52Status = {.description = "Example52 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example51Status};
  Status Example53Status = {.description = "Example53 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example52Status};
  Status Example54Status = {.description = "Example54 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example53Status};
  Status Example55Status = {.description = "Example55 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example54Status};
  Status Example56Status = {.description = "Example56 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example55Status};
  Status Example57Status = {.description = "Example57 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example56Status};
  Status Example58Status = {.description = "Example58 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example57Status};
  Status Example59Status = {.description = "Example59 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example58Status};
  Status Example60Status = {.description = "Example60 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example59Status};
  Status Example61Status = {.description = "Example61 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example60Status};
  Status Example62Status = {.description = "Example62 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example61Status};
  Status Example63Status = {.description = "Example63 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example62Status};
  Status Example64Status = {.description = "Example64 Status",
                            .characteristic = STATUS_NORMAL,
                            .prev = &Example63Status};

  Status statbuff[64] = {{0}};

  status_dump(Example64Status, statbuff, 0);

  Status *p = &Example64Status;
  int cnt = 0;
  while (p != NULL) {
    (void)printf("%d:%d %s\n", cnt++, p->characteristic, p->description);
    p = p->prev;
  };

  return 0;
}
