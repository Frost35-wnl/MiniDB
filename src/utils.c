#include "../include/utils.h"
#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define PUBLIC
#define PRIVATE static

PUBLIC void create_directory(char *parent_directory, char *directory) {

  char current_path[MAX_BUFF];

  getcwd(current_path, MAX_BUFF);
  chdir(parent_directory);
  if (mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH) == -1) {
    if (errno == EEXIST) {
      chdir(current_path);
      return;
    }
    fprintf(stderr, "Error in create_path : failed to create %s/%s folder",
            parent_directory, directory);
    chdir(current_path);
    exit(EXIT_FAILURE);
  }

  chdir(current_path);
}
