#include "../../include/commands/create.h"
#include "../../include/storage/catalog_file.h"
#include "../../include/storage/table_meta_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(PUBLIC) && !defined(PRIVATE)

#define PUBLIC
#define PRIVATE static

#endif /* ifndef */

PRIVATE void terminate(char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

PRIVATE void switch_context(DBContext ctx, const char *table_name) {
  // print if the user want to use this table after creation
  char ans;
  fprintf(stdout, "Do you want to select this table ? (y/n) : ");
  if ((ans = getchar()) == 'y' || ans == '\n') {
    free_context(ctx);
    set_current_table(ctx, load_table(table_name));
  }
}

// tokens = ["students", "id", "name", "note", null]
PUBLIC void handle_create(DBContext ctx, char **tokens) {
  char *table_name = tokens[0];
  char **table_fields = malloc(sizeof(char *));
  char **pt = tokens;
  pt++; /*To avoid table name*/
  int table_fields_count = 0;
  while (pt++) {
    table_fields =
        realloc(table_fields, sizeof(char *) * table_fields_count + 1);
    strcpy(table_fields[table_fields_count], *pt);
    table_fields_count++;
  }

  add_table_to_catalog(table_name);
  Table tmp = create_table(table_name, (const char **)table_fields);
  create_table_meta(tmp);

  free_table(tmp);
  pt = table_fields;
  while (pt++) {
    free(*pt);
  }
  free(table_fields);

  switch_context(ctx, table_name);
  free(table_name);
}
