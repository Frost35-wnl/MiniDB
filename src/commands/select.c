#include "../../include/commands/select.h"
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

PUBLIC void handle_select(DBContext ctx, const char *table_name) {
  Table tmp = load_table(table_name);
  set_current_table(ctx, tmp);
}
