#include "../../include/commands/dispatcher.h"
#include "../../include/commands/create.h"
#include "../../include/commands/insert.h"
#include "../../include/commands/list.h"
#include "../../include/commands/read.h"
#include "../../include/commands/select.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#if !defined(PUBLIC) && !defined(PRIVATE)

#define PUBLIC
#define PRIVATE static

#endif /* ifndef */

void dispatch_command(DBContext ctx, ParesedCommand cmd) {
  char *command = get_command_name(cmd);
  char **args = get_args(cmd);

  if (strcmp(command, "CREATE") == 0) {
    handle_create(ctx, (const char **)args);
    return;
  }

  if (strcmp(command, "INSERT") == 0) {
    handle_insert(ctx, (const char **)args);
    return;
  }

  if (strcmp(command, "LIST") == 0) {
    handle_list();
    return;
  }

  if (strcmp(command, "READ") == 0) {
    handle_read(ctx);
    return;
  }

  if (strcmp(command, "SELECT") == 0) {
    handle_select(ctx, (const char *)args[0]);
    return;
  }

  fprintf(stderr, "Command not found : %s\n", command);
}
