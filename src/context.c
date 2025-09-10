#include <stdio.h>
#include <stdlib.h>
#include "../include/context.h"

#if !defined(PUBLIC) && !defined(PRIVATE)

#define PUBLIC
#define PRIVATE static

#endif /* ifndef */

struct context_type {
  Table current_table;
};

PRIVATE void terminate(char *message)
{
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

PUBLIC DBContext init_context()
{
  DBContext ctx = malloc(sizeof(struct context_type));
  if (ctx == NULL)  
    terminate("Error in init_context : can't create a context ");
  
  ctx->current_table = NULL;

  return ctx;
}

PUBLIC void set_current_table(DBContext ctx, Table t)
{
  if (ctx->current_table != NULL) {
    free_table(ctx->current_table);
  }
  ctx->current_table = t;
}

PUBLIC Table get_current_table(DBContext ctx)
{
  return ctx->current_table;
}

PUBLIC void free_context(DBContext ctx)
{
  free_table(ctx->current_table);
  free(ctx);
}
