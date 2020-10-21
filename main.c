/* Author: Alexander Hughey
 * CS4760 F2020
 * Project 3 - OS Shell
 * main driver for project 3
 * invoked as "oss"
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
#include <sys/wait.h>

int main(int argc, char* argv[])
{
  //variable declarations for command line options and defaults
  int opt;
  int child_max = 5;
  int countdown = 20;
  char * log_file = "logfile.txt";
  
  //processes command line arguments
  //options are -h, -c x, -l file, -t time
  while((opt = getopt(argc, argv, ":hc:l:t:")) != -1)
  {
    switch(opt)
    {
      case 'h':
        printf("Usage:\n");
        printf("master [-c x] [-l fielname] [-t time] infile\n");
        printf("\t-c x\tindicate the maximum total of child processes master will ");
        printf("\n\t\tspawn. (Default 5)\n");
        printf("\t-l x\tspecifies the name of the log file.\n");
        printf("\t-t time\tdetermines the time in seconds when the master will ");
        printf("\n\t\tterminate itself and all children (default 20).\n");
        break;
      case 'c':
        child_max = atoi(optarg);
        if(child_max >= 20)
        {
          printf("no more than 19 children may exist at once\n");
          printf("you attempted %d\n", child_max);
          child_max = 19;
          printf("value has been defaulted to %d...\n", child_max);
        }
        else
          printf("called with c option %d value\n", child_max);
        break;
      case 'l':
        log_file = optarg;
        printf("called with l option %d value\n", log_file);
        break;
      case 't':
        countdown = atoi(optarg);
        printf("called with t option %d value\n", countdown);
        break;
      case ':':
        fprintf(stderr, "option needs a value\n");
        perror("ERROR: ");
        return(-1);
        break;
      case'?':
        printf("unknown option\n");
        perror("ERROR: ");
        return(-1);
        break;
    }//end of switch
    
  }//end of while loop
  
  //catches extra arguments
  for(; optind < argc; optind++)
  { 
    char * test_str_file = "bb.bb";
    test_str_file = argv[optind];
    printf("extra argument: %s\n", test_str_file);  
  }//end of for loop
  
  // create shared memory for clock.
  // seconds, nanosecond, shmPID (used by child processes to indicate when they have
  // terminated.)
  //keys for shmget
  key_t sec_key; 
  key_t ns_key;
  key_t shmPID_key;
  //ids returned from shmget
  int sec_shmid;
  int ns_shmid;
  int shmPID_shmid;
  //shared mem size (same for all 3)
  int size;
  
  //inserting values
  sec_key = 909090;
  ns_key = 808080;
  shmPID_key = 707070;
  size = sizeof(int);
  
  if((sec_shmid = shmget( sec_key, size, IPC_CREAT)) == -1)
  {
    perror("failed to create shared memory for clock seconds");
    return -1;
  }//end of if
  
  if((ns_shmid = shmget( ns_key, size, IPC_CREAT)) == -1)
  {
    perror("failed to create shared memory for clock nanoseconds");
    return -1;
  }//end of if
  
  if((shmPID_shmid = shmget( shmPID_key, size, IPC_CREAT)) == -1)
  {
    perror("failed to create shared memory for shmPID");
    return -1;
  }//end of if
  
  ////////////////destroy shm
  
  if((shmctl( sec_shmid, IPC_RMID, NULL)) == -1)
  {
    perror("failed to destroy shared memory for sec");
    return -1;
  }//end of if
  
  if((shmctl( ns_shmid, IPC_RMID, NULL)) == -1)
  {
    perror("failed to destroy shared memory for nanosec");
    return -1;
  }//end of if
  
  if((shmctl( shmPID_shmid, IPC_RMID, NULL)) == -1)
  {
    perror("failed to destroy shared memory for shmPID");
    return -1;
  }//end of if
  
  //array of character arrays used as an argument for exec
  char *args[]={"./user",NULL};
  //iterator
  int it = 0;
  //launches initial children
  for( it = 1; it <= child_max ; it++ )
  {
    if(fork() == 0)//child enter
    { 
      execvp(args[0],args);
      return 0;
    }//end of if
  }//end of for loop L1
  
  
  int child_tot = child_max; //total number of child processes
  int checkpoint = 0; //holds ns since last process termination
  int sec_temp = 0; //holds seconds from shared memory clock
  
  while( checkpoint < 2000000000 && child_tot < 100 && sec_temp < countdown)
  {
    //{critical section}
    //  increment clock
    //
    //{critical section}
    //  check shmPID
    //  if( shmPID != 0)
        {
    //    open log file
    //    write shmPID and time
    //    close log file
    //    shmPID = 0
    //    child_tot++
          if(fork() == 0)//child enter
          { 
            execvp(args[0],args);
            return 0;
          }//end of if  
        }
  }//end of while loop L1
  wait();
  return 0;
}//end of main