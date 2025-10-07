#include "../../include/storage/catalog_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PUBLIC
#define PRIVATE static

PRIVATE void terminate(char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

PUBLIC bool does_table_exist(const char *table_name) {

  bool table_exists = false;

  FILE *ctlg = fopen(ROOT_DIR "/data/meta/catalog.meta", "r+");
  if (ctlg == NULL) {
    fprintf(stderr, "Error in is_table_exists : can't open catalog file");
    return false;
  }

  char buffer[TABLE_NAME_WIDTH];
  while (fgets(buffer, sizeof(buffer), ctlg) != NULL) {
    trim_newline(buffer);
    if (strcmp(buffer, table_name) == 0) {
      table_exists = true;
      break;
    }
  }

  fclose(ctlg);
  return table_exists;
}

PUBLIC bool add_table_to_catalog(const char *table_name) {
#if defined(DEBUG) && DEBUG == 1
  printf("Debug : %scatalog.meta\n", ROOT_DIR "data/");
#endif

  create_directory(ROOT_DIR, "data");
  create_directory(ROOT_DIR "/data/", "meta");

  FILE *ctlg = fopen(ROOT_DIR "/data/meta/catalog.meta", "a+");
  if (ctlg == NULL) {
    terminate("Error in add_table_to_catalog : can't open catalog file");
  }

  if (does_table_exist(table_name)) {
    printf("%s is already in the catalog\n", table_name);
    fclose(ctlg);
    return false;
  }

  fprintf(ctlg, "%s\n", table_name);
  fclose(ctlg);
  return true;
}

PUBLIC void remove_table_from_catalog(const char *table_name) {

  if (!does_table_exist(table_name)) {
    terminate("Erro in remove_table_from_catalog : this table doesn't exist");
  }

  delete_file_line(ROOT_DIR "/data/meta/", "catalog.meta", table_name);
}

PUBLIC int list_tables() {

  int table_num = 0;
  FILE *ctlg = fopen(ROOT_DIR "/data/meta/catalog.meta", "r");
  if (ctlg == NULL) {
    terminate("Erro in list_tables : can't open catalog file");
  }

  char *line = NULL;
  size_t len = 0;
  size_t read;

  while ((read = getline(&line, &len, ctlg)) != -1) {
    trim_newline(line);
    printf("%s\n", line);
    table_num++;
  }

  free(line);
  fclose(ctlg);
  return table_num;
}
