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

  strcpy(table_meta_path, ROOT_DIR "/data/meta/");
  strcat(table_meta_path, table_name);
  strcat(table_meta_path, ".meta");

  return table_meta_path;
}

PRIVATE bool is_table_meta_exists(const char *table_name) {

  char *table_meta_path = get_table_meta_path(table_name);
  FILE *table_meta_file = fopen(table_meta_path, "r");
  if (table_meta_file == NULL) {
    return false;
  }

  return true;
}

PUBLIC bool write_table_meta(Table t) {
  const char *table_name = get_table_name(t);

#if defined(DEBUG) && DEBUG == 1
  printf("%s\n", table_name);
#endif

  char *table_fields_str = get_table_fields_str(t);

#if defined(DEBUG) && DEBUG == 1
  printf("%s\n", table_fields_str);
#endif

  char *table_meta_path = get_table_meta_path(table_name);

  if (is_table_meta_exists(table_name))
    terminate("Error in write_table_meta : this table meta already exists");

  FILE *table_meta_file = fopen(table_meta_path, "w");
  if (table_meta_file == NULL) {
    fprintf(stderr, "Error in write_table_meta :  can't create %s",
            table_meta_path);
    return false;
  }

  fprintf(table_meta_file, "%s\n", table_fields_str);
  free(table_meta_path);
  free(table_fields_str);
  fclose(table_meta_file);
  return true;
}

PUBLIC Table read_table_meta(const char *table_name) {

  if (!is_table_meta_exists(table_name)) {
    terminate("Error in read_table_meta : this table doesn't exist");
  }

#if defined(DEBUG) && DEBUG == 1
  printf("Debug : Table exist\n");
#endif

  char *table_meta_path = get_table_meta_path(table_name);
  FILE *table_meta_file = fopen(table_meta_path, "r");
  if (table_meta_file == NULL) {
    terminate("Erro in read_table_meta : can't open table meta file");
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
