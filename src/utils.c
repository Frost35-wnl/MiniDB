#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "../include/utils.h"

#define PUBLIC
#define PRIVATE static

PUBLIC void create_directory(char *parent_directory, char *directory) 
{
  chdir(parent_directory);
  if ( mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH ) == -1) {
    if (errno == EEXIST)
      return;
    fprintf(stderr, "Error in create_path : failed to create %s/%s folder", parent_directory, directory);
    exit(EXIT_FAILURE);
  }
}
