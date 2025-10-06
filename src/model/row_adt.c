#include "../../include/model/row_adt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(PUBLIC) && !defined(PRIVATE)
#define PUBLIC
#define PRIVATE static
#endif

struct row_type {
  char **values;
  int fields_count;
};

PRIVATE void terminate(const char *message) {
  printf("%s\n", message);
  exit(EXIT_FAILURE);
}

PUBLIC Row create_row(const char **values) {
  int num_fields = 0;
  const char **ptr_c = values;
  while (*ptr_c) {
    ptr_c++;
    num_fields++;
  }

  Row r = malloc(sizeof(struct row_type));
  if (r == NULL)
    terminate("Error in create_row : Row could not be created.");
  r->values = malloc(num_fields * sizeof(char *));
  if (r->values == NULL) {
    free(r);
    terminate("Error in create_row : Row could not be created.");
  }

  const char **ptr = values;
  for (int i = 0; i < num_fields; i++, ptr++) {
    r->values[i] = malloc(strlen(*ptr) + 1);
    if (r->values[i] == NULL)
      terminate("Error in create_row : Row could not be created.");
    strcpy(r->values[i], *ptr);
  }

  r->fields_count = num_fields;
  return r;
}

PUBLIC void free_row(Row row) {
  for (int i = 0; i < row->fields_count; i++) {
    free(row->values[i]);
  }
  free(row->values);
  free(row);
}

PUBLIC int print_row(const Row row) {
  int values_printed = 0;
  for (int i = 0; i < row->fields_count; i++) {
    printf("%-*s|", COLUMN_WIDTH_DISPLAY, row->values[i]);
    values_printed++;
  }
  printf("\n");
  return values_printed;
}

PUBLIC int get_row_fields_count(const Row row) { return row->fields_count; }

PUBLIC char *get_row_str(const Row row) {
  if (!row || !row->values)
    terminate("Error in get_row_str : row or row values don't exist");

  const int row_num = get_row_fields_count(row);
  if (row_num == 0) {
    char *empty = malloc(1);
    if (empty == NULL)
      terminate("Error in get_row_str : malloc failed");
    empty[0] = '\0';
    return empty;
  }

  char *row_str = malloc(strlen(row->values[0]) + 1);
  if (row_str == NULL)
    terminate("Erro in get_row_str : can't create the string of rows");
  strcpy(row_str, row->values[0]);

  for (int i = 1; i < row_num; i++) {
    size_t new_len = strlen(row_str) + 1 /*comma*/ + strlen(row->values[i] + 1);
    char *tmp = realloc(row_str, new_len);
    if (tmp == NULL) {
      free(row_str);
      terminate("Error in get_row_str : realloc failed");
    }
    row_str = tmp;
    strcat(row_str, ",");
    strcat(row_str, row->values[i]);
  }

  return row_str;
}
