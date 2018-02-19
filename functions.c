#ifndef FUNC

#define FUNC

#include "main.h"

int mybarrier(MPI_Comm mcw)
{
  int world_rank;
  MPI_Comm_rank(MCW, &world_rank);
  int world_size;
  MPI_Comm_size(MCW, &world_size);

  int level, offset, sender, receiver, tag = 0, sig = 1;
  MPI_status status;

  // Initial loop....

  tag++;

// Final loop....

  return 0;
}

#endif
