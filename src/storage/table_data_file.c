#include "../../include/storage/table_data_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PUBLIC
#define PRIVATE static

PRIVATE void terminate(char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

PRIVATE char *get_table_data_path(const char *table_name) {
  size_t len = strlen(ROOT_DIR "/data/db/") + strlen(table_name) + 4 /*.db*/;
  char *table_data_path = malloc(len);
  if (table_data_path == NULL) {
    fprintf(stderr, "Error in get_table_data_path : can't reach file path");
    return NULL;
  }

  snprintf(table_data_path, len, "%s%s%s", ROOT_DIR "/data/db/", table_name,
           ".db");

  return table_data_path;
}

PUBLIC bool does_table_data_exist(const char *table_name) {
  char *table_data_path = get_table_data_path(table_name);
  FILE *table_data_file = fopen(table_data_path, "r");
  if (table_data_file == NULL) {
    return false;
  }

  free(table_data_path);
  fclose(table_data_file);
  return true;
}

PUBLIC bool create_table_data(Table table) {

  create_directory(ROOT_DIR, "data");
  create_directory(ROOT_DIR "/data/", "db");

  char *table_name = get_table_name(table);

  char *table_data_path = get_table_data_path(table_name);

  if (does_table_data_exist(table_name)) {
    fprintf(stderr, "Error in create_table_data : %s data already exists\n",
            table_data_path);
    return false;
  }

  FILE *table_data_file = fopen(table_data_path, "w");
  if (table_data_file == NULL) {
    fprintf(stderr, "Error in create_table_data : can't create %s\n",
            table_data_path);
    free(table_name);
    free(table_data_path);
    return false;
  }

  free(table_name);
  free(table_data_path);
  fclose(table_data_file);
  return true;
}

bool write_table_row(const char *table_name, const Row row) {

  char *table_data_path = get_table_data_path(table_name);
  if (!does_table_data_exist(table_name)) {
    fprintf(stderr, "Error in write_table_row : %s.db doesn't exist",
            table_name);
    return false;
  }

  FILE *table_data_file = fopen(table_data_path, "a+");
  if (table_data_file == NULL) {
    fprintf(stderr, "Error in write_table_row : can't open %s",
            table_data_path);
    free(table_data_path);
    return false;
  }

  char *row_str = get_row_str(row);
  trim_newline(row_str);
  fprintf(table_data_file, "%s\n", row_str);
  free(table_data_path);
  fclose(table_data_file);
  return true;
}

Row *read_table_rows(const char *table_name, int *row_count) {

  if (!does_table_data_exist(table_name)) {
    terminate("Error in read_table_rows : this table doesn't exist");
  }

#if defined(DEBUG) && DEBUG == 1
  printf("Debug : Table exist\n");
#endif

  char *table_data_path = get_table_data_path(table_name);
  FILE *table_data_file = fopen(table_data_path, "r");
  if (table_data_file == NULL)
    terminate("Error in read_table_rows : can't open table data file");

  Row *rows = NULL;
  char buffer[MAX_BUFF];

  while (fgets(buffer, sizeof(buffer), table_data_file) != NULL) {
    trim_newline(buffer);

    char *token = strtok(buffer, ",");
    char **values = NULL;
    int field_count = 0;

    while (token != NULL) {
      values = realloc(values, sizeof(char *) * (field_count + 1));
      if (values == NULL)
        terminate("Error in read_table_rows : realloc failed");

      values[field_count] = strdup(token);
      if (values[field_count] == NULL)
        terminate("Error in read_table_rows : strdup failed");

      field_count++;
      token = strtok(NULL, ",");
    }

    values = realloc(values, sizeof(char *) * (field_count + 1));
    values[field_count] = NULL;

    Row r = create_row((const char **)values);

    rows = realloc(rows, sizeof(Row *) * (*row_count + 1));
    if (rows == NULL)
      terminate("Error in read_table_rows : realloc failed");

    rows[*row_count] = r;
    (*row_count)++;

    free(values);

#if defined(DEBUG) && DEBUG == 1
    printf("Debug : %s", get_row_str(r));
#endif
  }

  rows = realloc(rows, sizeof(Row *) * (*row_count + 1));
  rows[*row_count] = NULL;

  fclose(table_data_file);
  free(table_data_path);
  return rows;
}

void clear_table_data(const char *table_name) {

  if (!does_table_data_exist(table_name))
    terminate("Error in clear_table_data : this table doesn't exist");

  char *table_data_path = get_table_data_path(table_name);
  if (remove(table_data_path) == 0)
    printf("File %s successfully deleted. \n", table_data_path);
  else
    terminate("Error in clear_table_data : can't delete file");

  free(table_data_path);
}
