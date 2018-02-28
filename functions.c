#ifndef FUNC

#define FUNC

#include "main.h"

int mybarrier(MPI_Comm mcw)
{
  int world_rank;
  MPI_Comm_rank(mcw, &world_rank);
  int world_size;
  MPI_Comm_size(mcw, &world_size);
  printf("%d entered function\n",world_rank);

  int level, offset, tag = 0, sig = 1, max = getMax(world_size);
  MPI_Status status;
  MPI_Request request;

  // Main loop....
  for(
      level = 2, offset = 1;
      level <= max;
      level = level * 2, offset = offset * 2
     )
  {
      if((world_rank % level) < offset)
      {
        MPI_Isend(&world_rank, 1, MPI_INT, world_rank + offset, tag, mcw, &request);
        MPI_Recv(&sig, 1, MPI_INT, world_rank + offset, tag, mcw, &status);        
      }
      else if((world_rank % level) >= offset)
      {
        MPI_Isend(&world_rank, 1, MPI_INT, world_rank - offset, tag, mcw, &request);
        MPI_Recv(&sig, 1, MPI_INT, world_rank - offset, tag, mcw, &status);
      }
      tag++;
  }

  // for(
  //     level = max, offset = max/2;
  //     level >= 2;
  //     level = level / 2, offset = offset / 2
  //    )
  // {
  //     if((world_rank % level) < offset)
  //     {
  //       if ((world_rank + offset) < world_size)
  //       {
  //         MPI_Isend(&world_rank, 1, MPI_INT, world_rank + offset, tag, mcw, &request);
  //         MPI_Recv(&sig, 1, MPI_INT, world_rank + offset, tag, mcw, &status);
  //       }
  //     }
  //     else if((world_rank % level) >= offset)
  //     {
  //       MPI_Isend(&world_rank, 1, MPI_INT, world_rank - offset, tag, mcw, &request);
  //       MPI_Recv(&sig, 1, MPI_INT, world_rank - offset, tag, mcw, &status);
  //     }
  //     tag++;
  // }


  // Broadcast of all-clear signal from world_rank 0.
  // for (level = world_size,
  //      offset = world_size/2;
  //      level >= 2;
  //      level = level / 2,
  //      offset = offset / 2
  //      )
  //  {
  //    if ((world_rank % level) == 0)
  //    {
  //      // Process is a sender and must relay its all-clear to its recipient.
  //      MPI_Send(&sig, 1, MPI_INT, world_rank + offset, tag, mcw);
  //    }
  //    else if ((world_rank % level) == offset)
  //    {
  //      // Process is a receiver and must wait for a check-in from its sender.
  //      MPI_Recv(&sig, 1, MPI_INT, world_rank - offset, tag, mcw, &status);
  //    }
  //    else
  //    {
  //      // Process is neither a sender nor a receiver on this iteration.
  //      continue;
  //    }
  //  }

  return 0;
}

int getMax(int world_size)
{
  int start = 2;
  while (start <= world_size)
  {
    start *= 2;
  }
  return start;
}

#endif
