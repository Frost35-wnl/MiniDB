#ifndef UTILS_H
#define UTILS_H
#include "./config.h"

// create a directory
void create_directory(char *parent_directory, char *directory_name);
// delete a line with specific string
void delete_file_line(char *file_parent_directory, const char *file_name,
                      const char *to_remove);

void trim_newline(char *s);
#endif // !UTILS_H
