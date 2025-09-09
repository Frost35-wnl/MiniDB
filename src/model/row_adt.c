#include "../../include/model/row_adt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct row_type {
  char **values;
  int num_fields;
};

static void terminate(const char * message)
{
  printf("%s\n", message);
  exit(EXIT_FAILURE);
}

Row create_row(const char **values)
{
  int num_fields = 0;
  const char **ptr_c = values;
  while(*ptr_c){
      ptr_c++;
      num_fields++;
  }

  Row r = malloc(sizeof(struct row_type));
  if ( r == NULL )
    terminate("Error in create_row : Row could not be created.");
  r->values = malloc(num_fields * sizeof(char*));
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

  r->num_fields = num_fields;
  return r;
}

void free_row(Row row)
{
  for(int i = 0; i < row->num_fields; i++) {
      free(row->values[i]);
  }
  free(row->values);
  free(row);
}

int print_row(const Row row)
{
  int values_printed = 0;
  for (int i = 0 ; i < row->num_fields; i++) {
    printf("%-*s|",COLUMN_WIDTH_DISPLAY, row->values[i]);    values_printed++;
  }
  printf("\n");
  return values_printed;
}
