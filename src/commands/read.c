#include "../../include/commands/read.h"
#include <stdio.h>
#include <stdlib.h>

#if !defined(PUBLIC) && !defined(PRIVATE)

#define PUBLIC
#define PRIVATE static

#endif /* ifndef */

PRIVATE void terminate(char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

PUBLIC void handle_read(DBContext ctx) {
  Table tmp = get_current_table(ctx);
  if (tmp == NULL)
    terminate("Error int handle_insert : no table selected");

  print_table(tmp);
}
