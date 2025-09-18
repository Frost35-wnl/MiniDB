#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/storage/table_file.h"

#define PUBLIC
#define PRIVATE static

PRIVATE void terminate(char *message)
{
fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

PUBLIC bool write_table_meta(Table t)
{
  const char *table_file_path  = strcat(DATA_DIR"meta/", t->name);

  FILE* table_file = fopen(table_file_path, "w");
  if (table_file == NULL) {
    terminate("Error in write_table_meta :  can't create file");
  }


}
