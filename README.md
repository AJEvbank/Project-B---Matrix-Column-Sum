# Project-B---Matrix-Column-Sum
This is for the second parallel programming project.

Note: The name is wrong. We misunderstood the original project assignment.

Concept: Upon entering the mybarrier function, processes being a sequence of
'check-in' messages. The check-ins are relayed to process 0 which, when all
check-ins have been completed, broadcasts an 'all-clear' signal to the other
processes. Once a process has relayed its all-clear message, it leaves the
function.

The fundamental concept of our algorithm is recursion over comm worlds which
double or half in size. There is a consistent mathematical relationship
between the ranks of processes which must participate in message relaying. The
process of relaying and broadcasting works in a set number of iterations (i.e.
log of world size). On each iteration the role of each process may be
calculated using a modulo operation with a set of base variables.

The algorithm given below reveals the relationship and how to determine the
role of a process on a given iteration.

Constraints: The overall world size must be a power of 2.

Algorithm:

var level: int \\ The relative world size each process will use on an iteration
               \\ to determine its communication role.
    offset: int \\ The offset from the world size each process will use on an
                \\ iteration to determine its communication role.
    sender: int \\ In a communication transaction, the sender of a message.
    receiver: int \\ In a communication transaction, the receiver of a message.
    world_size: int \\ The overall size of the comm world.
    world_rank: int \\ The rank of an individual process.
    message: int \\ A message variable.

\\ Check-in process to relay the arrival of all processes to world_rank 0.
for (level = 2,
     offset = 1;
     level <= world_size;
     level = level * 2,
     offset = offset * 2)
{
  if ((world_rank % level) == offset)
  {
    \\ Process is a sender and must relay its check-in to its recipient.
    Send message to recipient process (world_rank - offset).
  }
  else if ((world_rank % level) == 0)
  {
    \\ Process is a receiver and must wait for a check-in from its sender.
    Receive message from process (world_rank + offset).
  }
  else
  {
    \\ Process is neither a sender nor a receiver on this iteration.
    continue
  }
}

\\ Broadcast of all-clear signal from world_rank 0.
for (level = world_size,
     offset = world_size/2;
     level >= 2;
     level = level / 2,
     offset = offset / 2
     )
 {
   if ((world_rank % level) == 0)
   {
     \\ Process is a sender and must relay its all-clear to its recipient.
     Send message to recipient process (world_rank + offset).
   }
   else if ((world_rank % level) == offset)
   {
     \\ Process is a receiver and must wait for a check-in from its sender.
     Receive message from process (world_rank - offset).
   }
   else
   {
     \\ Process is neither a sender nor a receiver on this iteration.
     continue
   }
 }

Note: All sends and receives are blocking calls. No process can leave the
function until all other processes have entered. The time complexity of the
function is 2logP where P is the world size and must be a power of 2.
