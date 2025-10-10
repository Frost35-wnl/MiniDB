#include "../../include/commands/insert.h"
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

PUBLIC void handle_insert(DBContext ctx, const char **values) {
  Table tmp = get_current_table(ctx);
  if (tmp == NULL)
    terminate("Error int handle_insert : no table selected");

  Row new_row = create_row(values);
  add_row(tmp, new_row);
  save_table(tmp);
}
