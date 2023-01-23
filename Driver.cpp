#include "Logger.hpp"

#include <mpi.h>

#include <sstream>
#include <cassert>
#include <cstdlib>

MPI_Win g_SequenceFeed;

int main(int argumentCount, char *argumentVector[])
{

  int programStatus = EXIT_FAILURE;

  try {

    int processRank = 0;

    auto mpiInitError = MPI_Init(NULL, NULL);
    assert(0 == mpiInitError);

    mpiInitError = MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
    assert(0 == mpiInitError);

    int maxProcesses = 0;
    mpiInitError = MPI_Comm_size(MPI_COMM_WORLD, &maxProcesses);
    assert(0 == mpiInitError);

    MPI_Aint elementSize = sizeof(long double);
    size_t segmentSize = 512;
    long double *base = NULL;

    mpiInitError = MPI_Win_allocate_shared(elementSize, segmentSize, MPI_INFO_NULL, MPI_COMM_WORLD, &base, &g_SequenceFeed);
    assert(0 == mpiInitError);

    GLOBAL_LOG("Rank: " << processRank << " Max Processes: " << maxProcesses << ' ' << g_SequenceFeed << ':' << base << std::endl);

    MPI_Win_free(&g_SequenceFeed);
    //MPI_Free_mem(base);
    MPI_Finalize();

    programStatus = EXIT_SUCCESS;

  } catch(std::exception &anException) {

    std::cerr << anException.what() << std::endl;;

  }

  return(programStatus);
  
}
