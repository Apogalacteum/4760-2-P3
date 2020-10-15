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
  int child_total_max = 4;
  int child_concurrent_max = 2;
  int countdown = 100;
  
  //processes command line arguments
  //options are -h, -n x, -s x, -t x
  while((opt = getopt(argc, argv, ":hn:s:t:")) != -1)
  {
    switch(opt)
    {
      case 'h':
        printf("Usage:\n");
        printf("master [-n x] [-s x] [-t time] infile\n");
        printf("\t-n x\tIndicate the maximum total of child processes master will ");
        printf("\n\t\tever create. (Default 4)\n");
        printf("\t-s x\tIndicate the number of children allowed to exist in the ");
        printf("\n\t\tsystem at the same time. (Default 2)\n");
        printf("\t-t time\tThe time in seconds after which the process will ");
        printf("\n\t\tterminate, even if it has not finished. (Default 100)\n");
        printf("\tinfile\tInput file containing strings to be tested.\n");
        break;
      case 'n':
        child_total_max = atoi(optarg);
        printf("called with n option %d value\n", child_total_max);
        break;
      case 's':
        child_concurrent_max = atoi(optarg);
        if(child_concurrent_max >= 20)
        {
          printf("no more than 19 children may exist at once\n");
          printf("you attempted %d\n", child_concurrent_max);
          child_concurrent_max = 19;
          printf("value has been defaulted to %d...\n", child_concurrent_max);
        }
        else
          printf("called with s option %d value\n", child_concurrent_max);
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