#include "../include/utils.h"
#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PUBLIC
#define PRIVATE static

PUBLIC void create_directory(char *parent_directory, char *directory_name) {

  char current_path[MAX_BUFF];

  getcwd(current_path, MAX_BUFF);
  chdir(parent_directory);
  if (mkdir(directory_name, S_IRWXU | S_IRWXG | S_IROTH) == -1) {
    if (errno == EEXIST) {
      chdir(current_path);
      return;
    }
    fprintf(stderr, "Error in create_path : failed to create %s/%s folder",
            parent_directory, directory_name);
    chdir(current_path);
    exit(EXIT_FAILURE);
  }

  chdir(current_path);
}

PUBLIC void delete_file_line(char *file_parent_directory, const char *file_name,
                             const char *to_remove) {
  char file_path[MAX_BUFF];
  if (file_parent_directory[strlen(file_parent_directory) - 1] == '/')
    snprintf(file_path, sizeof(file_path), "%s%s", file_parent_directory,
             file_name);
  else
    snprintf(file_path, sizeof(file_path), "%s/%s", file_parent_directory,
             file_name);

  FILE *src = fopen(file_path, "r");
  if (src == NULL) {
    perror("Error in delete_file_line : can't open source");
    return;
  }

  char tmp_path[MAX_BUFF];
  if (file_parent_directory[strlen(file_parent_directory) - 1] == '/')
    snprintf(tmp_path, sizeof(tmp_path), "%stmp.txt", file_parent_directory);
  else
    snprintf(tmp_path, sizeof(tmp_path), "%s/tmp.txt", file_parent_directory);

  FILE *tmp = fopen(tmp_path, "w");
  if (tmp == NULL) {
    perror("Error in delete_file_line : can't create temporary file");
    fclose(src);
    return;
  }

  char buffer[MAX_BUFF];
  while (fgets(buffer, sizeof(buffer), src) != NULL) {
    buffer[strcspn(buffer, "\r\n")] = 0;
    if (strcmp(buffer, to_remove) != 0) {
      fprintf(tmp, "%s\n", buffer);
    }
  }

  fclose(src);
  fclose(tmp);

  if (remove(file_path) != 0) {
    perror("Error in delete_file_line : can't remove original file");
    return;
  }

  if (rename(tmp_path, file_path) != 0) {
    perror("Error in delete_file_line : can't rename tmp file");
    return;
  }
}
