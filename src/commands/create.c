#include "../../include/commands/create.h"
#include "../../include/storage/catalog_file.h"
#include "../../include/storage/table_meta_file.h"
#include "../../include/utils.h"
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
  fprintf(stdout, "Do you want to select %s ? (y/n) : ", table_name);
  fflush(stdout);
  if ((ans = getch()) == 'y' || ans == '\n') {
    fprintf(stdout, "\n");
    set_current_table(ctx, load_table(table_name));
  }
}

PRIVATE int get_fields_count(const char **tokens) {
  int fields_count = 0;
  const char **ptr = tokens + 1;
  while (*ptr) {
    fields_count++;
    ptr++;
  }

  return fields_count;
}

PRIVATE bool is_table_name_long(const char *table_name) {
  return strlen(table_name) > TABLE_NAME_WIDTH;
}

// tokens = ["students", "id", "name", "note", null]
PUBLIC void handle_create(DBContext ctx, const char **tokens) {
  const char *table_name = tokens[0];
  if (is_table_name_long(table_name))
    terminate("Error in handle_create : table name too long (MAX : 120) ");

  int table_fields_count = get_fields_count(tokens);
  char **table_fields = malloc((table_fields_count + 1) * sizeof(char *));
  if (table_fields == NULL)
    terminate("Error in handle_create : malloc failed");

  const char **ptr = tokens + 1;
  for (int i = 0; i < table_fields_count; i++, ptr++) {
    table_fields[i] = malloc(strlen(*ptr) + 1);
    if (table_fields[i] == NULL)
      terminate("Error in handle_create : malloc failed");
    strcpy(table_fields[i], *ptr);
  }

  add_table_to_catalog(table_name);
  table_fields[table_fields_count] = NULL;
  Table tmp = create_table(table_name, (const char **)table_fields);
  create_table_meta(tmp);
  free_table(tmp);

  char **ptr2 = table_fields;
  while (*ptr2) {
    free(*ptr2);
    ptr2++;
  }
  free(table_fields);

  switch_context(ctx, table_name);
}
