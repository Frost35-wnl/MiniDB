#include "../include/context.h"
#include "../include/model/table_adt.h"
#include "../include/storage/catalog_file.h"
#include "../include/storage/table_meta_file.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool catalog_test();
bool meta_test();
bool data_test();

int main(void) {
  if (catalog_test())
    printf("Catalog runs out of the box \n\n");
  if (meta_test())
    printf("meta runs out of the box\n\n");
  if (data_test())
    printf("data runs out of the box\n\n");

  return 0;
}

bool data_test() {
  DBContext ctx = init_context();

  const char table1_name[] = "TABLE1";
  const char table2_name[] = "TABLE2";
  const char table3_name[] = "TABLE3";

  const char *table1_fields[] = {"Number", "Freq", "Total", NULL};
  const char *table2_fields[] = {"True", "False", NULL};
  const char *table3_fields[] = {"Jan", "Feb",  "Mar", "Ap",  "Jun", "Jul",
                                 "Aug", "Sept", "Oct", "Nov", "Dec", NULL};

  Table table1 = create_table(table1_name, table1_fields);
  Table table2 = create_table(table2_name, table2_fields);
  Table table3 = create_table(table3_name, table3_fields);

  create_table_data(table1);
  create_table_data(table2);
  create_table_data(table3);

  free_table(table1);
  free_table(table2);
  free_table(table3);

  // We load table from files
  Table tmp = load_table(table1_name);
  set_current_table(ctx, tmp);

  const char *values1[] = {"0", "0", "0", NULL};
  const char *values2[] = {"1", "1", "1", NULL};
  Row r1 = create_row(values1);
  Row r2 = create_row(values2);

  add_row(get_current_table(ctx), r1);
  add_row(get_current_table(ctx), r2);

  print_table(get_current_table(ctx));
  save_table(get_current_table(ctx));

  return true;
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
  // remove_table_from_catalog(table1_name);
  // remove_table_from_catalog(table2_name);
  // remove_table_from_catalog(table3_name);
  list_tables();

  printf("Test successfull\n");

  return true;
}
