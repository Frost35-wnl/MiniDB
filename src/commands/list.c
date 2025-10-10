#include "../../include/commands/list.h"
#include "../../include/storage/catalog_file.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#if !defined(PUBLIC) && !defined(PRIVATE)

#define PUBLIC
#define PRIVATE static

#endif /* ifndef */

PUBLIC void handle_list() {
  int table_count = get_table_count();
  char message[MAX_BUFF];
  sprintf(message, "Number of table : %d ", table_count);

  fprintf(stdout, "%s\n", message);
  for (size_t i = 0; i < strlen(message); i++) {
    fprintf(stdout, "-");
  }
  printf("\n");
  list_catalog_tables();
}
