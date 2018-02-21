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
  MPI_Status status;

  // Initial loop....
  for(level = 2, offset = 1;
    level <= world_size;
    level = level * 2, offset = offset * 2){
      if((world_rank % level) == offset){
        //send
        MPI_Send(&world_rank, 1, MPI_INT,
          world_rank - offset, MPI_ANY_TAG, mcw);
      }
      else if((world_rank % level) == 0){
        //receive
        int dummy;
        MPI_Recv(&dummy, 1, MPI_INT,
          world_rank + offset, MPI_ANY_TAG, mcw);
      }
      else {
        continue;
      }
    }

  tag++;

  // Final loop....

  return 0;
}

#endif
