#ifndef UTILS_H
#define UTILS_H
#include "./config.h"

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#elif defined(__linux__)
#include <termios.h>
#include <unistd.h>
char getch();
#endif
// create a directory
void create_directory(char *parent_directory, char *directory_name);
// delete a line with specific string
void delete_file_line(char *file_parent_directory, const char *file_name,
                      const char *to_remove);

void trim_newline(char *s);
#endif // !UTILS_H
