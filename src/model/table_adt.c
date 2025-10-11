#include "../../include/model/table_adt.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(PUBLIC) && !defined(PRIVATE)
#define PUBLIC
#define PRIVATE static
#endif

struct table_type {
  char *name;
  char **field_names;
  Row *rows;
  int fields_count;
  int rows_count;
};

PRIVATE void terminate(const char *message) {
  printf("%s\n", message);
  exit(EXIT_FAILURE);
}

PUBLIC Table create_table(const char *name, const char **field_names) {

  int field_index = 0;
  const char **ptr_f = field_names;
  while (*ptr_f) {
    ptr_f++;
    field_index++;
  }

  Table t = malloc(sizeof(struct table_type));
  if (t == NULL)
    terminate("Error in create_table : Table could not be created.");
  t->name = malloc(strlen(name) + 1);
  if (t->name == NULL) {
    free(t);
    terminate("Error in create_table : Table could not be created.");
  }
  strcpy(t->name, name);

  t->field_names = malloc(field_index * sizeof(char *));
  if (t->field_names == NULL) {
    free(t->name);
    free(t);
    terminate("Error in create_table : Table could not be created.");
  }

  const char **ptr = field_names;
  field_index = 0;
  while (*ptr) {
    t->field_names[field_index] = malloc(strlen(*ptr) + 1);
    if (t->field_names[field_index] == NULL)
      terminate("Error in create_table : Table could not be created.");
    strcpy(t->field_names[field_index], *ptr);
    ptr++;
    field_index++;
  }

  t->fields_count = field_index;
  t->rows_count = 0;
  t->rows = malloc(t->rows_count * sizeof(Row));
  if (t->rows == NULL) {
    free(t->name);
    for (int i = 0; i < t->fields_count; i++) {
      free(t->field_names[i]);
    }
    free(t);
    terminate("Error in create_table : Table could not be created");
  }
  return t;
}

PUBLIC bool add_row(Table table, const Row row) {
  const int row_num_fields = get_row_fields_count(row);
  if (row_num_fields != table->fields_count) {
    printf("Error in add_row : Row and Table fields don't contain the same "
           "number of fields (Rows : %d, Table: %d)",
           row_num_fields, table->fields_count);
    terminate("");
  }

  table->rows = realloc(table->rows, (table->rows_count + 1) * sizeof(Row));
  if (table->rows == NULL)
    terminate("Error in add_row : Row element couldn't be added to the Table");
  table->rows[table->rows_count] = row;
  table->rows_count++;

  return true;
}

PUBLIC void free_table(Table table) {
  if (table == NULL)
    return;

  free(table->name);
  for (int i = 0; i < table->fields_count; i++) {
    free(table->field_names[i]);
  }
  free(table->field_names);
  for (int i = 0; i < table->rows_count; i++) {
    free_row(table->rows[i]);
  }
  free(table->rows);
  free(table);
}

PUBLIC int print_table(const Table table) {
  printf("%s\n", table->name);
  int values_printed = 0;
  for (int i = 0; i < table->fields_count; i++) {
    printf("%-*s|", COLUMN_WIDTH_DISPLAY, table->field_names[i]);
  }
  printf("\n");
  for (int i = 0; i < table->rows_count; i++) {
    print_row(table->rows[i]);
    values_printed++;
  }
  return values_printed;
}

PUBLIC char *get_table_name(const Table table) {
  if (!table || !table->name)
    return NULL;

  char *table_name = malloc(strlen(table->name) + 1);
  if (!table_name) {
    fprintf(stderr, "Error in get_table_name : memory allocation failed\n");
    return NULL;
  }

  strcpy(table_name, table->name);
  return table_name;
}

PUBLIC int get_table_fields_count(const Table table) {
  return table->fields_count;
}

PUBLIC char *get_table_fields_str(const Table table) {
  if (!table || !table->field_names)
    terminate(
        "Error in get_table_fields_str : table or table fields don't exist");

  const int table_field_num = get_table_fields_count(table);
  if (table_field_num == 0) {
    char *empty = malloc(1);
    if (empty == NULL)
      terminate("Error in get_table_fields_str : malloc failed");
    empty[0] = '\0';
    return empty;
  }

  char *table_fields_str = malloc(strlen(table->field_names[0]) + 1);
  if (table_fields_str == NULL)
    terminate(
        "Error in get_table_fields_str : can't create the string of fields");
  strcpy(table_fields_str, table->field_names[0]);

#if defined(DEBUG) && DEBUG == 1
  printf("%s\n", table_fields_str);
#endif

  for (int i = 1; i < table_field_num; i++) {
    size_t new_len = strlen(table_fields_str) + 1 /*comma*/ +
                     strlen(table->field_names[i]) + 1;
    char *tmp = realloc(table_fields_str, new_len);
    if (tmp == NULL) {
      free(table_fields_str);
      terminate("Error in get_table_fields_str : realloc failed");
    }
    table_fields_str = tmp;
    strcat(table_fields_str, ",");
    strcat(table_fields_str, table->field_names[i]);
  }

  return table_fields_str;
}

PUBLIC int get_table_row_count(const Table table) { return table->rows_count; }

PUBLIC Row get_row_at(const Table table, size_t index) {
  return table->rows[index];
}
