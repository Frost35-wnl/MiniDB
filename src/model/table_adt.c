#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/model/table_adt.h"

#if !defined(PUBLIC) && !defined(PRIVATE)
#define PUBLIC
#define PRIVATE static
#endif

struct table_type {
  char *name;
  char **field_names;
  Row *rows;
  int num_fields;
  int num_rows;
};

PRIVATE void terminate (const char *message)
{
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

PUBLIC Table create_table(const char *name, const char **field_names)
{

  int field_index = 0;
  const char **ptr_f = field_names;
  while (*ptr_f) {
      ptr_f++;
      field_index++;
  }

  Table t = malloc(sizeof(struct table_type));
  if (t == NULL)
    terminate("Error in create_table : Table could not be created.");
  t->name = malloc(strlen(name) + 1) ;
  if (t->name == NULL)
    terminate("Error in create_table : Table could not be created.");
  strcpy(t->name, name);


  t->field_names = malloc(field_index * sizeof(char*));
  if (t->field_names == NULL)
    terminate("Error in create_table : Table could not be created.");

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

  t->num_fields = field_index;
  t->num_rows = 0;
  t->rows = malloc(t->num_rows * sizeof(Row));
  return t;
}

PUBLIC bool add_row(Table table, const Row row)
{
    const int row_num_fields = get_row_num_fields(row);
    if (  row_num_fields != table->num_fields)
        terminate("error in add_row : Row and Table fields doesn't contain the same number of fields");

    table->rows = realloc(table->rows, (table->num_rows + 1) * sizeof(Row));
    if (table->rows == NULL)
      terminate("Error in add_row : Row element couldn't be added to the Table");
    table->rows[table->num_rows] = row;
    table->num_rows++;

  return true;
}

PUBLIC void free_table(Table table)
{
  free(table->name);
  for(int i = 0; i < table->num_fields; i++) {
      free(table->field_names[i]);
  }
  free(table->field_names);
  for(int i = 0; i < table->num_rows; i++) {
      free_row(table->rows[i] );
  }
  free(table->rows);
  free(table);
}

PUBLIC int print_table(const Table table)
{
    printf("%s\n", table->name);
    int values_printed = 0;
    for(int i = 0; i < table->num_fields; i++) {
         printf("%-*s|",COLUMN_WIDTH_DISPLAY, table->field_names[i]);
    }
    printf("\n");
    for(int i = 0; i < table->num_rows; i++) {
        print_row(table->rows[i]);
        values_printed++;
    }
    return values_printed;
}


PUBLIC int get_table_num_fields(const Table table)
{
  return table->num_rows;
}
