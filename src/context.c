#include "../include/context.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#if !defined(PUBLIC) && !defined(PRIVATE)

#define PUBLIC
#define PRIVATE static

#endif /* ifndef */

struct context_type {
  Table current_table;
};

PRIVATE void terminate(char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

PUBLIC DBContext init_context() {
  DBContext ctx = malloc(sizeof(struct context_type));
  if (ctx == NULL)
    terminate("Error in init_context : can't create a context ");

  ctx->current_table = NULL;

  return ctx;
}

PUBLIC void set_current_table(DBContext ctx, Table t) {
  if (ctx->current_table != NULL) {
    free_table(ctx->current_table);
  }
  ctx->current_table = t;
}

PUBLIC Table get_current_table(DBContext ctx) { return ctx->current_table; }

PUBLIC void free_context(DBContext ctx) {
  free_table(ctx->current_table);
  free(ctx);
}

PUBLIC Table load_table(const char *table_name) {
  Table table = read_table_meta(table_name);
  if (!table)
    terminate("Error in load_table : can't read table meta");

  int row_count = 0;
  Row *rows = read_table_rows(table_name, &row_count);
  if (!rows) {
    return table;
  }

  for (size_t i = 0; i < row_count; i++) {
    add_row(table, rows[i]);
  }

  free(rows);
  return table;
}

bool save_table(const Table table) {

  if (table == NULL)
    terminate("Error in save_table : table is NULL");

  char *table_name = get_table_name(table);
  if (table_name == NULL)
    terminate("Error in save_table : table_name is NULL");

  if (does_table_meta_exist(table_name))
    clear_table_meta(table_name);
  if (!create_table_meta(table))
    terminate("Error in save_table : can't create table meta");

  if (does_table_data_exist(table_name))
    clear_table_data(table_name);
  if (!create_table_data(table))
    terminate("Error in save_table : can't create table data");
  size_t row_count = get_table_row_count(table);

  for (size_t i = 0; i < row_count; i++) {
    Row row = get_row_at(table, i);
    if (!write_table_row(table_name, row)) {
      fprintf(stderr, "Error in save_table : failed to write row %zu for %s\n",
              i, table_name);
      return false;
    }
  }

#if defined(DEBUG) && DEBUG == 1
  printf("Debug: Table '%s' saved successfully with %zu rows\n", table_name,
         row_count);
#endif

  free(table_name);
  return true;
};
