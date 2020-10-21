/* Author: Alexander Hughey
 * CS4760 F2020
 * Project 3 - OS Shell
 * Child process for project 3
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/msg.h> 


int main()
{
  //loopflag = 0;
  //lifetime = rand int 1-1000000
  //{critical section}
  //  start = time (ns + s*1000000000)
  //
  //loop while( loopflag == 0 )
  //  {critical section}
  //    check clock
  //    if( current - start > lifetime )
  //      if( shmPID == 0 )
  //        shmPID = PID
  //        loopflag = 1
  perror("test");

  return 0;
}