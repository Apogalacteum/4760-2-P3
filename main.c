/* Author: Alexander Hughey
 * CS4760 F2020
 * Project 3 - Palindromes
 * main driver for project 2
 * invoked as "master"
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>

int main(int argc, char* argv[])
{
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
        printf("\t-c x\tIndicate the maximum total of child processes master will ");
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
        log_filename = optarg;
        printf("called with l option %d value\n", log_filename);
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
  
  //catches extra arguments (should be infile)
  for(; optind < argc; optind++)
  { 
    char * test_str_file = "bb.bb";
    test_str_file = argv[optind];     
    printf("extra arguments: %s\n", test_str_file);  
  }//end of for loop
  
  return 0;
}//end of main