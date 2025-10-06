#include "../../include/storage/table_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PUBLIC
#define PRIVATE static

PRIVATE void terminate(char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

PRIVATE char *get_table_meta_path(const char *table_name) {
  char *table_meta_path =
      malloc(strlen(ROOT_DIR "/data/meta/") + strlen(table_name) + 6 /*.meta*/);
  if (table_meta_path == NULL) {
    fprintf(stderr, "Error in get_table_file_path : can't reach file path");
    return NULL;
  }

  snprintf(table_meta_path, strlen(table_meta_path), "%s%s%s",
           ROOT_DIR "/data/meta/", table_name, ".meta");

  return table_meta_path;
}

PRIVATE char *get_table_data_path(const char *table_name) {
  char *table_data_path =
      malloc(strlen(ROOT_DIR "/data/db/") + strlen(table_name) + 4 /*.db*/);
  if (table_data_path == NULL) {
    fprintf(stderr, "Error in get_table_data_path : can't reach file path");
    return NULL;
  }

  snprintf(table_data_path, strlen(table_data_path), "%s%s%s",
           ROOT_DIR "/data/db/", table_name, ".db");

  return table_data_path;
}

PRIVATE bool does_table_meta_exist(const char *table_name) {

  char *table_meta_path = get_table_meta_path(table_name);
  FILE *table_meta_file = fopen(table_meta_path, "r");
  if (table_meta_file == NULL) {
    return false;
  }

  fclose(table_meta_file);
  return true;
}

PRIVATE bool does_table_data_exist(const char *table_name) {
  char *table_data_path = get_table_data_path(table_name);
  FILE *table_data_file = fopen(table_data_path, "r");
  if (table_data_file == NULL) {
    return false;
  }

  fclose(table_data_file);
  return true;
}

PUBLIC bool create_table_meta(Table t) {
  char *table_name = get_table_name(t);

#if defined(DEBUG) && DEBUG == 1
  printf("%s\n", table_name);
#endif

  char *table_fields_str = get_table_fields_str(t);

#if defined(DEBUG) && DEBUG == 1
  printf("%s\n", table_fields_str);
#endif

  char *table_meta_path = get_table_meta_path(table_name);

  if (does_table_meta_exist(table_name)) {
    fprintf(stderr, "Error in create_table_meta : this table already exists\n");
    return false;
  }

  FILE *table_meta_file = fopen(table_meta_path, "w");
  if (table_meta_file == NULL) {
    fprintf(stderr, "Error in create_table_meta :  can't create %s\n",
            table_meta_path);
    free(table_name);
    free(table_meta_path);
    free(table_fields_str);
    return false;
  }

  fprintf(table_meta_file, "%s\n", table_fields_str);
  free(table_name);
  free(table_meta_path);
  free(table_fields_str);
  fclose(table_meta_file);
  return true;
}

PUBLIC Table read_table_meta(const char *table_name) {

  if (!does_table_meta_exist(table_name)) {
    terminate("Error in read_table_meta : this table doesn't exist");
  }

#if defined(DEBUG) && DEBUG == 1
  printf("Debug : Table exist\n");
#endif

  char *table_meta_path = get_table_meta_path(table_name);
  FILE *table_meta_file = fopen(table_meta_path, "r");
  if (table_meta_file == NULL) {
    terminate("Erro in read_table_meta : can't open table meta file\n");
  }

  int fields_num = 0;
  char *fields_name_str = NULL;
  char **fields_name = NULL;

  int ch;
  while ((ch = getc(table_meta_file)) != EOF) {
    char ch_str[2];
    ch_str[0] = (char)ch;
    ch_str[1] = '\0';

    if (fields_name_str == NULL) {
      fields_name_str = malloc(2);
      if (fields_name_str == NULL)
        terminate("Error in read_table_meta : can't get fields name");

      strcpy(fields_name_str, ch_str);
      continue;
    }
    if (!strcmp(ch_str, ",")) {
      fields_name = realloc(fields_name, (fields_num + 1) * sizeof(char *));
      if (fields_name == NULL)
        terminate("Error in read_table_meta : realloc failed");

      fields_name[fields_num] = strdup(fields_name_str);
      if (fields_name[fields_num] == NULL)
        terminate("Error in read_table_meta : strdup failed");

      free(fields_name_str);
      fields_name_str = NULL;
      fields_num++;
      continue;
    }

    fields_name_str = realloc(fields_name_str, strlen(fields_name_str) + 2);
    if (fields_name_str == NULL)
      terminate("Error in read_table_meta : realloc failed");
    strcat(fields_name_str, ch_str);
  }

  if (fields_name_str != NULL) {
    fields_name = realloc(fields_name, (fields_num + 1) * sizeof(char *));
    if (fields_name == NULL)
      terminate("Error in read_table_meta : realloc failed");

    fields_name[fields_num] = strdup(fields_name_str);
    if (fields_name[fields_num] == NULL)
      terminate("Error in read_table_meta : strdup failed");

    free(fields_name_str);
    fields_num++;
  }

  fields_name = realloc(fields_name, (fields_num + 1) * sizeof(char *));
  if (fields_name == NULL)
    terminate("Error in read_table_meta : realloc failed");

  fields_name[fields_num] = NULL;
  fclose(table_meta_file);

  Table table = create_table(table_name, (const char **)fields_name);
  free(fields_name);
  return table;
}

PUBLIC void clear_table_meta(const char *table_name) {

  if (!does_table_meta_exist(table_name))
    terminate("Error in clear_table_meta : this table doesn't exist");

  char *table_meta_path = get_table_meta_path(table_name);
  if (remove(table_meta_path) == 0)
    printf("File %s successfully deleted. \n", table_meta_path);
  else
    terminate("Error in clear_table_meta : can't delete file");
}

PUBLIC bool create_table_data(Table t) {

  create_directory(ROOT_DIR, "data");
  create_directory(ROOT_DIR "/data/", "db");

  char *table_name = get_table_name(t);

  char *table_data_path = get_table_data_path(table_name);

  if (does_table_data_exist(table_name)) {
    fprintf(stderr, "Error in create_table_data : can't create %s\n",
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
    free(table_data_path);
    fprintf(stderr, "Error in write_table_row : can't open %s",
            table_data_path);
    return false;
  }

  char *row_str = get_row_str(row);
  fprintf(table_data_file, "%s\n", row_str);
  free(table_data_path);
  fclose(table_data_file);
  return true;
}

Row **read_table_rows(const char *table_name) {

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

  Row **rows = NULL;
  int row_count = 0;
  char buffer[MAX_BUFF];

  while (fgets(buffer, sizeof(buffer), table_data_file)) {
    buffer[strcspn(buffer, "\n")] = 0;

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

    rows = realloc(rows, sizeof(Row *) * (row_count + 1));
    if (rows == NULL)
      terminate("Error in read_table_rows : realloc failed");

    rows[row_count] = &r;
    row_count++;

    free(values);
  }

  rows = realloc(rows, sizeof(Row *) * (row_count + 1));
  rows[row_count] = NULL;

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
}
