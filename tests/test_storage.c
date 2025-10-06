#include "../include/context.h"
#include "../include/model/table_adt.h"
#include "../include/storage/catalog_file.h"
#include "../include/storage/table_meta_file.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool catalog_test();
bool meta_test();

int main(void) {
  // if (catalog_test())
  // printf("Catalog runs out of the box \n\n");
  if (meta_test())
    printf("meta runs out of the box");
}

bool meta_test() {
  DBContext ctx = init_context();

  const char table1_name[] = "TABLE1";
  const char table2_name[] = "TABLE2";
  const char table3_name[] = "TABLE3";
  // Suppose we have table fields
  const char *table1_fields[] = {"Number", "Freq", "Total", NULL};
  const char *table2_fields[] = {"True", "False", NULL};
  const char *table3_fields[] = {"Jan", "Feb",  "Mar", "Ap",  "Jun", "Jul",
                                 "Aug", "Sept", "Oct", "Nov", "Dec", NULL};
  // Create Table
  Table table1 = create_table(table1_name, table1_fields);
  Table table2 = create_table(table2_name, table2_fields);
  Table table3 = create_table(table3_name, table3_fields);

  create_table_meta(table1);
  create_table_meta(table2);
  create_table_meta(table3);

  read_table_meta(table1_name);
  read_table_meta(table2_name);
  read_table_meta(table3_name);

  int ch;
  do {
    printf("Do you want to delete meta data ? (y/n) ");
    ch = getchar();
  } while (ch != 'y' && ch != 'n');

  if (ch == 'y') {
    clear_table_meta(table1_name);
    clear_table_meta(table2_name);
    clear_table_meta(table3_name);
  } else {
    printf("You didn't delete meta data\n");
  }

  return true;
}

bool catalog_test() {

  // Table name
  const char table1_name[] = "TABLE1";
  const char table2_name[] = "TABLE2";
  const char table3_name[] = "TABLE3";

  // Suppose we have created the tables
  const char *table1_fields[] = {"Number", "Freq", "Total", NULL};
  const char *table2_fields[] = {"True", "False", NULL};
  const char *table3_fields[] = {"Jan", "Feb",  "Mar", "Ap",  "Jun", "Jul",
                                 "Aug", "Sept", "Oct", "Nov", "Dec", NULL};

  // Create Table
  Table table1 = create_table(table1_name, table1_fields);
  Table table2 = create_table(table2_name, table2_fields);
  Table table3 = create_table(table3_name, table3_fields);

  // Catalog meta test
  add_table_to_catalog(table1_name);
  add_table_to_catalog(table2_name);
  add_table_to_catalog(table3_name);

  printf("\nList of the tables : \n");
  list_tables();
  printf("\n");

  printf("Everything is freed\n");
  if (does_table_exist(table1_name)) {
    printf("%s exists\n", table1_name);
  }
  if (does_table_exist(table2_name)) {
    printf("%s exists\n", table2_name);
  }
  if (does_table_exist(table3_name)) {
    printf("%s exists\n", table3_name);
  }

  // delete table1
  remove_table_from_catalog(table1_name);
  remove_table_from_catalog(table2_name);
  remove_table_from_catalog(table3_name);
  list_tables();

  printf("Test successfull\n");

  return true;
}
