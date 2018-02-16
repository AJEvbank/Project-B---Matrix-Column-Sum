#include "main.h"

int main(int argc, char ** argv)
{
  MPI_Init(&argc,&argv);
  int world_rank;
  MPI_Comm_rank(MCW, &world_rank);
  int world_size;
  MPI_Comm_size(MCW, &world_size);

  if (world_rank == 0)
  {
    printf("World_size = %d.\n\n",world_size);
  }
  
  printf("Rank: %d PRE-barrier.\n",world_rank);

  mybarrier(MCW);

  printf("Rank: %d POST-barrier.\n",world_rank);


  MPI_Finalize();
  return 0;
}
