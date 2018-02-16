#ifndef FUNC

#define FUNC

#include "main.h"

int mybarrier(MPI_Comm mcw)
{
  // Process: Gather check-in notifications on world_rank 0.
    // Question: Who am I waiting on to check-in with me?
    // Question: To whom am I sending my notification?

  // When all check-ins are complete, continue...

  // Process: Broadcast all-clear notifications to all processes.
    // Question: Who am I waiting on for the all-clear signal?
    // Question: To whom do I send the all clear signal?

  // Once the all clear signal has been received and retransmitted, the
  // process may exit the function.
  return 0;
}

#endif
