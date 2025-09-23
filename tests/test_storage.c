#include "../include/context.h"
#include "../include/model/table_adt.h"
#include "../include/storage/catalog_file.h"
#include "../include/storage/table_file.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool catalog_meta_test();
bool db_test();

int main(void) {
  if (catalog_meta_test())
    printf("Catalog runs out of the box");
  if (db_test())
    printf("Db runs out of the box");
}

bool db_test() { return false; }

bool catalog_meta_test() {

  // DBContext
  DBContext ctx = init_context();

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
  // Table meta test
  set_current_table(ctx, table1);
  Table tmp = get_current_table(ctx);
  printf("Current table is table1\n");
  write_table_meta(tmp);

  set_current_table(ctx, table2);
  printf("Current table is table2\n");
  write_table_meta(get_current_table(ctx));

  set_current_table(ctx, table3);
  printf("Current table is table3\n");
  write_table_meta(get_current_table(ctx));

  free_context(ctx);

  printf("Everything is freed\n");

  ctx = init_context();
  printf("Context initialization\n");

  if (is_table_exists(table1_name)) {
    Table table1_file = read_table_meta(table1_name);
    set_current_table(ctx, table1_file);
    Table tmp = get_current_table(ctx);

    print_table(tmp);
    printf("The %s is loaded from meta\n", get_table_name(tmp));
  }

  printf("\n\n");
  if (is_table_exists(table2_name)) {
    Table table2_file = read_table_meta(table2_name);
    set_current_table(ctx, table2_file);
    Table tmp2 = get_current_table(ctx);

    print_table(tmp2);
    printf("The %s is loaded from meta\n", get_table_name(tmp2));
  }

  printf("\n\n");
  if (is_table_exists(table3_name)) {
    Table table3_file = read_table_meta(table3_name);
    set_current_table(ctx, table3_file);
    Table tmp3 = get_current_table(ctx);

    print_table(tmp3);
    printf("The %s is loaded from meta\n", get_table_name(tmp3));
  }

  // delete table1
  remove_table_from_catalog(table1_name);
  clear_table_meta(table1_name);

  // if the ctx is the table that we want to delete we must free the context
  // then delete from catalog and clear table meta

  list_tables();

  printf("Test successfull\n");

  return true;
}
